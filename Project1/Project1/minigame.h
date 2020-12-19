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
	double speed;		//���ڰ� �������� �ӵ�




//����Լ�
public:
	MiniGame();
	~MiniGame();
	void print_input();	//str�� �����.
	void ui_clear(int clear_row);	//ui�� clear_row���� ����(' ')���� �ٲ㼭 ����.
	void ui_print();	//ui�� �����.
	void game(string word);	//word�� ���޹޾� �꼺��ó�� �������� �ϰ�, input�� �Է¹޾� �´� ��� score�� +1��.
	void print_score();		//score�� �� �� �ٹٲް� �Բ� �����.
	int return_score();	//score�� return��.
};