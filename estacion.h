
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
 * Manejo de estación
 * 
 * Estructura Estación y cabeceras de las funciones Estación.h
 */

#ifndef TREN_H 
#define TREN_H
#include "tren.h"
#include <stdbool.h> 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	
    char idTren[8];
    char estacionOrigen[5];
    char estacionDestino[5];
    char  pasajeros[6];
    int combustible;
    int tViaje;
    char estado[10];
    char motivo[10];  
} ST_TREN;

typedef struct {	
    int sId;
    bool usoAnden;
   ST_TREN regTrenes[5];

}ST_ESTACION;

void itoa(int valor, char *linea);

char identificarEntidad(char* buffer);

void decodificarTren(char* buffer,ST_TREN * tren);

void escribirRegTrenes(ST_TREN tren);


#ifdef __cplusplus
}

#endif
#endif /* TREN_H */
