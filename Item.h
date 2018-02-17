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
	string pickupDescription;	//so its like. You pick up the Sword. It feels heavy in your grasp. BADASS!
	bool getable;

	int hp;	//if item is a potion, hp=0. Else, it heals by the hp amount.
	int worth;

public:

	//Look at all these constructors! You can totally customize your items! How cool is that?. Dude, like right now, everything works exactly the way i want it. So now you'll see some extremely optimistic comments to complement the suicide "wtfisthisshit" ones.
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
		if (HP>0)hp=HP; else hp=0;	//prolly could use a ternary operator here
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

	//this should totally be named GetDescription, but its too late for that.
	void ReadDescription()
	{
		cout<<description<<endl;
	}
	bool Getable()
	{
		return getable;
	}

	//prototype
	//bool operator == (const Item& other) const;

	//!!!this lets you compare a string to an item. (suuuuper important)
	//implementation	<-- written by a TA. i get what it does, but don't totally understand it.
	bool  operator==(const Item& item) const
	{
		return name == item.name;
	}
	/*void SetPickupDescription(string PickUpDescription)	//dont acutally need this.
	{
		pickupDescription=PickUpDescription;
	}*/
	//~Item(void);
};

