//
// Created by pkpm on 2019/11/25.
//

#include "ASMOwner.h"
#include<vector>
#include <algorithm>
#include<iostream>
#include<set>
#include "AutoSaleMachine.h"
using namespace std;
ASMOwner::ASMOwner()
{
}
ASMOwner::~ASMOwner()
{
}

//ͨ������idɾ��ĳ����
void ASMOwner::DeleteASMById(int asmId) {
	vector<AutoSaleMachine>::iterator it = saleMachines.begin(), end = saleMachines.end();
	for (; it != end; ++it){
		if ((*it).GetId() == asmId)
			saleMachines.erase(it);
	}
}
//������ӻ���
void ASMOwner::AddASM() {
	if (saleMachines.empty()){
		AutoSaleMachine machine(1);
		saleMachines.push_back(machine);
		return;
	}
	vector<int>hasAssignedId;
	vector<AutoSaleMachine>::iterator it = saleMachines.begin(), end = saleMachines.end();
	for (; it != end; ++it){
		hasAssignedId.push_back((*it).GetId());
	}

	vector<int>temp;
	for (int i = 1; i <= hasAssignedId[hasAssignedId.size() - 1]; ++i) {
		temp.push_back(i);
	}
	if (hasAssignedId.size() != temp.size()){
		vector<int>::iterator it;
		vector<int>Diff(temp.size(),0);
		sort(hasAssignedId.begin(), hasAssignedId.end());
		it = std::set_difference(temp.begin(), temp.end(), hasAssignedId.begin(), hasAssignedId.end(), Diff.begin());

		AutoSaleMachine saleMachine(Diff[0]);
		saleMachines.push_back(saleMachine);
		return;
	}
	AutoSaleMachine machine(hasAssignedId[hasAssignedId.size() - 1] + 1);
	saleMachines.push_back(machine);

}

//�����ض����������ϼ۸�
void ASMOwner::ChangeDrinkPrice(int machineId, string drinkname, float targetPrice) {
	if (targetPrice < 0){
		std::cout << "**ERROR: INVALID PRICE SET!!**" << std::endl;
		return;
	}
	vector<AutoSaleMachine>::iterator it = saleMachines.begin(), end = saleMachines.end();
	for (; it != end; ++it){
		if ((*it).GetId() == machineId)
		{
			if (!(*it).ChangePrice(drinkname, targetPrice)){
				std::cout << "**FAILURE: NO SUCH DRINK IN THIS MACHINE!!**" << std::endl;
				return;
			}
			else{
				std::cout << "**SUCCESS: PRICE RESET!!**" << std::endl;
				return;
			}
		}
	}
}
//�������л����ϵĴ��������ϼ۸�
void ASMOwner::ChangeDrinkPrice(string drinkname, float targetPrice) {
	vector<AutoSaleMachine>::iterator it = saleMachines.begin(), end = saleMachines.end();
	for (; it != end; ++it){
		(*it).ChangePrice(drinkname, targetPrice);
	}
}
//���ض�����������ĳ������
void ASMOwner::AddDrink(int machineId, string drinkName, int nums) {
	for (int i = 0; i < saleMachines.size(); ++i) {
		if (saleMachines[i].GetId() == machineId){
			saleMachines[i].AddDrink(Drink(drinkName), nums);
		}
	}
}
//���ض�������ɾ��ĳ������
void ASMOwner::DeleteDrink(int machineId, string drinkname) {
	for (int i = 0; i < saleMachines.size(); ++i) {
		if (saleMachines[i].GetId() == machineId){
			saleMachines[i].DeleteDrinkByName(drinkname);
			return;
		}
	}
}


//������ʾ
void ASMOwner::ShowDrinksInfo(int id,float pay) {
	for (int i = 0; i < saleMachines.size(); ++i)
	{
		if (saleMachines[i].GetId() == id)
		{
			saleMachines[i].ShowInfo(pay);
			return;
		}
	}
	std::cout << "**ERROR: INVALID MACHINE ID**" << std::endl;
}

void ASMOwner::InitMachine(const std::vector<AutoSaleMachine> &saleMachineVec)
{
	for (int i = 0; i < saleMachineVec.size(); i++)
	{
		saleMachines.push_back(saleMachineVec[i]);
	}
}

