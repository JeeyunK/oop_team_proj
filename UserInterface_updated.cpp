#include "ingame.h"
#include "Score.h"
#include "Start.h"

UserInterface::UserInterface() {
	_userInfo = "";
	_entireCorrectness = 0;
	_entireTime = 0;
	choice = 0;
	running = true;
}

//
void UserInterface::basic_out() {
	load_written();
	system("cls");
	cout << "Start game after 3 seconds!!" << endl;
	Sleep(3000);
	system("cls");
	int i = 0;
	//in_sentence();
	while (!_writtenQueue.empty()) {
		i++;
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << tot_letters / _entireTime * 60 << endl;
		cout << i << ". " << _writtenQueue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		_entireTime += _userTime;
		_entireCorrectness = check_info(_writtenQueue, _userSentence);
		_writtenQueue.pop();
	}
}

void UserInterface::load_info() {
	Score score;
	int option_choice = 0;

choice_loop:
	cout << "Please insert your name : ";
	getline(cin, _userInfo);
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
		basic_out();
		cout << "Great job! " << endl;
		cout << "           Your Score" << endl;
		cout << "Correctness : " << _entireCorrectness << " Speed : " << tot_letters / _entireTime * 60 << endl;
		score.Write_score(_userInfo, _entireCorrectness, tot_letters / _entireTime * 60);
		score.update_score();
		cout << "Ranking is updated." << endl;
		break;
	case 2:
		break;
	case 3:
		score.update_score();
		score.show_Score();
		break;
	case 4:
		cout << "What do you want?" << endl;
		cout << "1: Font Size Change" << endl;
		cout << "2: Go back" << endl;

		option_loop:

		cout << endl << "Choice: ";
		cin >> option_choice;

		switch (option_choice) {
		case 1:
			fontsizeChange();
			goto choice_loop;
			break;
		case 2:
			goto choice_loop;
		default:
			cout << "Please enter the number in the list" << endl;
			goto option_loop;
			break;
		}
		break;
	case 5:
		running = false;
		cout << endl << "Bye!";
		break;
	default:
		cout << "Please enter the number in the list" << endl;
		goto choice_loop;
		break;
	}



	//cout << "entire correct : " << _entireCorrect << endl;
}


void UserInterface::progressBar() {
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

void UserInterface::fontsizeChange() {
	int x, y;
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