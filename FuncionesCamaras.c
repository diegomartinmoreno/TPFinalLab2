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
    do{
    printf("La prioridad ingresada debe ser MAYOR a 0 (cero) y MENOR a 9 (nueve).\n");
    printf("Ingrese prioridad: ");
    fflush(stdin);
    scanf("%i",&aux.prioridad);
    }while (aux.prioridad>9 && aux.prioridad<0);
    aux.estado=0;
    aux.eliminada=0;
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


int mostrarArbolCamaras(arbolCamara * arbol, int modo, int rep, char cliente[]){
    if(arbol){
        celda aux;
        rep=mostrarArbolCamaras(arbol->izquierda, modo, rep, cliente);
        rep=mostrarArbolCamaras(arbol->derecha, modo, rep, cliente);
        if(rep==8){
            puts("");
            rep=0;
        }
        rep++;
        aux=arbol->C;
        mostrarUnaCamara(aux, modo, cliente);
    }
    return rep;
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

arbolCamara * fileToArbol(arbolCamara *arbol){
    int i, cantCam=cantidadRegistrosEnFile();
    FILE *fp=fopen(rutaCamaras, "rb");
    celda aux;
    arbolCamara *nuevo;
    for (i=0; (i<cantCam-1); i++){
        fread(&aux, sizeof(celda), 1, fp);
        nuevo=crearNodoArbolCamara(aux);
        arbol=insertarNodoCamaraEnArbol(arbol, nuevo);
    }
    fclose(fp);
    return arbol;
}

/// <<<<<< DEBUGEA Y TE AHORRABAS UNA FUNCION!
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

arbolCamara * buscarCamaraXID (arbolCamara *arbol, int ID){
    arbolCamara *rta=0;
    if (arbol){
        if (arbol->C.IDcamara==ID){
            rta=arbol;
        }
        rta=buscarCamaraXID(arbol->derecha, ID);
        rta=buscarCamaraXID(arbol->izquierda, ID);
    }
    return rta;
}

arbolCamara * buscarCamaraXLugar (arbolCamara *arbol, int ID){

}

arbolCamara * buscarCamara (arbolCamara *arbol){
    char input[sizeNom];
    arbolCamara *encontrado;
    int ID, dimL=0, i=0;
    char clientes[50][sizeNom];
    dimL=obtenerClientes(arbol, clientes, 0);
    puts("Ingrese un ID de camara o un cliente:");
    puts("Clientes existentes:");
    for (i=0; i<dimL; i++){
        printf("| %s |", clientes[i]);
    }
    puts("");
    puts("IDs de camara existentes:");
    mostrarArbolCamaras(arbol, 3, 0, input);
    puts("");
    fflush(stdin);
    gets(input);
    if (input[0]<58&&input[0]>47){ /// ES UNA ID
        ID=atoi(input);
        encontrado=buscarCamaraXID(arbol, ID);
        if (encontrado==0){
            puts("No se encontro la camara buscada en la base de datos.");
        }
    }else{ /// es un cliente
        puts("<<<---------------------------->>>");
        printf("Seleccione la ID de la camara del cliente %s buscada\n", input);
        mostrarArbolCamaras(arbol, 4, 0, input);
        puts("");
        fflush(stdin);
        gets(input);
        ID=atoi(input);
        encontrado=buscarCamaraXID(arbol, ID);
        if (encontrado==0){
            puts("No se encontro la camara buscada en la base de datos.");
        }
    }
    return encontrado;
}


void iniciarMenuCamaras(){
    char op='n', input, confirmacion;
    arbolCamara *arbol=0, *aux=0;
    arbol=fileToArbol(arbol);
    do{
        system("cls");
        imprimirHeader("    Menu de Camaras   ");
        imprimirMenuCamaras();
        fflush(stdin);
        input=getch();
        switch (input){
            case '1':
                aux=buscarCamara(arbol);
                system("cls");
                imprimirHeader("    Datos de camara   ");
                puts("");
                imprimirCamaraEncontrada (aux->C);
                system("Pause");
                break;
            case '2':
                mostrarArbolCamaras(arbol, 1, 30, 0);
                puts("");
                system("Pause");
                break;
            case '3':
                mostrarArbolCamaras(arbol, 2, 30, 0);
                puts("");
                system("Pause");
                break;
            case '4':

                break;
            case '5':
                aux=buscarCamara(arbol);
                if (aux!=NULL){
                    system("cls");
                    imprimirHeader("    Datos de camara   ");
                    puts("");
                    imprimirCamaraEncontrada (aux->C);
                    puts("Eliminar la camara de la base de datos? S/N");
                    fflush(stdin);
                    confirmacion=getch();
                    if (confirmacion=='s'||confirmacion=='S'){
                        aux->C.eliminada=1;
                        puts("La camara ha sido eliminada.");
                    }else{
                        puts("La camara no ha sido eliminada.");
                    }
                }
                system("Pause");
                break;
            case '6':
                op=control();
                break;
            default:
                printf("Opcion invalida!\n");
                break;
        }
    }while (op!='s'&&op!='s');
    arbolToFile(arbol);
}

