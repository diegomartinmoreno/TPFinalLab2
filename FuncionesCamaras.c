#include "headers.h"

arbolCamara* inicializarArbolCamaras(){
    return NULL;
};
/*
void obtenerContrasena (char contrasena[], char user[]){
    FILE *fp;
    fp==fopen(rutaSupervisores, "rb");
    usuario aux;
    int i, cantSup=contarUsuariosCreados();
    for (i=0; i<cantSup; i++){
        fread(&aux, sizeof(usuario), 1, fp);
        if(strcmp(aux.nomUsuario, user)==0){
            strcpy(contrasena, aux.contrasena);
        }
    }
}

int comprobarRepetido (char clientes[][sizeNom], int dimLClientes, char nuevo[]){

}

lugar crearCliente(){
    lugar aux;
    char input[sizeNom];
    puts(">>> Carga de un nuevo cliente:");
    printf("Ingrese nombre de cliente: ");
    fflush(stdin);
    gets(aux.nombre);
    printf("\nIngrese localidad de la instalacion: ");
    fflush(stdin);
    gets(aux.ciudad);
    printf("\nIngrese calle de la instalacion: ");
    fflush(stdin);
    gets(aux.calle);
    printf("\nIngrese altura de la calle: ");
    fflush(stdin);
    gets(input);
    aux.altura=atoi(input);
    printf("\nIngrese numero departamento: ");
    fflush(stdin);
    gets(input);
    aux.departamento=atoi(input);
    printf("\nIngrese la planta de instalacion (PB=0): ");
    fflush(stdin);
    gets(input);
    aux.piso=atoi(input);
};

lugar pasarClienteALugar(char cliente[]){
    int cantCam=cantidadRegistrosEnFile();
    FILE *fp=fopen(rutaCamaras, "rb");
    celda aux;


};

///DESPUES DE CREAR LA CAMARA ACTUALIZAR FILE DE SUPERVISORES!!!!!!!!
celda crearCamara(char clientes[][sizeNom], int dimLClientes){
    celda aux;
    char opchar='n', control='n';
    int encontrado, input, i=0;
    do{
        puts("Ingrese 1 para crear un nuevo cliente y 2 para agregar camara a un cliente existente.")
        do{
            opchar='n';
            fflush(stdin);
            opchar=getch();
            input=atoi(&opchar);
        }while (input!=1&&input!=2);
        if (input==1){
            aux.ubicacion=crearCliente();
        }else{
            for(i=0;i<dimLClientes;i++){
                textcolor(10);
                printf("\n\t%i.- ", i+1);
                textcolor(15);
                printf("%s.", clientes[i]);
            }
            printf("Ingrese su seleccion entre 1 y %i", dimLClientes);
            do{
                fflush(stdin);
                opchar=getch();
                input=atoi(&opchar);
            }while (input<0||input>dimLClientes);
        }
    }while (control!='s'&&control!='S');
    control='n';
    do{
        printf("Ingrese usuario del Supervisor a cargo de la vigilacia: ");
        fflush(stdin);
        gets(&(aux.supervisor));
        encontrado=buscarExistente(aux.supervisor, rutaSupervisores);
        if(encontrado==0){
            puts("Se ha detectado un nombre de usuario de Supervisor nuevo.");
            puts("Desea crear un nuevo usuario? S/N.");
            opchar='n';
            fflush(stdin);
            opchar=getch();
            if (opchar=='S'||opchar=='s'){
                puts("Ingrese una contrasena para el nuevo usuario:");
                fflush(stdin);
                gets(aux.supervisor.contrasena);
                puts("\nNuevo usuario creado.");
                control='s';
                Sleep(500);
            }
        } else{
            obtenerContrasena(&aux.supervisor.contrasena, aux.supervisor.nomUsuario);
            control='s';
        }
    }while (control!='s'&&control!='S');
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
*/

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
/*
arbolCamara * cargarCamaras(arbolCamara * arbol){
    char opc='s';
    char clientes [30][sizeNom];
    int dimLClientes=0;
    dimLClientes=obtenerClientes(arbol, clientes, 0);
    printf("\n<< A CONTINUACION, INGRESE LOS DATOS SOLICITADOS PARA LA CARGA DE UNA CAMARA >>\n\n");
    while (opc=='s'){
        arbol=insertarNodoCamaraEnArbol(arbol,crearNodoArbolCamara(crearCamara(clientes, dimLClientes)));
        opc=control();
    }
    return arbol;
};

*/



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

FILE *cargaArbolToFile(arbolCamara * arbol, FILE *cam){
    celda aux;
    if(arbol){
        aux=arbol->C;
        fwrite(&aux,sizeof(celda),1,cam);
        if (arbol->izquierda!=NULL){
            cam=cargaArbolToFile(arbol->izquierda, cam);
        }
        if (arbol->derecha!=NULL){
            cam=cargaArbolToFile(arbol->derecha, cam);
        }
    }
    return cam;
};

void arbolToFile (arbolCamara *arbol){
    FILE * cam=fopen(rutaCamaras,"wb");
    if (cam){
        cam = cargaArbolToFile(arbol, cam);
    }
    else{
        puts("Error en apertura.");
        printf("\a");
    }
    fclose(cam);
}



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

///---------------------------------------------------------------------------------------------

celda eliminarMasIzquierdo(arbolCamara **arbol){
    celda eliminado;
    if ((*arbol)!=NULL){
        if((*arbol)->izquierda!=NULL){
            eliminado=eliminarMasIzquierdo(&(*arbol)->izquierda);
        }else{
            eliminado=(*arbol)->C;
            if((*arbol)->derecha!=NULL){
                (*arbol)=(*arbol)->derecha;
            }
        }
    }
    return eliminado;
}

void eliminarCamara(arbolCamara **arbol, celda eliminar){
    celda aux;
    if ((*arbol)!=NULL){
        if ((*arbol)->C.IDcamara==eliminar.IDcamara){
            ///SI NO TIENE HIJOS.
            if ((*arbol)->derecha==NULL&&(*arbol)->izquierda==NULL){
                (*arbol)=NULL;
            }
            ///SI TIENE UN SOLO HIJO IZQUIERDO.
            else{
                if ((*arbol)->derecha==NULL&&(*arbol)->izquierda!=NULL){
                    (*arbol)=(*arbol)->izquierda;
                }
                ///SI TIENE UN SOLO HIJO RADICAL.
                else{
                    if ((*arbol)->izquierda==NULL&&(*arbol)->derecha!=NULL){
                        (*arbol)=(*arbol)->derecha;
                    }
                    /// SI TIENE DOS HIJOS
                    else{
                        if ((*arbol)->izquierda!=NULL&&(*arbol)->derecha!=NULL){
                            ///Lo reemplazo por el nodo mas izquierdo del subarbol derecho,
                            ///y reemplazo el lugar anterior de ese nodo por su subarbol derecho si lo tiene.
                            aux=eliminarMasIzquierdo(&(*arbol)->derecha);
                            (*arbol)->C=aux;
                        }
                    }
                }
            }
        }else{
            if (eliminar.prioridad>(*arbol)->C.prioridad){
                eliminarCamara(&(*arbol)->derecha, eliminar);
            }
            else{
                eliminarCamara(&(*arbol)->izquierda, eliminar);
            }
        }
    }
}

void buscarCamaraXID (arbolCamara *arbol, arbolCamara **rta, int ID){
    if (arbol!=NULL){
        buscarCamaraXID(arbol->derecha, rta, ID);
        buscarCamaraXID(arbol->izquierda, rta, ID);
        if (arbol->C.IDcamara==ID){
            *rta=arbol;
        }
    }
}

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

int obtenerIDS(arbolCamara *actual, int dimL, int IDS[], char usuario[]){
    char aux[sizeNom];
    if (actual->izquierda!=NULL){
        dimL=obtenerIDS(actual->izquierda, dimL, IDS, usuario);
    }
    strcpy(aux, &(actual->C.supervisor));
    if (usuario!=0){
        if (strcmp(aux, usuario)==0){
            IDS[dimL]=actual->C.IDcamara;
            dimL++;
        }
    }else{
        IDS[dimL]=actual->C.IDcamara;
        dimL++;
    }

    if (actual->derecha!=NULL){
        dimL=obtenerIDS(actual->derecha, dimL, IDS, usuario);
    }
    return dimL;
}

int comprobarID(int IDS[], int dimL, int input){  /// Retorna 1 si es una ID valida y 0 si no lo es.
    int rta=0, i=0;
    for (i=0; i<dimL; i++){
        if (IDS[i]==input){
            rta=1;
        }
    }
    return rta;
}

arbolCamara * buscarCamara (arbolCamara *arbol){
    char input[sizeNom];
    arbolCamara *encontrado;
    int ID, dimL=0, i=0, IDS[100], dimLIDS=0, flag=0;
    dimLIDS=obtenerIDS(arbol, dimLIDS, IDS, 0);
    char clientes[50][sizeNom];
    dimL=obtenerClientes(arbol, clientes, 0);
    puts("Ingrese un ID de camara o un cliente:\n");
    puts("Clientes existentes:");
    for (i=0; i<dimL; i++){
        printf("| %s |", clientes[i]);
    }
    puts("");
    puts("\nIDs de camara existentes:");
    mostrarArbolCamaras(arbol, 3, 0, input);
    puts("");
    while (flag==0){
        fflush(stdin);
        gets(input);
        if (input[0]<58&&input[0]>47){ /// ES UNA ID
            ID=atoi(input);
            if (comprobarID(IDS, dimLIDS, ID)){
                buscarCamaraXID(arbol, &encontrado, ID);
                flag=1;
            }
            else{
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
            if (comprobarID(IDS, dimLIDS, ID)){
                buscarCamaraXID(arbol, &encontrado, ID);
                flag=1;
            }
            else{
                puts("No se encontro la camara buscada en la base de datos.");
            }
        }
    }
    return encontrado;
}


///---------------------------------------------------------------------------------------------



