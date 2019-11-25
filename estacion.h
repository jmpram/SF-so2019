
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

/*typedef struct {
	
    char idTren[8];
    char estacionOrigen[5];
    char estacionDestino[5];
    char  pasajeros[6];
    int combustible;
    int tViaje;
    char estado[10];
    char motivo[10];  
} ST_TREN;*/

typedef struct {	
    int sId;
    bool usoAnden;
    ST_TREN regTrenes[5];

}ST_ESTACION;

void printestacion(ST_TREN anden,ST_TREN V[],int n,int usoanden);

ST_TREN enviarAnden (ST_TREN v[],int socktren[], int n, int usoanden);

void escribirMensajeEst(ST_TREN anden,ST_TREN v[],int n,int u,int socktren[]);

//void itoa(char *linea,int valor);

void enviarTrenE(ST_TREN * tren, int sockTren);

char identificarEntidad(char* buffer);

void decodificarTren(char* buffer,ST_TREN * tren);

void escribirRegTrenes(ST_TREN tren);

void inicializar (int v[],int n);

void inicializarcola (ST_TREN v[],int n);

void balanceo(ST_TREN v[],int vsock[],int n);

#ifdef __cplusplus
}

#endif

