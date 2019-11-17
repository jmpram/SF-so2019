
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
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {	
    int sId;
    bool usoAnden;
    ST_TREN regTrenes[5];

}ST_ESTACION;

typedef struct nodo{
    ST_TREN data;
    struct nodo *ste;
    
}ST_LISTA;


void create(ST_LISTA **list);

ST_LISTA * crearnodo(ST_TREN dato);

ST_LISTA * instordlistaesp (ST_LISTA **list, ST_TREN dato);

void itoa(int valor, char *linea);

ST_TREN * decodificarTren(const char* buffer);

char identificarEntidad(const char * buffer);

void escribirRegTrenes(ST_TREN tren);


#ifdef __cplusplus
}

#endif
#endif /* TREN_H */
