#ifndef MINSOURCE_H
#define MINSOURCE_H
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
private:
	char m_name[256];
	int m_p;		//ָ��λ��
	int m_n;		//�ļ���С
	char* m_i;		//�ַ��ļ�����
	bool m_isLoad;
};
#endif