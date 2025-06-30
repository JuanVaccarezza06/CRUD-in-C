#ifndef PASSENGERS_H_INCLUDED
#define PASSENGERS_H_INCLUDED

#define MAX_LEN 100

typedef struct
{
  char nombreCompleto[MAX_LEN];
  char dni [MAX_LEN];
}stPassengers;

int cargarPasajeros (stPassengers [],int );
void mostrarPasajeros(stPassengers [],int ,int );
void mostrarsitoPasajeros(stPassengers );

#endif // PASSENGERS_H_INCLUDED
