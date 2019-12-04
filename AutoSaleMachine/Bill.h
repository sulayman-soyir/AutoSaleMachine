//
// Created by sulay on 2019/11/26.
//

#ifndef AUTODRINKSALEMACHINESYSTEM_BILL_H
#define AUTODRINKSALEMACHINESYSTEM_BILL_H
#include<string>
class Bill{
public:
	Bill(std::string init) :BillType(init){};
	~Bill(){};
	std::string GetBillType(){ return BillType; };
	virtual float GetVal() = 0;

private:
	std::string BillType;
};
class Bill10Cents :public Bill
{
public:
	Bill10Cents() :Bill("Bill10Cents"){};
	~Bill10Cents(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 0.1; //10 cents
};
class Bill50Cents :public Bill
{
public:
	Bill50Cents() :Bill("Bill50Cents"){};
	~Bill50Cents(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 0.5; //cents;
};
class BillYuan :public Bill
{
public:
	BillYuan() :Bill("BillYuan"){};
	~BillYuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 1; //cents;
};
class Bill5Yuan :public Bill
{
public:
	Bill5Yuan() :Bill("Bill5Yuan"){};
	~Bill5Yuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 5; //cents;
};
class Bill10Yuan :public Bill{
public:
	Bill10Yuan() :Bill("Bill10Yuan"){};
	~Bill10Yuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 10; //cents;
};
class Bill20Yuan :public Bill{
public:
	Bill20Yuan() :Bill("Bill20Yuan"){};
	~Bill20Yuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 20; //cents
};
class Bill50Yuan :public Bill{
public:
	Bill50Yuan() :Bill("Bill50Yuan"){};
	~Bill50Yuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 50; //cents
};
class Bill100Yuan :public Bill{
public:
	Bill100Yuan() :Bill("Bill100Yuan"){};
	~Bill100Yuan(){};
	virtual float GetVal()override{ return val; };
private:
	float val = 100; //cents
};
#endif //AUTODRINKSALEMACHINESYSTEM_BILL_H
