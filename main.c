#include <stdio.h>
#include <stdlib.h>
#include "flights.h"
#include "passengers.h"

#define DIMENSION_ESTANDAR 10
#define INCREMENTO 10

// -- MENU --
void menu ();

// -- CREATE --
void createVuelo(char nombreArchivo[30]);

// -- READ --
void readVuelo(char nombreArchivo[30]);
void readPasajeros(char nombreArchivo[]);

// -- UPDATE --
void updateVuelo(char nombreArchivo[]);
void updatePasajeros(stFlight vuelo, char nombreArchivo[]);
void subMenuUpdate(char dniObjetivo[], stFlight vuelo, char nombreArchivo[]);

// -- DELETE --
void deleteVuelo(char nombreArchivo[]);

// -- COMPONENTES --
stFlight* realizarRealloc(stFlight* vuelos, size_t nuevaSize);
int desplazarVuelos(stFlight vuelos[], int* validos, int idBuscado);
void sobreescribirArchivo(stFlight array[], int validos, char nombreArchivo[]);
int transferirArchivoHaciaArreglo(char nombreArchivo[], stFlight** arr, int* dimensionArreglo);
int contarValidos(char nombreArchivo[]);
void sobreescribirVueloPorPosicion(stFlight vuelo, int pos, char nombreArchivo[]);
void sobrescribirPasajeroEnVuelo(stFlight* vuelo, stPassengers pasajeroModificado, int posicion);

// -- BUSCAR X POR Z --
stFlight buscarPorId(int idObjetivo, char nombreArchivo[]);
int buscarPosicion(int idObjetivo, char nombreArchivo[]);
stPassengers buscarPorDNI(char dniObjetivo[], char nombreArchivo[]);
int buscarPosicionPasajeroPorDNI(stFlight vuelo, char DNI[]);

// -- CONSOLA --
void ingresarString(char cadena[]);
int pedirInt(void);
void clearScreen(void);



int main()
{

    printf("--Comienzo el programa--\n");
    menu();
    printf("\n--Fin del programa--");

    char s1 [30] = "Hola mundo";
    char s2 [30];

    ingresarString(s2);

    if (strcmp(s1,s2) == 0 ) printf("%s y %s, SI SON IGUALES",s1,s2);
    else printf("%s y %s, SI SON IGUALES",s1,s2);

    return 0;
}

void menu()
{

    int option;
    char nombreArchivo [MAX_LEN] = "Vuelos";
    stFlight vuelo;
    stPassengers pasajero;
    int variableTipoInt = 0;
    char variableTipoCadena[MAX_LEN];

    do
    {
        printf("\n=== MENU DE GESTION DE VUELOS ===\n");
        printf(" 1. Cargar un vuelo\n");
        printf(" 2. Listar todos los vuelos\n");
        printf(" 3. Listar pasajeros\n");
        printf(" 4. Eliminar vuelo\n");
        printf(" 5. Actualizar vuelo\n");
        printf(" 6. Buscar vuelo por ID\n");
        printf(" 7. Buscar pasajero por DNI\n");
        printf(" 8. Vaciar archivo\n");
        printf(" 0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Cargando menu para registro de vuelos... ");
            createVuelo(nombreArchivo);
            //clearScreen();
            break;

        case 2:
            printf("Cargando interfaz para vuelos...");
            readVuelo(nombreArchivo); // FALTA MOSTRAR EN CADA VUELO, SUS PASAJEROS
            break;

        case 3:
            printf("Cargando interfaz para pasajeros");
            readPasajeros(nombreArchivo);
            break;

        case 4:
            printf("Cargando menu para eliminacion de registros...");
            deleteVuelo(nombreArchivo);
            break;

        case 5:
            printf("Cargando menu para actualizacion de registros...");
            updateVuelo(nombreArchivo);
            break;

        case 6:
            printf("Cargando menu para buscar vuelo por ID...");
            printf("\nIngrese el id del avion a buscar:");
            variableTipoInt = pedirInt();
            vuelo = buscarPorId(variableTipoInt,nombreArchivo);
            if (!vuelo.id == NULL)mostrarsitoVuelos(vuelo);
            break;

        case 7:
            printf("Cargando menu para buscar pasajero por DNI...");
            printf("\nIngrese el DNI del pasajero a buscar:");
            ingresarString(variableTipoCadena);
            pasajero = buscarPorDNI(variableTipoCadena,nombreArchivo);
            if (!pasajero.dni[0] == '\0') mostrarsitoPasajeros(pasajero);
            break;
        case 8:
            printf("Limpiar archivo...\n");
            printf("Confirme la accion: S/N\n");

            char seguir = 's';
            fflush(stdin);
            scanf("%c",&seguir);

            if(seguir == 's')
            {
                FILE* archi = fopen(nombreArchivo,"wb");
                fclose(archi);
            }
            else
            {
                printf("\nOperacion cancelada...\n");
            }
            break;

        case 0:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opción no válida. Reintente.\n");
            break;
        }

    }
    while (option != 0);

}

// -- CREATE --

void createVuelo(char nombreArchivo [30])
{

    printf("\nMenu para insertar un vuelo al archivo.\n");

    stFlight vuelo = cargarVueloPorTeclado();
    FILE* archi = fopen(nombreArchivo,"ab");
    if(archi == NULL)
    {
        perror("fopen");
        return;
    }

    if(fwrite(&vuelo,sizeof(stFlight),1,archi) != 1)
    {
        fclose(archi);
        perror("fwrite");
    }

    fclose(archi);
}

// -- READ --

void readVuelo(char nombreArchivo[30])
{
    printf("\nMenu para mostrar los vuelos del archivo.\n");

    FILE* archi = fopen(nombreArchivo,"rb");
    if(archi == NULL)
    {
        perror("fopen");
        return;
    }

    int validos = 0;
    int dimension = DIMENSION_ESTANDAR;
    stFlight *vuelos = malloc(dimension * sizeof(stFlight) );
    if (!vuelos)
    {
        perror("malloc inicial");
        fclose(archi);
        return;
    }
    while (fread(&vuelos[validos], sizeof *vuelos, 1, archi) > 0)
    {
        validos++;
        // Si ya llenamos el buffer, lo agrandamos
        if (validos == dimension)
        {
            stFlight* tmp = realizarRealloc(vuelos, (dimension+INCREMENTO) );
            if (!tmp)
            {
                // ya imprimió el error y liberó el viejo si así lo definiste
                fclose(archi);
                return;
            }
            vuelos = tmp;
            dimension = dimension + INCREMENTO;
        }
    }

    mostrarVuelos(vuelos,validos);

    free(vuelos);
    fclose(archi);

}

void readPasajeros(char nombreArchivo[])
{
    printf("\nDe que avion desea ver los pasajeros: ");
    int idVuelo = pedirInt();

    stFlight vuelo = buscarPorId(idVuelo,nombreArchivo);
    if(vuelo.id == 0) return;
    mostrarPasajeros(vuelo.pasajeros,vuelo.id,vuelo.pasajerosAbordo);
    printf("\nSaliendo...\n");
}

// -- UPDATE --

void updateVuelo(char nombreArchivo[])
{

    printf("\nIngrese el id del vuelo a actualizar:");
    int idVueloObjetivo = pedirInt();
    stFlight vuelo = buscarPorId(idVueloObjetivo,nombreArchivo);
    if(vuelo.id == NULL) return;

    char variableTipoCadena [100];
    int variableTipoInt = 0;
    int segundaVTI = 0;


    int opcion;
    do
    {
        printf("\n--- Que queres actualizar del vuelo ID %d? ---\n", idVueloObjetivo);
        printf(" 1. Nombre del piloto\n");
        printf(" 2. Destino\n");
        printf(" 3. Capacidad\n");
        printf(" 4. Pasajeros a bordo\n");
        printf(" 0. Guardar y salir\n");
        printf("\nElija una opcion:");
        opcion = pedirInt();

        switch (opcion)
        {
        case 1:
            printf("Ingrese el nuevo nombre del piloto:");
            ingresarString(variableTipoCadena);
            strcpy(vuelo.nombreCompletoPiloto,variableTipoCadena);

            variableTipoInt = buscarPosicion(idVueloObjetivo,nombreArchivo);
            sobreescribirVueloPorPosicion(vuelo,variableTipoInt,nombreArchivo);
            break;
        case 2:
            printf("Ingrese el nuevo destino del vuelo:");
            ingresarString(variableTipoCadena);
            strcpy(vuelo.destino,variableTipoCadena);

            variableTipoInt = buscarPosicion(idVueloObjetivo,nombreArchivo);
            sobreescribirVueloPorPosicion(vuelo,variableTipoInt,nombreArchivo);
            break;
        case 3:
            printf("Ingrese la nueva capacidad del vuelo:\n");
            variableTipoInt = pedirInt();
            vuelo.dimension = variableTipoInt;

            segundaVTI = buscarPosicion(idVueloObjetivo,nombreArchivo);
            sobreescribirVueloPorPosicion(vuelo,segundaVTI,nombreArchivo);
            break;
        case 4:
            updatePasajeros(vuelo,nombreArchivo);
            break;
        case 0:
            puts("Guardando cambios y saliendo...");
            break;
        default:
            puts("Opción inválida, probá de nuevo.");
        }
    }
    while (opcion != 0);

    // … código para reescribir el archivo con arr[0..n-1] usando "wb" …
    // … free(arr) …
}

void updatePasajeros(stFlight vuelo,char nombreArchivo[])
{
    if (vuelo.pasajerosAbordo == 0)
    {
        puts("No hay pasajeros para actualizar.");
        return;
    }

    char dniObjetivo[MAX_LEN];
    printf("\n--- Elige un pasajero por su DNI o -1 para salir ---\n");
    for (int i = 0; i < vuelo.pasajerosAbordo; i++)
    {
        printf(" %d. %s DNI: %s\n",
               i+1,
               vuelo.pasajeros[i].nombreCompleto,
               vuelo.pasajeros[i].dni
              );
    }
    ingresarString(dniObjetivo);

    // Esto elimina cualq. /r y /n, las cadenas son muy quisquillosas.
    dniObjetivo[strcspn(dniObjetivo, "\r\n")] = '\0';
    if( strcmp (dniObjetivo,"-1") == 0)
    {
        printf("Actualizacion de pasajeros cancelada.");
        return;
    }

    subMenuUpdate(dniObjetivo,vuelo,nombreArchivo);
}
void subMenuUpdate(char dniObjetivo[],stFlight vuelo,char nombreArchivo[])
{

    int campo;
    char variableTipoCadena [MAX_LEN];
    int variableTipoInt = 0;
    stPassengers pasajero = {0};
    do
    {
        puts("\nQue campo queres actualizar?");
        puts(" 1. Nombre completo");
        puts(" 2. DNI");
        puts(" 0. Finalizar y volver");
        campo = pedirInt();

        switch (campo)
        {
        case 1:
            printf("Ingrese el nuevo nombre del pasajero: \n");
            ingresarString(variableTipoCadena);
            pasajero = buscarPorDNI(dniObjetivo,nombreArchivo);

            if (pasajero.dni[0] == '0')
            {
                printf("Busqueda fallida. 'buscarPorDNI' %s",pasajero.dni);
                return;
            }
            strcpy(pasajero.nombreCompleto,variableTipoCadena);

            variableTipoInt = buscarPosicionPasajeroPorDNI(vuelo,dniObjetivo);
            if (variableTipoInt == -1)
            {
                perror("Busqueda fallida. 'buscarPosicionPasajeroPorDNI'");
                return;
            }
            sobrescribirPasajeroEnVuelo(&vuelo, pasajero,variableTipoInt);

            variableTipoInt = buscarPosicion(vuelo.id,nombreArchivo);
            if (variableTipoInt == -1)
            {
                perror("Busqueda fallida. 'buscarPosicion'");
                return;
            }
            sobreescribirVueloPorPosicion(vuelo,variableTipoInt,nombreArchivo);
            break;
        case 2:
            printf("Ingrese el nuevo DNI del pasajero: \n");
            ingresarString(variableTipoCadena);
            pasajero = buscarPorDNI(dniObjetivo,nombreArchivo);

            if (pasajero.dni[0] == '0')
            {
                printf("Busqueda fallida. 'buscarPorDNI' %s",pasajero.dni);
                return;
            }
            strcpy(pasajero.dni,variableTipoCadena);

            variableTipoInt = buscarPosicionPasajeroPorDNI(vuelo,dniObjetivo);
            if (variableTipoInt == -1)
            {
                perror("Busqueda fallida. 'buscarPosicionPasajeroPorDNI'");
                return;
            }
            sobrescribirPasajeroEnVuelo(&vuelo, pasajero,variableTipoInt);

            variableTipoInt = buscarPosicion(vuelo.id,nombreArchivo);
            if (variableTipoInt == -1)
            {
                perror("Busqueda fallida. 'buscarPosicion'");
                return;
            }
            sobreescribirVueloPorPosicion(vuelo,variableTipoInt,nombreArchivo);
            break;
        case 0:
            puts("Finalizando actualización de pasajero.");
            break;
        default:
            puts("Opción inválida. Probá de nuevo.");
        }
    }
    while (campo != 0);

}

// -- DELETE --

void deleteVuelo (char nombreArchivo[])
{
    printf("\nIngrese el id del avion que desea eliminar: \n");
    int id = pedirInt(); // Ask what flights want to delete (by id).
    int dimension = DIMENSION_ESTANDAR;

    stFlight* arr = malloc(dimension * sizeof(stFlight) );
    int validos = transferirArchivoHaciaArreglo(nombreArchivo,&arr,&dimension);

    int eliminado = desplazarVuelos(arr, &validos, id); // Invoke this function for delete the record pedido

    if (eliminado != 0)
    {
        sobreescribirArchivo(arr, validos,nombreArchivo);    // sobreescribo el arreglo con el dato ya eliminado en el archivo con un valido menos
        printf("Eliminado correctamente.");
    }
    else printf ("El dato no pudo ser eliminado \n");

    free(arr);

}


// -- COMPONENTES --

stFlight* realizarRealloc(stFlight* vuelos, size_t nuevaSize)
{
    stFlight* temporal = realloc(vuelos, nuevaSize*sizeof(stFlight));
    if (!temporal)
    {
        perror("Error al realizar el realloc");
        free(vuelos);
        return NULL;
    }
    return temporal;
}


int desplazarVuelos(stFlight vuelos[], int* validos, int idBuscado)
{
    int eliminado = 0;

    // Itera cada indice desde el 0 hasta el validos-1
    for (int i = 0; i < *validos; i++)
    {
        // Si el idBuscado es igual/matchea con el id de la iteracion, entra.
        if (vuelos[i].id == idBuscado)
        {
            // Desplaza todos los vuelos posteriores hacia la derecha
            for (int k = i; k < *validos; k++)
            {
                vuelos[k] = vuelos[k + 1];
            }
            eliminado++;
            i--;       // Paso atras para re-examinar este indice despues del desplazamiento
            (*validos)--;   // Descuenta un valido ya que eliminamos un vuelo.
        }
    }
    return eliminado;
}
void sobreescribirArchivo (stFlight array[], int validos,char nombreArchivo[])
{
    FILE* archi;
    archi = fopen (nombreArchivo, "wb"); //  sobreescribo de 0, por eso wb
    if(!archi)
    {
        perror("Error al abrir el archivo. 'sobreescribirArchivo'");
        return;
    }
    for(int i = 0; i < validos; i++)
    {
        if (fwrite (&array[i], sizeof(stFlight), 1, archi) != 1)
        {
            perror("Error en el fwrite. 'sobreescribirArchivo'");
        }
    }
    fclose (archi);
}

int transferirArchivoHaciaArreglo(char nombreArchivo[],stFlight** arr,int* dimensionArreglo)
{
    FILE* archi;
    archi = fopen (nombreArchivo, "rb");
    if(!archi)
    {
        perror("Error al abrir el archivo. 'sobreescribirArchivo'");
        return -1;
    }

    int validos = 0;
    while (fread(&(*arr)[validos], sizeof(stFlight), 1, archi) == 1)
    {
        validos++;

        if (validos == *dimensionArreglo)
        {
            stFlight* tmp = realizarRealloc(*arr, (*dimensionArreglo += INCREMENTO));
            if (!tmp)
            {
                perror("Realloc fallido. 'transferirArchivoHaciaArreglo'");
                fclose(archi);
                return -1;
            }
            *arr = tmp;
        }
    }

    fclose(archi);
    return validos;
}
int contarValidos(char nombreArchivo[])
{

    int validos = 0;
    stFlight vueloAuxiliar;

    FILE* archi = fopen(nombreArchivo,"rb");
    if(!archi)
    {
        perror("Error al abrir el archivo. 'contarValidos'");
        return -1;
    }

    while(fread(&vueloAuxiliar,sizeof(stFlight),1,archi) > 0) validos++;

    fclose(archi);
    return validos;
}
void sobreescribirVueloPorPosicion (stFlight vuelo, int pos,char nombreArchivo [])
{
    FILE* archi;
    archi = fopen (nombreArchivo, "r+b");
    if(!archi)
    {
        perror("Error al abrir el archivo. 'sobreescribirVueloPorPosicion'");
        return;
    }
    if(fseek(archi, sizeof(stFlight)*pos, SEEK_SET) == 0)
    {
        fwrite (&vuelo, sizeof(stFlight), 1, archi);
    }
    else
    {
        perror("El fseek fallo en: 'overrideByPosition'");
    }

    fclose(archi);
}
void sobrescribirPasajeroEnVuelo(stFlight* vuelo, stPassengers pasajeroModificado, int posicion)
{
    if (posicion >= 0 && posicion < vuelo->pasajerosAbordo) vuelo->pasajeros[posicion] = pasajeroModificado;
    else perror("Posición inválida para sobrescribir pasajero.\n");
}
// -- BUSCAR X POR Z


stFlight buscarPorId(int idObjetivo,char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo,"rb");
    stFlight vacio = {0};
    if(!archi)
    {
        perror("Error al abrir el archivo. 'buscarPorId'");
        return vacio;
    }
    stFlight aux;
    while (fread(&aux, sizeof (aux), 1, archi) == 1)
    {
        if (aux.id == idObjetivo)
        {
            fclose(archi);
            return aux;
        }
    }
    fclose(archi);
    printf("No se encontro ningun registro con id %d\n",idObjetivo);
    return vacio;
}
int buscarPosicion(int idObjetivo,char nombreArchivo[])
{
    FILE* archi;
    archi = fopen (nombreArchivo, "r+b");
    if(!archi)
    {
        perror("Error al abrir el archivo. 'sobreescribirVueloPorPosicion'");
        return -1;
    }

    stFlight vuelo;
    int i = 0;
    int posicion = -1;
    int seguir = 1;

    while (fread(&vuelo, sizeof(stFlight), 1, archi) > 0 && seguir == 1)
    {
        if (vuelo.id == idObjetivo)
        {
            posicion = i;                 // Save index where match occurred
        }
        i++;                         // Advance to next index
    }

    fclose(archi);                    // Close the file
    return posicion;                           // Return found index or -1 (if it is found, return the BOF)

}
stPassengers buscarPorDNI(char dniObjetivo[],char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo,"rb");
    stPassengers vacio = {0}; // Variable para el retorno null. Sin uso concreto.

    if(!archi)
    {
        perror("Error al abrir el archivo. 'buscarPorDNI'");
        return vacio;
    }

    stFlight vuelo;
    while (fread(&vuelo, sizeof(stFlight), 1, archi) == 1)
    {
        for(int i = 0; i < vuelo.pasajerosAbordo; i++)
        {
            if (strcmp(vuelo.pasajeros[i].dni,dniObjetivo) == 0 )
            {
                fclose(archi);
                return vuelo.pasajeros[i];
            }
        }

    }
    fclose(archi);
    printf("No se encontro ningun pasajero con DNI en: %s\n",dniObjetivo);
    return vacio;
}
int buscarPosicionPasajeroPorDNI(stFlight vuelo, char DNI[])
{
    for (int i = 0; i < vuelo.pasajerosAbordo; i++)
    {
        if (strcmp(vuelo.pasajeros[i].dni,DNI) == 0)
        {
            return i; // lo encontré, devuelvo la posición
        }
    }
    return -1; // no lo encontré
}
// -- CONSOLA --


void ingresarString(char s[MAX_LEN])
{
    fflush(stdin);
    do {
        if (!fgets(s, MAX_LEN, stdin)){
            perror("Error en el fgets. 'IngresarString'");
            return;             // en caso de EOF o error
        }
    } while (s[0] == '\n');      // si sólo leíste un Enter, repetí

    // recortá \r y \n finales
    s[strcspn(s, "\r\n")] = '\0';

}
int pedirInt ()
{
    int num;
    printf ("\n:");
    scanf ("%d", &num);

    return num;
}
void clearScreen(void)
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");    // Windows
#else
    system("clear");  // Linux/macOS
#endif
}



















