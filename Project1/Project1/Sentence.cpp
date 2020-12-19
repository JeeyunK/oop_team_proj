#include "ingame.h"

//initialize the sentence object.
Sentence::Sentence() {
	_writtenQueue = {};
	//_userVector = {};
	_userSentence = "";
	_writtenNum = 0;
	_userTime = 0;
	_file;
	_score;
}
//load the filepath and open the file.
//if there is no file, we just print "we have a problem ~ "
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
// get the typed sentence and record the typing speed. 
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

void Sentence::in_stage() {
	system("cls");
	cout << "\nStart game after 3 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	cout << "\nStart game after 2 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	cout << "\nStart game after 1 seconds!!" << endl;
	Sleep(1000);
	system("cls");
	int i = 0;
	//in_sentence();
	int qsize = _writtenQueue.size();
	string lastWrittenSentece;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!_writtenQueue.empty()) {
		float prog = ((float)i / (float)qsize);
		progressBar(prog);
		i++;
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << tot_letters / _entireTime * 60 << endl;
		if (i > 1) {
			print_last_sentence(i, qsize, lastWrittenSentece);
		}
		cout << i << ". " << _writtenQueue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		_entireTime += _userTime;
		for (int j = 0; j < _wrongLetterIndex.size(); j++) {
			_wrongLetterIndex.pop();
		}
		_entireCorrectness = check_info(_writtenQueue, _userSentence);
		lastWrittenSentece = _writtenQueue.front();
		_writtenQueue.pop();
	}
}

void Sentence::progressBar(float progress) {
	//float progress = 0.0;
	//while (progress < 1.0) {
	//cout << progress;
	int barWidth = 50;
	cout << "\n progress : [";
	int pos = (barWidth * progress);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos)
			cout << "=";
		else if (i == pos)
			cout << ">";
		else
			cout << " ";
	}
	cout << "] " << int(progress * 100.0) << "%\r";
	cout.flush();
	cout << endl;
}

void Sentence::print_last_sentence(int i, int qsize, std::string lastWrittenSentece) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << i - 1 << ". " << lastWrittenSentece << endl;
	cout << " -> ";
	for (int j = 0; j < _userSentence.size(); j++) {
		int wrongIndex = -1;
		if (!_wrongLetterIndex.empty()) {
			wrongIndex = _wrongLetterIndex.front();

		}
		if (wrongIndex == j) {
			SetConsoleTextAttribute(hConsole, 12);
			cout << _userSentence[j];
			_wrongLetterIndex.pop();
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
			cout << _userSentence[j];
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;
}
