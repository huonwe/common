#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct PairNode {
	string key;
	string value;
	PairNode* next;
};

class Config
{
public:
	Config();
	Config(string file_path);
	~Config();
	bool insert(string key, string value);
	string query(string key);

	void printAll();
private:
	bool LineInitilize();
	bool writeFile();
	bool readFile();
	void freeLine();
private:
	string file_path;
	PairNode* head;

};

