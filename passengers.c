#include <stdint.h>
#include <stdio.h>

#include "passengers.h"

int cargarPasajeros (stPassengers pasajeros[],int dimension)
{
    int validos = 0;
    char seguir = 's';

    for (int i = 0; i < dimension && seguir == 's'; i++)
    {
        printf ("\nAhora llenaremos los datos de los pasajeros: \n");

        printf ("\nIngrese dni del pasajero: ");
        ingresarString(pasajeros[i].dni);

        printf ("Ingrese nombre completo del pasajero: ",pasajeros[i].dni);
        ingresarString(pasajeros[i].nombreCompleto);

        validos++;

        printf("Desea seguir ingresando pasajeros al arreglo? S/N ");
        fflush(stdin);
        scanf("%c",&seguir);
    }

    if (validos == dimension-1){
        printf("No puede haber mas pasajeros que asientos.");
    }

    return validos;
}
void mostrarPasajeros(stPassengers pasajeros[],int vueloId,int validos){

    printf ("A continuacion se mostraran todos los pasajeros del vuelo %d: \n",vueloId);

    // Le paso la direccion de memoria del arreglo simplemente para manejar punteros dobles.

    for(int i = 0; i < validos;i++){
        mostrarsitoPasajeros(pasajeros[i]);
    }

    printf("\nSe mostraron en total %d pasajeros.\n",validos);

}
void mostrarsitoPasajeros(stPassengers pasajero){

    printf ("---------------------------------------------------------------------------------------------------------\n");

    printf ("Pasajero con DNI en: %s\n",pasajero.dni);
    printf ("Nombre completo del pasajero: %s\n",pasajero.nombreCompleto);

    printf ("---------------------------------------------------------------------------------------------------------\n");

}
