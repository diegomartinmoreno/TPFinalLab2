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
        printf("\nSeleccione la averia deseada: \n");
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
        break;
    case 2:
        printf("\nSeleccione la alerta deseada: \n");
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
