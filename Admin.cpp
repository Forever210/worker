#include "Admin.h"
using namespace std;


void CAdmin::Register()
{
	char sName[32], sPass[32], sNew[32], s[256];
	int nPrior;
	system("cls");
	cout << "\t\t注册账号" << endl;
	cout << "请输入用户名：";
	cin >> sName;
	bool b = CheckName(sName);
	if (b)
		return;
	cout << "请输入密码：";
	cin >> sPass;
	cout << "再输一次密码：";
	cin >> sNew;
	if (strcmp(sPass, sNew) != 0)
		return;
	cout << "请输入等级(0、高级 1、普通):";
	cin >> nPrior;
	sprintf(s, "insert into t_admin value('%s','%s',%d)", sName, sPass, nPrior);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "注册错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;

}
bool CAdmin::CheckPass(const char* sOdl)
{
	bool b = false;
	char s[256];
	sprintf(s, "select * from t_admin where f_pass='%s'", sOdl);
	int n = mysql_query(m_sql, s);
	if (n)
	{
		cout << "pass错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	auto res = mysql_store_result(m_sql);
	if (res)
		b = res->row_count > 0;
	else
		cout << "pass的pass错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	return b;
}
void CAdmin::Input()
{
	char sName[32], sPass[32];
	int nPrior;
	char s[256];
	cout << "请输入用户名：";
	cin >> sName;
	auto b = CheckName(sName);
	if (b)
		return;
	cout << "请输入密码：";
	cin >> sPass;
	cout << "输入用户级别(0、高级 1、普通)：";
	cin >> nPrior;

	sprintf(s, "INSERT INTO t_admin VALUE('%s','%s',%d)", sName, sPass, nPrior);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "添加错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();

}
void CAdmin::Print()
{
	system("cls");
	int n = mysql_query(m_sql, "select * from t_admin");
	if (n)
	{
		cout << "打印错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return;
	}
	MYSQL_RES* res = mysql_store_result(m_sql);
	if (!res)
	{
		cout << "打印res错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return;
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		int m = mysql_num_fields(res);
		while (m--)
			printf("%-20s", *row++);
		cout << endl;
	}
	mysql_free_result(res);
	system("pause");
}
void CAdmin::Delete()
{
	char sName[32], str[256];
	cout << "请输入你要删除的用户：";
	cin >> sName;
	bool b = FindName(sName);
	if (!b)
	{
		cout << "没有该用户！" << endl;
		return;
	}
	cout << "你确定要删除吗?[Y/N]:";
	char c;
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	sprintf(str, "delete from t_admin where f_name='%s'", sName);
	int n = mysql_query(m_sql, str);
	if (n)
		cout << "删除错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();
}
void CAdmin::ChangePass()
{
	char sPass[32], sOdl[32], sRep[32], s[256];
	cout << "请输入旧密码：";
	cin >> sOdl;
	bool b = CheckPass(sOdl);
	if (!b)
		return;
	cout << "请输入新密码：";
	cin >> sPass;
	cout << "在输入一次密码：";
	cin >> sRep;
	if (strcmp(sPass, sRep) != 0)
		cout << "密码不一致！" << endl;
	else
	{
		sprintf(s, "UPDATE t_admin SET f_pass = '%s' WHERE f_name = '%s'", sPass, m_sName.c_str());
		int n = mysql_query(m_sql, s);
		if (n)
			cout << "change错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	}

}
bool CAdmin::CheckName(char* sName)
{
	bool b = false;
	char s[256];
	while (true)
	{
		sprintf(s, "select * from t_admin where f_name='%s'", sName);
		int n = mysql_query(m_sql, s);
		if (n)
		{
			cout << "Check用户名错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
			return false;
		}
		auto res = mysql_store_result(m_sql);
		if (res)
			b = res->row_count > 0;
		else
			cout << "Check用户res错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		if (!b)
			break;
		cout << "用户已存在，请重新输入[E是放弃]：";
		cin >> sName;
		if (strcmp(sName, "E"))
			return true;
	}
	return b;
}

bool CAdmin::FindName(char* sName)
{
	bool b = false;
	char s[256];
	sprintf(s, "select * from t_admin where f_name='%s'", sName);
	int n = mysql_query(m_sql, s);
	if (n)
	{
		cout << "Check用户名错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	auto res = mysql_store_result(m_sql);
	if (res)
	{
		b = res->row_count > 0;
		if(b)
		{
			auto row = mysql_fetch_row(res);
			n = mysql_num_fields(res);
			while (n--)
				printf("%15s", *row++);
			cout << endl;
		}
	}
	else
		cout << "Check用户res错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	mysql_free_result(res);
	return b;
}

int CAdmin::MenuM()
{
	if (GetPriority())
		ChangePass();
	else
		while (Menu())
			;
	return 0;
}
int CAdmin::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1、浏览账号            *");
	puts("\t\t*\t2、添加账号            *");
	puts("\t\t*\t3、删除账号            *");
	puts("\t\t*\t4、修改密码            *");
	puts("\t\t*\t0、返回主菜单           *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		Print();
		break;
	case 2:
		Input();
		break;
	case 3:
		Delete();
		break;
	case 4:
		ChangePass();
		break;
	}
	return i;
}

std::string CAdmin::GetPriText()const
{
	switch (m_prior)
	{
	case 0:
		return "高级";
	case 1:
		return "普通";
	}
	return "未知";
}

CAdmin::CAdmin(MYSQL*& sql) :m_sql(sql), m_sName(""), m_prior(-1)
{
}