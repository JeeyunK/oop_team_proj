#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <istream>
#include <fstream>
#include <time.h>

using namespace std;

//checking correct/incorrect
class PracticeInfo {
public:
	int correct;   //the number of total correct letters
	int wrong;     //the number of total incorrect letters
	int tot_letters;	//the number of total letters, used in calculating speed
	double user_correctness;	//정확도

public:
	PracticeInfo();
	~PracticeInfo() {}
	//compare user_sentence and stage_sentence(for correctness)
	virtual double check_info(queue <string> written_vector, string user_sentence);
};

class Sentence : public PracticeInfo {
public:
	queue <string> _writtenQueue;	//save the stage file
	//vector <string> _userVector;
	string _userSentence;	//save user input
	int _writtenNum;	//stage number
	ifstream _writtenFile;	//stage file
	double _userTime;	//time(sec) for the last sentence

public:
	Sentence();
	virtual ~Sentence() {}
	//loading file
	virtual void load_written();
	//print a sentence one by one
	virtual void in_sentence();
};


class UserInterface : public Sentence {
	string _userInfo;	//user nickname
	double _entireCorrectness;	//전체 정확도
	double _entireTime;		//전체 경과 시간
	//int _entireCorrect;

public:
	UserInterface();
	~UserInterface() {}
	virtual void basic_out();	//managing total stage playing (invoke every methods)
	virtual void load_info();	//invoking basic_out()
};


