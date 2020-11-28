#include "ingame.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <istream>
#include <fstream>
#include <time.h>

Sentence::Sentence() {
	_writtenQueue = {};
	_userVector = {};
	_userSentence = "";
	_writtenNum = 0;
	_userTime = 0;
}

void Sentence::load_written() {
	cout << "Please select number" << endl;
	cout << "1: Lesiure" << endl;
	cin >> _writtenNum;
	Sleep(10);
	system("cls");
	switch (_writtenNum) {
	case 1:
		_writtenFile.open("C:\\Users\\junyh\\OneDrive\\Desktop\\Lesiure.txt", ios::in);
		break;
	}
	if (_writtenFile.is_open()) {
		while (!_writtenFile.eof()) {
			string written_sentence;
			getline(_writtenFile, written_sentence);
			_writtenQueue.push(written_sentence);
		}
		_writtenFile.close();
	}
	else {
		cout << "We have a problem with open file: Can not open the file" << endl;
	}
}

void Sentence::in_sentence() {
	Sleep(10);
	_userSentence = "";
	cout << "-> ";
	clock_t start, finish;
	start = clock();
	int i = 0;
	while (_userSentence.empty()) {
		if (i > 2) {
			cout << "please insert sentence" << endl;
		}
		getline(cin, _userSentence);
		i++;
	}
	finish = clock();
	_userTime = (finish - start);
	_userTime = _userTime / 1000.0;
	_userVector.push_back(_userSentence);
}


PracticeInfo::PracticeInfo() {
	correct = 0;
	wrong = 0;
	user_correctness = 0;
}

double PracticeInfo::check_info(queue <string> written_vector, string user_sentence, int& entire_correct) {
	string written_buffer;
	string user_buffer;
	written_buffer = written_vector.front();
	written_vector.pop();
	user_buffer = user_sentence;

	int i = 0;
	while (user_buffer[i] != '\0') {
		if (i > written_buffer.size()) {
			wrong+= user_buffer.size() - i;
			break;
		}
		if (user_buffer[i] == written_buffer[i]) {
			correct++;
		}
		else {
			wrong++;
		}
		i++;
	}
	if (i < written_buffer.size()) {
		
		wrong += (written_buffer.size() - i);
	}
	entire_correct = correct;	user_correctness = (double) ((correct*100) / (correct + wrong));
	Sleep(500);
	return user_correctness;
}

UserInterface::UserInterface() {
	_userInfo = "";
	_entireCorrectness = 0;
	_entireTime = 0;
	_entireCorrect = 0;
}
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
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << _entireCorrect / _entireTime << endl;
		cout << i << ". " << _writtenQueue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		_entireTime += _userTime;
		_entireCorrectness = check_info(_writtenQueue, _userSentence, _entireCorrect);
		_writtenQueue.pop();
	}
}

void UserInterface::load_info() {
	cout << "Please insert your name : ";
	getline(cin, _userInfo);
	basic_out();
	cout << "Great job! " << endl;
	cout << "           Your Score" << endl;
	cout << "Correctness : " << _entireCorrectness << " Speed : " << _entireCorrect / _entireTime << endl;
}


int main() {
	UserInterface start;
	start.load_info();
	return 0;
}