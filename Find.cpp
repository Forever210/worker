#include "Find.h"
using namespace std;

bool CFind::FindNumb(int numb)
{
	bool b = false;
	char s[256];
	sprintf(s, "SELECT * FROM t_worker WHERE f_numb=%d", numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "FindNumb查询错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	auto res = mysql_store_result(m_sql);
	if (res)
	{
		b = res->row_count > 0;
		if (b)
		{
			auto row = mysql_fetch_row(res);
			n = mysql_num_fields(res);
			while (n--)
				printf("%15s", *row++);
			cout << endl;
		}
	}
	else
		cout << "FindNumb查询错误(res):(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	mysql_free_result(res);
	return b;
}
void CFind::FindbyNumb()
{
	int numb;
	cout << "请输入你要查询的工号：";
	cin >> numb;
	bool b = FindNumb(numb);
	if (b == false)
		cout << "没有查到" << numb << "工号！" << endl;
	system("pause");
}

void CFind::FindbyName()
{
	char sName[20],s[256];
	cout << "请输入你要查询的姓名:";
	cin >> sName;
	sprintf(s,"SELECT * FROM t_worker WHERE f_name Like '%%%s%%'", sName);
	Select(s);
}

void CFind::FindbySala()
{
	float fMin, fMax;
	char s[256];
	cout << "请输入工资段(两个正数)：";
	cin >> fMin >> fMax;
	if (fMin > fMax)
		swap(fMin, fMax);
	sprintf(s, "SELECT * FROM t_worker WHERE f_sala>=%g AND f_sala<=%g", fMin, fMax);
	Select(s);
}

void CFind::FindbyDate()
{
	string sDate1, sDate2;
	char s[256];
	cout << "请输入两个日期（yyyy-mm-dd):";
	cin >> sDate1 >> sDate2;
	sprintf(s, "SELECT * FROM t_worker WHERE f_date>='%s' AND f_date<='%s'", sDate1.c_str(), sDate2.c_str());
	Select(s);
}

void CFind::Select(const char* sSQL)
{
	system("cls");
	int n = mysql_query(m_sql, sSQL);
	if (n)
	{
		cout << "查询错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return;
	}
	MYSQL_RES* res = mysql_store_result(m_sql);
	if (!res)
	{
		cout << "查询res错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return;
	}
	MYSQL_ROW row;
	cout << "\n\n\n\n\n";
	while (row = mysql_fetch_row(res))
	{
		cout << "\t\t";
		int l = mysql_num_fields(res);
		while (l--)
			printf("%-15s", *row++);
		cout << endl;
	}
	mysql_free_result(res);
	system("pause");
}

CFind::CFind(MYSQL*& sql):m_sql(sql)
{
}
