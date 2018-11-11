#include "headers.h"

tiempo generarFecha (){
    tiempo aux;
    aux.ano=(rand()%10)+2008;
    aux.dia=rand()%90;
    aux.hora=rand()%24;
    aux.mes=rand()%13;
    aux.minuto=rand()%60;
    aux.segundo=rand()%60;
    return aux;
}


lugar generarUbicacion (int ID){
    lugar aux;
    int IDlugar=ID/100;
    char nombre[][sizeNom]={{"Grido"},{"Italia"},{"San Marino"},{"Reggio"},{"Ischia"},{"Freddo"},{"Giannelli"},{"Arlequin"}};
    char calle [][sizeNom]={{"A. Edison"},{"Alem"},{"Constitucion"},{"Av Libertad"},{"Luro"},{"Rawson"},{"Luro"},{"Luro"}};
    int altura[8]={ 1411, 3618, 4018, 4326, 4004, 1313, 3358, 7198};
    aux.altura=altura[IDlugar];
    strcpy(aux.nombre, nombre[IDlugar]);
    strcpy(aux.calle, calle[IDlugar]);
    aux.piso=0;
    aux.departamento=0;
    strcpy(aux.ciudad, "Mar del Plata");
    return aux;
}

void generarCamara (int ID){
    celda camara;
    int i;
    char supervisores[][sizeNom]={{"Domingo"},{"Nestor"},{"Mauri"},{"Sergio"},{"Gaby"},{"Mariu"},{"Lilita"},{"Cristina"}};
    i=rand()%8;
    strcpy(camara.supervisor, supervisores[i]);
    camara.fechaInstalacion=generarFecha();
    camara.histAlertas=0;
    camara.histAlertas=0;
    camara.estado=rand()%3;
    camara.IDcamara=ID;
    camara.ubicacion=generarUbicacion(ID);
    camara.prioridad=rand()%10;
    FILE *fp=fopen(rutaCamaras, "ab");
    if (fp){
        fwrite(&camara, sizeof(celda), 1, fp);
    }
    fclose(fp);
}

void generarBaseCamaras(){
    int i, j, ID;
    for (i=0; i<8; i++){
        for (j=0;j<6; j++){
            ID=(i*100)+j;
            generarCamara(ID);
        }
    }
}

void inicializarCamaras (){

    FILE *fp=fopen(rutaCamaras, "rb");
    if (!fp){
        generarBaseCamaras();
        puts("Se creo una nueva base de datos de Camaras aleatorias.");
    }
    else
        puts("Base de datos de Camaras disponible.");
    fclose(fp);
}
