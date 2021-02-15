
/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 * /
 
 /** 
 * 
 * estacion.h
 * Manejo de estación
 * 
 * Estructura Estación y cabeceras de las funciones Estación.h
 */




#include "tren.h"
#include <stdbool.h> 

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {	
    int sId;
    bool usoAnden;

}ST_ESTACION;

void inicializar (int v[],int n);

void inicializarcola (ST_TREN v[],int n);

void balanceo(ST_TREN v[],int vsock[],int n);

char identificarEntidad(char* buffer);

void decodificarTren(char * buffer,ST_TREN * tren);

void escribirRegTrenes(ST_TREN tren);

void printEstacion(ST_TREN anden , ST_TREN v[], int n, int usoanden,int socktren);

ST_TREN enviarAnden (ST_TREN v[],int socktren[], int n, int *usoanden);


#ifdef __cplusplus
}

#endif

