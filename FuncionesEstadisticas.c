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

int verificarRepetido(char clientes[][sizeNom], char nuevo[], int i) { ///0 si ya se encuentra, 1 si es nuevo.
    int rta=1;
    int j;
    for (j=0; j<i; j++){
        if (strcmp(clientes[j], nuevo)==0){
            rta=0;
        }
    }
    return rta;
}

int obtenerClientes(arbolCamara *arbol, char clientes[][sizeNom], int i)
{
    lugar auxLugar; ///
    celda auxCelda; ///
    char nuevo[sizeNom]; ///
    if(arbol != NULL){
        auxCelda=arbol->C; ///
        auxLugar=auxCelda.ubicacion; ///
        strcpy(nuevo, auxLugar.nombre); /// La que tepa codeblocks.
        if (verificarRepetido(clientes, nuevo, i)){
            strcpy(clientes[i], nuevo);
            i++;
        }
        if(arbol->derecha != NULL)
            i = obtenerClientes(arbol->derecha, clientes, i);
        if(arbol->izquierda != NULL)
            i = obtenerClientes(arbol->izquierda, clientes, i);
    }
    return i;
}

int obtenerInput (char input[], int *numero){ /// Retorna 1 si se ingreso un ID y 0 si se ingreso una palabra.
    int i=0, rta=0;
    fflush(stdin);
    while (stdin){
        input[i]=getch;
        i++;
    }
    input [i]='\0';
    if (47<(input[0])&& (input[0])<58) { /// Es numero
        *numero=atoi(input);
        rta=1;
    }
    return rta;
}

void histAverias(arbolCamara *arbol){
    system("cls");
    char input[sizeNom];
    int esNumero, ID;
    imprimirHeader(" Historico de Averias ");
    puts("Ingrese el nombre del cliente o el ID de la camara buscada:");
    esNumero=obtenerInput(input, &ID);
    if (esNumero){
        ///obtenerHist(ID);
    }

}
