#include "headers.h"

arbolCamara* inicializarArbolCamaras(){
    return NULL;
};

lugar crearCliente(char nombre[]){
    lugar aux;
    char input[sizeNom];
    printf(">>> Carga del nuevo cliente: %s\n", nombre);
    strcpy(aux.nombre, nombre);
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
    return aux;
};

lugar esCliente (lugar clientes[], lugar nuevo, int dimL){
/// Retorna el lugar si ya se conoce, o rta.altura == -1 si es nuevo.
/// nuevo solo necesita estar lleno en el campo nuevo.nombre.
    int i=0;
    nuevo.altura=-1;
    for (i=0; i<dimL; i++){
        if (strcmp(clientes[i].nombre, nuevo.nombre)==0){
            nuevo=clientes[i];
        }
    }
    return nuevo;
}

void obtenerCamarasCliente (arbolCamara *arbol, celda camaras[], lugar cliente, int *centesimas){
    int posicion=0;
    if (arbol!=NULL){
        if (strcmp(arbol->C.ubicacion.nombre, cliente.nombre)==0){
            *centesimas=arbol->C.IDcamara;
            *centesimas=(*centesimas)/100;
            posicion=(arbol->C.IDcamara)-((*centesimas)*100);
            camaras[posicion]=arbol->C;
        }
        obtenerCamarasCliente(arbol->derecha, camaras, cliente, centesimas);
        obtenerCamarasCliente(arbol->izquierda, camaras, cliente, centesimas);
    }
}

int obtenerIDLibreCliente(arbolCamara *arbol, lugar cliente){
    celda camarasCliente[99];
    int i, flag=0, IDLibre=-1, centesimas=0;
    for (i=0; i<100; i++){
        camarasCliente[i].IDcamara=-1; /// inicio todas en -1.
    }
    obtenerCamarasCliente(arbol, camarasCliente, cliente, &centesimas); /// Cargo las posiciones del arreglo relativas a la centesima que ocupan en el arreglo.
    i=0;
    while (flag==0 && i<100){
        if (camarasCliente[i].IDcamara==-1){
            IDLibre=i+(centesimas*100);
            flag=1;
        }
        i++;
    }
    return IDLibre;
}

///DESPUES DE CREAR LA CAMARA ACTUALIZAR FILE DE SUPERVISORES!!!!!!!!
celda crearCamara(arbolCamara *arbol, lugar clientes[], int *dimLClientes){
    celda aux;
    FILE *supervisores;
    char opchar='n', control='n', inputCliente[sizeNom], inputChar;
    int encontrado, input, i=0;
    system("cls");
    imprimirHeader("     Nueva Camara    ");
    puts("Ingrese el nombre del cliente al que se le instalara la nueva camara: ");
    fflush(stdin);
    gets(inputCliente);
    strcpy(&(aux.ubicacion.nombre), inputCliente);
    aux.ubicacion=esCliente(clientes, aux.ubicacion, *dimLClientes);
    if (aux.ubicacion.altura==-1){
        puts("Se ha detectado un nuevo cliente.");
        aux.ubicacion=crearCliente(aux.ubicacion.nombre);
        clientes[*dimLClientes]=aux.ubicacion;
        (*dimLClientes) ++;
        aux.IDcamara=((*dimLClientes) * 100)+1;
        system("cls");
        imprimirHeader("     Nueva Camara    ");
    }else{ /// Debo obtener un ID disponible para ese cliente (dentro del rango de cientos del cliente).
        aux.IDcamara=obtenerIDLibreCliente(arbol, aux.ubicacion);
    }
    do{
        system("cls");
        imprimirHeader("     Nueva Camara    ");
        printf("El sistema selecciono la ID = %i para su camara.\n",aux.IDcamara);
        printf("Ingrese usuario del Supervisor a cargo de la vigilacia: ");
        fflush(stdin);
        gets(&(aux.supervisor));
        encontrado=buscarExistente(&aux.supervisor, rutaSupervisores, 2);
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
                puts("Nuevo usuario creado.\n\n");
                control='s';

                supervisores=fopen(rutaSupervisores, "ab");
                fwrite(&aux.supervisor, sizeof(usuario), 1, supervisores);
                fclose(supervisores);
                Sleep(500);
            }
        } else{
            control='s';
        }
    }while (control!='s'&&control!='S');
    printf("Prioridad de Camara:");
    do{
        fflush(stdin);
        scanf("%i", &(aux.prioridad));
        if (aux.prioridad>10 || aux.prioridad<0){
            printf("La prioridad ingresada debe ser MAYOR igual a 0 (cero) y MENOR  a 10 (diez).\n");
            printf("Ingrese prioridad: ");
        }
    }while (aux.prioridad>10 || aux.prioridad<0);
    aux.estado=1;
    aux.fechaInstalacion=time(NULL);
    system("cls");
    imprimirHeader("     Nueva Camara    ");
    puts("Se creo la siguiente camara: ");
    imprimirCamaraEncontrada(aux);
    system("Pause");
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

arbolCamara * cargarCamaras(arbolCamara * arbol){
    char opc='s';
    lugar clientes [50];
    int dimLClientes=0;
    dimLClientes=obtenerClientes(arbol, clientes, 0);
    while (opc=='s'){
        arbol=insertarNodoCamaraEnArbol(arbol,crearNodoArbolCamara(crearCamara(arbol, clientes, &dimLClientes)));
        opc=control();
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

int esNuevo(lugar clientes[], lugar nuevo, int dimL) { ///0 si ya se encuentra, 1 si es nuevo.
    int rta=1;
    int j;
    for (j=0; j<dimL; j++){
        if (strcmp(clientes[j].nombre, nuevo.nombre)==0){
            rta=0;
        }
    }
    return rta;
}

int obtenerClientes(arbolCamara *arbol, lugar clientes[], int dimL)
{
    lugar auxLugar, nuevo; ///
    celda auxCelda; ///
    if(arbol != NULL){
        auxCelda=arbol->C; ///
        auxLugar=auxCelda.ubicacion; /// La que tepa codeblocks
        nuevo=auxLugar;
        if (esNuevo(clientes, nuevo, dimL)){
            clientes[dimL]=nuevo;
            dimL++;
        }
        if(arbol->derecha != NULL)
            dimL = obtenerClientes(arbol->derecha, clientes, dimL);
        if(arbol->izquierda != NULL)
            dimL = obtenerClientes(arbol->izquierda, clientes, dimL);
    }
    return dimL;
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
    lugar clientes[50];
    dimL=obtenerClientes(arbol, clientes, 0);
    puts("Ingrese un ID de camara o un cliente:\n");
    puts("Clientes existentes:");
    for (i=0; i<dimL; i++){
        printf("| %s |", clientes[i].nombre);
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



