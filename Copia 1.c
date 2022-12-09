#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef enum Mazo
{
    Diamantes,
    Corazones,
    Trebol,
    Pica
} Mazo;

typedef enum Numero
{
    Dos,
    Tres,
    Cuatro,
    Cinco,
    Seis,
    Siete,
    Ocho,
    Nueve,
    Diez,
    Jota,
    Quina,
    Ka,
    As

} Numero;

typedef struct Carta
{
    Mazo mazo;
    Numero numero;
} Carta;

typedef struct Baraja
{
    Carta cartas[52];
    short cartas_repartidas[52];
    int cartas_disponibles;
} Baraja;

Baraja *crear_baraja();
Carta **repartir(Baraja *, int);
void imprimir_baraja(Baraja *);
void imprimir_mano(Carta **, size_t);


Baraja *crear_baraja()
{
    Baraja *baraja = malloc(sizeof(Baraja));

    baraja->cartas_disponibles = 52;
    memset(baraja->cartas_repartidas, 0, 52 * sizeof(short));

    for (int mazo = 0; mazo <= 3; mazo++)
    {
        for (int numero = 0; numero <= 12; numero++)
        {
            int num_carta = (mazo * 13) + numero;
            baraja->cartas[num_carta].mazo = mazo;
            baraja->cartas[num_carta].numero = numero;
        }
    }

    return baraja;
}

Carta **repartir(Baraja *baraja, int cantidad)
{
    if (cantidad > baraja->cartas_disponibles)
    {
        return NULL;
    }

    Carta **cartas_repartidas = malloc(sizeof(Carta *) * cantidad);

    int repartidas = 0;
    while (repartidas < cantidad)
    {
        int carta_aleatoria = rand() % 52;

        if (baraja->cartas_repartidas[carta_aleatoria] == 1)
        {
            continue;
        }

        cartas_repartidas[repartidas] = &baraja->cartas[carta_aleatoria];
        baraja->cartas_repartidas[carta_aleatoria] = 1;
        baraja->cartas_disponibles--;
        repartidas++;
    }

    return cartas_repartidas;
}

void imprimir_baraja(Baraja *baraja)
{
    printf("Baraja (%d):\n", baraja->cartas_disponibles);
    for (int carta = 0; carta < 52; carta++)
    {
        Carta actual = baraja->cartas[carta];
        printf(
            "%d - Numero: %d, Mazo: %d, Repartida?: %d\n",
            carta,
            actual.numero,
            actual.mazo,
            baraja->cartas_repartidas[carta]);
    }
}

void imprimir_mano(Carta **mano, size_t cantidad)
{
    if (mano == NULL)
    {
        printf("Iniciando.\n");
        return;
    }

    for (int carta = 0; carta < cantidad; carta++)
    {
        Carta *actual = mano[carta];
        printf(
            "Numero: %d, Mazo: %d\n",
            actual->numero,
            actual->mazo);
    }
}

void Pedir_Nombre ()
{
    char Nombre;
    printf("Como te llamas?");
    Nombre = scanf("%c", &Nombre);

}

int Evaluador_de_mano (Carta **mano)
{
    int pareja=0, trio=0 , escalera=0, mismo_simbolo=0, poker=0, carta_consecutiva=0, puntos_in_game=0;

    int i;
    int NumMano[13];
    int SimMano[4];
    
    memset(NumMano,0,sizeof(NumMano));
    memset(SimMano,0,sizeof(SimMano));

    for (i=0; i<5; i++)
    {
        NumMano[mano[i] ->numero]++;
        SimMano[mano[i] ->mazo]++;
    }

    int j = SimMano[0];
    int k = SimMano[1];
    int l = SimMano[2];
    int m = SimMano[3];
    int n = SimMano[4];

    if (j == k && k == l && l == m && m == n && n == j )
        mismo_simbolo++;

    i=0;

    while (NumMano[i] == 0)
    {
        i++;
        for(; i < 5 && NumMano[i]; i++)
            carta_consecutiva ++;
        if (carta_consecutiva = 5)
            escalera++;
    }
    
    for (i=0; i <= 13; i++)
    {
        if (NumMano[i] == 4)
            poker++;
        if (NumMano[i] == 3)
            trio++;
        if (NumMano[i] == 2)
            pareja++;  
    }

    if (escalera == 1 && mismo_simbolo == 1)
        puntos_in_game = 8;
    else if (poker == 1)
        puntos_in_game = 7;
    else if (trio == 1 && pareja == 1)
        puntos_in_game = 6;
    else if (escalera == 1)
        puntos_in_game = 5;
    else if (mismo_simbolo == 1)
        puntos_in_game = 4;
    else if (trio == 1)
        puntos_in_game = 3;
    else if (pareja == 2)
        puntos_in_game = 2;
    else if (pareja == 1)
        puntos_in_game = 1;
    else
        puntos_in_game = 0;

    printf("puntos obtenidos: %i.\n", puntos_in_game);
    return (puntos_in_game);
}

int Determinar_ganador (int Puntos1, int Puntos2)
{
    int contador = 0;

    if (Puntos1 > Puntos2)
        printf("El jugador gana!\n");
        contador++;
    if (Puntos1 < Puntos2)
        printf("Gana la computadora!\n");
    else
        printf("Empate!\n");

    return contador;
}

int menu()
{
    //char nombre = Pedir_Nombre ();
    int opcion;
    int Puntos_jugador_1;
    int Puntos_jugador_2;

    do
    {
        //printf("Bienvenido %c, seleccione una opcion\n", nombre);
        printf("Bienvenidso seleccione una ocion:\n");
        printf("1 - jugar\n");
        printf("2 - puntuaciones\n");
        printf("3 - salir\n");
        scanf("%i", &opcion);
        
        switch(opcion)
        {
            case 1:
            printf("opcion 1 seleccionada\n");
            srand(time(0));

            Baraja *baraja = crear_baraja();
            // imprimir_baraja(baraja);

            Carta **mano = repartir(baraja, 53); // mano == NULL
            imprimir_mano(mano, 53);

            Carta **mano2 = repartir(baraja, 5);
            printf("La mano del jugador 1 es:\n");
            imprimir_mano(mano2, 5);
            Puntos_jugador_1 = Evaluador_de_mano (mano2);

            Carta **mano3 = repartir(baraja, 5);
            printf("La mano del jugador 2 es:\n");
            imprimir_mano(mano3, 5);
            Puntos_jugador_2 = Evaluador_de_mano (mano3);
            
            Determinar_ganador(Puntos_jugador_1, Puntos_jugador_2);

            break;

            case 2:
            printf("opcion 2 seleccionada\n");
            printf(contador);
            break;
            case 3:
            printf("Gracias por jugar\n");
            break;
            default:
            printf("error, intente de nuevo\n");
            break;
        }

    } while (opcion != 3);
    
    return 0;
}

int main()
{
    menu();

}