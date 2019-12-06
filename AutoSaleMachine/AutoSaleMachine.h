#pragma  once

#include<vector>
#include<string>
#include<utility>
#include "Drink.h"
#include "Consumer.h"
using namespace std;
class AutoSaleMachine
{
public:
	AutoSaleMachine(int idInit) :m_id(idInit){};
	AutoSaleMachine& operator =(const AutoSaleMachine &othrs);
	~AutoSaleMachine(){};
public:
	int GetId(){ return m_id; };
	void AddDrink(Drink drinkItem, int nums);
	void DeleteDrinkByName(string name);
	bool ChangePrice(string drinkName, float targetPrice);
	vector<pair<Drink, int>> GetDrinksInMachine(){ return DrinkindWithNums; };
	void GiveChange(Consumer &con, float change){ con.GetChange(change); };
	void AddMoney(float fee){ money += fee; };
	void InitDrinks(const std::vector<pair<Drink, int>> &initDrinks);
	void ShowInfo(float money=0);
	int GetCurKind() { return DrinkindWithNums.size(); }
	std::string Sale(int drinkId);
	Drink GetDrinkByNo(int No) { return DrinkindWithNums[No-1].first; }
	
private:
	const int MaxItemKind = 6;  //最大饮料种类
	const int MaxDrinkNums = 40; //饮料最多瓶数
	int currentDrinkNums=0;   //当前机器里的饮料数
	vector<pair<Drink, int>> DrinkindWithNums;   //[饮料，数量]
	int m_id;
	float money;
};