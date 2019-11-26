
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

void createTren(ST_TREN * tren);

void obtenerPalabra (const char* linea, char * palabra, int *indice);

void itoa(char *linea,int valor);

void cargarTren(const char* linea,ST_TREN * tren);

void enviarTren(ST_TREN * tren, int sockTren);

void concatenarMsj (char *buffer,char *aux, char* msj);

void codificarMsj(char * buffer, ST_TREN * tren);

void escribirMensaje(int sockTren,ST_TREN * tren);

void registrarTren(ST_TREN * tren);

#endif /* TREN_H */
