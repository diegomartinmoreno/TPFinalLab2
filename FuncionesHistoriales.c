#include "headers.h"

historial ingresarNuevoHistorial(int IDRegistro){
    imprimirHeader("    Ingresar alerta    ");
    historial aux;
    time(&(aux.fecha));
    puts("Ingrese una descripcion de la entrada:");
    fflush(stdin);
    gets(aux.descripcion);
    aux.activo=1;
    aux.tiempoRespuesta=-1;
    aux.IDregistro=IDRegistro;
    return aux;
}

float obtenerTiempoGestion(time_t horaHist){
    float rta=0;
    time_t tiempoSeed=time(NULL);
    rta=(float)((difftime(tiempoSeed, horaHist))/3600);
    return rta;
}

int obtenerHistorial (celda camara, int modo){ /// 1 para averias, 2 para alertas /// retorna posicion en arreglo de la seleccion.
    int i=0, posiciones[50], dimSeleccion=0,seleccion;
    char input;
    switch (modo){
    case 1:
        printf("\nSeleccione la averia deseado: \n");
        for(i=0; i<camara.dimAverias; i++){
            if (camara.averias[i].activo==1){
                textcolor(10);
                printf("%i.-", dimSeleccion+1);
                textcolor(15);
                imprimirUnHistorial(camara.averias[i]);
                posiciones[dimSeleccion]=i;
                dimSeleccion++;
            }
        }
        if (dimSeleccion>1){
            do{
                fflush(stdin);
                input=getch();
                seleccion=atoi(&input);
                seleccion--;
            }while (seleccion<0||seleccion>dimSeleccion);
        }
        else{
            Sleep(3000);
        }
        break;
    case 2:
        printf("\nSeleccione la alerta deseado: \n");
        for(i=0; i<camara.dimAlertas; i++){
            if (camara.alertas[i].activo==1){
                textcolor(10);
                printf("%i.-", dimSeleccion+1);
                textcolor(15);
                imprimirUnHistorial(camara.alertas[i]);
                posiciones[dimSeleccion]=i;
                dimSeleccion++;
            }
        }
        if (dimSeleccion>1){
            do{
                fflush(stdin);
                input=getch();
                seleccion=atoi(&input);
                seleccion--;
            }while (seleccion<0||seleccion>dimSeleccion);
            break;
        }
        else{
            Sleep(3000);
        }
    }
    return posiciones[seleccion];
}

void reportarGestion(arbolCamara *camara, int modo){
    int seleccionado;
    switch (modo){
    case 1:
        seleccionado=obtenerHistorial(camara->C, modo);
        camara->C.averias[seleccionado].tiempoRespuesta=obtenerTiempoGestion(camara->C.averias[seleccionado].fecha);
        camara->C.averias[seleccionado].activo=0;
        break;
    case 2:
        seleccionado=obtenerHistorial(camara->C, modo);
        camara->C.alertas[seleccionado].tiempoRespuesta=obtenerTiempoGestion(camara->C.alertas[seleccionado].fecha);
        camara->C.alertas[seleccionado].activo=0;
        break;
    }
}


/*

void reportarGestion(historial hist, char ruta[]){
    int cantHist=contarHistoriales(ruta), i=0;
    historial aux;
    FILE *fp=fopen(ruta, "ab+");
    fseek(fp, 0, SEEK_SET);
    for (i=0; i<cantHist; i++){
        fread(&aux, sizeof(historial), 1, fp);
        if (hist.IDregistro==aux.IDregistro){
            hist.activo=0;
            hist.tiempoRespuesta=obtenerTiempoGestion(hist.fecha);
            fseek(fp, -(sizeof(historial)), SEEK_CUR);
            fwrite(&hist, sizeof(historial), 1, fp);
            }
    }
    fclose(fp);
}

void atenderAA(int IDCamara, int op, char ruta[]){ /// op=0 imprime inactivas /// op=1 imprime activas. /// op=2 imprime todas.
    historial historiales[50];
    char opchar;
    int seleccion;
    int dimL=0;
    imprimirHeader("      Historiales      ");
    dimL=obtenerArrayAA(historiales, IDCamara, op, ruta);
    puts("Ingrese una seleccion:");
    fflush(stdin);
    opchar=getch();
    seleccion=atoi(&opchar);
    seleccion--;
    reportarGestion(historiales[seleccion], ruta);
}

int obtenerIDSCliente(int IDS[], int dimLClientes, char clientes [][sizeNom]){
    FILE *fp=fopen(rutaCamaras, "rb");
    char clienteSeleccionado[sizeNom], opchar;
    celda aux;
    int dimL=0, i=0, op=0, cantCam=cantidadRegistrosEnFile();
    puts("Seleccione el cliente cuyo historial de alertas desea mostrar:");
    for(i=0; i<dimLClientes; i++){
        textcolor(10);
        printf("\n\t%i.- ", i+1);
        textcolor(15);
        printf("%s.", clientes[i]);
    }
    fflush(stdin);
    opchar=getch();
    op=atoi(&opchar);
    op--;
    for (i=0; i<cantCam; i++){
        fread(&aux, sizeof(celda), 1, fp);
        if(strcmp(aux.ubicacion.nombre, clientes[op])==0){
            IDS[dimL]=aux.IDcamara;
            dimL++;
        }
    }
    fclose(fp);
    return dimL;
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
    fclose(fp);
    return dimL;
}
*/
