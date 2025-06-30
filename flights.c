#include <stdint.h>
#include <stdio.h>

#include "flights.h"

stFlight cargarVueloPorTeclado()
{
        stFlight vuelo;

        printf ("\nIngrese el numero de identificacion del avion: ");
        vuelo.id = pedirInt();

        printf ("Ingrese nombre del piloto: ");
        ingresarString(vuelo.nombreCompletoPiloto);

        printf ("Hacia donde se dirije el vuelo %d: ",vuelo.id);
        ingresarString(vuelo.destino);

        printf ("Ingrese la capacidad del avion: ");
        vuelo.dimension = pedirInt();

        printf("\nCargando apartado de carga para pasajeros...\n");

        vuelo.pasajerosAbordo = cargarPasajeros(vuelo.pasajeros,vuelo.dimension);

    return vuelo;
}
void mostrarVuelos(stFlight array [],int validos){

    printf ("A continuacion se mostraran todos los vuelos del archivo:\n");

    int finales = 0;

    for(int i = 0; i < validos;i++){
        mostrarsitoVuelos(array[i]);
        finales=i;
    }

    if(finales==0) printf("\nSe mostraron en total %d vuelos.\n",finales);
    else printf("\nSe mostraron en total %d vuelos.\n",finales+1);
}
void mostrarsitoVuelos(stFlight vuelo){

    printf ("La informacion de su vuelo con ID en %d, es la siguiente:\n",vuelo.id);


    printf ("---------------------------------------------------------------------------------------------------------\n");

    printf ("El id del avion es %d\n",vuelo.id);
    printf ("El destino de su vuelo, es hacia %s\n",vuelo.destino);
    printf ("La capacidad de su vuelo es de %d pasajeros\n",vuelo.dimension);
    printf ("El piloto se llama: %s\n",vuelo.nombreCompletoPiloto);

    printf ("---------------------------------------------------------------------------------------------------------\n");

}


