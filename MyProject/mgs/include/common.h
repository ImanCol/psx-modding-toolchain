#ifndef COMMON_H
#define COMMON_H

struct Vec3
{
    int x;
    int z;
    int y;
};

void MENU_Color(int r,int g,int b);
void MENU_Locate(short param_1,short param_2, short param_3);

//undefined return LINE_F4* pLine
void MENU_Printf(char * text, ...);
void menu_Text_Init();

extern struct Vec3 position;
extern struct Vec3 SVECTOR;

extern int offset;
extern int PlayerPostOffset;

#endif