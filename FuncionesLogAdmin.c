#include "headers.h"


typedef struct{
    char nomUsuario[sizeNom];
    char contrasena[sizeNom];
}usuario;
//.---------------------------------------------------------------.-.-.----------------------------------------------
void crearArchivo(){
    FILE *admin=fopen(rutaAdministradores,"a+b");
    if(admin){
        puts(" ");
        fclose(admin);
    }
};
char control(){
    char opc;
    printf("Desea Continuar? S/N.\n");
    fflush(stdin);
    opc=getch();
    opc=tolower(opc);

    return opc;
};
usuario registro(){
    usuario aux;

    printf("Ingrese nombre de usuario: ");
    fflush(stdin);
    gets(aux.nomUsuario);

    printf("Ingrese contrase%ca: ",-92);
    fflush(stdin);
    gets(aux.contrasena);

    return aux;
};

int buscarExistente(usuario aux){

    FILE *admin=fopen(rutaAdministradores,"rb");
    int rta=0,valid,ingreso=0;
    usuario auxReg;

    if(admin){
        while(!feof(admin) && ingreso==0){
            fread(&auxReg,sizeof(usuario),1,admin);
            rta=strcmp(auxReg.nomUsuario,aux.nomUsuario);

            if(rta==0){
                valid=strcmp(auxReg.contrasena,aux.contrasena);
                if(valid==0){
                    ingreso=1;
                }
            }
        }
        fclose(admin);
    }
    return ingreso;
};

int cantReg(){
    FILE * admin=fopen(rutaAdministradores,"rb");
    usuario ad;
    int i=0;

    if(admin){

        while(fread(&ad,sizeof(usuario),1,admin)>0){
            i++;
        }
        fclose(admin);
    }
    return i;
};

void cargarUsuarios(){
    FILE *admin=fopen(rutaAdministradores,"a+b");
    char opc='s';
    int ingreso=0,validos;
    usuario aux;

    if(admin){
        system("cls");
        
        while(opc=='s'){

            aux=registro();
            validos=cantReg();

            if(validos==0){
                fwrite(&aux,sizeof(usuario),1,admin);
            }else{
                ingreso=buscarExistente(aux);
                if(ingreso==0){
                    fwrite(&aux,sizeof(usuario),1,admin);
                }else{
                    puts("Usuario existente.");
                }
            }

            opc=control();
        }
        fclose(admin);
    }
};
void iniciarSesion(){
    usuario in;
    int acceso=0;

    in=registro();
    acceso=buscarExistente(in);
    if(acceso==1){
        printf("Exito.\n");
    }else{
        printf("ERROR.\n");
    }

};
