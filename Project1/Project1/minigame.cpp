#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	str[100] = {};
	row = 24;	//세로 길이 설정
	column = 30;	//가로 길이 설정
	score = 0;
	speed = 500;	//시작 속도 설정

	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//이중배열 동적 할당
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//이중배열 삭제
}

void MiniGame::get_input() {		//_getch() 연습용 함수. 사용하지 않음.
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

void MiniGame::ui_clear(int clear_row) {		//ui를 공백으로 초기화함.
	for (int i = 0; i < clear_row; i++) {
		for (int j = 0; j < column; j++) {
			ui[i][j] = ' ';
		}
	}
}

void MiniGame::ui_print() {			//ui의 양 옆에 #으로 된 선을 붙여서 출력함.
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

void MiniGame::make_start() {		//원래는 동전 쌓기를 생각해서 만든 함수. 사용하지 않음.
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

		if (_kbhit()) {		//입력하고 있으면(_kbhit()가 키가 눌리고 있을때는 non zero value, 아니면 zero)
			input = _getch();
			if (input == 13) {			//사용자가 enter를 입력하면. enter의 코드가 13임.
				str[count] = NULL;		//마지막에 NULL 문자 넣기.
				string str_copy;		//string 클래스에 복사하기 위한 string.
				for (int k = 0; k < length; k++) {
					str_copy += str[k];		//str_copy에 여태까지 입력받은 글자를 하나씩 더함.
				}
				if (word.compare(str_copy) == 0) {		//정확하게 일치하면
					for (int k = 0; k < count; k++) {	//str 초기화
						str[k] = '\0';
					}
					//count = 0;		
					score++;		//점수 올리기
					cout << "Current Score: "<< score;	//현재 점수 출력
					speed = speed / 2;		//속도를 1/2배함
					Sleep(500);				//0.5초만큼 쉼. 화면 전환이 너무 빨라서 넣음.

					break;
				}
				else {		//정확하게 일치하지 않으면
					for (int k = 0; k < count; k++) {		
						str[k] = '\0';		//입력받은 문자열 str 초기화
					}
					count = 0;		//count 초기화
				}
			}
			str[count++] = input;		//str에 count index에 input을 집어넣고 count를 1 더함.
			cout << endl;
			cout << "Current Score: " << score;		//현재 점수 출력
			cout << endl;
			print_input();		//입력하고 있는 문자열(str) 출력
			Sleep(speed);		//단어가 내려가는 시간만큼 딜레이.
		}
		else {		//입력하고 있지 않으면 단어가 내려가게 함.
			cout << endl;
			cout << "Current Score: " << score;
			cout << endl;
			print_input();
			Sleep(speed);
		}
		if (i+1==row)	//단어가 끝까지 내려왔으면
		{
			cout << endl << "Time Over!" << endl;		//Time Over를 출력하고
			for (int k = 0; k < count; k++) {			//입력받았던 문자열 초기화
				str[k] = '\0';
			}
			Sleep(1000);		//다음 스테이지로 넘어가기 전까지 딜레이.
			break;
		}

	}
}


void MiniGame::coin_stacking() {
	make_start();
}

int MiniGame::return_score() {
	return score;
}
