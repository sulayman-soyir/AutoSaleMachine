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
	stringstream ss;
	while (1){

		/*操作身份*/
		std::vector < std::string>output{"1.Consumer", "2.ASMOwner", "3.Quit App"};
		CD::ChoiceOutput(output);
		
		std::string input;
		std::cin >> input;
		std::cout << std::endl;
		
		if (!CD::JudgeInputValid(input, {'1','3'}))
			continue;
		//退出应用
		if (input[0] == '3')
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
		if (input[0] == '1')
		{
			
			Consumer consumer; 
			std::cout << "Your Profile:" << std::endl;
			
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
				//购买阶段
				std::vector<string>choices{ "1.Buy","2.Back" };
				CD::ChoiceOutput(choices);
				
				std::string input;
				cin >> input;
				std::cout << std::endl;
				if (!CD::JudgeInputValid(input, { '1','2' }))
					continue;

				if (input[0] == '1')
				{
					/*购买*/
					float pay;
					while (1)
					{
						std::cout << "Insert Coin Into AutoSaleMachine>";
						
						std::cin >> pay;
						std::cout << std::endl;
						if(pay < 0)
						{
							cout << std::endl << "*****ERROR: NON NEGATIVE INTEGER*****" << endl;
							continue;
						}
						else if (pay > consumer.HowMoney())
						{
							cout << std::endl << "*****ERROR: YOU DON'T HAVE SUCH MONEY*****" << endl;
							continue;
						}
						break;
					}
					int r = 0;
					r = pay / 0.1;
					pay = r*0.1;
					consumer.Pay(pay);

					consumer.ShowInfo();
					asmOwner.ShowDrinksInfo(1,pay);
					
					while (1 && pay > 0)
					{
						CD::ChoiceOutput({ "1.Buy(choose id","2.Continue To Insert Coin","3.WithDraw Money(Go Back)" });
						std::string input;
						std::cin >> input;
						if (!CD::JudgeInputValid(input, { '1','3' }))
							continue;

						if (input[0] == '1')
						{
							while (1)
							{
								std::cout << "Input Drink Id（'q' to cancel)>";
								std::string input;
								std::cin >> input;
								if (input[0] == 'q')
								{
									consumer.ShowInfo();
									asmOwner.ShowDrinksInfo(1, pay);
									break;
								}
								if (!CD::JudgeInputValid(input, { '0','9' }))
									continue;

								unsigned int id;
								ss.clear();
								ss << input;
								ss >> id;

								if (id > asmOwner.GetMachineById(0)->GetCurKind())
								{
									std::cout << "*****ERROR: WRONG DRINK ID*****" << std::endl;
									continue;
								}

								if (pay < asmOwner.GetMachineById(0)->GetDrinkByNo(id).GetPrice())
								{
									//金币不足以购买选择的饮料
									std::cout << "*****YOUR PAID NOT ENOUGH FOR THIS DRINK*****" << std::endl;
									CD::ChoiceOutput({ "You can:","1.Choose Others","2.Go Back" });
									string input;
									std::cin >> input;
									if (!CD::JudgeInputValid(input, { '1','2' }))
										continue;

									//choose other drink
									if (input[0] == '1')
									{
										consumer.ShowInfo();
										asmOwner.ShowDrinksInfo(1, pay);
										continue;
									}
									else if (input[0] == '2')
									{
										break;
									}
								}

								//构造饮料，添加到用户队列
								float specDrinkPrice = name_price[asmOwner.GetMachineById(0)->GetDrinkByNo(id).GetName()];
								Drink boughtDrink(asmOwner.GetMachineById(0)->Sale(id), specDrinkPrice);
								//用户购买的饮料添加至用户信息
								consumer.PushDrinkVec(std::make_pair(boughtDrink, 1));
								//售货机找零
								CD::ChoiceOutput({ "1.找零回退","2.继续购买" });
								bool contiORbreak = false;
								while (1)
								{
									string input;
									std::cin >> input;
									if (!CD::JudgeInputValid(input, { '1','2' }))
										continue;
									if (input[0] == '2')
										break;
									else
									{
										contiORbreak = true;
										break;
									}
								}
								if (contiORbreak)
								{
									asmOwner.GetMachineById(0)->GiveChange(consumer, pay - specDrinkPrice);
									consumer.ShowInfo();
									asmOwner.ShowDrinksInfo(1);
									pay = 0;
									break;
								}
								else
								{
									pay = pay - specDrinkPrice;
									consumer.ShowInfo();
									asmOwner.ShowDrinksInfo(1, pay);
									continue;
								}
								
							}
						}
						else if (input[0] == '2')
						{
							/*continue inserting coin*/
							std::cout << "<Tip:already inserted: " << pay <<">"<< std::endl;
							float addpay;
							while (1)
							{
								std::cout << "Insert Coin Into AutoSaleMachine>";

								std::cin >> addpay;
								std::cout << std::endl;
								if (addpay < 0)
								{
									cout << std::endl << "*****ERROR: NON NEGATIVE INTEGER*****" << endl;
									continue;
								}
								else if (addpay > consumer.HowMoney())
								{
									cout << std::endl << "*****ERROR: YOU DON'T HAVE SUCH MONEY*****" << endl;
									continue;
								}
								break;
							}
							int left = 0;
							left = addpay / 0.1;
							addpay = left * 0.1;
							consumer.Pay(addpay);

							pay += addpay;

							consumer.ShowInfo();
							asmOwner.ShowDrinksInfo(1, pay);
						}
						else if (input[0] == '3')
						{
							/*退钱回退至上一步*/
							consumer.GetChange(pay);
							consumer.ShowInfo();
							asmOwner.ShowDrinksInfo(1);
							break;
						}

					}
				}
				else if (input[0] == '2')
				{
					/*回退到选择操作者*/
					break;
				}		
			}
		}
		if (input[0] == '2')
		{
			/*消费者*/
		}
	}
}

