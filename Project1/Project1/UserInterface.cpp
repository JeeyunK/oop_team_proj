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
bool UserInterface::basic_out() {
	bool check = load_written();
	if (check) return true;

	system("cls");
	cout << "\nStart game after 3 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	cout << "\nStart game after 2 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	cout << "\nStart game after 1 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	int i = 0;
	//in_sentence();
	int qsize = _writtenQueue.size();
	while (!_writtenQueue.empty()) {
		float prog = ((float)i / (float)qsize);
		progressBar(prog);
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
	return false;
}

void UserInterface::choose_option() {
	int option_choice = 0;
	system("cls");
	cout << "\nWhat do you want?" << endl;
	cout << "1: Font Size Change" << endl;
	cout << "2: Insert the Game File" << endl;
	cout << "3: Go back" << endl;
option_loop:
	cout << endl << "Choice: ";
	cin >> option_choice;

	switch (option_choice) {
	case 1:
		system("cls");
		fontsizeChange();
		cout << "\n\nWhat do you want now?" << endl;
		Sleep(2000);
		break;
	case 2:
		system("cls");
		std::cin.ignore(32767, '\n');
		_file.get_file();
		cout << "\n\nWhat do you want now?" << endl;
		Sleep(2000);
		break;
	case 3:
		system("cls");
		break;
	default:
		cout << "Please enter the number in the list" << endl;
		goto option_loop;
		break;
	}
}

void UserInterface::load_info() {
	//Score score;
	_file.update_filepath();
	_score.update_score();
	cout << "\nPlease insert your name : ";
	getline(cin, _userInfo);
choice_loop:
	cout << "MAIN MENU" << endl << endl;
menu:
	cout << "1: Short Writing" << endl;
	cout << "2: Long Writing" << endl;
	cout << "3: Ranking" << endl;
	cout << "4: Options" << endl;
	cout << "5: Quit" << endl;
	cout << endl << "Choice: ";

	cin >> choice;
	bool check;
	switch (choice) {
	case 1:
		check = basic_out();
		if (check) break;
		cout << "Great job! " << endl;
		cout << "           Your Score" << endl;
		cout << "Correctness : " << _entireCorrectness << " Speed : " << tot_letters / _entireTime * 60 << endl;
		_score.add_score(_userInfo, _entireCorrectness, tot_letters / _entireTime * 60);
		reset_score();
		//cout << "Ranking is updated.\n" << endl;
		cout << "\nWhat do you want to now?" << endl;
		goto menu;
		break;
	case 2:
		break;
	case 3:
		system("cls");
		//_score.update_score();
		_score.show_Score();
		cout << "\n\nWhat do you want to now?" << endl;
		goto menu;
		break;
	case 4:
		choose_option();
		break;
	case 5:
		system("cls");
		running = false;
		cout << endl << "Bye!";
		return;
	default:
		system("cls");
		cout << "\nPlease enter the number in the list" << endl;
		//goto choice_loop;
		break;
	}
	goto choice_loop;


	//cout << "entire correct : " << _entireCorrect << endl;
}


void UserInterface::progressBar(float progress) {
	//float progress = 0.0;
	//while (progress < 1.0) {
	//cout << progress;
	int barWidth = 50;
	cout << "\n progress : [";
	int pos = (barWidth * progress);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos)
			cout << "=";
		else if (i == pos)
			cout << ">";
		else
			cout << " ";
	}
	cout << "] " << int(progress * 100.0) << "%\r";
	cout.flush();	
	cout << endl;
}

void UserInterface::fontsizeChange() {
	int x, y;
	cout << "\nInput desire font size in terms of length of X and Y" << endl;

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

void UserInterface::reset_score() {
	correct = 0;
	wrong = 0;
	tot_letters = 0;
	user_correctness = 0;

	_entireCorrectness = 0;
	_entireTime = 0;
}