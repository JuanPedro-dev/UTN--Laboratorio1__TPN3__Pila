#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include "../Librerias/pila.h"
#include <math.h> // Necesario para sacar potencia en el 10.!!!!

/** Extra:
    Realizar una función que cargue la pila sin utilizar la función leer.
    Realizar una función que muestre la pila sin utilizar la función mostrar.*/
void cargarPila(Pila * pilaInput)
{
    int input;
    char option;
    do
    {
        printf("Ingrese valor para la pila: ");
        fflush(stdin);
        scanf("%i", &input);
        apilar(pilaInput, input);
        printf("¿Desea ingresar otro? n/N: no, otro: si --> ");
        fflush(stdin);
        scanf("%c", &option);
    }
    while(option !='n' && option!='N');
}

void verPila(Pila pilaInput)
{
    int output;
    Pila aux;
    inicpila(&aux);

    while(!pilavacia(&pilaInput))
    {
        apilar(&aux, desapilar(&pilaInput));
    }


    printf("      Base Pila--> ");
    while(!pilavacia(&aux))
    {
        output = desapilar(&aux);
        printf("| %i ", output);
    }
    printf("|<-- Tope Pila\n");
}

/** Extra pila random de 0 a 100*/
void pilaRandom(Pila * pilaInput,const int DIM)
{
    for(int i = 1; i<=DIM;i++ )
    {
        apilar(pilaInput, rand()%100);
    }
}


/** 1. Hacer una función que permita ingresar varios elementos a una pila, tanto como quiera el usuario.
  -->  como ya he creado cargarPila() para variar voy a crear una que diga la cantidad e ir ingresando*/
void nCargaSPila(Pila * pilaInput, const int cantidad)
{
    int input;
    char option;
    for(int i = 1; i <= cantidad; i++)
    {
        printf("Ingrese el %iº valor para la pila: ", i);
        fflush(stdin);
        scanf("%i", &input);
        apilar(pilaInput, input);
    }
}

/** 2. Hacer una función que pase todos los elementos de una pila a otra.*/
void pasarPila(Pila * pilaInput, Pila * pilaOutput)
{
    while(!pilavacia(pilaInput))
    {
        apilar(pilaOutput, desapilar(pilaInput));
    }
}

/** 3. Hacer una función que pase todos los elementos de una pila a otra, pero conservando el orden. */
// Clono y elimino en origen
void trasladarAPila(Pila * pilaInput, Pila * pilaOutput)
{
    Pila aux;
    inicpila(&aux);
    pasarPila(pilaInput,&aux);
    pasarPila(&aux,pilaOutput);
}

/** 4. Hacer una función que encuentre el menor elemento de una pila y lo retorna. La misma debe eliminar ese dato de la pila.*/
// intento modularizar mas aun generando una función que busque el menor y otra que lo elimine.

int minimoPila (Pila * pilaInput)
{
    int menor;
    Pila aux;
    inicpila(&aux);
    menor = tope(pilaInput);

    while(!pilavacia(pilaInput))
    {
        if(tope(pilaInput) < menor)
        {
            menor = tope(pilaInput);
            apilar(&aux,desapilar(pilaInput));
        }
        else
        {
            apilar(&aux,desapilar(pilaInput));
        }
    }
    pasarPila(&aux, pilaInput);
    return menor;
}

int eliminarMenor(Pila * pilainput)
{
    Pila aux;
    inicpila(&aux);
    int menor;
    menor = minimoPila(pilainput);
    while(!pilavacia(pilainput))
    {
        if(tope(pilainput) == menor)
        {
            desapilar(pilainput);
        }
        else
        {
            apilar(&aux, desapilar(pilainput));
        }
    }
    pasarPila(&aux, pilainput);
    return menor;
}
/** 5. Hacer una función que pase los elementos de una pila a otra, de manera que se genere una nueva
    pila ordenada. Usar la función del ejercicio 4. (Ordenamiento por selección)*/
Pila ordenarSeleccion(Pila * origen,Pila * destino)
{
    while(!pilavacia(origen))
    {
        apilar(destino, eliminarMenor(origen));
    }
}
/** 6. Hacer una función que inserta en una pila ordenada un nuevo elemento, conservando el orden de ésta. */
void insertarElementoEnPila(Pila * origen, const int elemento)
{
    Pila auxiliar;
    inicpila(&auxiliar);
    int flagInsertado = 0;
    while(!pilavacia(origen) && flagInsertado == 0)
    {
        if(tope(origen) < elemento)
        {
            apilar(&auxiliar, desapilar(origen));
        } else
        {
            apilar(origen, elemento);
            flagInsertado = 1;
        }
    }
    // Si no se inserto es porque es mayor a todos y va en la base.
    if(flagInsertado == 0)
    {
        apilar(origen, elemento);
    }
    // Si hay ya se inserto simplemente devuelvo los valores que quedaron en auxiliar,
    while(!pilavacia(&auxiliar))
    {
        apilar(origen, desapilar(&auxiliar));
    }
}
/** 7. Hacer una función que pase los elementos de una pila a otra, de manera que se genere una nueva pila
ordenada. Usar la función del ejercicio 6.  (Ordenamiento por inserción)*/

void ordenarInsercion(Pila * pilaInput, Pila * pilaOutput)
{
    if(!pilavacia(pilaInput))
    {
        apilar(pilaOutput, desapilar(pilaInput));
    }
    while(!pilavacia(pilaInput))
    {
        insertarElementoEnPila(pilaOutput, desapilar(pilaInput));
    }
}

/** 8. Hacer una función que sume y retorne los dos primeros elementos de una pila (tope y anterior), sin alterar su contenido. */

int sumarUltimoConAnterior(Pila pilaInput)
{
    int acumulador = 0;
    if(!pilavacia(&pilaInput))
    {
        acumulador += tope(&pilaInput);
        desapilar(&pilaInput);
        if(!pilavacia(&pilaInput))
        {
            acumulador += tope(&pilaInput);
        }
    }
    return acumulador;
}

/** 9. Hacer una función que calcule el promedio de los elementos de una pila,
    para ello hacer también una función que calcule la suma, otra para la cuenta y otra que divida.
    En total son cuatro funciones, y la función que calcula el promedio invoca a las otras 3. */
int sumatoriaPila(Pila pilaInput) // Paso por valor para no modificar la original
{
    int acumulador = 0;
    while(!pilavacia(&pilaInput))
    {
        acumulador += tope(&pilaInput);
        desapilar(&pilaInput);
    }
    return acumulador;
}
int contadorElementosPila(Pila pilaInput) // Paso por valor para no modificar la original
{
    int contador = 0;
    while(!pilavacia(&pilaInput))
    {
        contador ++;
        desapilar(&pilaInput);
    }
    return contador;
}
float dividir(int suma, int cantidad)
{
    float division = (suma * 1.0) /cantidad;
    return division;
}
float promedioElementosPila(Pila pilainput)
{
    return dividir(sumatoriaPila(pilainput), contadorElementosPila(pilainput));
}

/** 10. Hacer una función que reciba una pila con números de un solo dígito (es
responsabilidad de quien usa el programa) y que transforme esos dígitos en un número decimal*/

void pilaRandomUnDigito(Pila * pilaInput,const int DIM)
{
    for(int i = 0; i < DIM ; i++)
    {
        apilar(pilaInput, rand()%10);
    }
}

int generarNumero(Pila pilaInput)
{
    int acumulador = 0;
    int base;
    int digitos = 1;
    int numero;
    Pila auxiliar;
    inicpila(&auxiliar);

    while(!pilavacia(&pilaInput))
    {
        apilar(&auxiliar, desapilar(&pilaInput));
    }

    while(!pilavacia(&auxiliar))
    {
        base = tope(&auxiliar);
        numero = base * digitos;
        acumulador += numero;
        digitos *= 10;
        desapilar(&auxiliar);
    }
    return acumulador;
}



// Menu
void menu()
{
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    Sleep(50);
    printf("//                                                                                                            //\n");
    Sleep(50);
    printf("//                                     TPN3 - Funciones con pilas                                             //\n");
    Sleep(50);
    printf("//                                                                                                            //\n");
    Sleep(50);
    printf("//  int main (ejercicio)                                                                                      //\n");
    Sleep(50);
    printf("//  {                                                                                                         //\n");
    Sleep(50);
    printf("//      int opción A = 'Cargar indefinida de elementos a una Pila';                                           //\n");
    Sleep(50);
    printf("//      int opción B = 'Pasar todos los elementos de una pila a otra(invertida).';                            //\n");
    Sleep(50);
    printf("//      int opción C = 'Pasar todos los elementos de una pila a otra(conservar el orden)';                    //\n");
    Sleep(50);
    printf("//      int opción D = 'Encuentre y elimine el menor elemento de una pila y retornarlo';                      //\n");
    Sleep(50);
    printf("//      int opción E = 'Pasar y ordenar a una pila (Ordenamiento por selección)';                             //\n");
    Sleep(50);
    printf("//      int opción F = 'Insertar en una pila ordenada un nuevo elemento, conservando su orden.';              //\n");
    Sleep(50);
    printf("//      int opción G = 'Pasar y ordenar a una pila (Ordenamiento por Inserción)';                             //\n");
    Sleep(50);
    printf("//      int opción H = 'Retornar la suma de los dos primeros elementos de una pila (tope y anterior)';        //\n");
    Sleep(50);
    printf("//      int opción I = 'Promedio de los elementos de una pila';                                               //\n");
    Sleep(50);
    printf("//      int opción J = 'Forma un número con todos los elementos de la pila';                                  //\n");
    Sleep(50);
    printf("//  }                                                                                                         //\n");
    Sleep(50);
    printf("//        /////////  //      //    //////////   //      //         //      //   //////////  //      //        //\n");
    Sleep(50);
    printf("//               //  //      //    //      //   ///     //         //      //       //      ///     //        //\n");
    Sleep(50);
    printf("//               //  //      //    //      //   //  /   //         //      //       //      //  /   //        //\n");
    Sleep(50);
    printf("//               //  //      //    //      //   //  /   //         //      //       //      //  /   //        //\n");
    Sleep(50);
    printf("//       //      //  //      //    //////////   //   /  //         //      //       //      //   /  //        //\n");
    Sleep(50);
    printf("//       //      //  //      //    //      //   //    / //         //      //       //      //    / //        //\n");
    Sleep(50);
    printf("//       //      //  //      //    //      //   //     ///         //      //       //      //     ///        //\n");
    Sleep(50);
    printf("//       //////////  //////////    //      //   //      //         //////////       //      //      //        //\n");
    Sleep(50);
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    Sleep(50);
    printf("\n                                Tu entrada (Terminar Programa: s o S): ");
}

// Son 10 puntos
int main()
{
    setlocale(LC_ALL,"");
    system("color 3e");
    srand(time(NULL));
    char option;

    do
    {
        system("cls");
        menu();
        fflush(stdin);
        scanf("%c", &option);

        switch(option)
        {
        case 'a':
        case 'A':
            do
            {
                system("cls");
                Pila DADA;
                inicpila(&DADA);
                printf("\n                    opción A = 'Cargar indefinida de elementos a una Pila'\n\n") ;
                cargarPila(&DADA);
                printf("\n    La pila cargada quedo: \n\n   ");
                verPila(DADA);

                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción A: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');

            break;
        case 'b':
        case 'B':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandom(&origen, 5);
                Pila destino;
                inicpila(&destino);
                printf("\n                    opción B = 'Pasar todos los elementos de una pila a otra'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Vamos a pasarla a una pila destino. \n\n   ");
                pasarPila(&origen, &destino);
                printf("\n    Pila origen. \n\n   ");
                verPila(origen);
                printf("\n    Pila destino. \n\n   ");
                verPila(destino);                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción B: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'c':
        case 'C':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandom(&origen, 5);
                Pila destino;
                inicpila(&destino);
                printf("\n                    opción C = 'Pasar todos los elementos de una pila a otra(conservar el orden)'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Vamos a pasarla a una pila destino. \n\n   ");
                trasladarAPila(&origen, &destino);
                printf("\n    Pila origen. \n\n   ");
                verPila(origen);
                printf("\n    Pila destino. \n\n   ");
                verPila(destino);                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción C: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'd':
        case 'D':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandom(&origen, 5);
                printf("\n                    opción D = 'Encuentre y elimine el menor elemento de una pila y retornarlo'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función. \n\n   ");
                printf(">> El elemento eliminado fue: %i",eliminarMenor(&origen));
                printf("\n    Pila origen. \n\n   ");
                verPila(origen);
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción D: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'e':
        case 'E':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                Pila destino;
                inicpila(&destino);

                pilaRandom(&origen, 5);

                printf("\n                    opción E = 'Pasar y ordenar a una pila (Ordenamiento por selección)'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función. \n\n   ");
                ordenarSeleccion(&origen, &destino);
                printf("\n    Pila origen. \n\n   ");
                verPila(origen);
                printf("\n    Pila destino. \n\n   ");
                verPila(destino);
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción E: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'f':
        case 'F':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                Pila auxiliar;
                inicpila(&auxiliar);

                pilaRandom(&origen, 5);
                ordenarSeleccion(&origen, &auxiliar);
                pasarPila(&auxiliar, &origen);

                int numeroRandom = rand() % 100;

                printf("\n                    opción F = 'Insertar en una pila ordenada un nuevo elemento, conservando su orden. '\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random) y ordenada: \n\n   ");

                verPila(origen);
                printf("\n    Veamos los resultados de la función insertando el número random: %d. \n\n   ", numeroRandom);

                insertarElementoEnPila(&origen, numeroRandom);

                printf("\n    Pila origen (con el elemento nuevo). \n\n   ");
                verPila(origen);
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción F: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'g':
        case 'G':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                Pila destino;
                inicpila(&destino);

                pilaRandom(&origen, 5);

                int numeroRandom = rand() % 100;

                printf("\n                    opción G = 'Pasar y ordenar a una pila (Ordenamiento por Inserción)'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función falta hacer: \n\n   ");
                ordenarInsercion(&origen, &destino );

                printf("\n    Pila destino ordenada. \n\n   ");
                verPila(destino);
                printf("\n    Pila origen vacia. \n\n   ");
                verPila(origen);

                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción G: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'h':
        case 'H':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandom(&origen, 5);

                printf("\n                    opción H = 'Retornar la suma de los dos primeros elementos de una pila (tope y anterior)'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función: \n\n   ");

                printf("\n    >> La suma de los ultimos 2 valores es: %d. \n\n   ", sumarUltimoConAnterior(origen));
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción H: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'i':
        case 'I':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandom(&origen, 5);

                printf("\n                    opción I = 'Promedio de los elementos de una pila'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random): \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función: \n\n   ");

                printf("\n    >> El promedio de la pila es: %.2f. \n\n   ", promedioElementosPila(origen));
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción I: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;
        case 'j':
        case 'J':
            do
            {
                system("cls");
                Pila origen;
                inicpila(&origen);
                pilaRandomUnDigito(&origen, 5);

                printf("\n                    opción J = 'Forma un número con todos los elementos de la pila'\n\n") ;
                printf("\n    Usando la siguiente pila origen generada (random) con valores entre 0 y 9: \n\n   ");
                verPila(origen);
                printf("\n    Veamos los resultados de la función: \n\n   ");

                printf("\n    >> El número generado de la concatenación es: %d. \n\n   ",generarNumero(origen));
                printf("\n\n    Volver al menu: v , Salir del programa: 's',  Repetir opción J: otra tecla. ") ;
                fflush(stdin);
                scanf("%c", &option);
            }while(option !='v' && option !='V' && option !='s' && option !='S');
            break;

    }
    }while(option!='s' && option!='S');
    printf("\n\n 'Si la depuración es el proceso de eliminar errores, entonces la programación debe ser el proceso de introducirlos.' \n    -- Edsger W. Dijkstra\n");

    system("pause");
    return 0;
}
