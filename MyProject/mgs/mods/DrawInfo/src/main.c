#include "math.h"
#include "../../../include/common.h"

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

// Implementación de un generador de números pseudoaleatorios
unsigned int seed = 1;

unsigned int simple_rand() {
  seed = seed * 1103515245 + 12345;
  return (seed / 65536) % 32768;
}

Color current_color = {255, 0, 0}; // Color inicial (Rojo)

// Función para cambiar de color al azar
void change_color() {
  current_color.r = simple_rand() % 256;
  current_color.g = simple_rand() % 256;
  current_color.b = simple_rand() % 256;
}

// Función para imprimir el color ANSI basado en RGB
void print_color() {
  // printf("\033[38;2;%d;%d;%dm", current_color.r, current_color.g,
  // current_color.b);
}

int set = -120;

int x = 0, y = 0;               // Posición inicial
int dx = SPEED_X, dy = SPEED_Y; // Dirección de movimiento

// void item_act_80033784(ItemWork *work)
void Init() {

  // printf("%i\n", *ptr);

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

  // int getinfo = lseek(1, 0x800ae318,  1)

  if (set > 100) {
    set = -120;
  }

  set += 1;

  // amerinca.txt : offset = 0x800ae318
  unsigned int *PlayerPointer =
      (unsigned int *)offset; // get Pointer Player Position
  unsigned int *PlayerAddrsXY = PlayerPointer + 0x8; // set offset X Y Position
  unsigned int *PlayerAddrstZ = PlayerPointer + 0x9; // set offset Z Position
  unsigned int PlayerPostXY = *PlayerAddrsXY;        // get Value X Y Position
  unsigned int PlayerPostZ = *PlayerAddrstZ;         // get Value Z Position

  // Dividir el valor en dos partes de 2 bytes (16 bits)
  unsigned int PlayerX =
      (PlayerPostXY >> 16) & 0xFFFF; // Parte alta (16 bits más significativos)
  unsigned int PlayerY =
      PlayerPostXY & 0xFFFF; // Parte baja (16 bits menos significativos)
  unsigned int PlayerZ =
      PlayerPostZ & 0xFFFF; // Parte baja (16 bits menos significativos)

  // Snake Info
  Color rgb2 = {255, 255, 255};
  // Formatear el texto
  char buffer[64];
  sprintf(buffer, "Snake\n X: %d Y: %d Z: %d \n", PlayerX, PlayerY, PlayerZ);
  // Usar la función directamente con los valores que tienes
  DrawInfo(0x8f, 0xd0, 0x1, rgb2, buffer);

  // HIDEO
  char *pcVar5 = ("HIDEO");
  DrawInfo((x + 0x10) + 0xa0, (y + 0x12) + 0x68, 0x12, current_color, pcVar5);

  // Ground black
  Color rgb3 = {1, 1, 1};
  DrawInfo((x + 0x10) + 0xa1, (y + 0x12) + 0x69, 0x12, rgb3, pcVar5);

  SnakeTag(PlayerX, PlayerY, PlayerZ);
  return;
}

void SnakeTag(int X, int Y, int Z) {
  unsigned int *PlayerPointer =
      (unsigned int *)offset; // get Pointer Player Position

  Color rgb;

  int isLook = 0;

  char *uVar11 = ("IMAN");

  rgb.r = 0xff;
  rgb.g = 0x30;
  rgb.b = 0x30;
  long sStack_38;
  short sStack_36 = 0;

  SVECTOR textPost = {Y, X, Z, 1000};

  isLook = gte_info((long *)&sStack_38, &textPost); // inverter SVECTOR?
  sStack_36 = sStack_36 - *(short *)(offset + 0x110);

  if (isLook != 0) {
    // Call Drawinfo
  }

  unsigned int PostX =
      sStack_38 & 0xFFFF; // Parte baja (16 bits menos significativos)
  unsigned int PostY =
      (sStack_38 >> 16) & 0xFFFF; // Parte alta (16 bits más significativos)

Color modrgb = {255,200,152};
  DrawInfo(PostX + 0xa6, PostY + 0x58, 0x1, rgb, "SNAKE");
  DrawInfo(0x13a,0xd8, 0x1, modrgb, "Mod by: ImanCol");
}

void DrawInfo(short X, short Y, short size, Color rgb, char *cText /*, ...*/) {

  /*
// Formatear el texto
char buffer[64];
sprintf(buffer, cText);
*/

  MENU_Color(rgb.r, rgb.g, rgb.b);
  MENU_Locate(X, Y, size);
  MENU_Printf(cText);
  menu_Text_Init();
}