#include "headers.h"

void histAverias(arbolCamara *arbol){
    int i=0, salto=0;
    arbolCamara *encontrada=buscarCamara(arbol);
    system("cls");
    imprimirHeader(" Historico de Averias ");
    for (i=0; i<(encontrada->C.dimAverias); i++){
        imprimirUnHistorial(encontrada->C.averias[i]);
        salto++;
        if (salto==5){
                salto=0;
            puts("Continua en la siguiente pagina.");
            system("Pause");
            system("cls");
            imprimirHeader(" Historico de Averias ");
        }
    }
    puts("No hay mas entradas en el historial de la camara.");
}

void histAlertas(arbolCamara *arbol){
    int i=0, salto=0;
    arbolCamara *encontrada=buscarCamara(arbol);
    system("cls");
    imprimirHeader(" Historico de Averias ");
    for (i=0; i<(encontrada->C.dimAlertas); i++){
        imprimirUnHistorial(encontrada->C.alertas[i]);
        salto++;
        if (salto==5){
                salto=0;
            puts("Continua en la siguiente pagina.");
            system("Pause");
            system("cls");
            imprimirHeader(" Historico de Averias ");
        }
    }
    puts("No hay mas entradas en el historial de la camara.");
}

float tiempoRespuestaCamaraAveria (arbolCamara *arbol, int IDCamara){
    float rta=0, tiempoTotal=0;
    int cantRegistros=0, i=0;
    if (arbol!=NULL){
        if (arbol->C.IDcamara==IDCamara){
            if (arbol->C.dimAverias!=0){
                for (i=0; i<(arbol->C.dimAverias); i++){
                    tiempoTotal+=arbol->C.averias[i].tiempoRespuesta;
                }
                rta=tiempoTotal/(arbol->C.dimAverias);
            }
        }
        rta+=tiempoRespuestaCamaraAveria(arbol->derecha, IDCamara);
        rta+=tiempoRespuestaCamaraAveria(arbol->izquierda, IDCamara);
    }
    return rta;
}

void tiempoRespuestaAveriaSistema(arbolCamara *arbol, float *rta){
    int IDS[200], dimLIDS=0, i=0;
    float sumatoria=0;
    dimLIDS=obtenerIDS(arbol, dimLIDS, IDS, 0);
    for (i=0; i<dimLIDS; i++){
        sumatoria+=tiempoRespuestaCamaraAveria(arbol, IDS[i]);
    }
    *rta=sumatoria/(float)dimLIDS;
}

float tiempoRespuestaCamaraAlerta (arbolCamara *arbol, int IDCamara){
    float rta=0, tiempoTotal=0;
    int cantRegistros=0, i=0;
    if (arbol!=NULL){
        if (arbol->C.IDcamara==IDCamara){
            if ((arbol->C.dimAlertas)!=0){
                for (i=0; i<(arbol->C.dimAlertas); i++){
                    tiempoTotal+=arbol->C.alertas[i].tiempoRespuesta;
                }
                rta=tiempoTotal/(arbol->C.dimAlertas);
            }
        }
        if (arbol->izquierda!=NULL){
            rta+=tiempoRespuestaCamaraAlerta(arbol->izquierda, IDCamara);
        }
        if (arbol->derecha!=NULL){
            rta+=tiempoRespuestaCamaraAlerta(arbol->derecha, IDCamara);
        }
    }
    return rta;
}

void  tiempoRespuestaAlertaSistema(arbolCamara *arbol, float *rta){
    int IDS[200], dimLIDS=0, i=0;
    float sumatoria=0;
    dimLIDS=obtenerIDS(arbol, dimLIDS, IDS, 0);
    for (i=0; i<dimLIDS; i++){
        sumatoria+=tiempoRespuestaCamaraAlerta(arbol, IDS[i]);
    }
    *rta=sumatoria/(float)dimLIDS;
}
