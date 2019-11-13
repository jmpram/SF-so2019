
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
     
} ST_TREN ;

void createTren(ST_TREN * tren);

void cargarTren(const char* linea,ST_TREN * tren);

void enviarTren(ST_TREN * tren, int sockTren);

void registrarTren(ST_TREN * tren);

void pasardatosabuffer(char*linea, ST_TREN tren);

void bufferatren(const char*linea, ST_TREN*tren);

#ifdef __cplusplus
}

#endif
#endif /* TREN_H */
