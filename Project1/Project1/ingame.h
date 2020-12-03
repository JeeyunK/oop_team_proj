#pragma once

#include "file.h"
#include "Score.h"

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <istream>
#include <fstream>
#include <time.h>
#include <cwchar>


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
	class file _file;
	class Score _score;

public:
	Sentence();
	virtual ~Sentence() {}
	//loading file
	virtual bool load_written();
	//print a sentence one by one
	virtual void in_sentence();
};


class UserInterface : public Sentence {
	string _userInfo;	//user nickname
	double _entireCorrectness;	//전체 정확도
	double _entireTime;		//전체 경과 시간
	//int _entireCorrect;
	unsigned int choice;	//메인 메뉴 입력
	bool running;	//프로그램 가동 status

public:
	UserInterface();
	~UserInterface() {}
	virtual bool basic_out();	//managing total stage playing (invoke every methods)
	virtual void load_info();	//invoking basic_out()
	bool load_shortwriting();
	virtual void choose_option();
	inline bool getRunning() const { return	running; }	//실행 중 출력
	void progressBar(float);		//로딩바 출력
	void fontsizeChange();		//폰트 크기 변경
	void reset_score();
	void reset_input();
};


/*class Start		//시작 화면
{
private:
	unsigned int choice;	//메인 메뉴 입력
	bool running;	//프로그램 가동 status
public:
	Start();
	~Start();

	//Functions
	void mainMenu();	//메인 메뉴 출력
	inline bool getRunning() const { return	running; }	//실행 중 출력
	void progressBar();		//로딩바 출력
	void fontsizeChange(int x, int y);		//폰트 크기 변경
};
*/

