///Funciones de inicializacion de arbol, carga de nodo arbol camara, ordenacion por prioridad, muestra de datos de una camara y del
///arbol de camaras.


arbolCamara* inicializarArbolCamaras(){
    return NULL;
};

camara crearCamara(){
    camara aux;

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

arbolCamara * crearNodoArbolCamara(camara c){
    arbolCamara * aux=(arbolCamara *)malloc(sizeof(arbolCamara));

    aux->cam=c;
    aux->derecha=0;
    aux->izquierda=0;

    return aux;
};

arbolCamara * insertarNodoCamaraEnArbol(arbolCamara * arbol, arbolCamara * nuevo){

    if(arbol){
        if(arbol->cam.prioridad < nuevo->cam.prioridad)
            arbol->derecha=insertarNodoCamaraEnArbol(arbol->derecha,nuevo);
        else
            arbol->izquierda=insertarNodoCamaraEnArbol(arbol->izquierda,nuevo);
    }else{
        arbol=nuevo;
    }
    return arbol;
};

void mostrarUnaCamara(camara c){
    printf("-----------------------------------------------------------------------------------------\n");
    printf("ID de camara: %i\n",c.IDcamara);
    printf("Nombre y Apellido de supervisor: %s\n",c.supervisor);
    printf("Estado: %i(0.- Offline; 1.- Online; 2.- En Reparacion)\n",c.estado);
    printf("Prioridad de Camara: %i",c.prioridad);
    printf("\n---------------------------------------------------------------------------------------\n");
};

void mostrarArbolCamaras(arbolCamara * arbol){
    if(arbol){
        mostrarArbolCamaras(arbol->izquierda);
        mostrarArbolCamaras(arbol->derecha);
        mostrarUnaCamara(arbol->cam);
    }
};

char control(){
    char opc;
    puts("Desea continuar? S/N .");
    fflush(stdin);
    opc=getch();
    return opc;
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

int main(){

    arbolCamara * arbolMain=inicializarArbolCamaras();

    arbolMain=cargarCamaras(arbolMain);

    printf("\n\n\n\n");
    mostrarArbolCamaras(arbolMain);

    return(0);
}


///Falta cargar funcion ARBOLTOFILE.
