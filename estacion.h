
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

void itoa(int valor, char *linea);

ST_TREN * decodificarTren(const char* buffer);

char identificarEntidad(const char * buffer);

void escribirRegTrenes(ST_TREN tren);


#ifdef __cplusplus
}

#endif
#endif /* TREN_H */
