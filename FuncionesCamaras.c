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

void buscarCamaraXID (arbolCamara *arbol, arbolCamara **rta, int ID){
    if (arbol!=NULL){
        buscarCamaraXID(arbol->derecha, rta, ID);
        buscarCamaraXID(arbol->izquierda, rta, ID);
        if (arbol->C.IDcamara==ID){
            *rta=arbol;
        }
    }
}

arbolCamara * buscarCamara (arbolCamara *arbol){
    char input[sizeNom];
    arbolCamara *encontrado;
    int ID, dimL=0, i=0;
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
    fflush(stdin);
    gets(input);
    if (input[0]<58&&input[0]>47){ /// ES UNA ID
        ID=atoi(input);
        buscarCamaraXID(arbol, &encontrado, ID);
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
        buscarCamaraXID(arbol, &encontrado, ID);
        if (encontrado==0){
            puts("No se encontro la camara buscada en la base de datos.");
        }
    }
    return encontrado;
}




