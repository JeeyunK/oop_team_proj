#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	row = 24;	//���� ���� ����
	column = 30;	//���� ���� ����
	str[100] = {};
	score = 0;
	speed = 300;	//���� �ӵ� ����
	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//���߹迭 ���� �Ҵ�
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//���߹迭 ����
}



void MiniGame::print_input() {		//str ���ڿ� ���
	cout << str;
}

void MiniGame::ui_clear(int clear_row) {		//ui�� �������� �ʱ�ȭ��.
	for (int i = 0; i < clear_row; i++) {
		for (int j = 0; j < column; j++) {
			ui[i][j] = ' ';
		}
	}
}

void MiniGame::ui_print() {			//ui�� �� ���� #���� �� ���� �ٿ��� �����.
	//for (int i = 0; i < row; i++) { cout << "#";}
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);	//Ŀ���� ���� ���, �Ⱥ��̰� �ٲ�.
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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);	//Ŀ���� ���� �β���, ���̰� �ٲ�.

}

void MiniGame::game(string word) {
	system("cls");
	int length = word.length();		//���޹��� �ܾ��� ����
	int c = rand() % (column-length);		//���ڰ� ������ column ��ġ
	int count = 0;		//�Է¹��� ���ڸ� str�� �ֱ� ���� ����

	for (int i = 0; i < row; i++)		//i�� ���ڰ� �ִ� ��
	{
		ui_clear(row);		//ui �����
		for (int j = c; j < c + length; j++) {	//�ܾ� �ֱ�
			ui[i][j] = word[j - c];
		}
		//system("cls");
		COORD pos = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);		//�� �����Ÿ��鼭 ȭ���� �ʱ�ȭ
		ui_print();
		if (_kbhit()) {		//�Է��ϰ� ������(_kbhit()�� Ű�� ������ �������� non zero value, �ƴϸ� zero)
			input = _getch();
			if (input == 13) {			//����ڰ� enter�� �Է��ϸ�. enter�� �ڵ尡 13��.
				str[count] = NULL;		//�������� NULL ���� �ֱ�.
				string str_copy(str);		//string Ŭ������ str ���ڿ��� ����.
				if (word.compare(str_copy) == 0) {		//��Ȯ�ϰ� ��ġ�ϸ�
					for (int k = 0; k < count; k++) {	//str �ʱ�ȭ
						str[k] = NULL;
					}
					//count = 0;		
					score++;		//���� �ø���
					print_score();
					speed = speed / 2;		//�ӵ��� 1/2����
					Sleep(500);						//0.5�ʸ�ŭ ��. ȭ�� ��ȯ�� �ʹ� ���� ����.

					break;
				}
				else {		//��Ȯ�ϰ� ��ġ���� ������
					system("cls");
					ui_print();
					cout << endl << "Wrong Answer" << endl;
					for (int k = 0; k < count; k++) {		
						str[k] = NULL;		//�Է¹��� ���ڿ� str �ʱ�ȭ
					}
					count = 0;		//count �ʱ�ȭ
					Sleep(1000);		//���� ���������� �Ѿ�� ������ ������.
					break;
				}

			}
			else {		//����ڰ� enter ���� �ٸ� ���ڸ� �Է��ϸ�
				str[count++] = input;		//str�� count index�� input�� ����ְ� count�� 1 ����.
			}
			print_score();
			print_input();		//�Է��ϰ� �ִ� ���ڿ�(str) ���
			Sleep(50+speed);		//�ܾ �������� �ð���ŭ ������.
		}
		else {		//�Է��ϰ� ���� ������ �ܾ �������� ��.
			print_score();
			print_input();
			Sleep(50+speed);
		}
		if (i+1==row)	//�ܾ ������ ����������
		{
			cout << endl << "Time Over!" << endl;		//Time Over�� ����ϰ�
			for (int k = 0; k < count; k++) {			//�Է¹޾Ҵ� ���ڿ� �ʱ�ȭ
				str[k] = NULL;
			}
			Sleep(1000);		//���� ���������� �Ѿ�� ������ ������.
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

