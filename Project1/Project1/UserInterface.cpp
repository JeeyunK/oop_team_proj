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

bool UserInterface::load_shortwriting(int tag) {
retry:
	_file.update_filepath(tag);
	cout << "Please select number" << endl;
	_file.show_list();
	cout << "0. goto main menu" << endl;
	cout << "Choice :";
	cin >> _writtenNum;
	if (cin.fail()) {
		reset_input();
		goto retry;
	}
	if (_writtenNum > _file.size) {
		system("cls");
		cout << "\nPlease enter the number in the list" << endl;
		goto retry;
	}
	if (_writtenNum == 0) {
		system("cls");
		return true;
	}
	if (load_written()) goto retry;
	Sleep(10);
	return false;
}


//
bool UserInterface::basic_out(int tag) {

	bool check = load_shortwriting(tag);
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
	string lastWrittenSentece;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!_writtenQueue.empty()) {
		float prog = ((float)i / (float)qsize);
		progressBar(prog);
		i++;
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << tot_letters / _entireTime * 60 << endl;
		if (i > 1) {
			cout << i - 1 << ". " << lastWrittenSentece << endl;
			cout << " -> ";
			for (int j = 0; j < _userSentence.size(); j++) {
				int wrongIndex = -1;
				if (!_wrongLetterIndex.empty()) {
					wrongIndex = _wrongLetterIndex.front();
				}
				if (wrongIndex == j) {
					SetConsoleTextAttribute(hConsole, 12);
					cout << _userSentence[j];
					_wrongLetterIndex.pop();
				}
				else {
					SetConsoleTextAttribute(hConsole, 15);
					cout << _userSentence[j];
				}
			}
			SetConsoleTextAttribute(hConsole, 15);
			cout << endl;
		}
		cout << i << ". " << _writtenQueue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		_entireTime += _userTime;
		_entireCorrectness = check_info(_writtenQueue, _userSentence);
		lastWrittenSentece = _writtenQueue.front();
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
		reset_input();
		goto option_loop;
		break;
	}
}

void UserInterface::load_info() {
	//Score score;
	_file.update_filepath(0);
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
		system("cls");
		check = basic_out(0);
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
		system("cls");
		check = basic_out(1);
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
		reset_input();
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

void UserInterface::reset_input() {
	system("cls");
	cout << "\nPlease enter the number in the list" << endl; // 에러 메시지 출력
	cin.clear(); // 오류스트림을 초기화
	cin.ignore(256, '\n'); // 입력버퍼를 비움
}