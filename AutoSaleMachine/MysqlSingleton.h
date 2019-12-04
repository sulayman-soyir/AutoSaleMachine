#pragma once
#include<mysql.h>
#include<string>
#include<vector>
class MysqlSingleton{
public:
	~MysqlSingleton(){};
	static MysqlSingleton * GetInstance();
	int Query(const std::string &queryStatement, std::vector<std::vector<std::string>> &queryRes, int colNum);

private:
	MysqlSingleton() : conn(nullptr){};
	bool InitMysql();
private:
	static MysqlSingleton *m_instance;
	MYSQL *conn;

};