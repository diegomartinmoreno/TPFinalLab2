#include "headers.h"

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



nodoSupervisor * crearNodoSupervisor(usuario s){
    nodoSupervisor * aux=(nodoSupervisor *)malloc(sizeof(nodoSupervisor));

    strcpy(aux->sup.nomUsuario,s.nomUsuario);
    strcpy(aux->sup.contrasena,s.contrasena);

    aux->sig=0;

    return aux;
};


nodo2Supervisor * crearNodoDobleSupervisor(usuario s){
    nodo2Supervisor * aux=(nodo2Supervisor *)malloc(sizeof(nodo2Supervisor));

    strcpy(aux->sup.nomUsuario,s.nomUsuario);
    strcpy(aux->sup.contrasena,s.contrasena);

    aux->ante=0;
    aux->sig=0;

    return aux;
};


nodoSupervisor * insertarSupEnListaOrdenNombre(nodoSupervisor * lista, nodoSupervisor * nuevo){
    nodoSupervisor * ante=lista;

    if(lista){
        if((strcmp(lista->sup.nomUsuario,nuevo->sup.nomUsuario))<0){
            nuevo->sig=lista;
            lista=nuevo;
        }else{
            nodoSupervisor * seg=ante->sig;
            while(seg && (strcmp(seg->sup.nomUsuario,nuevo->sup.nomUsuario))>0){
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


nodo2Supervisor * insertarSupEnListaDobleOrdenNombre(nodo2Supervisor * listaD, nodo2Supervisor * nuevo){

    if(listaD){
            if((strcmp(listaD->sup.nomUsuario,nuevo->sup.nomUsuario))>0){
                nuevo->sig=listaD;
                listaD=nuevo;
            }else{
                nodo2Supervisor * ante=listaD;
                nodo2Supervisor * seg=ante->sig;
                while(seg && ((strcmp(seg->sup.nomUsuario,nuevo->sup.nomUsuario))<0)){
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

void mostrarNodoSupervisor(nodoSupervisor * s){
    printf("\n-------------------------------- \n");
    printf("Nombre de usuario: %s\n",s->sup.contrasena);
    printf("\n-------------------------------- \n");
};


void mostrarUnSupervisor(usuario  s){
    printf("\n-------------------------------- \n");
    printf("Nombre de usuario: %s\n",s.nomUsuario);
    printf("\n-------------------------------- \n");
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
    usuario nuevo;


    while(opc=='s'){

        nuevo=cargarUnSupervisor();

        lista=insertarSupEnListaOrdenNombre(lista,crearNodoSupervisor(nuevo));

        opc=control();
    }
    return lista;
}


void listaToArchivo(nodoSupervisor * lista){
    FILE *personal=fopen(rutaPersonal,"a+b");
    nodoSupervisor * seg=lista;
    usuario aux;

    if(personal){
        while(seg){
            aux=seg->sup;
            fwrite(&aux,sizeof(usuario),1,personal);
            seg=seg->sig;
        }
    fclose(personal);
    }else{
        puts("ERROR pasar de lista a un archivo.");
    }
};


void mostrarArchivoPersonal(){
    FILE *personal=fopen(rutaPersonal,"rb");
    usuario aux;

    if(personal){

        while(fread(&aux,sizeof(usuario),1,personal)>0){
            mostrarUnSupervisor(aux);
        }

        fclose(personal);
    }else{
        puts("ERROR mostrar.");
    }
};

nodo2Supervisor * archivoToLista(nodoSupervisor * listaD){
    FILE *personal=fopen(rutaPersonal,"rb");
    int i=0,orden,val=contarUsuariosCreados();
    usuario  aux;
    nodo2Supervisor * nuevo;


    if(personal){
        for(i=0;i<val;i++){
            fread(&aux,sizeof(usuario),1,personal);

            nuevo=crearNodoDobleSupervisor(aux);

            listaD=insertarSupEnListaDobleOrdenNombre(listaD,nuevo);

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
