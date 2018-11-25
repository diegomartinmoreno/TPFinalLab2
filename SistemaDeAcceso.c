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


void crearArchivoAdministradores(){
    FILE *admin=fopen(rutaAdministradores,"rb");
    usuario in;
    if(admin==NULL){
        fclose(admin);
        admin=fopen(rutaAdministradores, "wb");
        strcpy(in.nomUsuario,"master");
        strcpy(in.contrasena,"master");
        fwrite(&in,sizeof(usuario),1,admin);
        fclose(admin);
    }
};

int realocarArreglo (celda camaras[], int dimF){
    camaras=realloc(camaras, sizeof(celda)+10);
    if (!camaras)
        perror("No se encontro espacio suficiente para realocar arreglo de camaras.");
    return dimF;
}

int generarArregloTodasLasCamaras (celda camaras[], int dimL, int dimF){
    int cantCamaras=cantidadRegistrosEnFile();
    celda aux;
    FILE *fp=fopen(rutaCamaras, "rb");
    int i=0;
    for (i=0; i<cantCamaras; i++){
        if (i>dimF){
            dimF=realocarArreglo(camaras,dimF);
        }
        fread(&aux, sizeof(celda), 1, fp);
        camaras[i]=aux;
    }
    fclose(fp);
    return i;
}

int verificarSupRepetido(usuario supervisores[], int dimL, usuario supervisor){ ///0=repetido /// 1=nuevo
    int i=0, rta=1;
    for (i=0; i<dimL; i++){
        if (strcmp(supervisores[i].nomUsuario, supervisor.nomUsuario)==0){
            rta=0;
        }
    }
    return rta;
}

int generarArregloSupervisores(celda camaras[], int dimL, usuario supervisores[]){
    int i=0, j=0;
    for (i=0; i<dimL; i++){
        if (verificarSupRepetido(supervisores, j, camaras[i].supervisor)==1){
            strcpy(supervisores[j].nomUsuario, camaras[i].supervisor.nomUsuario);
            strcpy(supervisores[j].contrasena, camaras[i].supervisor.contrasena);
            j++;
        }
    }
    return j;
}

void actualizarArchivoSupervisores(){
    FILE *sup=fopen(rutaSupervisores,"wb");
    celda camaras[100];
    usuario supervisores[50];
    int dimL=0, dimF=100, dimLsup=0, i=0;
    dimL=generarArregloTodasLasCamaras(camaras, dimL, dimF);
    dimLsup=generarArregloSupervisores(camaras, dimL, supervisores);
    for(i=0; i<dimLsup; i++){
        fwrite(&supervisores[i], sizeof(usuario), 1, sup);
    }
    fclose(sup);
}

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


int buscarExistente(usuario aux, char ruta[]){ /// 1 si encuentra existente, 0 si no esta en la base de datos.

    FILE *fp=fopen(ruta,"rb");
    int rta=0,valid,ingreso=0;
    usuario auxReg;

    if(fp){
        while(!feof(fp) && ingreso==0){
            fread(&auxReg,sizeof(usuario),1,fp);
            rta=strcmp(auxReg.nomUsuario,aux.nomUsuario);

            if(rta==0){
                valid=strcmp(auxReg.contrasena,aux.contrasena);
                if(valid==0){
                    ingreso=1;
                }
            }
        }
        fclose(fp);
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
                ingreso=buscarExistente(aux, rutaAdministradores);
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
    do{
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
        }
    }while(i<20&&pass!=13);
    encontrado=buscarExistente(aux, rutaAdministradores);
    if(encontrado==1){
        ingreso=1;
    }
    return ingreso;
};
