#include "ingame.h"
#include "Score.h"
#include "Start.h"
#include "minigame.h"
//initialize the userinterface object. 

UserInterface::UserInterface() {
	_userInfo = "";
	_entireCorrectness = 0;
	_entireTime = 0;
	choice = 0;
	running = true;
}
// we take a tag and make a choice to have a short/long game. 
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



bool UserInterface::basic_out(int tag) {

	bool check = load_shortwriting(tag);
	if (check) return true;
	// make a wait time for 3 seconds.
	in_stage();
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
	
	//as a default, we upadate filenames about short sentences and score info.
	_file.update_filepath(0);
	_score.update_score();
	cout << "\nPlease insert your name : ";
	getline(cin, _userInfo);
	_userNickname = _userInfo;
choice_loop:
	cout << "MAIN MENU" << endl << endl;
menu:
	cout << "1: Short Writing" << endl;
	cout << "2: Long Writing" << endl;
	cout << "3: Ranking" << endl;
	cout << "4: Options" << endl;
	cout << "5: Minigame" << endl;
	cout << "6: Quit" << endl;
	cout << endl << "Choice: ";

	cin >> choice;
	bool check;
	switch (choice) {
	case 1:
		system("cls");
		check = basic_out(0);
		if (check) break;
		print_result();
		//cout << "Ranking is updated.\n" << endl;
		cout << "\nWhat do you want to now?" << endl;
		goto menu;
		break;
	case 2:
		system("cls");
		check = basic_out(1);
		if (check) break;
		print_result();
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
		minigame_start();
		goto menu;
		break;
	case 6:
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


void UserInterface::reset_input() {
	system("cls");
	cout << "\nPlease enter the number in the list" << endl; // 에러 메시지 출력
	cin.clear(); // 오류스트림을 초기화
	cin.ignore(256, '\n'); // 입력버퍼를 비움
}

void UserInterface::minigame_start() {
	MiniGame minigame;
	string gameword[12] = { "Blue", "Red", "Orange", "Yellow", "Apple", "Cup", "Computer", "Bottle", "Mouse", "C++", "Medicine", "Congratulation" };
	system("cls");
	for (int i = 0; i < 12; i++) {		//게임 실행
		minigame.game(gameword[i]);
	}
	system("cls");		//화면 비우기
	cout << "Game Over!" << endl;
	Sleep(500);
	cout << "Your Final Score is: " << minigame.return_score() << endl;		//점수 출력
	Sleep(2000);		//점수를 보여주기 위한 딜레이.
	system("cls");
	cout << "What do you want to do now?" << endl;
}