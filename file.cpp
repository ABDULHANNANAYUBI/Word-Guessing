#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<algorithm>
#include<string.h>
#include "file.h"

using namespace std;
bool _Open(fstream& _filen, string name) {
	_filen.open(name, ios::in);
	if (!_filen.is_open())
		return false;
	else
		return true;
}

string convertToString(char* a, int size) {
	string s = "";
	for (int i = 0; i < size; i++) {
		s = s + a[i];
		if (a[i] == '\0') break;
	}
	return s;
}
_Dic::_Dic() {
	bool _TestTheSecret(string _Sword = NULL);
}

_Dic::_Dic(char* __nameoffile) {//Reading File
	fstream _file;
	string _Read;
	int _st = _Open(_file, __nameoffile);
	if (_st == true) cout << "The File Opened Succesfully.." << endl;
	else {
		cout << "Error..!" << endl; exit(0);
	}
	_file >> _Read;
	while (!_file.eof()) {
		_word.insert(_Read);
		_file >> _Read;
	}
}

bool _Dic::_TestTheSecret(string _getWord) {
	transform(_getWord.begin(), _getWord.end(), _getWord.begin(), ::toupper);
	int flag = false;
	for (int i = 0; i < _secret.size(); i++) {
		string temp = _GiveWord();
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		if (_getWord == temp) {
			flag = true;
			break;
		}
		else
			flag = false;
	}
	return flag;
}

string _Dic::_GiveWord() {//Getting Random Word
	string Temp;
	srand(time(NULL));
	for (set<string>::iterator it = _word.begin(); it != _word.end(); ++it) {
		Temp = *it;
		int flag = 0, n = Temp.length();
		char* temp = new char[n + 1];
		Temp.copy(temp, Temp.size() + 1);
		temp[Temp.size()] = '\0';
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < n - i; j++) {
				if (temp[i] == temp[j + i]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) break;
		}
		if (flag == 0) {
			string _Temp = convertToString(temp, n);
			_secret.push_back(_Temp);
		}
		delete[] temp;
	}
	string _word = _secret[rand() % _secret.size()];
	cout << "The SECRET Word is : ";
	cout << _word << endl;//The Random word.......
	return _word;
}

bool _Dic::_CorrectWord(string _getWord) {
	transform(_getWord.begin(), _getWord.end(), _getWord.begin(), ::toupper);
	int flag = false;
	for (set<string>::iterator it = _word.begin(); it != _word.end(); ++it) {
		string temp = *it;
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		if (_getWord == temp) {
			flag = true;
			break;
		}
		else
			flag = false;
	}
	return flag;
}

_words::_words() {//Default Constructor
	int _countthematch(string _words = NULL);
	int _counttheplace(string _words = NULL);
	int _Numberofguesses = 0;
	bool _cheated = false;
	string secret = "\0";
}

void _words::_PlaytheGame(_words& _w) {
	char _file[] = "words.txt";
	_Dic d(_file);
	string Word, _cheat = "xxxxx";
	bool _isValid, _tesethesecret, _cheatt = false;
	int _Countforcommon, _CounterforCommonPlace, _NumberofGuess = 0;
	secret = d._GiveWord();
	cout << "\n\n\n\n\t\t\t***********Welcome To Guess And Win Game***********" << endl;
	cout << "\t\t\t***********You Have To Enter Five Letter Word***********" << endl;
	while (true) {
		cout << "Enter your String : ";
		getline(cin, Word); transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
		if (Word == secret) { _NumberofGuess++; break; }
		if (Word == _cheat) { _cheated = true; _cheatt = true; }
		if (_cheated == true) {
			_NumberofGuess++;
			cout << "The Secret Word is : ";
			cout << secret << endl;
			cout << "Enter your String : ";
			getline(cin, Word); transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
			if (Word == secret) { _NumberofGuess++; break; }
			_cheated = false;
		}
		_isValid = d._CorrectWord(Word);
		if (_isValid == true) {
			_NumberofGuess++;
			_Countforcommon = _words::_countthematch(Word);
			cout << "The common Letter Number : ";
			cout << _Countforcommon << endl;
			_CounterforCommonPlace = _words::_counttheplace(Word);
			cout << "The common Letter Place : ";
			cout << _CounterforCommonPlace << endl;
		}
		else {
			cout << "The Word Is'nt In Dictionary...!" << endl;
		}
	}
	_Numberofguesses = _NumberofGuess;
	if (_cheatt == true) {
		cout << endl << "You Guessed The Word in " << _Numberofguesses << " time by using (HINT)" << endl;
	}
	else {
		cout << endl << "You Guessed The Word in " << _Numberofguesses << " time" << endl;
	}
}

int _words::_countthematch(string _getstring) {
	int counter = 0;
	char* temp = new char[_getstring.size() + 1];
	char* temp1 = new char[secret.size() + 1];
	_getstring.copy(temp, _getstring.size() + 1);
	temp[_getstring.size()] = '\0';
	secret.copy(temp1, secret.size() + 1);
	temp1[secret.size()] = '\0';
	for (int i = 0; i < _getstring.size(); i++) {
		for (int j = 0; j < _getstring.size(); j++) {
			if (temp1[i] == temp[j]) {
				counter++;
				break;
			}
		}
	}
	delete[] temp, temp1;
	return counter;
}

int _words::_counttheplace(string _getS) {
	int counter = 0;
	char* temp = new char[_getS.size() + 1];
	char* temp1 = new char[secret.size() + 1];
	_getS.copy(temp, _getS.size() + 1);
	temp[_getS.size()] = '\0';
	secret.copy(temp1, secret.size() + 1);
	temp1[secret.size()] = '\0';
	for (int i = 0; i < _getS.size(); i++) {
		if (temp[i] == temp1[i]) {
			counter++;
		}
	}
	delete[] temp, temp1;
	return counter;
}
_Dic :: ~_Dic() {}//Distructor
_words ::~_words() {}//Distructor
