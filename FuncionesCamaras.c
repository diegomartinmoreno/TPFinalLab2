#include "headers.h"

arbolCamara* inicializarArbolCamaras(){
    return NULL;
};


celda crearCamara(){
    celda aux;

    printf("\nIngrese ID Camara: ");
    fflush(stdin);
    scanf("%i",&aux.IDcamara);

    printf("Ingrese nombre y apellido del Supervisor:  ");
    fflush(stdin);
    gets(aux.supervisor);

    printf(".:Prioridad de Camara:.\n");
    printf("La prioridad ingresada debe ser MAYOR a 0 (cero) y MENOR a 9 (nueve).\n");
    printf("Ingrese prioridad: ");
    fflush(stdin);
    scanf("%i",&aux.prioridad);

    aux.estado=0;

    return aux;
};


arbolCamara * crearNodoArbolCamara(celda cam){
    arbolCamara * aux=(arbolCamara *)malloc(sizeof(arbolCamara));

    aux->C=cam;
    aux->derecha=0;
    aux->izquierda=0;

    return aux;
};


arbolCamara * insertarNodoCamaraEnArbol(arbolCamara * arbol, arbolCamara * nuevo){

    if(arbol){
        if(arbol->C.prioridad < nuevo->C.prioridad)
            arbol->derecha=insertarNodoCamaraEnArbol(arbol->derecha,nuevo);
        else
            arbol->izquierda=insertarNodoCamaraEnArbol(arbol->izquierda,nuevo);
    }else{
        arbol=nuevo;
    }
    return arbol;
};


void mostrarArbolCamaras(arbolCamara * arbol){
    if(arbol){
        mostrarArbolCamaras(arbol->izquierda);
        mostrarArbolCamaras(arbol->derecha);
        mostrarUnaCamara(arbol->C);
    }
};


arbolCamara * cargarCamaras(arbolCamara * arbol){
    char opc='s';

    printf(".:A CONTINUACION, INGRESE LOS DATOS SOLICITADOS PARA LA CARGA DE UNA CAMARA:.\n\n");
    while (opc=='s'){

        arbol=insertarNodoCamaraEnArbol(arbol,crearNodoArbolCamara(crearCamara()));

        opc=control();
    }
    return arbol;
};


void crearArchivoCamaras(){
    FILE * cam=fopen(rutaCamaras,"a+b");

    if(cam)
        puts("Archivo Creado con Exito.");
    else
        puts("Error al crear archivo.");

    system("cls");

    fclose(cam);
};


void arbolToFile(arbolCamara * arbol){
    FILE * cam=fopen(rutaCamaras,"a+b");

    celda aux;

    if(cam){
        if(arbol){
            aux=arbol->C;
            fwrite(&aux,sizeof(celda),1,cam);
            arbolToFile(arbol->izquierda);
            arbolToFile(arbol->derecha);
        }
    }else{
        puts("Error en apertura.");
        printf("\a");
    }
    fclose(cam);
};


void mostrarUnaCamara(celda cam){
    printf("-----------------------------------------------------------------------------------------\n");
    printf("ID de camara: %i\n",cam.IDcamara);
    printf("Nombre y Apellido de supervisor: %s\n",cam.supervisor);
    if(cam.estado == 0)
        printf("Estado: OFFLINE\n");
    if(cam.estado == 1)
        printf("Estado: ONLINE\n");
    if(cam.estado == 2)
        printf("Estado: EN REPARACION\n");
    printf("Prioridad de Camara: %i",cam.prioridad);
    printf("\n---------------------------------------------------------------------------------------\n");
};


void mostrarFile(){
    FILE * cam = fopen(rutaCamaras,"rb");
    celda aux;

    if(cam){
        while(!feof(cam))
        {
            fread(&aux,sizeof(celda),1,cam);
            mostrarUnaCamara(aux);
        }
    }else{
        puts("Error en apertura.");
        printf("\a");
    }
    fclose(cam);
};


int cantidadRegistrosEnFile(){
    FILE * cam=fopen(rutaCamaras,"rb");
    int rta=0;

    if(cam){
        fseek(cam,0,SEEK_END);
        rta=ftell(cam)/sizeof(celda);
    }else{
        puts("Error en apertura.");
        printf("\a");
    }
    fclose(cam);
    return rta;
};
