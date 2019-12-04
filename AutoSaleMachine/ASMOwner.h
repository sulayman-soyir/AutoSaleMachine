//
// Created by pkpm on 2019/11/25.
//

#ifndef AUTODRINKSALEMACHINESYSTEM_ASMOWNER_H
#define AUTODRINKSALEMACHINESYSTEM_ASMOWNER_H


#include "AutoSaleMachine.h"
#include<vector>
#include<string>
#include<utility>
#include "Drink.h"


class ASMOwner {
public:
	ASMOwner();
	~ASMOwner();
	void AddASM();
	void DeleteASMById(int asmId);
	void AddDrink(int machineId, string drinkName, int nums);
	void DeleteDrink(int machineId, string drinkname);
	void ChangeDrinkPrice(int machineId, string drinkname, float targetPrice);  //更改特定机器上饮料价格
	void ChangeDrinkPrice(string drinkname, float targetPrice);     //更改所有机器上此种类饮料价格
	void ShowDrinksInfo(int id,float pay=0);
	void InitMachine(AutoSaleMachine machine){ saleMachines.push_back(machine); };
	void InitMachine(const std::vector<AutoSaleMachine> &saleMachineVec);
private:
	std::vector<AutoSaleMachine>saleMachines;

public:



};


#endif //AUTODRINKSALEMACHINESYSTEM_ASMOWNER_H
