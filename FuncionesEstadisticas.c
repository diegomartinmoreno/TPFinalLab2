#include "headers.h"


/// PROMEDIOS
/// Cantidad de averias por camara.
/// Cantidad de alertas por cliente.
/// Promedio de tiempo inactiva.
/// Promedio de alertas por supervisor.
/// Promedio de averias por supervisor.
/// Promedio de alertas/averias totales en un periodo de tiempo.
/// Tiempo medio respuesta alertas.
/// Tiempo medio respuesta averias.

/*
int comprobarRepetido (listaClientes *primero, char cliente[sizeNom]) { /// Retorna 0 si ya tengo ese cliente y 1 si no lo tengo.
    listaClientes *lista=primero;
    int rta=1;
    while (lista){
        if (strcmp(lista->cli, cliente)==0){
            rta=0;
        }
        lista=lista->sig;
    }
    return rta;
}

void agregarFinal(listaClientes **clientes, char agregar []){
    listaClientes *seg=*clientes;
    if (*clientes){
        while (seg->sig!=NULL){
            seg=seg->sig;
        }
        seg->sig=(listaClientes*)malloc(sizeof(listaClientes));
        seg=seg->sig;
        strcpy(seg->cli, agregar);
        seg->sig=0;
    }else{
    *clientes=(listaClientes*)malloc(sizeof(listaClientes));
    strcpy((*clientes)->cli, agregar);
    (*clientes)->sig=0;
    }
}

listaClientes * obtenerClientes (arbolCamara *arbol, listaClientes *lista){
    celda aux;
    lugar aux2;
    if (arbol){
        lista=obtenerClientes(arbol->izquierda, lista);
        lista=obtenerClientes(arbol->derecha, lista);
        aux=arbol->C;
        aux2=aux.ubicacion; /// Gracias por tanto Code::Blocks
        if (comprobarRepetido(lista, aux2.nombre)){
            agregarFinal(&lista, aux2.nombre);
        }
    }
    return lista;
}
*/ ///Resolvi manejarlo con arreglos ya que era mucho mas sencillo de pasar desde el arbol.



void histAverias(arbolCamara *arbol){
    int i=0;
    arbolCamara *encontrada=buscarCamara(arbol);
    system("cls");
    imprimirHeader(" Historico de Averias ");
    for (i=0; i<(encontrada->C.dimAverias); i++){
        imprimirUnHistorial(encontrada->C.averias[i]);
    }
}

void histAlertas(arbolCamara *arbol){
    int i=0;
    arbolCamara *encontrada=buscarCamara(arbol);
    system("cls");
    imprimirHeader(" Historico de Averias ");
    for (i=0; i<(encontrada->C.dimAlertas); i++){
        imprimirUnHistorial(encontrada->C.alertas[i]);
    }
}
