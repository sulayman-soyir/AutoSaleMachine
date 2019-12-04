//
// Created by pkpm on 2019/11/25.
//
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <utility>
#include <map>
#include "ASMOwner.h"
#include "AutoSaleMachine.h"
#include "MysqlSingleton.h"
#include "StaticFun.h"
using namespace std;
int main(int argc, const char *argv[])
{
	while (1){
		cout << "1.Consumer" << std::endl;
		cout << "2.ASMOwner" << std::endl;
		cout << "3.Quit App" << std::endl;
		std::cout << "option>";
		std::string s;
		std::cin >> s;
		std::cout << std::endl;
		if (s.size() != 1){
			cout << std::endl<< "**ERROR: INVALID INPUT!!**" << endl;
			continue;
		}
		else if (s[0] != '1' && s[0] != '2' && s[0] != '3'){
			cout << std::endl<< "**ERROR: INVALID INPUT!!**" << endl;
			continue;
		}

		//退出应用
		if (s[0] == '3')
			 break;
		
		
		
		//饮料以及价格
		std::map<std::string, float>name_price;
		if (!CD::initDrink(name_price))
			return 0;

		//初始化厂家
		ASMOwner asmOwner;
		if (!CD::initAsmOwner(asmOwner,name_price))
			return 0;
		
		

		//消费者
		if (s[0] == '1')
		{
			std::cout << "Your Profile:" << std::endl;

			//name <-> wallet
			MysqlSingleton *mysql = MysqlSingleton::GetInstance();
			stringstream ss;

			std::vector<vector<std::string>> conStr;
			
			
			Consumer consumer;
			if (!CD::initConsumer(consumer))
			{
				std::cout << "****************************************************" << std::endl;
				std::cout << "*			ERROR: INIT CONSUMER FAILED!             *" << std::endl;
				std::cout << "****************************************************" << std::endl;
				return 0;
			}
			consumer.ShowInfo();
			asmOwner.ShowDrinksInfo(1);
			while (1)
			{
				std::cout << "1.Buy" << std::endl;
				std::cout << "2.Back" << std::endl;
				std::cout << "option>";
				std::string input;
				cin >> input;
				if (input.size() > 1 || input.empty())
				{
					cout << std::endl << "**ERROR: INVALID INPUT!!**" << endl;
					continue;
				}
				else if (input[0] == '1')
				{
					std::cout << "insert money into AutoSaleMachine>";
					float pay;
					std::cin >> pay;
					std::cout << std::endl;
					while(pay < 0)
					{
						cout << std::endl << "*****************ERROR: INVALID INPUT***************" << endl;
						std::cin >> pay;
					}
					while (pay > consumer.HowMoney())
					{
						cout << std::endl << "**********ERROR: YOU DON'T HAVE SUCH MONEY**********" << endl;
						std::cin >> pay;
					}
					int r = 0;
					r = pay / 0.1;
					consumer.GetChange(pay - r*0.1);
					pay = r*0.1;
					consumer.Pay(pay);

					consumer.ShowInfo();
					asmOwner.ShowDrinksInfo(1,pay);


					
				}
					
			}
		}
	}
}

