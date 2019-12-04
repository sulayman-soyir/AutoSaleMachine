//
// Created by sulay on 2019/11/26.
//
#include<utility>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include "Consumer.h"
//void Consumer::AddMoney(Bill *bill, int nums) {
//	vector<pair<Bill *, int>>::iterator it = wallet.begin(), end = wallet.end();
//	for (; it != end; ++it){
//
//	}
//}

bool Consumer::Bought(std::string drinkName)
{
	return true;
}

bool Consumer::Pay(float fee)
{
	//float totalMoney=0;
	//vector<pair<Bill *, int>>::iterator it = wallet.begin(), end = wallet.end();
	/*for (; it != end; it++)
	{
	totalMoney += it->first->GetVal();
	}
	if (totalMoney < fee)
	{
	std::cout << "**FAIL: NO ENGOUH MONEY!**" << std::endl;
	return false;
	}*/
	if (account < fee)
	{
		std::cout << "**FAILURE: NO ENGOUH MONEY!**" << std::endl;
		return false;
	}
	account -= fee;
	return true;
}

void Consumer::ShowInfo()
{
	std::cout << "+--------------------------------+--------------------------------+" << std::endl;
	std::cout << "|Name: " << name;
	std::string str1 = "|NAME: " + name;
	for (int i = str1.size() + 1; i <= 33; i++)
		std::cout << " ";
	std::cout << "|";
	std::string str2;
	stringstream ss;
	ss << account;
	ss >> str2;
	str1 = "Account: " + str2;
	std::cout << str1;
	for (int i = str1.size()+1; i <= 32; i++)
	{
		std::cout << " ";
	}
	std::cout << "|" << std::endl;
	std::cout << "+--------------------------------+--------------------------------+" << std::endl;

	//std::cout << "Have Bought:" << std::endl;
	for (int i = 0; i < drinkVec.size(); i++)
	{
		str1 = "|"+drinkVec[i].first.GetName();
		std::cout << str1;
		for (int j = str1.size() + 1; j <= 33; j++)
			std::cout << " ";
		std::cout << "|";
		ss.clear();
		ss << drinkVec[i].second;
		ss >> str1;
		std::cout << str1;
		for (int j = str1.size() + 1; j <= 32; j++)
			std::cout << " ";
		std::cout << "|" << std::endl;
	}
	std::cout << "+--------------------------------+--------------------------------+" << std::endl;
	std::cout << std::endl;
}

void Consumer::PushDrinkVec(const std::pair<Drink, int> &drinkNumPair)
{
	drinkVec.push_back(drinkNumPair);
}
