#include "headers.h"

void imprimirUnHistorial(historial hist){
    puts(" <<<----------------------------->>>");
    printf("Entrada de historial vinculada a la camara %i\n", hist.IDcamara);
    printf("Ingresada en ");
    imprimirFecha(hist.fecha);
    puts("");
    if(hist.activo==0){
        printf("La entrada ha sido gestionada en: %.2f horas\n", hist.tiempoRespuesta);
    }
    else{
        puts("La entrada se encuentra pendiente para ser gestionada.");
    }
    printf("Descripcion: %s\n", hist.descripcion);
    puts("<<<--------------------------------->>>");
}

int contarHistoriales(char path[]){
    int rta;
    FILE *fp=fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    rta=ftell(fp);
    rta=rta/sizeof(historial);
    fclose(fp);
    return rta;
}


int obtenerArrayAA(historial aux[], int IDCamara, int op, char ruta[]){ /// op=0 imprime inactivas /// op=1 imprime activas. /// op=2 imprime todas.
    int cantHist=contarHistoriales(ruta), i=0, dimL=0;
    FILE *fp=fopen(ruta, "rb");
    imprimirHeader("      Historiales      ");
    for (i=0; i<cantHist; i++){
        fread(&aux[dimL], sizeof(historial), 1, fp);
        if (aux[dimL].IDcamara==IDCamara){
            switch (op) {
            case 0:
                if (aux[dimL].activo==0){
                    textcolor(10);
                    printf("%i.- ", dimL+1);
                    textcolor(15);
                    imprimirUnHistorial(aux[dimL]);
                    dimL++;
                }
                break;
            case 1:
                if (aux[dimL].activo==1){
                    textcolor(10);
                    printf("%i.- ", dimL+1);
                    textcolor(15);
                    imprimirUnHistorial(aux[dimL]);
                    dimL++;
                }
                break;
            case 2:
                textcolor(10);
                printf("%i.- ", dimL+1);
                textcolor(15);
                imprimirUnHistorial(aux[dimL]);
                dimL++;
                break;
            }
        }
    }
    return dimL;
}

float obtenerTiempoGestion(tiempo horaHist){
    float rta=0;
    time_t tiempoSeed=time(NULL);;
    struct tm * tiempoLocal;
    tiempoLocal=localtime(&tiempoSeed);
    rta+=horaHist.hora-tiempoLocal->tm_hour;
    rta+=horaHist.minuto-tiempoLocal->tm_sec;
    if (horaHist.mes==(tiempoLocal->tm_mon+1)){
        rta+=((tiempoLocal->tm_mday)-(horaHist.dia))*24;
    }
    return rta;
}

void reportarGestion(historial hist, char ruta[]){
    int cantHist=contarHistoriales(ruta), i=0;
    historial aux;
    FILE *fp=fopen(ruta, "ab+");
    fseek(fp, 0, SEEK_SET);
    for (i=0; i<cantHist; i++){
        fread(&aux, sizeof(historial), 1, fp);
        if (hist.IDregistro==aux.IDregistro){
            fseek(fp, -sizeof(historial), SEEK_CUR);
            hist.activo=0;
            fwrite(&hist, sizeof(historial), 1, fp);
        }
    }
}

void atenderAA(int IDCamara, int op, char ruta[]){ /// op=0 imprime inactivas /// op=1 imprime activas. /// op=2 imprime todas.
    historial historiales[50];
    char opchar;
    int seleccion;
    int dimL=0;
    dimL=obtenerArrayAA(historiales, IDCamara, op, ruta);
    puts("Ingrese una seleccion:");
    fflush(stdin);
    opchar=getch();
    seleccion=atoi(&opchar);
    seleccion--;
    reportarGestion(historiales[seleccion], ruta);
}

