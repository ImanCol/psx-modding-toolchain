#ifndef COMMON_H
#define COMMON_H

struct Vec3
{
    int x;
    int z;
    int y;
};

// Estructura para almacenar colores RGB
typedef struct {
  int r;
  int g;
  int b;
} Color;

typedef struct {		/* short word type 3D vector */	
	short	vx, vy;
	short	vz, pad;
} SVECTOR;

int sprintf(char * str, char * format, ...);

//void MENU_Color(int r,int g,int b); //MGS
void MENU_Color(int r,int g,int b); //V8SO
//void MENU_Locate(short x,short y, short size); //MGS
void MENU_Locate(int *_unknow,char * text, short position, int size); //V8SO:(int _,char Text,short (X(2byte). Y(2byte)) , uint size) Imprime y Posiciona el texto
void DrawText(int *_unknow,char * text, short position, int size); //V8SO:(int _,char Text,short (X(2byte). Y(2byte)) , uint size) Imprime y Posiciona el texto
extern int postString;


//undefined return LINE_F4* pLine
void MENU_Printf(char * text, ...);


extern int offset;
extern int PlayerPostOffset;

void DrawInfo(short X, short Y, short size, Color rgb, char *cText);

#endif