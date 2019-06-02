#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <list>

#include "Room.h"
#include "Player.h"
#include "Item.h"

#include "main.h" //<-- for global vars

using namespace std;

#pragma once
class TextParser
{
private:

	//sees if the user input holds at least 1 item.
	bool searchForItem ( list<string> userinputs, list<Item> inventory)
	{
		bool itemFound=false;

		for (int i=0;i<userinputs.size();i++)
		{
			//the first element of userinputs
			string current_string = userinputs.front();

			for (int j=0;j<inventory.size();j++)
			{
				//get the first element of inventory
				Item current_item=inventory.front();

				if (current_string.compare(current_item.GetName())==0) itemFound=true;

				//move element to the end of the list so we can continue looking through our list
				inventory.splice(
					inventory.end(),	//destination
					inventory,			//source
					inventory.begin());	//beginning position
			}

			//move element to the end of the list so we can continue looking through our list
			userinputs.splice(
				userinputs.end(),	//destination
				userinputs,			//source
				userinputs.begin());	//beginning position
		}

		return itemFound;
	}

	//searches through the strings in user inputs and the items in a list and finds a match, and returns the item.
	Item function (list<string> userinputs, list<Item> inventory)
	{
		bool itemFound=false;

		for (int i=0;i<userinputs.size();i++)
		{
			//the first element of userinputs
			string current_string = userinputs.front();

			for (int j=0;j<inventory.size();j++)
			{
				//get the first element of inventory
				Item current_item=inventory.front();

				if (current_string.compare(current_item.GetName())==0)
				{
					itemFound=true;
					Item returnItem=inventory.front();

					//lets try returning it without finishing shuffling through our list
					return returnItem;
					//seems to work ok.

				}


				//move element to the end of the list so we can continue looking through our list
				inventory.splice(
					inventory.end(),	//destination
					inventory,			//source
					inventory.begin());	//beginning position
			}

			//move element to the end of the list so we can continue looking through our list
			userinputs.splice(
				userinputs.end(),	//destination
				userinputs,			//source
				userinputs.begin());	//beginning position
		}

		//note: because of the searchForItem function, the below code should NEVER HAPPEN. but its there just in case.
		if (itemFound==false)
		{
			// if no item was found, return a default item.
			Item defaultItem("Default Item","Do what with what now?",0);
			return defaultItem;
		}
	}

	//1 of 4  -  preliminary checks for input parsing before we deal with items.
	bool check_for_save(string user_input, Player player)
	{
		if (user_input.compare("save game")==0)
		{
			player.saveGame();

			//then return true
			return true;
		}
		else return false;
		/* else do nothing */
	}
	//2 of 4
	bool check_for_load(string user_input,Player player)
		{
			if (user_input.compare("load game")==0)
			{
				//uhh, loading is handeled automatically at the beginning of the game now. Don't need this function anymore.

				return true;
			}
			else return false;
			/* else do nothing */
		}
	//3 of 4
	bool check_for_movement( list<string> user_inputs, Room room)
		{
			string direction;
			/*
			for each (string current_string in user_inputs)
			{
				//why doesn't the switch statement works with strings?

				if (current_string.compare("north")==0 || current_string.compare("upstairs")==0) direction = "north";
				else if (current_string.compare("south")==0 || current_string.compare("downstairs")==0) direction = "south";
				else if (current_string.compare("east")==0||current_string.compare("right")==0) direction="east";
				else if (current_string.compare("west")==0|| current_string.compare("left")==0) direction="west";
			}*/
			for (int i=0;i<user_inputs.size();i++)
			{
				//get the first element of inventory
				string current_string=user_inputs.front();

				if (current_string.compare("north")==0 || current_string.compare("upstairs")==0) direction = "north";
				else if (current_string.compare("south")==0 || current_string.compare("downstairs")==0) direction = "south";
				else if (current_string.compare("east")==0||current_string.compare("right")==0) direction="east";
				else if (current_string.compare("west")==0|| current_string.compare("left")==0) direction="west";

				//move element to the end of the list so we can continue looking through our list
				user_inputs.splice(user_inputs.end(),	//destination
					user_inputs,			//source
					user_inputs.begin());	//beginning position
			}

			if (direction.empty()==false)//while direction isn't empty, means we changed it
			{
				has_room_changed=true;

				//go direction
				temporary_index=room.GoDirection(direction);

				//check if we've changed it
				if (temporary_index==NG) has_room_changed=false;

				return true;
			}	//we didn't change it, return false
			else
			{
				has_room_changed=false;
				return false;
			}
		}
	//4 of 4									          //"player"/"room"	"inventory"
	bool check_for_list_inventory(list<string> user_inputs, string wordOne, string wordTwo, list<Item> inventory)
	{
		//flags
		bool itemFound=false;	//itemFound tracks if what they typed (userinput) means they want to look in a inventory

		bool wordOneFound=false;
		bool wordTwoFound=false;
		for (int i=0;i<user_inputs.size();i++)
		{
			string current_string = user_inputs.front();

			if (current_string.compare(wordOne)==0) wordOneFound=true;
			if (current_string.compare(wordTwo)==0) wordTwoFound=true;

			//move element to the end of the list so we can continue looking through our list
			user_inputs.splice(user_inputs.end(),	//destination
			user_inputs,			//source
			user_inputs.begin());	//beginning position
		}



		//if it does, then they want to search the inventory
		if (wordOneFound==true && wordTwoFound==true)
		{
			itemFound=true;
			cout<<"You see:"<<endl;

			//if the inventory is empty, say so
			if (inventory.size()==0) cout<<" ...nothing."<<endl;
			else
			{
				//else list the items in that inventory

				for (int i=0;i<inventory.size();i++)
				{
					Item current_item = inventory.front();

					cout<<current_item.GetName()<<" - "<<current_item.getDescription()<<endl;

					//move element to the end of the list so we can continue looking through our list
					inventory.splice(inventory.end(),	//destination
					inventory,			//source
					inventory.begin());	//beginning position
				}
			}
		}
		return itemFound;
	}

	//1. compare user input to some inventory (room/player) to see if there is a noun to find
	bool LookForNoun(list <string> userInputs, list<Item> inventory)
	{
		//if there is an item in the (inventory: player/room depending on the function call), return true.
		if(searchForItem(userInputs, inventory)==true)
			return true;

		//else if nothing was found
		return false;
	}

	//2. compare user input to some inventory (room/player) to see actually find the noun
	Item returnNoun (list <string> userInputs, list<Item> inventory)
	{
		//search in player
		if(searchForItem(userInputs, inventory)==true)
			return function(userInputs, inventory);

		//note: the below code should never have to run. (it's there as a failsafe)
		Item defaultItem("Default Item","Do what with what now?",0);
			return defaultItem;

	}

	//helper function : move element to the end of the list so we can continue looking through our list.
	void moveElementsBack(list<string> myList)
	{
		myList.splice(myList.end(),	//destination
		myList,			//source
		myList.begin());	//beginning position
	}
	void moveElementsBack(list<Item> myList)
	{
		myList.splice(myList.end(),	//destination
		myList,			//source
		myList.begin());	//beginning position
	}






public:
	//ctor.
	TextParser()
	{
		//no private variables. Should have have actions
	}

	// magic
	bool ParseInput(Player& player, Room& room)
	{

		//GET USER INPUT!
		string userInput;

		//put a litle '>' before the input, so it looks cool and prompts for their input.
		cout<<">";

		getline (cin,userInput);
		string userInputCopy=userInput;

		//loop through string input
		string tempString;	//temp string holds the current word
		int count;			//count holds the length of the word

		// note:
    //   don't confuse userInput with userInputs.
    //   userInput is the string, userInputs is the list of strings.
    //   userInputCopy is a copy of userInput used to make userInputs.
    //   With me still?
		list<string> userInputs;

	#pragma region get words into a list
		//This while loop splits the userInput string into words, and adds said words into userInputs list
		while (userInputCopy.empty()!= true)
		{
			//FOR ONE WORD:

			//1. delete initial whitespace
			while (userInputCopy[0]==' ')
			{
					userInputCopy.erase(0,1);
			}

			//reset count for each word. count tracks the characters in each word, so we can use substr l8r
			count=0;

			//loop through all characters and count how many characters the word has
			for (int i=0;i<userInputCopy.length();i++)
			{
				if ( userInputCopy[i]!=' ')
				{
					count++;
				}
				else
				{
					break;
				}
			}
			//add to new string, and erase from old string
			tempString=userInputCopy.substr(0,count);
			userInputCopy.erase(0,count);
			//add temp string to list
			userInputs.push_back(tempString);
		}
#pragma endregion
		//with this loop done, we should have a list of all the words that the user specified.


		//first we're going to check for the default cases:

		//1. SAVE GAME: see if they said "save game" <-- in that type case.
		if (check_for_save(userInput, player)==true) return true;

		//2. LOAD GAME: (note: loading is now handeled automatically)
		/*if (check_for_load(userInput, player)==true) return true;*/

		//3. CHECK FOR MOVEMENT: check for movement already has the movement function built in it.
		if (check_for_movement(userInputs, room)==true) return true;


		//4. CHECK FOR LIST OF INVENTORY: check if they want to list the inventory of the [player/rooom]
											//gotta type these strings if you want to list the inven
		if (check_for_list_inventory(userInputs, "player","inventory",player.Inventory)==true) return true;
		if (check_for_list_inventory(userInputs, "room","inventory",room.Inventory)==true) return true;

		//ok.

		//1. see if the noun the user inputted is in the player.inventory then do stuff based on that
		if (LookForNoun(userInputs, player.Inventory)==true)
		{
			//actually get the noun
			Item noun = returnNoun(userInputs, player.Inventory);

			for (int i=0;i<userInputs.size();i++)
			{
				string current_string=userInputs.front();

				//this should only work for the player.inven
				if (current_string.compare("drop")==0)
				{
					//if it was successful return true
					player.DropItem(noun,room);
					return true;
				}
				//this should only work for the player.inven
				else if (current_string.compare( "use")==0)
				{
					player.UseItem(noun);
					return true;
				}
				//this should only work for the player.inven
				else if (current_string.compare( "drink")==0)
				{
					player.DrinkItem(noun);
					return true;
				}

				//move element to the end of the list so we can continue looking through our list
				userInputs.splice(userInputs.end(),	//destination
				userInputs,			//source
				userInputs.begin());	//beginning position
			}



			return false;
		}
		//2. see if the noun the user inputted is in the room.inventory then do stuff based on that
		else if (LookForNoun(userInputs, room.Inventory)==true)
		{
			//actually get the noun
			Item noun = returnNoun(userInputs, room.Inventory);

			for (int i=0;i<userInputs.size();i++)
			{
				string current_string = userInputs.front();
				//this should only work for the room.inven
				if (current_string.compare( "take")==0)
				{
					player.TakeItem(noun,room);
					return true;
				}

				moveElementsBack(userInputs);
			}

			return false;
		}
		//note: if there is NO NOUN, then we are DONE:   thus return false;
		else return false;
	}
};

