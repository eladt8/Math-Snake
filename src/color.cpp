#include "color.h"

void setTextColor(int foreground, int background)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, foreground % 0x10 | (background % 0x10) * 0x10);
}
