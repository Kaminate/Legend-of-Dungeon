#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <list>
#include "Item.h"
#include "main.h"
using namespace std;

#define	MAX_ROOMS	10
#define NG			MAX_ROOMS

#pragma once
class Room
{
private:

	string roomName;

	int index;

	//bool to control if you should reread the room description
	bool beenThere;

	//this decription is read if you've never been there before.
	string description;

	//index of what room you can go to
	int dirNorth;
	int dirEast;
	int dirSouth;
	int dirWest;
	int dirUp;
	int dirDown;

public:

	list<Item> Inventory;

	//constructor
	Room (int Index)
	{
		roomName="";
		index=Index;
		beenThere=false;
		description="";
		dirNorth=NG;
		dirEast=NG;
		dirSouth=NG;
		dirWest=NG;
		dirUp=NG;
		dirDown=NG;
	}

	//ReadDescription also sets beenThere
	void ReadDescription()
	{
		//cout room name
		cout<<endl;
		cout<<roomName<<"."<<endl;
		cout<<"-------------------"<<endl;

		//cout room description if never been there
		if (beenThere==false)
		{
			cout<<description<<endl;
			beenThere=true;
		}
	}
	void NameRoom( string RoomName)
	{
		roomName=RoomName;
	}
	void DescribeRoom (string Description)
	{
		description=Description;
	}
	int GetIndex ()
	{
		return index;
	}
	void SetExits (int North, int East, int South, int West, int Up, int Down)
	{
		dirNorth=North;
		dirEast=East;
		dirSouth=South;
		dirWest=West;
		dirUp=Up;
		dirDown=Down;
	}
	int GoDirection (string Direction)
	{
		Direction[0]=tolower(Direction[0]);

		//if the direction changed, has_room_changed=true; <-- best way to do this?... hmm

		//has_room_changed=true;

		if (Direction== "north") return dirNorth;
		else if (Direction== "east" ) return dirEast;
		else if (Direction== "south") return dirSouth;
		else if (Direction== "west" ) return dirWest;
		else if (Direction =="up") return dirUp;
		else if (Direction=="down") return dirDown;
		else
		{
			//this below code... should never run(?).
			cout<<"Sorry, I don't understand what that directions means."<<endl;
			has_room_changed=false;
			return NG;
		}
	}
};
