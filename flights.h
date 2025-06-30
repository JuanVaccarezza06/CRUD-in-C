#ifndef FLIGHTS_H_INCLUDED
#define FLIGHTS_H_INCLUDED
#include "passengers.h"

#define MAX_LEN 100
#define MAX_PASSENGERS 100

typedef struct {
    int    id;
    char   nombreCompletoPiloto[MAX_LEN];
    char   destino[MAX_LEN];
    int    dimension; // dimension o capacidad del avion/vuelo
    int    pasajerosAbordo; // count of passengers (less that dimension)
    stPassengers pasajeros[MAX_PASSENGERS];
}stFlight;

stFlight cargarVueloPorTeclado();
void mostrarVuelos(stFlight  [],int );
void mostrarsitoVuelos(stFlight);

#endif // FLIGHTS_H_INCLUDED

