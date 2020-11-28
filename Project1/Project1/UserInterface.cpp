#include "ingame.h"

UserInterface::UserInterface() {
	_userInfo = "";
	_entireCorrectness = 0;
	_entireTime = 0;
}

//
void UserInterface::basic_out() {
	load_written();
	system("cls");
	cout << "Start game after 3 seconds!!" << endl;
	Sleep(3000);
	system("cls");
	int i = 0;
	//in_sentence();
	while (!_writtenQueue.empty()) {
		i++;
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << tot_letters / _entireTime * 60 << endl;
		cout << i << ". " << _writtenQueue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		_entireTime += _userTime;
		_entireCorrectness = check_info(_writtenQueue, _userSentence);
		_writtenQueue.pop();
	}
}

void UserInterface::load_info() {
	cout << "Please insert your name : ";
	getline(cin, _userInfo);
	basic_out();
	cout << "Great job! " << endl;
	cout << "           Your Score" << endl;
	cout << "Correctness : " << _entireCorrectness << " Speed : " << tot_letters / _entireTime * 60 << endl;
	//cout << "entire correct : " << _entireCorrect << endl;
}
