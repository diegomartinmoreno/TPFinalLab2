#include "headers.h"

void imprimirMenuEstadisticas (){
    imprimirHeader("     Estadisticas     ");
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Historico de averias por camara.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Historico de alertas por cliente.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Promedio de tiempo de inactividad por camara.");
    textcolor(10);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Promedio de alertas/averias por supervisor.");
    textcolor(10);
    printf("\n\t5.- ");
    textcolor(15);
    printf("Promedio de alertas/averias por periodo.");
    textcolor(10);
    printf("\n\t6.- ");
    textcolor(15);
    printf("Tiempo medio de respuesta alertas/averias.");
}

void procesarMenuEstadisticas(arbolCamara *arbol){
    char control='n', op;
    while (control!='s'&&control!='S'){
        imprimirMenuEstadisticas();
        fflush(stdin);
        op=getch();
        switch(op){
        case '1':
            //histAverias();
            break;
        case '2':
            //histAlertas();
            break;
        case '3':
            //promInactividad();
            break;
        case '4':
            //promSupervisor();
            break;
        case '5':
            //promPeriodo();
            break;
        case '6':
            //promRespuesta();
            break;
        default:
            puts("Opcion incorrecta!");
            break;
        }
    }
}

/// PROMEDIOS
/// Cantidad de averias por camara.
/// Cantidad de alertas por cliente.
/// Promedio de tiempo inactiva.
/// Promedio de alertas por supervisor.
/// Promedio de averias por supervisor.
/// Promedio de alertas/averias totales en un periodo de tiempo.
/// Tiempo medio respuesta alertas.
/// Tiempo medio respuesta averias.

typedef struct
{
    char cli[sizeNom];
    struct listaClientes *sig;
} listaClientes;


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
    }else{
    *clientes=(listaClientes*)malloc(sizeof(listaClientes));
    strcpy((*clientes)->cli, agregar);
    }
}

listaClientes * obtenerClientes (arbolCamara *arbol, listaClientes *lista){
    celda aux;
    aux=arbol->C;
    lugar aux2;
    aux2=aux.ubicacion; /// Gracias por tanto Code::Blocks
    if (arbol){
        lista=obtenerClientes(arbol->izquierda, lista);
        lista=obtenerClientes(arbol->derecha, lista);
        if (comprobarRepetido(lista, aux2.nombre)){
            agregarFinal(&lista, aux2.nombre);
        }
    }
    return lista;
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
        obtenerHist(ID);
    }

}
