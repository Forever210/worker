#pragma once
#include"define.h"
class CAdmin
{
	
	MYSQL*& m_sql;
	
	
	void Input();
	void Print();
	void Delete();
	bool CheckName(char* sName);
	bool FindName(char* sName);
	bool CheckPass(const char* sOdl);
	void ChangePass();
	inline void Prompt(const char* sText)
	{
		std::cout << sText << std::endl;
		system("pause");
	}
	int Menu();
public:
	int MenuM();
	void Register();
	std::string m_sName;
	int m_prior;
	std::string GetPriText()const;

	std::string GetName()
	{
		return m_sName;
	}
	
	int GetPriority()
	{
		return m_prior;
	}
	
	CAdmin(MYSQL*& sql);
};

