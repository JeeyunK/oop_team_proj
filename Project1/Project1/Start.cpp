#include "Start.h"

Start::Start() {
	choice = 0;
	running = true;
}

Start::~Start() {

}

void Start::mainMenu() {
	cout << "MAIN MENU" << endl << endl;
	cout << "1: Short Writing" << endl;
	cout << "2: Long Writing" << endl;
	cout << "3: Ranking" << endl;
	cout << "4: Options" << endl;
	cout << "5: Quit" << endl;

	cout << endl << "Choice: ";

	cin >> choice;

	switch (choice) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		cout << "What do you want?" << endl;
		break;
	case 5:
		running = false;
		cout << endl << "Bye!";
		break;
	default:
		break;
	}
}

void Start::progressBar() {
	float progress = 0.0;

	while (progress < 1.0) {
		int barWidth = 70;
		cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; i++) {
			if (i < pos)
				cout << "=";
			else if (i == pos)
				cout << ">";
			else
				cout << " ";
		}
		cout << "]" << int(progress * 100.0) << "%\r";
		cout.flush();

		progress += 0.005;
	}
	cout << endl;
}

void Start::fontsizeChange(int x, int y) {
	cout << "Input desire font size in terms of length of X and Y" << endl;

	cin >> x >> y;

	CONSOLE_FONT_INFOEX cfi{};
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = x;
	cfi.dwFontSize.Y = y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);

	cout << "This is a changed font size" << endl;
}