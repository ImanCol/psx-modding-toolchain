#include <common.h>
#include "math.h"

char buffer[64];

void DrawSpeedometer()
{
	if (gameMode == 0)
	{
		unsigned int horSpeed = (unsigned int) ((speed.x * speed.x) + (speed.z * speed.z));
		horSpeed = sqrt(horSpeed);
		int verSpeed = speed.y;
		sprintf(buffer, "Hor Speed: %u", horSpeed);
		DrawText(buffer, 0xB0, 0x15, 1, 0);
		sprintf(buffer, "Ver Speed: %d", verSpeed);
		DrawText(buffer, 0xB0, 0x35, 1, 0);
	}
	sprintf(buffer, "Game mode: %u", gameMode);
	DrawText(buffer, 0xB0, 0x25, 0.5, 0);
}