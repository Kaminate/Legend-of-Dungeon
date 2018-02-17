#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <string>
//#include <sstream>
#include <list>

#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "TextParser.h"

//#include "Encounter.h"

#include "main.h"



using namespace std;


/*room indexes are:
0 the road to the castle
1 entrance hall
2 library
3 great hall
4 kitchen
5 wine cellar
6 upstairs hallway
7 bedroom 1
8 bedroom 2
9 attic
*/

//so the global variables in main.h are defined here.
int temporary_index;//=room_index;
int room_index;//=0;
bool has_room_changed;



int main()
{
	//create map
	Room Map[MAX_ROOMS]={(0),(1),(2),(3),(4),(5),(6),(7),(8),(9),};
	//initialize map
#pragma region initialize rooms


	//Hard Coding the rooms. this sucks without XML files
	Map[0].NameRoom("The road to the castle");
	Map[0].DescribeRoom(
		"You are trodding along a long winding road surrounded by a dense forest. A castle to the distant north overlooks the path.");
	Map[0].SetExits(1,NG,NG,NG,NG,NG);

	//<testing>

	//create an item
	Item Sword("Sword", "The sword blade gimmers brightly in the dim light", "It feels heavy in your grasp", true);
	Item Mitch("Mitch", "Mitch is a silly moppit.", false);
	Item Rubies("Rubies","Red rubies glitter brilliantly. The stones look almost organic, as if there's blood swirling within the crystals.","Cha-ching!",50000);
	Item Potion1("RedPotion","This potion looks scrumptous and healthy.","The bottle feels cold.", true, 30);
	//add it to the room
	Map[0].Inventory.push_back(Sword);
	Map[0].Inventory.push_back(Mitch);
	Map[0].Inventory.push_back(Rubies);
	Map[0].Inventory.push_back(Potion1);

	//</testing>

	Map[1].NameRoom("The entrance hall");
	Map[1].DescribeRoom(
		"You find yourself in the vast entrance hall of a castle. Flickering torch light barely lights up the rugged stone floors. If you stray away from the light, you will likely be eaten by a grue.");
	Map[1].SetExits(3, NG, 0, 2,6,NG);

	Map[2].NameRoom("The Library");
	Map[2].DescribeRoom(
		"");
	Map[2].SetExits( NG, 1, NG, NG,NG,NG);

	Map[3].NameRoom("Great Hall");
	Map[3].DescribeRoom(
		"");
	Map[3].SetExits(NG, NG, 1, 4,NG,NG);

	Map[4].NameRoom("The Kitchen");
	Map[4].DescribeRoom(
		"");
	Map[4].SetExits( NG, 3, NG, NG,NG,5);

	Map[5].NameRoom("The Wine Cellar");
	Map[5].DescribeRoom(
		"");
	Map[5].SetExits( NG, NG, NG, NG,4,NG);

	Map[6].NameRoom("Upstairs Hallway");
	Map[6].DescribeRoom(
		"");
	Map[6].SetExits(NG, NG, 7, 2,9,1);

	Map[7].NameRoom("Bedroom 1");
	Map[7].DescribeRoom(
		"");
	Map[7].SetExits(6, NG, NG, NG,NG,NG);

	Map[8].NameRoom("Bedroom 2");
	Map[8].DescribeRoom(
		"");
	Map[8].SetExits(6, NG, NG, NG,NG,NG);

	Map[9].NameRoom("The Attic");
	Map[9].DescribeRoom(
		"");
	Map[9].SetExits(NG, NG, NG, NG,NG,6);
#pragma endregion

	//create player based on user input
	//create//load file with player name
	string playername;
	cout<<"Enter your name: ";
	cin>>playername;

	//these below 2 lines fix some bug where the next getline would be completely ignored, so these lines are the ones that are ignored.
	string tempstring;
	getline (cin,tempstring);

	cout<<endl;

	Player Bob(playername, playername + " is professional and dangerous.");

	//load game (file name is based on player name)
	Bob.loadGame();




	//create text parser
	TextParser parser;

	//1 pt: use a do while loop.

	//initialize room_index and read it (first room only.
	room_index=0;
	Map[room_index].ReadDescription();
	has_room_changed=false;



	do
	{

		//read room description only if the room has CHANGED from last time. <-- that doesnt work
		if (has_room_changed==true) Map[room_index].ReadDescription();


        //1 : something chance --> call encounter function!
        // I'm not sure what kind of odds you have, this (1:5) seemed pretty standard to me. You can change it if you like :)
        if( rand() % 5 )
        {
            Encounter( PlayerStatistics );
        }


		//if the parser returned false, cout an error. otherwise, it takes care of the rest.
		if (parser.ParseInput(Bob,Map[room_index])==0)
		{
			//this means that input parsing was unsuccessful.
			cout<<"Do what with what now?"<<endl;//<-- or read a random error message(!)
		}


#pragma region update map
		//if the direction you want to go is == NG, dont update the room index


		if (temporary_index==NG) cout<<"Sorry, you can't go that way"<<endl;

		//update room_index
		else room_index=temporary_index;
#pragma endregion

	}
	//whie (ingame==true). Way too early in coding process for a victory condition, OTL...
	while (true);

	return 1;
}
