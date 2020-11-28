#include "ingame.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <istream>
#include <fstream>
#include <time.h>

Sentence::Sentence() {
	written_queue = {};
	user_vector = {};
	user_sentence = "";
	written_num = 0;
	user_time = 0;
}

void Sentence::load_written() {
	cout << "Please select number" << endl;
	cout << "1: Lesiure" << endl;
	cin >> written_num;
	Sleep(10);
	system("cls");
	switch (written_num) {
	case 1:
		written_file.open("C:\\Users\\junyh\\OneDrive\\Desktop\\Lesiure.txt", ios::in);
		break;
	}
	if (written_file.is_open()) {
		while (!written_file.eof()) {
			string written_sentence;
			getline(written_file, written_sentence);
			written_queue.push(written_sentence);
		}
		written_file.close();
	}
	else {
		cout << "We have a problem with open file: Can not open the file" << endl;
	}
}

void Sentence::in_sentence() {
	Sleep(10);
	user_sentence = "";
	cout << "-> ";
	clock_t start, finish;
	start = clock();
	int i = 0;
	while (user_sentence.empty()) {
		if (i > 2) {
			cout << "please insert sentence" << endl;
		}
		getline(cin, user_sentence);
		i++;
	}
	finish = clock();
	user_time = (finish - start);
	user_time = user_time / 1000.0;
	user_vector.push_back(user_sentence);
}


Practice_info::Practice_info() {
	correct = 0;
	wrong = 0;
	user_correctness = 0;
}

double Practice_info::check_info(queue <string> written_vector, string user_sentence, int& entire_correct) {
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

Interface::Interface() {
	user_info = "";
	entire_correctness = 0;
	entire_time = 0;
	entire_correct = 0;
}
void Interface::basic_out() {
	load_written();
	system("cls");
	cout << "Start game after 3 seconds!!" << endl;
	Sleep(3000);
	system("cls");
	int i = 0;
	//in_sentence();
	while (!written_queue.empty()) {
		i++;
		cout << "Current your correctness : " << entire_correctness << ", Current your speed : " << entire_correct / entire_time << endl;
		cout << i << ". " << written_queue.front() << endl;
		Sleep(10);
		in_sentence();
		Sleep(10);
		system("cls");
		entire_time += user_time;
		entire_correctness = check_info(written_queue, user_sentence, entire_correct);
		written_queue.pop();
	}
}

void Interface::load_info() {
	cout << "Please insert your name : ";
	getline(cin, user_info);
	basic_out();
	cout << "Great job! " << endl;
	cout << "           Your Score" << endl;
	cout << "Correctness : " << entire_correctness << " Speed : " << entire_correct / entire_time << endl;
}


int main() {
	Interface start;
	start.load_info();
	return 0;
}