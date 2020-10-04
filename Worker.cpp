#include "Worker.h"
using namespace std;
int CWorker::Menu()
{
	system("cls");
	cout << "\n\n\n\t\t��ǰ�˺ţ�" << m_admin.GetName() << "��" << m_admin.GetPriText() << "��" << endl;
	puts("\t\t********************************");
	puts("\t\t*                              *");
	puts("\t\t*\t1�����������Ϣ        *");
	puts("\t\t*\t2�������Ϣ            *");
	puts("\t\t*\t3��ɾ����Ϣ            *");
	puts("\t\t*\t4���޸���Ϣ            *");
	puts("\t\t*\t5��������Ϣ            *");
	if (m_admin.GetPriority())
		puts("\t\t*\t6���޸�����            *");
	else
		puts("\t\t*\t6���˻�����            *");
	puts("\t\t*\t0���˳�                *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
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
	puts("\t\t*\t1�����Ų���       *");
	puts("\t\t*\t2����������       *");
	puts("\t\t*\t3�����ʲ���       *");
	puts("\t\t*\t4�����ڲ���       *");
	puts("\t\t*\t0���˳�           *");
	puts("\t\t***************************");
	cout << "\t\t��ѡ��";
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
	puts("\t\t*\t1������������      *");
	puts("\t\t*\t2������������      *");
	puts("\t\t*\t3������������      *");
	puts("\t\t*\t4������������      *");
	puts("\t\t*\t0���˳�            *");
	puts("\t\t****************************");
	cout << "\t\t��ѡ��";
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
	puts("\t\t*\t1����¼       *");
	puts("\t\t*\t2��ע��       *");
	puts("\t\t*\t0���˳�       *");
	puts("\t\t***********************");
	cout << "\t\t��ѡ��";
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
	cout << "�������û�����";
	cin >> sName;
	cout << "���������룺";
	cin >> sPass;
	cout << "�����û�����(0���߼� 1����ͨ)��";
	cin >> nPrior;
	sprintf(s, "SELECT f_prior FROM t_admin WHERE f_name='%s'AND f_pass='%s'", sName.c_str(), sPass.c_str());
	int n = mysql_query(m_sql, s);
	if (n)
	{
		cout << "Login���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	auto res = mysql_store_result(m_sql);
	if (!res)
	{
		cout << "login��res���ݼ�����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
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
	cout << "�����빤�ţ�";
	cin >> numb;
	if (CheckNumb(numb))
		return;
	cout << "���������������ʺ���ְ����(yyyy-mm-dd):";
	cin >> sName >> fSala >> sDate;
	char s[256];
	sprintf(s, "insert into t_worker VALUE ( %d,'%s',%g,'%s')", numb, sName.c_str(), fSala, sDate.c_str());
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "��Ӵ���:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();

}

//void CWorker::Print()
//{
//	system("cls");
//	int n = mysql_query(m_sql, "SELECT * FROM t_worker");
//	if (n)
//	{
//		cout << "Print����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
//		return;
//	}
//	auto res = mysql_store_result(m_sql);
//	if (!res)
//	{
//		cout << "��ӡres����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
//		return;
//	}
//	MYSQL_ROW row ;//��ȡ����
//	cout << "\n\n\n";
//	while (row=mysql_fetch_row(res))
//	{
//		cout << "\t\t";
//		int m = mysql_num_fields(res);//��ȡ����
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
	cout << "��������Ҫɾ���Ĺ��ţ�";
	cin >> numb;
	if (!m_find.FindNumb(numb))
		return;
	cout << "��ȷ��Ҫɾ����[Y/N]:";
	char c;
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	char s[64];
	sprintf(s, "DELETE FROM  t_worker WHERE f_numb=%d", numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "Delete����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();
}

void CWorker::Modify()
{
	int numb;
	char c,s[256];
	string sName, sDate;
	float fSala;
	cout << "��������Ҫ�޸ĵĹ��ţ�";
	cin >> numb;
	if (!m_find.FindNumb(numb))
		return;
	cout << "��ȷ��Ҫ�޸���[Y/N]:";
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	cout << "���������������ʺ���ְ����(yyyy-mm-dd):";
	cin >> sName >> fSala >> sDate;
	sprintf(s, "UPDATE t_worker SET f_name='%s',f_sala=%g,f_date='%s' WHERE f_numb=%d",sName.c_str(),fSala,sDate.c_str(), numb);
	int n = mysql_query(m_sql, s);
	if (n)
		cout << "Modify����:(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
	else
		Print();
}

bool CWorker::ConnectDB()
{
	m_sql = mysql_init(NULL);
	if (!m_sql)
	{
		cout << "���ݿ���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		return false;
	}
	if (mysql_real_connect(m_sql, "localhost", "root", "123456", "worker", 3306, NULL, 0))
		return true;
	cout << "�������ݿ���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
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
			cout << "CheckNumb���󣺣�" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
			return false;
		}
		auto res = mysql_store_result(m_sql);
		if (res)
			b = res->row_count > 0;
		else
			cout << "CheckNumb����(res):(" << mysql_errno(m_sql) << ")" << mysql_errno(m_sql) << endl;
		mysql_free_result(res);
		if (!b)
			break;
		cout << "�����Ѿ����ڣ���������[0����]��";
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
