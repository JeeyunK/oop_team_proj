#pragma once
#include "conio.h"
#include "ingame.h"


class MiniGame {
//멤버변수
private:
	int input;		//입력받은 key
	char str[100];	//입력받은 key를 전달받는 문자열
	char** ui;		//동적할당된 이중 문자열, ui
	int row;		//ui의 row 개수(세로 길이)
	int column;		//ui의 column 개수(가로 길이)
	int score;		//맞춘 단어 수
	double speed;		//문자가 내려가는 속도




//멤버함수
public:
	MiniGame();
	~MiniGame();
	void print_input();	//str을 출력함.
	void ui_clear(int clear_row);	//ui를 clear_row까지 공백(' ')으로 바꿔서 지움.
	void ui_print();	//ui를 출력함.
	void game(string word);	//word를 전달받아 산성비처럼 내려가게 하고, input을 입력받아 맞는 경우 score를 +1함.
	void print_score();		//score를 앞 뒤 줄바꿈과 함께 출력함.
	int return_score();	//score를 return함.
};