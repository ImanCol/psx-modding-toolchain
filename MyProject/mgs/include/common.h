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

void MENU_Color(int r,int g,int b);
void MENU_Locate(short x,short y, short size);

//undefined return LINE_F4* pLine
void MENU_Printf(char * text, ...);
void menu_Text_Init();

//bool gte_info(long *param_1, SVECTOR *param_2);
int gte_info(long *param_1, SVECTOR *param_2);

extern struct Vec3 position;

extern int offset;
extern int PlayerPostOffset;


//declare another functions...
void SnakeTag();
void DrawInfo(short X, short Y, short size, Color rgb, char *cText);

#endif