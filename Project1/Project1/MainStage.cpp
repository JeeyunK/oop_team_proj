#include "ingame.h"

//initialize the sentence object.
MainStage::MainStage() {
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
bool MainStage::load_written() {
	const char* file_path = (_file.file_list[_writtenNum-1].PATH).c_str();
	_writtenFile.open(file_path, ios::in); // open sentece of user's pick
	if (_writtenFile.is_open()) {
		while (!_writtenFile.eof()) {
			string written_sentence;
			getline(_writtenFile, written_sentence); // read write file
			_writtenQueue.push(written_sentence); // insert write file's sentence to queue
		}
		_writtenFile.close(); // close write file
	}
	else {
		system("cls");
		cout << "We have a problem with open file: Can not open the file" << endl; // when fail to insert at write queue or other problem
		return true;
	}
	return false;
}
// get the typed sentence and record the typing speed. 
void MainStage::in_sentence() {
	Sleep(10);
	_userSentence = "";  // initialization of user's input
	cout << "-> ";
	clock_t start, finish;  // typing start time, typing finish time(when user insert 'enter')
	start = clock();  // record start time
	int i = 0;  // this variable increase when user insert just enter(nothing else)
	while (_userSentence.empty()) {
		if (i > 2) {
			cout << "please insert sentence" << endl;  // When user insert only 'enter;'
		}
		getline(cin, _userSentence); // user's input
		i++;
	}
	finish = clock(); // record finish time
	_userTime = (finish - start); // compute sentence typing time
	_userTime = _userTime / 1000.0; // compute typing speed
	//_userVector.push_back(_userSentence);
}

void MainStage::in_stage() {
	// game start after 3 seconds
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
	int qsize = _writtenQueue.size(); // Proposed sentence's size
	string lastWrittenSentece; // user's last sentence
	HANDLE hConsole; // for wrong letter's change
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// This is main part of typing game. If there is no more presentation, the loop will be terminated.
	while (!_writtenQueue.empty()) {
		float prog = ((float)i / (float)qsize);  // progress variable
		progressBar(prog);
		i++;
		cout << "Current your correctness : " << _entireCorrectness << ", Current your speed : " << tot_letters / _entireTime * 60 << endl;
		if (i > 1) {
			print_last_sentence(i, qsize, lastWrittenSentece);  // print user's last input
		}
		cout << i << ". " << _writtenQueue.front() << endl; // print sentence with number 
		Sleep(10);
		in_sentence(); // record typing and typing speed
		Sleep(10);
		system("cls");
		_entireTime += _userTime; // record entire typing time
		for (int j = 0; j < _wrongLetterIndex.size(); j++) {
			_wrongLetterIndex.pop();  // pop present wrong letters
		}
		_entireCorrectness = check_info(_writtenQueue, _userSentence); // record entire typing correctness
		lastWrittenSentece = _writtenQueue.front(); // update last sentence
		_writtenQueue.pop(); // pop present sentence
	}
}

void MainStage::progressBar(float progress) {
	//float progress = 0.0;
	//while (progress < 1.0) {
	//cout << progress;
	int barWidth = 50;
	cout << "\n progress : [";
	int pos = (barWidth * progress); // progress degree
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos)
			cout << "="; // =="="===>
		else if (i == pos)
			cout << ">"; // =====">"
		else
			cout << " "; // =====>    " " 
	}
	cout << "] " << int(progress * 100.0) << "%\r";
	cout.flush();
	cout << endl;
}

void MainStage::print_last_sentence(int i, int qsize, std::string lastWrittenSentece) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // to change wrong letter's color
	cout << i - 1 << ". " << lastWrittenSentece << endl;
	cout << " -> ";
	for (int j = 0; j < _userSentence.size(); j++) {
		int wrongIndex = -1;
		if (!_wrongLetterIndex.empty()) {
			wrongIndex = _wrongLetterIndex.front(); // update wrong letter's index

		}
		if (wrongIndex == j) {
			SetConsoleTextAttribute(hConsole, 12); // change wrong letter's color to red
			cout << _userSentence[j];
			_wrongLetterIndex.pop(); // remove present wrong letter
		}
		else {
			SetConsoleTextAttribute(hConsole, 15); // correct letter's color (white)
			cout << _userSentence[j];
		}
	}
	SetConsoleTextAttribute(hConsole, 15); // defalt color (white)
	cout << endl;
}

void MainStage::print_result() {
	cout << "Great job! " << endl;
	cout << "           Your Score" << endl;
	cout << "Correctness : " << _entireCorrectness << " Speed : " << tot_letters / _entireTime * 60 << endl;
	_score.add_score(_userNickname, _entireCorrectness, tot_letters / _entireTime * 60); // record score
	reset_score(); // reset socre
}

void MainStage::reset_score() {
	correct = 0;
	wrong = 0;
	tot_letters = 0;
	user_correctness = 0;

	_entireCorrectness = 0;
	_entireTime = 0;
}
