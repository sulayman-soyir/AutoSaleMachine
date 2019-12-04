//
// Created by sulay on 2019/11/26.
//

#ifndef AUTODRINKSALEMACHINESYSTEM_CONSUMER_H
#define AUTODRINKSALEMACHINESYSTEM_CONSUMER_H

#include<vector>
#include<string>
#include<utility>
#include "Bill.h"
#include "Drink.h"
using namespace std;
class Consumer {
public:
	Consumer(string nameInit) :name(nameInit){};
	Consumer(){};
	~Consumer(){};
	//void AddMoney(Bill * bill, int nums);

	void SetName(std::string nameSet){ name = nameSet; };
	bool Bought(std::string drinkName);
	bool Pay(float fee);
	void GetChange(float change){ account += change; };
	void ShowInfo();
	float HowMoney(){ return account; }
	void initMoney(float initMoney){ account = initMoney; };
	void PushDrinkVec(const std::pair<Drink, int> &drinkNumPair);
	


private:
	string name;
	vector<pair<Drink, int>>drinkVec;
	//vector<pair<Bill *, int>>wallet;
	float account;
};

//struct myclass{
//	bool operator()(pair<Bill *, int> p1, pair<Bill *, int> p2)
//	{
//		return p1.first->GetVal() <= p2.first->GetVal();
//	}
//}CmpObject;




#endif //AUTODRINKSALEMACHINESYSTEM_CONSUMER_H
