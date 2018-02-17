#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include "Item.h"
#include "Room.h"
using namespace std;

#pragma once
class Player
{
private:
	string name;

	string description;

	int money_in_debt;
	int level;

	//stats
	int PlayerStatistics[5]; //note: the constructor has to contain a loop.

	/*
	The array is:
	const int Stats = 5;
	int PlayerStatistics[Stats]

	0 - Attack
	1 - Defense
	2 - Max HP
	3 - Current HP
	4 - Experience
	*/

	//a helper function for save/load game
	bool isreallyempty(ifstream& file)
	{
		//returns true if file is empty
		return file.peek() == file.eof();
	}



	//I think I don't need any of the below 7 helper functions. dont delete yet though.

	//setname for use when loading
	void setName(string newName)
	{
		name=newName;
	}
	//setdescription for loading
	void setDescription (string newDescription)
	{
		description=newDescription;
	}
	//set money_in_debt
	void setMoney_in_Debt( int newDebt)
	{
		if (newDebt>0) money_in_debt=newDebt;
		else money_in_debt=50000;
	}
	void setLevel(int newLevel)
	{
		level=newLevel;
	}
	void setAttack(int newAttack)
	{
		PlayerStatistics[0]=newAttack;
	}
	void setDefense ( int newDefense)
	{
		PlayerStatistics[1]=newDefense;
	}
	void setMaxHP (int newMaxHP)
	{
		PlayerStatistics[2]=newMaxHP;
	}
	/*void setCurrentHP(int newCurrentHP)
	{
		PlayerStatistics[3]=newCurrentHP;
	}
	void setExperience(int newExperience)
	{
		PlayerStatistics[4]=newExperience;
	}
	*/
public:
	//overloaded >> operator. Has to be a friend (member function takes calling object implicitly)
	//read from file ( loading )
	friend istream& operator>> (istream& is, Player player)
	{
		is>>player.name;
		is>>player.description;
		is>>player.money_in_debt;
		is>>player.level;
		for (int i=0;i<5;i++)
		{
			is>>player.PlayerStatistics[i];
		}
		return is;
	}


	/* trial 2. same error messages.
	istream& operator >> (istream& is)
	{
		//loading
		string tempString;
		int tempInt;

		//set name
		getline(is, tempString); setName(tempString);
		//set description
		getline(is, tempString); setDescription(tempString);
		//set money_in_debt
		is>>tempInt; setMoney_in_Debt(tempInt);
		//set level
		is>>tempInt; setLevel (tempInt);
		//set stats
		is>>tempInt; setAttack(tempInt);
		is>>tempInt; setDefense(tempInt);
		is>>tempInt; setMaxHP(tempInt);
		is>>tempInt; setCurrentHP(tempInt);
		is>>tempInt; setExperience(tempInt);

	}*/

















	//overloeaded << operator. write to file ( saving)
	friend ostream& operator<< (ostream& os, Player player)
	{
		os<<player.name<<endl;
		os<<player.description<<endl;
		os<<player.level<<endl;
		for (int i=0;i<5;i++)
		{
			os<<player.PlayerStatistics[i]<<endl;
		}
		return os;
	}

	//getters
	int getMoney_in_Dept() {return money_in_debt;}
	int getLevel() {return level;}
	string getName() {return name;}
	string getDescription(){return description;}

	int getAttack()	{return PlayerStatistics[0];}
	int getDefense(){return PlayerStatistics[1];}
	int getMaxHP(){return PlayerStatistics[2];}
	int getCurrentHP(){return PlayerStatistics[3];}
	int getExperience(){return PlayerStatistics[4];}

	//setters
	void setCurrentHP(int newHP)
	{
		//check for bounds
		if (newHP>getMaxHP()) PlayerStatistics[3]=getMaxHP();
		else PlayerStatistics[3]=newHP;
	}
	void setExperience(int newEXP)
	{
		//check for bounds
		//if ... well, theres no max exp, which is prolly a mistake but might not matter any more.
		PlayerStatistics[4]=newEXP;
	}
	void collectMoney(int gemValue)
	{
		if (gemValue>0) money_in_debt-=gemValue;
	}
	//note: you might need to write more setters.

	//update experience() <-- you should write this heather, unless you already have somewhere
	//level up!()

	//list of items
	list <Item> Inventory;

	//our "default" constructor
	Player(string Name, string Description)
	{
		name=Name;
		description=Description;

		money_in_debt=1000000;
		level=1;
		//put what to initizlize his stats here:
		PlayerStatistics[0]=30;//atk
		PlayerStatistics[1]=5;//def
		PlayerStatistics[2]=100;//current hp
		PlayerStatistics[3]=100;//max hp
		PlayerStatistics[4]=0;//exp
	}

	void TakeItem(Item item, Room& room)
	{
		if (item.Getable()==true)
		{
			//remove item from current room
			room.Inventory.remove(item);

			bool isGem=false;

			//if its a gem, dont put it in your inventory. instead change your money in debt
			if (item.getWorth()>0)
			{
				isGem=true;
				collectMoney(item.getWorth());
			}
			else //it's not a gem, put it in your bag
			{
				Inventory.push_back(item);
			}

			//tell user you've taken it.
			cout<<"You take the "<<item.GetName()<<". "<<item.GetPickupDescription()<<endl;

			//if the item taken was a gem, cout your current balace:
			if (isGem==true)
			{
				cout<<"Money in debt: "<<getMoney_in_Dept()<<endl;
			}

		}
		else	//its not gettable
		{
			cout<<"You can't take the "<<item.GetName()<<endl;
		}
	}

	void DropItem(Item item, Room& room)
	{
		if (item.Getable()==true)
		{
			//add item to room inventory
			room.Inventory.push_back(item);

			//remove item from player
			Inventory.remove(item);

			cout<<"You drop the "<<item.GetName()<<" on the ground."<<endl;
		}
		else
		{
			cout<<"You cant drop the "<<item.GetName()<<endl;
		}
	}

	void DrinkItem(Item item)
	{
		//check to see if item is in the inventory.
		bool isInInventory=false;

		/*for each (Item current_item in Inventory)
		{
			if (item==current_item)
			{
				isInInventory=true;
			}
		}*/

		for (int i=0;i<Inventory.size();i++)
		{
			Item current_item = Inventory.front();

			if (item==current_item)
			{
				isInInventory=true;
			}

			Inventory.splice(
					Inventory.end(),	//destination
					Inventory,			//source
					Inventory.begin());	//beginning position
		}


		// if (item is in player.inventory)
		if (isInInventory==true)
		{
			if (item.getHP()>0)
			{
				setCurrentHP(getCurrentHP()+item.getHP());
				Inventory.remove(item);

				cout<<"You drink the potion. You feel rejuvenated."<<endl;
				cout<<"You gain "<<item.getHP()<<" hit points."<<endl;
				cout<<"Your HP is "<<getCurrentHP()<<" out of "<<getMaxHP()<<"."<<endl;
			}
			else
			{
				cout<<"You cannot drink "<<item.GetName()<<endl;
			}
		}
		else
		{
			cout<<"You do not have "<< item.GetName()<<endl;
		}
	}

	//lets not do that now, lol.
	void UseItem(Item item/*, Boss boss*/)
	{
		cout<<"Yeah, lets not do that yet. ( code is not written!)"<<endl;
	}
	//if (item is in player.inventory)
	//	if (boss.weakness == item)
	//		remove item from player.inventory
	//		cout boss death text
	//		add boss.inventory to room.inventory
	//	else
	//		cout boss.impervious_text;
	//		playerHP-=boss.attack

	//4.






	//	Read or write data to disk using a non-operator-overloaded class member function (such as input() or output()).
	//for high schores
	//
	//
	//
	//
	//




	//~Player(void);

	//---SAVE GAME---
	void saveGame()
	{
		//overrite the bob file with new bob data
		ofstream saveStream(name);
		if (!saveStream) cout<<"Error opening file to save."<<endl;
		//save data
		//note: it's *this, which is the object, not 'this', which would be the pointer to the object
		if (!(saveStream<<*this)) cout<<"Error saving file."<<endl;
		else cout<<"Data saved!"<<endl;
		//done with file, so close
		saveStream.close();
	}
	//load game
	void loadGame()
	{
		//if file doesnt exist, create it
		ifstream playerStream;
		playerStream.open(name , ifstream::in);
		if (!playerStream)
			//if it's empty, then read intro. (bob is already constructed with level 1 values.)
			cout<<"Hey, you must be new here. Good luck."<<endl;
		else
		{
			//if its not empty, read data from file and store into Bob. <LOADING>
			if (!(playerStream>>*this)) cout<<"Error loading save data. Starting new game with player: "<<getName()<<endl;
			else
			{
			cout<<"Data loaded!"<<endl;

			//welcome back our player
			cout<<"Welcome back, "<<name<<". In your absence, we've returned you to the beginning of the level.";
			cout<<"But don't worry, we've saved all of your stats."<<endl;
			}

		}
		//done with file, so close
		playerStream.close();
	}

};
