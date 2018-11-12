#include "headers.h"


void mostrarArchivoAdministrador(){
    FILE * admin=fopen(rutaAdministradores,"rb");
    usuario in;

    if(admin){
        while(fread(&in,sizeof(usuario),1,admin)>0){
            mostrarUnUsuario(in);
        }

        fclose(admin);
    }
};


void crearArchivo(){
    FILE *admin=fopen(rutaAdministradores,"wb");
    usuario in;
    if(admin){
        strcpy(in.nomUsuario,"diego");
        strcpy(in.contrasena,"diego");
        fwrite(&in,sizeof(usuario),1,admin);
        puts(" ");
        fclose(admin);
    }
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


void cargarUsuariosAdm(){
    FILE *admin=fopen(rutaAdministradores,"a+b");
    char opc='s';
    int ingreso=0,validos;
    usuario aux;

    system("cls");
    imprimirHeader("     Registrarse      ");

    if(admin){

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


int identificarse(){

    char pass,enmascarado[20];
    usuario aux;

    int i=0,ingreso=0,encontrado=0;

    strcpy(enmascarado,"**********");

    imprimirHeader("        Acceso        ");

    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(aux.nomUsuario);

    printf("\nIngrese contrase%ca: ",164);
    while(i<20){
        pass=getch();
        if(pass != 13 && pass != 8){
            printf("%c",enmascarado[i]);
            aux.contrasena[i]=pass;
            i++;
        }
        
        if(pass==8){ //si lee backspace
            i--;
            printf("\b");
            printf(" ");
            printf("\b");

        }
        if(pass==13){ //si lee retorno de carro
            aux.contrasena[i]='\0';
            encontrado=buscarExistente(aux);
            if(encontrado==1){
                ingreso=1;
            }
        }
    }
    return ingreso;
};
