#include "minigame.h"

MiniGame::MiniGame() {
	input = 0;
	str[100] = {};
	row = 24;	//���� ���� ����
	column = 30;	//���� ���� ����
	score = 0;
	speed = 500;	//���� �ӵ� ����

	ui = new char* [row];
	for (int i=0;i<row;i++) {ui[i]=new char[column]; }		//���߹迭 ���� �Ҵ�
}

MiniGame::~MiniGame() {
	for (int i = 0; i < row; i++) { delete[] ui[i]; }
	delete[] ui;		//���߹迭 ����
}

void MiniGame::get_input() {		//_getch() ������ �Լ�. ������� ����.
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

void MiniGame::ui_clear(int clear_row) {		//ui�� �������� �ʱ�ȭ��.
	for (int i = 0; i < clear_row; i++) {
		for (int j = 0; j < column; j++) {
			ui[i][j] = ' ';
		}
	}
}

void MiniGame::ui_print() {			//ui�� �� ���� #���� �� ���� �ٿ��� �����.
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

void MiniGame::make_start() {		//������ ���� �ױ⸦ �����ؼ� ���� �Լ�. ������� ����.
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

		if (_kbhit()) {		//�Է��ϰ� ������(_kbhit()�� Ű�� ������ �������� non zero value, �ƴϸ� zero)
			input = _getch();
			if (input == 13) {			//����ڰ� enter�� �Է��ϸ�. enter�� �ڵ尡 13��.
				str[count] = NULL;		//�������� NULL ���� �ֱ�.
				string str_copy;		//string Ŭ������ �����ϱ� ���� string.
				for (int k = 0; k < length; k++) {
					str_copy += str[k];		//str_copy�� ���±��� �Է¹��� ���ڸ� �ϳ��� ����.
				}
				if (word.compare(str_copy) == 0) {		//��Ȯ�ϰ� ��ġ�ϸ�
					for (int k = 0; k < count; k++) {	//str �ʱ�ȭ
						str[k] = '\0';
					}
					//count = 0;		
					score++;		//���� �ø���
					cout << "Current Score: "<< score;	//���� ���� ���
					speed = speed / 2;		//�ӵ��� 1/2����
					Sleep(500);				//0.5�ʸ�ŭ ��. ȭ�� ��ȯ�� �ʹ� ���� ����.

					break;
				}
				else {		//��Ȯ�ϰ� ��ġ���� ������
					for (int k = 0; k < count; k++) {		
						str[k] = '\0';		//�Է¹��� ���ڿ� str �ʱ�ȭ
					}
					count = 0;		//count �ʱ�ȭ
				}
			}
			str[count++] = input;		//str�� count index�� input�� ����ְ� count�� 1 ����.
			cout << endl;
			cout << "Current Score: " << score;		//���� ���� ���
			cout << endl;
			print_input();		//�Է��ϰ� �ִ� ���ڿ�(str) ���
			Sleep(speed);		//�ܾ �������� �ð���ŭ ������.
		}
		else {		//�Է��ϰ� ���� ������ �ܾ �������� ��.
			cout << endl;
			cout << "Current Score: " << score;
			cout << endl;
			print_input();
			Sleep(speed);
		}
		if (i+1==row)	//�ܾ ������ ����������
		{
			cout << endl << "Time Over!" << endl;		//Time Over�� ����ϰ�
			for (int k = 0; k < count; k++) {			//�Է¹޾Ҵ� ���ڿ� �ʱ�ȭ
				str[k] = '\0';
			}
			Sleep(1000);		//���� ���������� �Ѿ�� ������ ������.
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
