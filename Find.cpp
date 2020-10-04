#include "Find.h"
using namespace std;

bool CFind::FindNumb(int numb)
{
	bool b = false;
	char s[256];
	sprintf(s, "SELECT * FROM t_worker WHERE f_numb=%d", numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "FindNumb��ѯ���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
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
		cout << "FindNumb��ѯ����(res):(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	mysql_free_result(res);
	return b;
}
void CFind::FindbyNumb()
{
	int numb;
	cout << "��������Ҫ��ѯ�Ĺ��ţ�";
	cin >> numb;
	bool b = FindNumb(numb);
	if (b == false)
		cout << "û�в鵽" << numb << "���ţ�" << endl;
	system("pause");
}

void CFind::FindbyName()
{
	char sName[20],s[256];
	cout << "��������Ҫ��ѯ������:";
	cin >> sName;
	sprintf(s,"SELECT * FROM t_worker WHERE f_name Like '%%%s%%'", sName);
	Select(s);
}

void CFind::FindbySala()
{
	float fMin, fMax;
	char s[256];
	cout << "�����빤�ʶ�(��������)��";
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
	cout << "�������������ڣ�yyyy-mm-dd):";
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
		cout << "��ѯ���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return;
	}
	MYSQL_RES* res = mysql_store_result(m_sql);
	if (!res)
	{
		cout << "��ѯres����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
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
