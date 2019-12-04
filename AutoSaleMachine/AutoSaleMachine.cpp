#include<iostream>
#include<utility>
#include<sstream>
#include"AutoSaleMachine.h"
#include "Drink.h"
AutoSaleMachine& AutoSaleMachine:: operator =(const AutoSaleMachine &othrs)
{
	this->currentDrinkNums = othrs.currentDrinkNums;
	this->m_id = othrs.m_id;
	this->money = othrs.money;
	pair<Drink, int>drink_num;
	for (int i = 0; i < othrs.DrinkindWithNums.size(); i++)
	{
		drink_num = othrs.DrinkindWithNums[i];
		this->DrinkindWithNums.push_back(drink_num);
	}
	return *this;
}
void AutoSaleMachine::AddDrink(Drink drinkItem, int nums) {
	if (currentDrinkNums == MaxDrinkNums) {
		std::cout << "**Failure: The machine No." << GetId() << "is already full**" << std::endl;
		return;
	}
	else if (currentDrinkNums + nums > MaxDrinkNums) {
		std::cout << "**Failure: The machine's left space can only fill " << MaxDrinkNums - currentDrinkNums << std::endl;
		return;
	}
	else {
		for (int i = 0; i < DrinkindWithNums.size(); ++i) {
			if (DrinkindWithNums[i].first.GetName() == drinkItem.GetName()) {
				DrinkindWithNums[i].second += nums;
				return;
			}
		}
		if (DrinkindWithNums.size() != MaxItemKind){
			pair<Drink, int>temp = make_pair(drinkItem, nums);
			DrinkindWithNums.push_back(temp);
			return;
		}
		else{
			std::cout << "**Failure: The machine can only fill 6 kinds of drinks**" << std::endl;
			return;
		}

	}
}
void AutoSaleMachine::DeleteDrinkByName(string name) {
	vector<pair<Drink, int>>::iterator it = DrinkindWithNums.begin(), end = DrinkindWithNums.end();
	for (; it != end; ++it){
		if ((*it).first.GetName() == name){
			currentDrinkNums -= (*it).second;
			DrinkindWithNums.erase(it);
		}
	}
	std::cout << "**ERROR: FAILURE TO CANCEL DRINK: HAVE NO THIS KIND OF DRINK.**" << std::endl;
}
bool AutoSaleMachine::ChangePrice(string drinkName, float targetPrice) {
	vector<pair<Drink, int>>::iterator it = DrinkindWithNums.begin(), end = DrinkindWithNums.end();
	for (; it != end; ++it){
		if ((*it).first.GetName() == drinkName) {
			(*it).first.SetPrice(targetPrice);
			return true;
		}
	}
	return false;
}

void AutoSaleMachine::InitDrinks(const std::vector<pair<Drink, int>> &initDrinks)
{
	for (int i = 0; i < initDrinks.size(); i++)
	{
		DrinkindWithNums.push_back(initDrinks[i]);
	}
}

void AutoSaleMachine::ShowInfo(float money)
{
	//std::cout << std::endl;
	std::cout << "Machine Id: " << GetId() << std::endl;
	std::cout << "+----+--------------------------------+--------+----------------+----------------+" << std::endl;//4+32+8+16+16
	std::cout << "| id |            DrinkName           | Price  |      Num       |   PaidCanBuy   |" << std::endl;
	std::cout << "+----+--------------------------------+--------+----------------+----------------+" << std::endl;
	for (int i = 0; i < DrinkindWithNums.size(); i++)
	{
		//id
		stringstream ss;
		string tempstr;
		ss << i + 1;
		ss >> tempstr;
		string str = "|" + tempstr;
		std::cout << str;
		for (int j = 1; j <= 5-str.size(); j++)
			std::cout << " ";
		std::cout << "|";
		
		//DrinkName
		str.clear();
		str = DrinkindWithNums[i].first.GetName();
		std::cout << str;
		for (int j = DrinkindWithNums[i].first.GetName().size() + 1; j <= 32; j++)
		{
			std::cout << " ";
		}
		std::cout << "|";

		//Price
		str.clear();
		ss.clear();
		ss << DrinkindWithNums[i].first.GetPrice();
		ss >> str;
		std::cout << str;
		for (int j = str.size() + 1; j <= 8; j++)
		{
			std::cout << " ";
		}
		std::cout << "|";

		//Num
		ss.clear();
		str.clear();
		ss << DrinkindWithNums[i].second;
		ss >> str;
		std::cout << str;
		for (int j = str.size() + 1; j <= 16; j++)
		{
			std::cout << " ";
		}
		std::cout << "|";

		//CanBuy
		str.clear();
		if (money >= DrinkindWithNums[i].first.GetPrice())
		{
			str = "Yes";
		}
		else
			str = "No";
		std::cout << str;
		for (int j = str.size() + 1; j <= 16; j++)
		{
			std::cout << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "+----+--------------------------------+--------+----------------+----------------+" << std::endl;
	std::cout << std::endl;
}
