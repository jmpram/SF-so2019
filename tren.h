
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
 * tren.h 
 * Manejo de tren
 * 
 * Estructura Tren y cabeceras de las funciones tren.h
 */ 

 
#ifndef TREN_H 
#define TREN_H
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

    int idP;
    ST_TREN tren;

}ST_TRENP;

void inicializarTren(ST_TREN * tren);

void cargarTren(const char* linea,ST_TREN * tren);

void codificarMsj (char * buffer, ST_TREN * tren);

void imprimirInfoTren(ST_TREN * tren);


#endif /* TREN_H */
