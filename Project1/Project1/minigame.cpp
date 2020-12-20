#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	row = 24;	//세로 길이 설정
	column = 30;	//가로 길이 설정
	str[100] = {};
	score = 0;
	speed = 300;	//시작 속도 설정
	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//이중배열 동적 할당
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//이중배열 삭제
}



void MiniGame::print_input() {		//str 문자열 출력
	cout << str;
}

void MiniGame::ui_clear(int clear_row) {		//ui를 공백으로 초기화함.
	for (int i = 0; i < clear_row; i++) {
		for (int j = 0; j < column; j++) {
			ui[i][j] = ' ';
		}
	}
}

void MiniGame::ui_print() {			//ui의 양 옆에 #으로 된 선을 붙여서 출력함.
	//for (int i = 0; i < row; i++) { cout << "#";}
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);	//커서를 가장 얇게, 안보이게 바꿈.
	cout << endl;
	for (int i = 0; i < row; i++) {
		cout << "#";
		for (int j = 0; j <column; j++) {
			cout << ui[i][j];
		}
		cout <<"#"<< endl;
	}
	//for (int i = 0; i < row; i++) { cout << "#";}
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);	//커서를 가장 두껍게, 보이게 바꿈.

}

void MiniGame::game(string word) {
	system("cls");
	int length = word.length();		//전달받은 단어의 길이
	int c = rand() % (column-length);		//문자가 시작할 column 위치
	int count = 0;		//입력받은 글자를 str에 넣기 위한 변수

	for (int i = 0; i < row; i++)		//i는 문자가 있는 줄
	{
		ui_clear(row);		//ui 지우기
		for (int j = c; j < c + length; j++) {	//단어 넣기
			ui[i][j] = word[j - c];
		}
		//system("cls");
		COORD pos = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);		//안 깜빡거리면서 화면을 초기화
		ui_print();
		if (_kbhit()) {		//입력하고 있으면(_kbhit()가 키가 눌리고 있을때는 non zero value, 아니면 zero)
			input = _getch();
			if (input == 13) {			//사용자가 enter를 입력하면. enter의 코드가 13임.
				str[count] = NULL;		//마지막에 NULL 문자 넣기.
				string str_copy(str);		//string 클래스에 str 문자열을 복사.
				if (word.compare(str_copy) == 0) {		//정확하게 일치하면
					for (int k = 0; k < count; k++) {	//str 초기화
						str[k] = NULL;
					}
					//count = 0;		
					score++;		//점수 올리기
					print_score();
					speed = speed / 2;		//속도를 1/2배함
					Sleep(500);						//0.5초만큼 쉼. 화면 전환이 너무 빨라서 넣음.

					break;
				}
				else {		//정확하게 일치하지 않으면
					system("cls");
					ui_print();
					cout << endl << "Wrong Answer" << endl;
					for (int k = 0; k < count; k++) {		
						str[k] = NULL;		//입력받은 문자열 str 초기화
					}
					count = 0;		//count 초기화
					Sleep(1000);		//다음 스테이지로 넘어가기 전까지 딜레이.
					break;
				}

			}
			else {		//사용자가 enter 말고 다른 문자를 입력하면
				str[count++] = input;		//str에 count index에 input을 집어넣고 count를 1 더함.
			}
			print_score();
			print_input();		//입력하고 있는 문자열(str) 출력
			Sleep(50+speed);		//단어가 내려가는 시간만큼 딜레이.
		}
		else {		//입력하고 있지 않으면 단어가 내려가게 함.
			print_score();
			print_input();
			Sleep(50+speed);
		}
		if (i+1==row)	//단어가 끝까지 내려왔으면
		{
			cout << endl << "Time Over!" << endl;		//Time Over를 출력하고
			for (int k = 0; k < count; k++) {			//입력받았던 문자열 초기화
				str[k] = NULL;
			}
			Sleep(1000);		//다음 스테이지로 넘어가기 전까지 딜레이.
			break;
		}

	}
}

void MiniGame::print_score() {
	cout << endl;
	cout << "Current Score: " << score;
	cout << endl;
}

int MiniGame::return_score() {
	return score;
}

