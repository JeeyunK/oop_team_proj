#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	str[100] = {};
	row = 24;	//���� ���� ����
	column = 30;	//���� ���� ����
	score = 0;
	speed = 2000;	//���� �ӵ� ����
	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//���߹迭 ���� �Ҵ�
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//���߹迭 ����
}

void MiniGame::get_input() {
	int count = 0;
	while (true) {
		input = _getch();
		if (input == 13) break; //enter�� ������ break;
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
	int c = 0;		//���ڰ� ������ column ��ġ
	int length = word.length();		//���޹��� �ܾ��� ����
	int count = 0;		//�Է¹��� ���ڸ� str�� �ֱ� ���� ����

	srand((unsigned int)time(0));		//�õ� ����
	c = rand() % (column - length);		//������ ��ġ�� ���� ����

	for (int i = 0; i < row; i++)		//i�� ���ڰ� �ִ� ��
	{
		ui_clear(row);		//ui �����
		//c = rand() % (column - length);	//������ �������� �¿�� �Դٰ��� �Ϸ��� �־��µ�, �̻��غ����� ��.
		for (int j = c; j < c + length; j++) {
			ui[i][j] = word[j - c];
		}
		system("cls");
		ui_print();

		if (_kbhit()) {		//�̰Ÿ� ��� while������ �� �־ ���ڰ� ���� �� ���ÿ� �Էµǵ� ���� �� ���� �� ������ �𸣰���.
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

					//���⼭ ���ο� game�� �ҷ��;� ��.
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