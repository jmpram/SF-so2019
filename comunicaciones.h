
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
 * comunicaciones.h
 * Manejo de estación
 * 
 * funciones de comunicacion y cabeceras de las funciones comunicaciones.h
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/time.h>
#include "tren.h"
#include "user_interface.h"
#include <curses.h>

#ifdef __cplusplus
extern "C" {
#endif
#define CMD_LINE_LENGHT 50
    
//typedef enum {ERR_OK=0, ERR_UNKNOWN_CMD} ERROR;
    
ERROR processCommand(ST_TREN *tren, ST_APP_WINDOW *pWin, const char *commandLine);
void itoa(char *linea,int valor);

void concatenarMsj (char *buffer,char *aux, char* origen);

void obtenerPalabra (const char* linea, char * palabra, int *indice);

void enviarTrenE(ST_TREN * tren, int sockToE);

void escribirMensajeT(int sockTren,ST_TREN * tren);

void escribirMensajeEst(ST_TREN anden,ST_TREN v[],int n,int u,int socktren[]);

int crearSockTren(const char * port);


#ifdef __cplusplus
}

#endif

