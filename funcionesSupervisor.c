#include "headers.h"

int compararFechas (tiempo t1, tiempo t2){ /// 1 si son iguales, -1 si tienen mismo dia distinta hora. 2 si t1 es mayor y -2 si t2 es mayor.
    int rta=-2;
    if (t1.ano==t2.ano && t1.mes==t2.mes && t1.dia==t2.dia){ /// Compara fecha
        rta=-1
    }
    if (t1.hora==t2.hora && t1.minuto==t2.minuto && t1.segundo==t2.segundo){ /// Comprara hora
        rta=1;
    }
    if (t1.ano>t2.ano){
        rta=2;
    }else {
        if (t1.mes>t2.mes){
            rta=2;
        }else {
            if (t1.dia>t2.dia){
                rta=2;
            }else {
                if (t1.hora>t2.hora){
                    rta=2;
                }else{
                    if (t1.minuto>t2.minuto){
                        rta=2;
                    }
                    else{
                        if (t1.segundo>t2.segundo)
                            rta=2;
                    }
                }
            }
        }
    }
    return rta;
}

historial *insertarOrdenardoAA (historial *lista, historial *nuevo){
    historial *seg=lista, *anterior=lista;
    if (lista){
        if (compararFechas(seg->fecha, nuevo->fecha)==-2){
            while (seg->siguiente && compararFechas(seg->fecha, nuevo->fecha)==2){
                anterior=seg;
                seg=seg->siguiente;
            }
            anterior->siguiente=nuevo;
            nuevo->siguiente=seg;
        }else{
            nuevo->siguiente=lista;
            lista=nuevo;
        }
    }else{
        lista=nuevo;
    }
    return lista;
}

char cicloDeControl (){
    char rta=0;
    int i=0;
    while (i<14 && rta==0){
        fflush(stdin);
        Sleep(500);
        if (!feof(stdin)){
            rta=getch();
        }
    }
    return rta;
}


void inicSupervision (celda camaras[], int dimL){
    int prioridad=1, i=0;
    char control='0';
    do{
        system("cls");
        if (i<dimL){
            imprimirHeadSupervisor();
            puts ("Comienza supervision de la camara: %i", camaras[i].IDcamara);
            mostrarUnaCamara(celda);
            puts ("<<<<---------------------------------------------------->>>>");
            puts ("Cambiando de camara en 7 segundos.");
            control=cicloDeControl();
            if (control=='1'){
                ingresarAlarma(camaras[i]);
            }else{
                if (control =='2'){
                    ingresarAveria(camaras[i]);
                }
            }
        } else {
            puts("Vigilancia finalizada. Iniciando nueva ronda en 5 segundos.");
            i=0;
            Sleep(5000);
        }
    } while (control!='3');
}
