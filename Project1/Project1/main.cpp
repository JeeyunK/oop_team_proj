#include "ingame.h"


int main() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	UserInterface start;
	start.load_info();
	return 0;
}