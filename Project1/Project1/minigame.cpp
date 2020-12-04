#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	str[100] = {};
	row = 24;	//세로 길이 설정
	column = 30;	//가로 길이 설정
	score = 0;
	speed = 2000;	//시작 속도 설정
	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//이중배열 동적 할당
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//이중배열 삭제
}

void MiniGame::get_input() {
	int count = 0;
	while (true) {
		input = _getch();
		if (input == 13) break; //enter가 들어오면 break;
		str[count++] = input;
		if (_kbhit()) {
			input = _getch();
			str[count++] = input;
		}
	}
	str[count] = NULL;
}

void MiniGame::print_input() {
	cout << str;
}

void MiniGame::ui_clear(int clear_row) {
	for (int i = 0; i < clear_row; i++) {
		for (int j = 0; j < column; j++) {
			ui[i][j] = ' ';
		}
	}
}

void MiniGame::ui_print() {
	//for (int i = 0; i < row; i++) { cout << "#";}
	cout << endl;
	for (int i = 0; i < row; i++) {
		cout << "#";
		for (int j = 0; j <column; j++) {
			cout << ui[i][j];
		}
		cout <<"#"<< endl;
	}
	//for (int i = 0; i < row; i++) { cout << "#";}
}

void MiniGame::make_start() {
	ui[row - 1][column / 2 - 2] = '#';
	ui[row - 1][column / 2 - 1] = '#';
	ui[row - 1][column / 2] = '#';
	ui[row - 1][column / 2 + 1] = '#';
}

void MiniGame::game(string word) {
	int c = 0;		//문자가 시작할 column 위치
	int length = word.length();		//전달받은 단어의 길이
	int count = 0;		//입력받은 글자를 str에 넣기 위한 변수

	srand((unsigned int)time(0));		//시드 생성
	c = rand() % (column - length);		//무작위 위치에 문자 생성

	for (int i = 0; i < row; i++)		//i는 문자가 있는 줄
	{
		ui_clear(row);		//ui 지우기
		//c = rand() % (column - length);	//원래는 무작위로 좌우로 왔다갔다 하려고 넣었는데, 이상해보여서 뺌.
		for (int j = c; j < c + length; j++) {
			ui[i][j] = word[j - c];
		}
		system("cls");
		ui_print();

		if (_kbhit()) {		//이거를 어떻게 while문으로 잘 넣어서 문자가 여러 개 동시에 입력되도 받을 수 있을 것 같은데 모르겠음.
			input = _getch();
			if (input == 13) {
				str[count] = NULL;
				string str_copy;
				for (int k = 0; k < length; k++) {
					str_copy += str[k];
				}
				if (word.compare(str_copy) == 0) {
					score++;
					cout << score;
					speed = speed - 100;
					Sleep(500);

					//여기서 새로운 game을 불러와야 함.
					break;
				}
				else {
					for (int k = 0; k < count; k++) {
						str[k] = '\0';
					}
					count = 0;
				}
			}
			str[count++] = input;
			cout << endl;
			cout << score;
			cout << endl;
			print_input();
			Sleep(speed);
		}
		else
		{
			cout << endl;
			cout << score;
			cout << endl;
			print_input();
			Sleep(speed);
		}
		//str[count] = NULL;
		if (i+1==row)
		{
			cout << "Time Over!" << endl;
			cout << "Your Final Score is: " << score << endl;
		}

	}
}