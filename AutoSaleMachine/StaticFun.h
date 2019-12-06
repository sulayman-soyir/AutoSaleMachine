#pragma  once
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include<utility>
#include "ASMOwner.h"
#include "MysqlSingleton.h"
#include "Consumer.h"
#include "Drink.h"
#define NAMESPACE_CD_BEGIN namespace CD{
#define NAMESPACE_CD_END }

NAMESPACE_CD_BEGIN

void ShowASMOwnerMachineInfo(ASMOwner asmOwner)
{
	//asmOwner.ShowDrinksInfo();
}

bool initAsmOwner(ASMOwner &asmOwner,std::map<std::string,float> &name_price)
{
	MysqlSingleton *mysql = MysqlSingleton::GetInstance();
	stringstream ss;
	std::vector<vector<std::string>> machines;
	mysql->Query("select M_id from autosalemachine", machines, 1);
	for (int i = 0; i < machines.size(); i++)
	{
		std::string queryStatement = "select name,drinkNum from drinksinautosalemachine where M_id=" + machines[i][0];
		std::vector<vector<std::string>> machineInfo; //name <--> drinknum
		mysql->Query(queryStatement, machineInfo, 2);
		
		int id;
		ss.clear();
		ss << machines[i][0];
		ss >> id;

		AutoSaleMachine saleMachine(id);
		std::vector<pair<Drink, int>> drinkInMachine;
		for (int j = 0; j < machineInfo.size(); j++)
		{
			Drink drinks(machineInfo[j][0], name_price[machineInfo[j][0]]);
			ss.clear();
			int num;
			ss << machineInfo[i][1];
			ss >> num;
			pair<Drink, int>temp;
			temp = std::make_pair(drinks, num);
			drinkInMachine.push_back(temp);
		}
		saleMachine.InitDrinks(drinkInMachine);
		asmOwner.InitMachine(saleMachine);
	}
	return true;
}

/*
	<饮料,价格>键对
*/
bool initDrink(std::map<std::string,float> &drink_price)
{
	MysqlSingleton *mysql = MysqlSingleton::GetInstance();

	stringstream ss;
	std::vector<vector<std::string>>drinksWithPrice;
	
	
	mysql->Query("select * from drinks", drinksWithPrice, 2);
	for (int i = 0; i < drinksWithPrice.size(); i++)
	{
		ss.clear();
		float money;
		ss << drinksWithPrice[i][1];
		ss >> money;
		drink_price[drinksWithPrice[i][0]] = money;
	}
	return true;
}

bool initConsumer(Consumer &consumer)
{
	MysqlSingleton *mysql = MysqlSingleton::GetInstance();
	stringstream ss;

	std::vector<std::vector<std::string>> conStr;
	mysql->Query("select * from consumer", conStr, 2);
	consumer.SetName(conStr[0][0]);
	
	float money;
	ss.clear();
	ss << conStr[0][1];
	ss >> money;
	consumer.initMoney(money);

	std::vector<std::vector<std::string>> boughtVec;
	std::pair<Drink, int>drinkNumPair;
	//std::cout << "select drinkname,num from already_buy where name=\"" + conStr[0][0] + "\"" << std::endl;
	mysql->Query("select drinkname,num from already_buy where name=\"" + conStr[0][0]+"\"", boughtVec,2);
	for (int i = 0; i < boughtVec.size(); i++)
	{
		
		std::vector<std::vector<std::string>> drinkPrice;
		mysql->Query("select price from drinks", drinkPrice, 1);
		
		ss.clear();
		int num;
		ss << boughtVec[i][1];
		ss >> num;

		ss.clear();
		float price;
		ss << drinkPrice[0][0];
		ss >> price;

		Drink drink(boughtVec[i][0], price);
		drinkNumPair = make_pair(drink, num);
		consumer.PushDrinkVec(drinkNumPair);
	}
	return true;
}
bool JudgeInputValid(std::string input, const std::vector<char>& validRange, std::string SPECIAL_INPUT="")
{
	if (validRange.empty() || validRange.size() != 2)
	{
		std::cout << "*****ERROR: RANGE WRONG*****" << std::endl;
		return false;
	}
	if (SPECIAL_INPUT == "quit" || SPECIAL_INPUT == "Quit")
	{
		exit(1);
	}
	if (input.empty())
	{
		std::cout << "*****EMPTY INPUT*****" << std::endl;
		return false;
	}
	if (input.size() != 1)
	{
		std::cout << "*****INVALID INPUT*****" << std::endl;
		return false;
	}
	else if (input[0] < validRange[0] || input[0] > validRange[1])
	{
		std::cout << "****INPUT OUT OF RANGE*****" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}
void ChoiceOutput(std::vector<std::string> choices,std::string tip="option>")
{
	for (int i = 0; i < choices.size(); i++)
	{
		std::cout << choices[i] << std::endl;
	}
	std::cout << tip;
}

NAMESPACE_CD_END