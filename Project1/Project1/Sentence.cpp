#include "ingame.h"


Sentence::Sentence() {
	_writtenQueue = {};
	//_userVector = {};
	_userSentence = "";
	_writtenNum = 0;
	_userTime = 0;
	_file;
	_score;
}

bool Sentence::load_written() {
	const char* file_path = (_file.file_list[_writtenNum-1].PATH).c_str();
	_writtenFile.open(file_path, ios::in);
	if (_writtenFile.is_open()) {
		while (!_writtenFile.eof()) {
			string written_sentence;
			getline(_writtenFile, written_sentence);
			_writtenQueue.push(written_sentence);
		}
		_writtenFile.close();
	}
	else {
		system("cls");
		cout << "We have a problem with open file: Can not open the file" << endl;
		return true;
	}
	return false;
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

