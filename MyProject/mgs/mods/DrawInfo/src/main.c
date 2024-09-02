#include <common.h>
#include "math.h"



// Definición de la resolución de la pantalla
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Definición de los límites de movimiento
#define MIN_X -155
#define MAX_X 123
#define MIN_Y -120
#define MAX_Y 97

// Definición de la velocidad de movimiento
#define SPEED_X 2
#define SPEED_Y 2

// Estructura para almacenar colores RGB
typedef struct {
    int r;
    int g;
    int b;
} Color;


// Implementación de un generador de números pseudoaleatorios
unsigned int seed = 1;

unsigned int simple_rand() {
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 32768;
}

Color current_color = {255, 0, 0};  // Color inicial (Rojo)

// Función para cambiar de color al azar
void change_color() {
    current_color.r = simple_rand() % 256;
    current_color.g = simple_rand() % 256;
    current_color.b = simple_rand() % 256;
}

// Función para imprimir el color ANSI basado en RGB
void print_color() {
    //printf("\033[38;2;%d;%d;%dm", current_color.r, current_color.g, current_color.b);
}


int set = -120;

int x = 0, y = 0;  // Posición inicial
int dx = SPEED_X, dy = SPEED_Y;  // Dirección de movimiento

//void item_act_80033784(ItemWork *work)
void DrawInfo()
{

//printf("%i\n", *ptr);

    // Actualizar posición
    x += dx;
    y += dy;

    // Verificar colisiones y cambiar color si es necesario
    if (x >= MAX_X || x <= MIN_X) {
        dx = -dx;
        change_color();
    }
    if (y >= MAX_Y || y <= MIN_Y) {
        dy = -dy;
        change_color();
    }

    //int getinfo = lseek(1, 0x800ae318,  1)
    
	if (set > 100   )
	{
		set = -120;
	}

	set += 1;

    //amerinca.txt : offset = 0x800ae318
    unsigned int * PlayerPointer = (unsigned int *) offset; // get Pointer Player Position
    unsigned int * PlayerAddrsXY = PlayerPointer + 0x8; //set offset X Y Position
    unsigned int * PlayerAddrstZ = PlayerPointer + 0x9; //set offset Z Position
    unsigned int PlayerPostXY = *PlayerAddrsXY; //get Value X Y Position
    unsigned int PlayerPostZ = *PlayerAddrstZ; //get Value Z Position

    // Dividir el valor en dos partes de 2 bytes (16 bits)
    unsigned int PlayerX = (PlayerPostXY >> 16) & 0xFFFF; // Parte alta (16 bits más significativos)
    unsigned int PlayerY = PlayerPostXY & 0xFFFF;          // Parte baja (16 bits menos significativos)
    unsigned int PlayerZ = PlayerPostZ & 0xFFFF;          // Parte baja (16 bits menos significativos)


	//MENU_Color(0xff,0x30,0x30);
	MENU_Color(255,255,255);
	MENU_Locate(0x7f, 0x8,0x1);
	//MENU_Printf("%s 0x%d",pcVar5, SnakePostOffset);
	//MENU_Printf("Addrs:  0x%X Pointer:  0x%X Value: 0x%X",PlayerX, PlayerY, PlayerZ);
	MENU_Printf("Player Position\n X: %d Y: %d Z: %d \n Color: %X",PlayerX, PlayerY, PlayerZ, current_color);
	menu_Text_Init();

	//unsigned int off = (unsigned int) offset;
	//off = sqrt(off);
	char * pcVar5 =("HIDEO");
	short puVar6 = set;
	//MENU_Color(0xff,0x30,0x30);
	MENU_Color(255,255,255);
	//MENU_Locate(*(short *)(puVar7 + 0x10) + 0xa0,*(short *)(puVar7 + 0x12) + 0x68,0x12);
	//MENU_Locate(PlayerX, PlayerY, 0x1);
	//MENU_Printf("%s 0x%d",pcVar5, SnakePostOffset);
	//MENU_Printf("Addrs:  0x%X Pointer:  0x%X Value: 0x%X",PlayerX, PlayerY, PlayerZ);
	MENU_Printf(pcVar5);
	menu_Text_Init();

	//MENU_Color(0xff,0x30,0x30);
	MENU_Color(current_color.r,current_color.g,current_color.b);
	MENU_Locate((x + 0x10) + 0xa0,(y + 0x12) + 0x68,0x12);
	//MENU_Printf("%s 0x%d",pcVar5, SnakePostOffset);
	MENU_Printf("%s",pcVar5);
	menu_Text_Init();

	//Ground black
	MENU_Color(1,1,1);
	//MENU_Locate((puVar6 + 0x10) + 0xa1,(puVar6 + 0x12) + 0x69,0x12);
	MENU_Locate((x + 0x10) + 0xa1,(y + 0x12) + 0x69,0x12);
	//MENU_Printf("%s 0x%08X",pcVar5, SnakePostOffset);
	MENU_Printf("%s",pcVar5);
	
	menu_Text_Init();
}

void SnakeTag()
{
    Color rgb;

    int iVar3;
char * uVar11;
    rgb.r = 0xff;
    rgb.g = 0x30;
    rgb.b = 0x30;
    short sStack_38;
    short sStack_36;
    
    iVar3 = gte_info(&sStack_38,offset + 0x20);
    
    //sStack_36 = sStack_36 - *(short *)(offset + 0x110);

    MENU_Color(rgb.r,rgb.g,rgb.b);
    MENU_Locate(sStack_38 + 0xa0,sStack_36 + 0x68,0x12);
    MENU_Printf(uVar11);
    MENU_Color(1,1,1);
    MENU_Locate(sStack_38 + 0xa1,sStack_36 + 0x69,0x12);
    MENU_Printf(uVar11);
    menu_Text_Init();
}