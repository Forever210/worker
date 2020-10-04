#pragma once
#include"define.h"
class CFind
{
	MYSQL*& m_sql;
public:
	void FindbyNumb();
	void FindbyName();
	void FindbySala();
	void FindbyDate();

	void Select(const char* sSQL);
	bool FindNumb(int numb);
	CFind(MYSQL*& sql);
};

