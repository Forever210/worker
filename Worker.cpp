#include "Worker.h"
using namespace std;
int CWorker::Menu()
{
	system("cls");
	cout << "\n\n\n\t\t当前账号：" << m_admin.GetName() << "【" << m_admin.GetPriText() << "】" << endl;
	puts("\t\t********************************");
	puts("\t\t*                              *");
	puts("\t\t*\t1、浏览所有信息        *");
	puts("\t\t*\t2、添加信息            *");
	puts("\t\t*\t3、删除信息            *");
	puts("\t\t*\t4、修改信息            *");
	puts("\t\t*\t5、查找信息            *");
	if (m_admin.GetPriority())
		puts("\t\t*\t6、修改密码            *");
	else
		puts("\t\t*\t6、账户管理            *");
	puts("\t\t*\t0、退出                *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		while(SortMenu())
			;
		Print();
		break;
	case 2:
		Input();
		break;
	case 3:
		Delete();
		break;
	case 4:
		Modify();
		break;
	case 5:
		while(Find())
			;
		break;
	case 6:
		m_admin.MenuM();
		break;
	}
	return i;
}

int CWorker::Find()
{
	system("cls");
	puts("\n\n\n\t\t***************************");
	puts("\t\t*\t1、工号查找       *");
	puts("\t\t*\t2、姓名查找       *");
	puts("\t\t*\t3、工资查找       *");
	puts("\t\t*\t4、日期查找       *");
	puts("\t\t*\t0、退出           *");
	puts("\t\t***************************");
	cout << "\t\t请选择：";
	int i;
	cin >> i;
	switch (i)
	{
	case 1:
		m_find.FindbyNumb();
		break;
	case 2:
		m_find.FindbyName();
		break;
	case 3:
		m_find.FindbySala();
		break;
	case 4:
		m_find.FindbyDate();
		break;
	default:
		break;
	}

	return i;
}

int CWorker::SortMenu()
{
	system("cls");
	puts("\n\n\t\t****************************");
	puts("\t\t*\t1、按工号排序      *");
	puts("\t\t*\t2、按姓名排序      *");
	puts("\t\t*\t3、按工资排序      *");
	puts("\t\t*\t4、按日期排序      *");
	puts("\t\t*\t0、退出            *");
	puts("\t\t****************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	if (i > 0 && i < 5)
	{
		const char* fp[] = { "f_numb","f_name","f_sala","f_date" };
		Sort(fp[i - 1]);
	}
	return i;
}

int CWorker::LoginMenu()
{
	system("cls");
	puts("\n\n\t\t***********************");
	puts("\t\t*\t1、登录       *");
	puts("\t\t*\t2、注册       *");
	puts("\t\t*\t0、退出       *");
	puts("\t\t***********************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		Login();
		break;
	case 2:
		m_admin.Register();
		break;
	}
	return i;
}

bool CWorker::Login()
{
	string sName, sPass;
	int nPrior;
	system("cls");
	char s[256];
	cout << "请输入用户名：";
	cin >> sName;
	cout << "请输入密码：";
	cin >> sPass;
	cout << "输入用户级别(0、高级 1、普通)：";
	cin >> nPrior;
	sprintf(s, "SELECT f_prior FROM t_admin WHERE f_name='%s'AND f_pass='%s'", sName.c_str(), sPass.c_str());
	int n = mysql_query(m_sql, s);
	if (n)
	{
		cout << "Login错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	auto res = mysql_store_result(m_sql);
	if (!res)
	{
		cout << "login的res数据集错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	auto b = res->row_count > 0;
	if (b)
	{
		m_admin.m_sName = sName;
		auto row = mysql_fetch_row(res);
		m_admin.m_prior = atoi(*row);
		while (Menu())
			;
	}
	return b;


}

void CWorker::Sort(const char* sSQL)
{
	char s[256];
	sprintf(s, "select * from t_worker order by %s", sSQL);
	m_find.Select(s);
}

void CWorker::Input()
{
	int numb;
	string sName, sDate;
	float fSala;
	cout << "请输入工号：";
	cin >> numb;
	if (CheckNumb(numb))
		return;
	cout << "请输入姓名、工资和入职日期(yyyy-mm-dd):";
	cin >> sName >> fSala >> sDate;
	char s[256];
	sprintf(s, "insert into t_worker VALUE ( %d,'%s',%g,'%s')", numb, sName.c_str(), fSala, sDate.c_str());
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "添加错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();

}

//void CWorker::Print()
//{
//	system("cls");
//	int n = mysql_query(m_sql, "SELECT * FROM t_worker");
//	if (n)
//	{
//		cout << "Print错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
//		return;
//	}
//	auto res = mysql_store_result(m_sql);
//	if (!res)
//	{
//		cout << "打印res错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
//		return;
//	}
//	MYSQL_ROW row ;//获取行数
//	cout << "\n\n\n";
//	while (row=mysql_fetch_row(res))
//	{
//		cout << "\t\t";
//		int m = mysql_num_fields(res);//获取列数
//		while (m--)
//			printf("%-15s", *row++);
//		cout << endl;
//	}
//	mysql_free_result(res);
//	system("pause");
//}

void CWorker::Delete()
{
	int numb;
	cout << "请输入你要删除的工号：";
	cin >> numb;
	if (!m_find.FindNumb(numb))
		return;
	cout << "你确定要删除吗？[Y/N]:";
	char c;
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	char s[64];
	sprintf(s, "DELETE FROM  t_worker WHERE f_numb=%d", numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "Delete错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();
}

void CWorker::Modify()
{
	int numb;
	char c,s[256];
	string sName, sDate;
	float fSala;
	cout << "请输入你要修改的工号：";
	cin >> numb;
	if (!m_find.FindNumb(numb))
		return;
	cout << "你确定要修改吗？[Y/N]:";
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	cout << "请输入姓名、工资和入职日期(yyyy-mm-dd):";
	cin >> sName >> fSala >> sDate;
	sprintf(s, "UPDATE t_worker SET f_name='%s',f_sala=%g,f_date='%s' WHERE f_numb=%d",sName.c_str(),fSala,sDate.c_str(), numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "Modify错误:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();
}

bool CWorker::ConnectDB()
{
	m_sql = mysql_init(NULL);
	if (!m_sql)
	{
		cout << "数据库错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	if (mysql_real_connect(m_sql, "localhost", "root", "123456", "worker", 3306, NULL, 0))
		return true;
	cout << "连接数据库错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	return false;
}

bool CWorker::CheckNumb(int& numb)
{
	bool b = false;
	char s[64];
	while (true)
	{
		sprintf(s, "SELECT f_numb from t_worker where f_numb=%d", numb);
		int n = mysql_query(m_sql, s);
		if (n)
		{
			cout << "CheckNumb错误：（" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
			return false;
		}
		auto res = mysql_store_result(m_sql);
		if (res)
			b = res->row_count > 0;
		else
			cout << "CheckNumb错误(res):(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		mysql_free_result(res);
		if (!b)
			break;
		cout << "工号已经存在，重新输入[0放弃]：";
		cin >> numb;
		if (!numb)
			return true;
	}
	return b;
}



int CWorker::Start()
{
	if (!ConnectDB())
		return -1;
	mysql_query(m_sql, "set names 'gbk'");
	while (LoginMenu())
		;
	return 0;
}

CWorker::CWorker()
{
}
