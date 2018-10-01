#include "cabecera.h"

NodoAuto * inicNodo(){
    NodoAuto * nAuto;
    nAuto->siguiente=NULL;
    return nAuto;
};

NodoAuto * crearNodo(char patente[], int valor, char marca[]){
    NodoAuto * aux=(NodoAuto *)malloc(sizeof(NodoAuto));
    aux->automovil.valor=valor;
    strcpy(aux->automovil.patente,patente);
    strcpy(aux->automovil.marca, marca);
    aux->siguiente=NULL;
    return aux;
}

NodoAuto * buscarUltimo(NodoAuto * lista){
    NodoAuto * seg=lista;
    if(seg != NULL){
        while(seg!= NULL){
            seg=seg->siguiente;
        }
    }
    return seg;
};
void agregarAlFinal(NodoAuto * * lista, NodoAuto * nuevo){
    if((*lista) == NULL){
        (*lista)=nuevo;
    }else{
        NodoAuto * ultimo=buscarUltimo(*lista);
        ultimo->siguiente= nuevo;
    }
};
char control(){
    char opc;
    puts("DESEA CONTINUAR? S/N");
    fflush(stdin);
    opc=getch();
    opc=tolower(opc);
    return opc;
};
CeldaAuto cargaCelda(){
    CeldaAuto aux;
    puts("Ingrese patente");
    fflush(stdin);
    gets(aux.patente);
    puts("Ingrese valor entero");
    fflush(stdin);
    scanf("%d",&aux.valor);
    puts("Ingrese marca");
    fflush(stdin);
    gets(aux.marca);
    return aux;
};

void ordenarArregloPorValor(CeldaAuto A[],int dim){
    int i=0,aux;
    while(i<dim){
        if(A[i].valor > A[i+1].valor){
            aux=A[i].valor;
            A[i].valor=A[i+1].valor;
            A[i].valor=aux;
        }
        i++;
    }
}

int insertarCelda(CeldaAuto A[], char patente[], int valor, char marca[], int c){
    strcpy(A[c].marca,marca);
    A[c].valor=valor;
    strcpy(A[c].patente,patente);
    ordenarArregloPorValor(A,c);
    return c+1;
};

void agregarMuchos(NodoAuto * * lista){

      CeldaAuto carro,a[10];
      NodoAuto * aux = NULL;
      char opc='s';
      int dim=0;

    while(opc=='s' && dim<=30){
        carro=cargaCelda();
        dim=insertarCelda(a,carro.patente,carro.valor,carro.marca,dim);
        opc=control();
        aux=crearNodo(carro.patente,carro.valor,carro.marca);
        agregarAlFinal(lista,aux);
  }
};
void mostrarLista (NodoAuto * lista){

    if(lista!=NULL){
        printf("\n----------------------------------------\n");
        printf("Valor: %i \n",lista->automovil.valor);
        printf("Marca: %s",lista->automovil.marca);
        printf("Patente: %s ",lista->automovil.patente);
    }
}
