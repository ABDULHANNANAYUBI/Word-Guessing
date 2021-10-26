#ifndef FILE
#define FILE
#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
bool _Open(fstream&, string);
string convertToString(char*, int);
class _Dic {//Starting point of Dictionary
private:
	bool _TestTheSecret(string);
	set <string> _word;
	vector<string> _secret;
public:
	_Dic();
	_Dic(char*);
	~_Dic();
	string _GiveWord();
	bool _CorrectWord(string);
};

class _words : public _Dic {
private:
	int _countthematch(string);
	int _counttheplace(string);
	int _Numberofguesses;
	bool _cheated;
	string secret;

public:
	_words();
	~_words();
	void _PlaytheGame(_words&);
};
#endif // !FILE