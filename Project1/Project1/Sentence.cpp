#include "ingame.h"


Sentence::Sentence() {
	_writtenQueue = {};
	//_userVector = {};
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
onemore:
	switch (_writtenNum) {
	case 1:
		_writtenFile.open("Leisure.txt", ios::in);
		break;
	default:
		cout << "Please enter the number in the list" << endl;
		goto onemore;
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
		Sleep(3000);
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
	//_userVector.push_back(_userSentence);
}

