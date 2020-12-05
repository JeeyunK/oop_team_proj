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
	int speed;		//문자가 내려가는 속도




//멤버함수
public:
	MiniGame();
	~MiniGame();
	void get_input();	//getch()로 input을 받음. 이걸 사용하면 문자가 계속 내려가지 않고 멈추기 때문에 사용하지 않음.
	void print_input();	//str을 출력함.
	void ui_clear(int clear_row);	//ui를 clear_row까지 공백(' ')으로 바꿔서 지움.
	void ui_print();	//ui를 출력함.
	void make_start();	//원래는 단어 동전쌓기처럼 만드려고 한 건데 바뀜. 사용하지 않음. 
	void game(string word);	//word를 전달받아 산성비처럼 내려가게 하고, input을 입력받아 맞는 경우 score를 +1함.
	void coin_stacking();
	int return_score();	//score를 출력함.
};