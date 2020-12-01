# oop_team_proj
: 김성주, 김지윤, 양희웅, 전윤형

DGIST 객체 지향 프로그래밍 팀프로젝트를 위한 repo입니다.
최종 제출은 Project1 폴더의 프로젝트 파일로 제출할 생각입니다.

## Class
### ingame.h
1. class PracticeInfo

짧은글쓰기 stage 플레이 시 사용됨. 한 문장의 correct, wrong 정보를 확인 및 저장하는 데 사용함.

- member variable : 
  - int correct: stage 전체 맞은 글자 수
  - int wrong: stage 전체 틀린 글자 수
  - int tot_letters: stage 전체 글자 수
  - double user_correctness: 한 문장의 정확도 정보
- member function : 
  - double check_info(queue <string> written_vector, string user_sentence): 정답 문장과 유저가 입력한 문장을 비교하는 function

2. class Sentence : public PracticeInfo

class PracticeInfo를 상속함. 짧은글쓰기 stage list에서 유저가 선택한 파일을 열고, 플레이 중 유저의 input sentence를 받는다.

- member variable :
  - queue <string> _writtenQueue: 선택한 stage의 txt 파일의 문장들을 queue 형태로 저장한다.
  - string _userSentenc: 유저가 플레이 시 입력하는 sentence를 저장한다.
  - int _writtenNum: 선택한 stage의 index를 저장한다.
  - ifstream _writtenFile: 선택한 stage의 txt 파일.
  - double _userTime: 한 문장 입력에 소요된 시간
  - class file _file: stage list에 대한 정보를 다룬다.
  - class Score _score: stage score에 대한 정보를 다룬다.
- member function:
	- bool load_written(): file class를 통해 존재하는 stage list를 띄우고, 유저가 선택하면 해당 stage의 txt file을 연다.
	- void in_sentence(): stage txt file의 문장이 한 줄 출력되면, 이에 유저의 입력을 받아 소요 시간을 측정한다.
  
 3. class UserInterface : public Sentence
 
 Sentence class를 상속함. user에게 보이는 Interface를 관리하는 class이다. 
 
 - member variable:
	- string _userInfo: user가 입력한 nickname을 저장한다. 이후 ranking update에도 사용된다.
	- double _entireCorrectness: stage 플레이 시 정확도를 저장한다.
	- double _entireTime: stage 플레이 시 전체 경과 시간을 저장한다. 타수 계산에 사용된다.
	- unsigned int choice: 유저의 옵션 입력을 위해 사용된다.
	- bool running: 실행 상태. 사용하지 않는 variable
- member function:
	- bool basic_out(): 짧은글쓰기 play의 interface를 관리한다. 유저에게 입력마다 정확도와 타수를 알려준다.
	- void load_info(): 프로그램의 main interface를 관리한다.
  - void choose_option(): main menu 중 option을 선택했을 때의 interface를 관리한다.
  - bool getRunning(): running status를 출력한다. 사용하지 않음.
  - progressBar(): 로딩 바를 출력한다. 사용하지 않음.
  - fontsizeChange(): option의 Font Size Change를 선택했을 때의 interface를 관리한다.
  
 
### file.h
1. struct file_struct

file의 이름과 경로를 관리하기 위한 struct

2. class file

짧은글쓰기 stage의 file 입출력 관련 기능을 담당하는 class이다.

- member variable:
	- struct file_struct file_list: 스테이지 파일의 정보를 저장한다.
	- int size: file_list에 저장된 file_struct의 수를 저장한다.
- member function:
	- void update_filepath(): filepath.txt 파일 내에 저장된 file의 이름, 경로 정보를 file_list에 저장한다.
	- void show_path(): 저장된 file_struct의 PATH를 iterate해준다. 디버깅 용
	- void get_file(): option 메뉴의 Insert the Game File을 선택했을 때의 interface를 관리하고, 유저가 입력하는 filename과 filepath를 add_file() 함수로 전달한다.
	- bool add_file(string filename, string filepath): 전달받은 정보를 filepath.txt에 저장한다. 만약 입력받은 경로에 파일이 존재하지 않을 경우 이를 유저에게 알린다.
	- void show_list(): 저장된 file_list의 name을 iterate해준다.
	

### Score.h
1. struct form

ranking으로 저장할 닉네임, 정확도, 타수 정보를 저장한다.

2. class Score

플레이 한 점수를 관리하는 class이다.

- member variable:
	- int size: 점수를 저장하는 INITIAL_FILE.txt에 저장된 form struct의 수를 저장한다.
	- struct form list: 점수 정보를 저장한다.
- member function:
	- void update_score(): INITIAL_FILE.txt에 저장된 정보를 불러와 sorting한다.
	- void show_score(): main menu의 Ranking 옵션에 들어갔을 때 존재하는 ranking 정보를 print해준다.
	- void Add_Score(string name, double correctness, int speed): 짧은글쓰기 플레이 후 점수를 INITIAL_FILE.txt에 저장해준다.
