#include "headers.h"

void generarCamara (celda camara){
    int i;
    char supervisores[][]={{'Domingo'},{'Nestor'},{'Mauri'},{'Sergio'},{'Gaby'},{'Mariu'},{'Lilita'},{'Cristina'}};
    i=rand()%8;
    strcpy(camara->supervisor, supervisores[i]);

}
