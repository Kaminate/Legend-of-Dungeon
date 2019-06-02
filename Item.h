#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <string>


using namespace std;	//bad things happen when i leave this out

#pragma once
class Item
{
private:
	string name;	//NOTE: NAME MUST BE 1 WORD. "Red Gems" WILL *NOT* WORK. "Rubies" WILL.
	string description;
	string pickupDescription;	//so its like. You pick up the Sword. It feels heavy in your grasp.
	bool getable;

	int hp;	//if item is a potion, hp=0. Else, it heals by the hp amount.
	int worth;

public:

	//Wow such constructors
	Item(string Name, string Description)
	{
		name=Name;
		description=Description;
		pickupDescription="";	//i think i dont have to do this because strings are initialized to be empty already
		getable=false;
		hp=0;
		worth=0;
	}
	Item(string Name, string Description, bool Getable)
	{
		name=Name;
		description=Description;
		pickupDescription="";
		getable=Getable;
		hp=0;
		worth=0;
	}
	Item(string Name, string Description, string PickUpDescription, bool Getable)
	{
		name=Name;
		description=Description;
		pickupDescription=PickUpDescription;
		getable=Getable;
		hp=0;
		worth=0;
	}
	//for Potion creation
	Item(string Name, string Description, string PickUpDescription, bool Getable,int HP)
	{
		name=Name;
		description=Description;
		pickupDescription=PickUpDescription;
		getable=Getable;
		//is a potion.
		if (HP>0)hp=HP; else hp=0;	//ternary operator go here?
		worth=0;
	}
	//specifically for Gem creation
	Item(string Name, string Description, string PickUpDescription, int Worth)
	{
		name=Name;
		description=Description;
		pickupDescription=PickUpDescription;
		getable=true;
		//is a potion.
		if (Worth>0) worth=Worth;
		else worth = abs(Worth);
	}

	//for if its a potion
	int getHP()
	{
		return hp;
	}
	int getWorth()
	{
		return worth;
	}
	string GetName()
	{
		return name;
	}
	string getDescription()
	{
		return description;
	}

	string GetPickupDescription()
	{
		return pickupDescription;
	}

	//this should be named GetDescription, but its too late
	void ReadDescription()
	{
		cout<<description<<endl;
	}
	bool Getable()
	{
		return getable;
	}

  // TA wrote this function, I don't get it
	bool  operator==(const Item& item) const
	{
		return name == item.name;
	}
};

