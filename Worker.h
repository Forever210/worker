#pragma once


#include"Admin.h"
#include"Find.h"
class CWorker
{
	MYSQL* m_sql;
	CAdmin m_admin = m_sql;
	CFind m_find = m_sql;
	int Menu();
	int Find();
	int SortMenu();
	void Sort(const char* sSQL);
	void Input();
	void Print()
	{
		m_find.Select("SELECT * FROM t_worker");
	}
	void Delete();
	void Modify();
	bool Login();
	bool ConnectDB();
	bool CheckNumb(int& numb);
	int LoginMenu();
public:
	int Start();
	CWorker();
};

