#ifndef MIN_SOURCE_H
#define MIN_SOURCE_H
#include<string>
using std::string;
class MinSource
{
public:
	MinSource();
	~MinSource();
	MinSource& operator=(MinSource& s);
public:
	void Init(char* f);
	bool ReadC(char& c);
	void ResetP();
	void BackP();
	bool ReadLine(string& s);
private:
	char m_name[256];
	int m_p;		//指针位置
	int m_n;		//文件大小
	char* m_i;		//字符文件内容
	bool m_isLoad;
};
#endif
