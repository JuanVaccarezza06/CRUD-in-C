# CRUD-in-C
Se utiliza persistencia mediante archivos binarios; arreglos dinámicos y estáticos; punteros (simples y dobles cuando es necesario). Además de lectura y escritura de archivos binarios; transporte de datos a través de fread, fwrite y fseek.

## Objetivos del proyecto

- Practicar y demostrar el uso de:
  - Archivos binarios (`fread`, `fwrite`)
  - Manejo de memoria dinamica (`malloc`, `realloc`)
  - Arreglos de estructuras (`struct`)
  - Separación modular por funciones
  - Lógica de carga personalizada
  - Persistencia de datos
## Tecnologías y conceptos usados:
- Lenguaje C
- Punteros y punteros dobles
- Manejo de archivos en modo binario
- Menús en consola
- Validaciones básicas
- Manejo basico de excepciones

## Estructura del código:
- `main.c`: punto de entrada
- `flights.c / flights.h`: gestión de vuelos
- `utils.c / utils.h`: funciones auxiliares
- `data.dat`: archivo binario de persistencia

## Requisitos para compilar
- Lenguaje C
- Archivos binarios (`fread`, `fwrite`)
- Manejo dinámico de memoria (`malloc`, `realloc`)
- Estructuras (`struct`) y punteros
- Compilador GCC
- IDE recomendado: Code::Blocks(http://www.codeblocks.org/) (por su simplicidad para compilar y correr proyectos en C)
