#pragma once 

#include<string>
class Drink {
public:
	Drink(std::string nameInit, float priceInit) :m_name(nameInit), m_price(priceInit){};
	Drink(std::string nameInit) :m_name(nameInit){};
	Drink() = default;
	~Drink(){};
public:
	void SetPrice(float price){ m_price = price; };
	float GetPrice(){ return m_price; };
	std::string GetName(){ return m_name; };
	void SetName(std::string rename){ m_name = rename; };
private:
	std::string m_name;
	float m_price;
};