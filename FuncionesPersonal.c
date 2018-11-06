#define "headers.h"

typedef struct{
    supervisor sup;
    struct nodo2Supervisor * ante;
    struct nodo2Supervisor * sig;
}nodo2Supervisor;

//-------------------------------------------------------------------------------------------------------------------------------

char control(){
    char opc;
    puts("DESEA CONTINUAR? S/N");
    fflush(stdin);
    opc=getch();
    opc=tolower(opc);
    return opc;
};

nodoSupervisor * inicListaSupervisores(){
    return 0;
};

supervisor cargarUnSupervisor(){
    supervisor aux;

    printf("Carga de datos de supervisor.\n");

    printf("Ingrese ID de supervisor: \n");
    fflush(stdin);
    scanf("%i",&aux.idSupervisor);

    printf("Ingrese nombre y Apellido de supervisor: \n");
    fflush(stdin);
    gets(aux.nomYApe);

    aux.cantReportes=0;

    return aux;
};

nodoSupervisor * crearNodoSupervisor(supervisor s){
    nodoSupervisor * aux=(nodoSupervisor *)malloc(sizeof(nodoSupervisor));

    aux->sup.idSupervisor=s.idSupervisor;
    strcpy(aux->sup.nomYApe,s.nomYApe);
    aux->sup.cantReportes=s.cantReportes;

    aux->sig=0;

    return aux;
};

nodo2Supervisor * crearNodoDobleSupervisor(supervisor s){
    nodo2Supervisor * aux=(nodo2Supervisor *)malloc(sizeof(nodo2Supervisor));

    aux->sup.idSupervisor=s.idSupervisor;
    strcpy(aux->sup.nomYApe,s.nomYApe);
    aux->sup.cantReportes=s.cantReportes;

    aux->ante=0;
    aux->sig=0;

    return aux;
};

nodoSupervisor * agregarAlFinal(nodoSupervisor * lista, nodoSupervisor * nuevo){
    nodoSupervisor * seg=lista;
    if(lista){
        while(seg){
            seg=seg->sig;
        }
        seg->sig=nuevo;
    }else{
        lista=nuevo;
    }
    return lista;
};

nodoSupervisor * insertarSupervisorEnListaOrdenadoxId(nodoSupervisor * lista,nodoSupervisor * nuevo){
    nodoSupervisor * ante=lista;

    if(lista){
            if(lista->sup.idSupervisor > nuevo->sup.idSupervisor){
                nuevo->sig=lista;
                lista=nuevo;
            }else{
                nodoSupervisor * seg=ante->sig;
                while(seg && seg->sup.idSupervisor < nuevo->sup.idSupervisor){
                    ante=seg;
                    seg=seg->sig;
                }
                nuevo->sig=seg;
                ante->sig=nuevo;
                }
        }else{
            lista=nuevo;
        }
    return lista;
};

nodo2Supervisor * insertarSupervisorEnListaDobleOrdenadoXId(nodo2Supervisor * listaD, nodo2Supervisor * nuevo){

    if(listaD){
            if(listaD->sup.idSupervisor > nuevo->sup.idSupervisor){
                nuevo->sig=listaD;
                listaD=nuevo;
            }else{
                nodo2Supervisor * ante=listaD;
                nodo2Supervisor * seg=ante->sig;
                while(seg && (seg->sup.idSupervisor < nuevo->sup.idSupervisor)){
                    ante=seg;
                    seg=seg->sig;
                }
                if(seg){
                    nuevo->sig=seg;
                    nuevo->ante=ante;
                    seg->ante=nuevo;
                    ante->sig=nuevo;
                }else{
                    nuevo->ante=ante;
                    ante->sig=nuevo;
                }
            }
        }else{
            listaD=nuevo;
        }
    return listaD;
};

nodoSupervisor * insertarSupervisorEnListaOrdenadoxNombre(nodoSupervisor * lista, nodoSupervisor * nuevo){
    nodoSupervisor * ante=lista;

    if(lista){
        if((strcmp(lista->sup.nomYApe,nuevo->sup.nomYApe))<0){
            nuevo->sig=lista;
            lista=nuevo;
        }else{
            nodoSupervisor * seg=ante->sig;
            while(seg && (strcmp(seg->sup.nomYApe,nuevo->sup.nomYApe))>0){
                ante=seg;
                seg=seg->sig;
            }
            nuevo->sig=seg;
            ante->sig=nuevo;
        }
    }else{
        lista=nuevo;
    }
    return lista;
};

nodo2Supervisor * insertarSupervisorEnListaDobleOrdenadoxNombre(nodo2Supervisor * listaD, nodo2Supervisor * nuevo){

    if(listaD){
            if((strcmp(listaD->sup.nomYApe,nuevo->sup.nomYApe))>0){
                nuevo->sig=listaD;
                listaD=nuevo;
            }else{
                nodo2Supervisor * ante=listaD;
                nodo2Supervisor * seg=ante->sig;
                while(seg && ((strcmp(seg->sup.nomYApe,nuevo->sup.nomYApe))<0)){
                    ante=seg;
                    seg=seg->sig;
                }
                if(seg){
                    nuevo->sig=seg;
                    nuevo->ante=ante;
                    seg->ante=nuevo;
                    ante->sig=nuevo;
                }else{
                    nuevo->ante=ante;
                    ante->sig=nuevo;
                }
            }
        }else{
            listaD=nuevo;
        }
    return listaD;
};


int consultaOrdenacion(){
    int opc='s';

    printf("\n1. Ordenar por ID de Supervisor.\n2.Ordenar por nombre y apellido de Supervisor.\n");
    fflush(stdin);
    scanf("%i",&opc);

    system("cls");

   return opc;
};

void mostrarNodoSupervisor(nodoSupervisor * s){

    printf("\n-------------------------------- \n");
    printf("Id de Supervisor: %d\n",s->sup.idSupervisor);
    printf("Nombre y Apellido: %s\n",s->sup.nomYApe);
    printf("Cantidad de Reportes: %d",s->sup.cantReportes);
    printf("\n-------------------------------- \n");
};
void mostrarUnSupervisor(supervisor  s){

    printf("\n-------------------------------- \n");
    printf("Id de Supervisor: %d\n",s.idSupervisor);
    printf("Nombre y Apellido: %s\n",s.nomYApe);
    printf("Cantidad de Reportes: %d",s.cantReportes);
    printf("\n-------------------------------- \n");
};

int cantCargadosEnFilePersonal(){
    FILE *personal=fopen(rutaPersonal,"rb");
    supervisor aux;
    int i=0;

    if(personal){
        while(fread(&aux,sizeof(supervisor),1,personal)>0){
            i++;
        }

        fclose(personal);
    }

    return i;
};

void mostrarListaSupervisores(nodoSupervisor * lista){
    nodoSupervisor * seg=lista;
    while(seg){
        nodoSupervisor * ante=seg;

        mostrarNodoSupervisor(ante);

        ante=seg;
        seg=seg->sig;

    }
};

nodoSupervisor * cargarListaSupervisores(nodoSupervisor * lista){

    char opc='s';
    int opcOrdenacion;
    supervisor nuevo;

    opcOrdenacion=consultaOrdenacion();
    system("pause");
    system("cls");

    while(opc=='s'){

        nuevo=cargarUnSupervisor();

        if(opcOrdenacion==1)
            lista=insertarSupervisorEnListaOrdenadoxId(lista,crearNodoSupervisor(nuevo));
        if(opcOrdenacion==2)
            lista=insertarSupervisorEnListaOrdenadoxNombre(lista,crearNodoSupervisor(nuevo));


        opc=control();
    }
    return lista;
}

void listaToArchivo(nodoSupervisor * lista){
    FILE *personal=fopen(rutaPersonal,"a+b");
    nodoSupervisor * seg=lista;
    supervisor aux;

    if(personal){
        while(seg){
            aux=seg->sup;
            fwrite(&aux,sizeof(supervisor),1,personal);
            seg=seg->sig;
        }
    fclose(personal);
    }else{
        puts("ERROR pasar de lista a un archivo.");
    }
};

void mostrarArchivoPersonal(){
    FILE *personal=fopen(rutaPersonal,"rb");
    supervisor aux;

    if(personal){

        while(fread(&aux,sizeof(supervisor),1,personal)>0){
            mostrarUnSupervisor(aux);
        }

        fclose(personal);
    }else{
        puts("ERROR mostrar.");
    }
};

nodo2Supervisor *  cargarListaDobleDesdeArchivo(nodo2Supervisor * listaD, nodo2Supervisor * nuevo,int opcOrdenacion){


    if(opcOrdenacion==1)
        listaD=insertarSupervisorEnListaDobleOrdenadoXId(listaD,nuevo);
    if(opcOrdenacion==2)
        listaD=insertarSupervisorEnListaDobleOrdenadoxNombre(listaD,nuevo);

    return listaD;
};

nodo2Supervisor * archivoToLista(nodoSupervisor * listaD){
    FILE *personal=fopen(rutaPersonal,"rb");
    int i=0,opcOrdenacion,val=cantCargadosEnFilePersonal();
    supervisor aux;
    nodo2Supervisor * nuevo;

    opcOrdenacion=consultaOrdenacion();

    if(personal){
        for(i;i<val;i++){
            fread(&aux,sizeof(supervisor),1,personal);

            nuevo=crearNodoDobleSupervisor(aux);

            listaD=cargarListaDobleDesdeArchivo(listaD,nuevo,opcOrdenacion);

        }
        fclose(personal);
    }else{
        printf("Error en apertura de archivo.");
    }
    return listaD;
};

void mostrarListaDobleRecursion(nodo2Supervisor * listaD){
    if(listaD){
       mostrarUnSupervisor(listaD->sup);
       mostrarListaDobleRecursion(listaD->sig);
    }
};
