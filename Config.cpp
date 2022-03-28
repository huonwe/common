#include "Config.h"

Config::Config()
{
	file_path = ".config";
	LineInitilize();
	readFile();
}

Config::Config(string file_path)
{
	this->file_path = file_path;
	LineInitilize();
	readFile();
}

Config::~Config()
{
	freeLine();
	if (this->head != nullptr)
	{
		delete this->head;
	}
}

bool Config::LineInitilize()
{
	try
	{
		PairNode* head = new PairNode;
		head->key = "head";
		head->value = "head";
		head->next = nullptr;
		this->head = head;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
	
}

bool Config::writeFile()
{
	try
	{
		string key, value;
		PairNode* p = head;
		ofstream ofs;
		ofs.open(this->file_path, ios::out);
		ofs << "******* SAP Control APP Config File *******" << endl;
		while (p->next != nullptr)
		{
			p = p->next;
			ofs << p->key << "=" << p->value << endl;
		}
		ofs.close();
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool Config::readFile()
{
	try
	{
		ifstream ifs;
		ifs.open(this->file_path, ios::in);
		string st, key, value;
		char line[50];
		string::size_type idx;
		// 遍历文件到最后 按行
		while (!ifs.eof())
		{
			st = "";
			ifs >> st;
			if (st[0] == '#')
			{
				continue;
			}
			idx = st.find("=");
			if (idx == string::npos)	// 无 =
			{
				continue;
			}
			key = st.substr(0, idx);
			value = st.substr(idx + 1, st.length() - idx);
			insert(key, value);
		}
		ifs.close();
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
	
}

void Config::freeLine()
{
	PairNode* p = head->next;
	PairNode* cur = p;
	while (cur!=nullptr)
	{
		cur = p->next;
		delete p;
		p = cur;
	}
	head->next = nullptr;
}

bool Config::insert(string key, string value)
{
	if (this->head == nullptr)
	{
		return false;
	}
	try
	{	
		PairNode* p = head;
		while (p->next!=nullptr)
		{
			p = p->next;
			if (p->key.compare(key)==0)	// same		/-1 diff
			{
				p->value = value;
				return true;
			}
		}
		PairNode* node = new PairNode;
		node->key = key;
		node->value = value;
		node->next = nullptr;
		p->next = node;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

string Config::query(string key)
{
	try
	{
		PairNode* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
			if (p->key.compare(key) == 0)	// same		/-1 diff
			{
				return p->value;
			}
		}
		return "NULL";
	}
	catch (const std::exception&)
	{
		return "NULL";
	}
}

void Config::printAll()
{
	try
	{
		PairNode* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
			cout << p->key << "\t" << p->value << endl;
		}
	}
	catch (const std::exception&)
	{
		cout << "Failed" << endl;
	}
}
