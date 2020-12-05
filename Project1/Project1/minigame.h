#pragma once
#include "conio.h"
#include "ingame.h"


class MiniGame {
//�������
private:
	int input;		//�Է¹��� key
	char str[100];	//�Է¹��� key�� ���޹޴� ���ڿ�
	char** ui;		//�����Ҵ�� ���� ���ڿ�, ui
	int row;		//ui�� row ����(���� ����)
	int column;		//ui�� column ����(���� ����)
	int score;		//���� �ܾ� ��
	int speed;		//���ڰ� �������� �ӵ�




//����Լ�
public:
	MiniGame();
	~MiniGame();
	void get_input();	//getch()�� input�� ����. �̰� ����ϸ� ���ڰ� ��� �������� �ʰ� ���߱� ������ ������� ����.
	void print_input();	//str�� �����.
	void ui_clear(int clear_row);	//ui�� clear_row���� ����(' ')���� �ٲ㼭 ����.
	void ui_print();	//ui�� �����.
	void make_start();	//������ �ܾ� �����ױ�ó�� ������� �� �ǵ� �ٲ�. ������� ����. 
	void game(string word);	//word�� ���޹޾� �꼺��ó�� �������� �ϰ�, input�� �Է¹޾� �´� ��� score�� +1��.
	void coin_stacking();
	int return_score();	//score�� �����.
};