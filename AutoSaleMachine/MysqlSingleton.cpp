#include "MysqlSingleton.h"
#include<iostream>

MysqlSingleton *MysqlSingleton::m_instance;
MysqlSingleton * MysqlSingleton::GetInstance()
{
	if (m_instance)
		return m_instance;
	m_instance = new MysqlSingleton();
	return m_instance;
}

bool MysqlSingleton::InitMysql()
{
	conn = new MYSQL();
	mysql_init(conn);
	if (!mysql_real_connect(conn, "localhost", "root", "271828", "tien", 3306, NULL, 0))
	{
		std::cout << "**ERROR: Failed To Connect To MysqlServer.**" << std::endl;
		return false;
	}
	return true;
}


int MysqlSingleton::Query(const std::string &queryStatement, std::vector<std::vector<std::string>> &queryRes,int colNum)
{
	if (!conn)
	{
		if (!InitMysql())
			return -1;
	}
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	int status = mysql_query(conn, &queryStatement[0]);
	
	res_set = mysql_store_result(conn);
	int count = mysql_num_rows(res_set);
	for (int i = 0; i < count; i++)
	{
		row = mysql_fetch_row(res_set);
		std::vector<std::string> temp;
		for(int j = 0; j < colNum; j++)
		{
			temp.push_back(row[j]);
		}
		queryRes.push_back(temp);
	}
	return 1;
}
