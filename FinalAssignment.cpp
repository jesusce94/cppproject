// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/* CLASSES */
class MapObj {
protected:
	string name;
	string description;
	bool canPass;
	bool picked; // only for grid where there is an item to pick. It helps me to change the displayed message.
public:
	MapObj() {
		canPass = true; /* By default, you can pass. Further I modify the value for walls and unlocked doors to false.*/
		description = "There is no description.";
		picked = false;
	}

	string getName() {
		return name;
	}

	void setName(string inputName) {
		name = inputName;
	}

	void setCanPass(bool inputType) {
		canPass = inputType;
	}

	bool checkIfCanPass() {
		return canPass;
	}

	string getDescription() {
		return description;
	}

	void displayDescription() {
		cout << description;
	}

	void setDescription(string newDescription) {
		description = newDescription;
	}

	bool getPickedStatus() {
		return picked;
	}

	void setPicked(bool input) {
		picked = input;
	}
};

class Wall : public MapObj {
public:
	Wall() {
		name = "wall";
		description = "There is a wall there.";
	};
};

class Corridor : public MapObj {
public:
	Corridor(){
		name = "corridor";
		description = "You are in a terrifying corridor, do not let your guard down.";
	}
};

class Door : public MapObj {
public:
	Door() {
		name = "door";
		description = "This door seems unlocked, please continue in the same direction to get into the room.";
	}
};

class Room : public MapObj {
public:
	Room(){
		name = "room";
		description = "You are in a common room, a bit fancy tho.";
	}
};

class KeyMap : public MapObj {
public:
	KeyMap() {
		name = "key";
		description = "There is a key in this position.";
	}
};

class RingMap : public MapObj {
public:
	RingMap() {
		name = "ring";
		description = "There is a ring here, it looks quite pretty.";
	}
};

class SwordMap : public MapObj {
public:
	SwordMap() {
		name = "sword";
		description = "There is a lengendary sword in here, it's very powerful and sharp, perfect to cut dragon's heads.";
	}
};

class Tunnel : public MapObj {
public:
	Tunnel() {
		name = "tunnel";
		description = "You are getting through a tunnel.";
	}
};

class Dragon : public MapObj {
public:
	Dragon() {
		name = "dragon";
		description = "Sugar, it was a gold legendary dragon. Unfortunately, by when you finish reading this text you will be already dead.";
	}
};

class Princess : public MapObj {
public:
	Princess() {
		name = "princess";
		description = "There is a princess in this position.";
	}
};

class Item {
protected:
	string itemName;
	bool usable;
public:
	Item(){}
	Item(string name, bool status) {
		itemName = name;
		usable = status;
	}

	void setitemName(string name) {
		itemName = name;
	}

	string getItemName() {
		return itemName;
	};
	void setUsable(bool status) {
		usable = status;
	};

	bool getUsable() {
		return usable;
	};

	/*Not used.*/
	bool useItem(Item item) {
		return true;
	}

};

class Key : public Item {
public:
	Key() {
		itemName = "key";
	}
	Key(string name, bool status) {
		setitemName(name);
		setUsable(status);
	}
};

class Sword : public Item {
public:
	Sword() {
		itemName = "sword";
	}
	Sword(string name, bool status) {
		setitemName(name);
		setUsable(status);
	}
};

class Ring : public Item {
public:
	Ring() {
		itemName = "ring";
	}
	Ring(string name, bool status) {
		setitemName(name);
		setUsable(status);
	}
};

class Inventory {
	vector<Item> inventory;

public:
	Inventory() {};

	void setItem(Item object1) {
		inventory.push_back(object1);
	}

	Item getItem(int position) {
		return inventory[position];
	}

	int countItems() {
		return inventory.size();
	}

	void deleteItems() {
		inventory.clear();
	}

	bool hasItem(string itemName) {
		for (int temp = 0; temp < inventory.size(); temp++) {
			if (inventory[temp].getItemName() == itemName) {
				return true;
			}
		}
		return false;
	}
	
	void displayAllItems() {
		if (inventory.size() == 0) cout << "You have no items in your inventory.";
		for (int temp = 0; temp < inventory.size(); temp++) {
			cout << "Item name: " << inventory[temp].getItemName() << endl;
		}
	}
};

class Player {
	string playerName;
	int remainingLives;
	int playerPositionX;
	int playerPositionY;
	Inventory playerInventory;
	void restartPositionAndInventory() {
		playerPositionX = 5;
		playerPositionY = 0;
		playerInventory.deleteItems();
	}
public:
	Player() {
		playerName = "Unsetted name";
		remainingLives = 5;
		playerPositionX = 5;
		playerPositionY = 0;
	}
	Player(string name) {
		playerName = name;
		remainingLives = 5;
		playerPositionX = 5;
		playerPositionY = 0;
	}

	void setName(string name) {
		playerName = name;
	}

	void setRemainingLives(int lives) {
		remainingLives = lives;
	}

	string getName() {
		return playerName;
	}

	int getPlayerPositionX() {
		return playerPositionX;
	}

	int getPlayerPositionY() {
		return playerPositionY;
	}

	int getRemainingLives() {
		return remainingLives;
	}

	void die() {
		remainingLives--;
		restartPositionAndInventory();
	}

	bool checkRemainingLives() {
		if (remainingLives == 0) {
			cout << "You ran out of lives. GAME OVER." << endl;
			return false;
		}
		return true;
	}

	void displayPlayerPositionMessage() {
		cout << "Current position: " << playerPositionX << "," << playerPositionY << endl;
	}

	void setPlayerPositionX(int x) {
		playerPositionX = x;
	}

	void setPlayerPositionY(int y) {
		playerPositionY = y;
	}

	void setItemInInventory(Item test) {
		playerInventory.setItem(test);
	}

	Inventory getInventory() {
		return playerInventory;
	}

	/* RETURN TRUE WHEN IT IS NOT AN OBSTACLE, OR IN OTHER WORDS, YOU CAN PASS */
	bool checkMove(vector<vector<MapObj>>& map, char inputMove, Inventory inventory) {
		int tempPosX = playerPositionX;
		int tempPosY = playerPositionY;

		/*FIRST I CHECK WHERE THE POSITION IS INSIDE THE VECTOR SIZE. IF SO, I MODIFY THE VALUE FOR FURTHER ITERATIONS*/
		switch (inputMove) {
		case 'n':
			if (tempPosY - 1 >= 0) {
				tempPosY--;			
			}
			else {
				cout << "You cannot leave the cave without the princess. ";
				return false;
			}
			break;
		case 's':
			if (tempPosY + 1 < 10) {
				tempPosY++;
			}
			else {
				cout << "Out of array. ";
				return false;
			}
			break;
		case 'w':

			if (tempPosX - 1 >= 0) {
				tempPosX--;
			}
			else {
				cout << "Out of array. ";
				return false;
			}
			break;
		case 'e':
			if (tempPosX + 1 != 10) {
				tempPosX++;
			}
			else {
				cout << "Out of array. ";
				return false;
			}
			break;
		case 'i':
			inventory.displayAllItems();
			return false;
			break;
		default:
			cout << "Use 'n' for north, 's' for south, 'e' for east, 'w' for west and 'i' for inventory. Other characters will NOT be recognized." << endl;
			return false;
		} /* END SWITCH */

		/* SECOND PART. The code below check if can pass. If not, it will specify what kind of map item will face.*/
		if (map[tempPosY][tempPosX].checkIfCanPass()) {
			playerPositionY = tempPosY;
			playerPositionX = tempPosX;
			return true;
		}
		else if (map[tempPosY][tempPosX].getName() == "wall") {
			map[tempPosY][tempPosX].displayDescription();
			cout << endl;
		}/* For doors, I check whether the bit is a door and whether this door is locked or not.*/
		else if (map[tempPosY][tempPosX].getName() == "door" && !map[tempPosY][tempPosX].checkIfCanPass()) {
			map[tempPosY][tempPosX].displayDescription();
			if (inventory.hasItem("key")) { // If you have picked up the key, then the door will be unlocked and moving the user.
				cout << "Wait, seems like the key you picked up before can be used to unlock this door. Let's give a try..." << endl;
				/*unlock the door*/
				Door openedDoor;
				openedDoor.setCanPass(true);
				map[tempPosY][tempPosX] = openedDoor;
				playerPositionY = tempPosY;
				playerPositionX = tempPosX;
				return true;
			}
		} // END IF. If you find an item, princess or a dragon, you will be able to move. Except when you face the dragon without a sword.

		return false;
	}
};

class Game {
	Player player;
	Door openedDoor;
	Door closedDoor;
	Wall wall;
	Room dragonRoom;
	Room room;
	Key key;
	Sword sword;
	Ring ring;
	Corridor corridor;
	Dragon dragon;
	Princess princess;
	KeyMap keyMap;
	RingMap moneyMap;
	Tunnel tunnel;
	SwordMap swordMap;
	vector<vector<MapObj>> map;
	vector<vector<MapObj>>* ptrMap;
	bool hasPrincess = false;
	bool exitGame = false;

public:
	Game(int remainingLives) {
		player.setRemainingLives(remainingLives);
		wall.setCanPass(false);
		openedDoor.setCanPass(true);
		closedDoor.setCanPass(false);
		closedDoor.setDescription("You need a key to open this door.");
		corridor.setCanPass(true);
		key.setUsable(true);
		dragonRoom.setName("dragonRoom");
		dragonRoom.setDescription("There is a very bright light in this room, seems like a treasure.");
		ptrMap = &map;

		createMap();
	}

	/* Creates the map. I used first a loop to fill the whole map with walls and then modify those who are different from walls.*/
	void createMap() {
		/* = {
		{ wall, wall, wall,		  wall,       wall,		  corridor,   wall,   wall,   wall,		wall },
		{ wall, wall, dragonRoom, dragonRoom, wall,		  corridor,   wall,   wall,   wall,		wall },
		{ wall, wall, dragon,     dragonRoom, openedDoor, corridor,   wall,   wall,   wall,		wall },
		{ wall, wall, dragonRoom, dragonRoom, wall,		  corridor,	  tunnel, key,    dragon,   wall },
		{ wall, wall, wall,       wall,		  wall,		  corridor,   wall,   wall,   wall,		wall },
		{ wall, wall, wall,       wall,		  wall,		  closedDoor, wall,   wall,   wall,		wall },
		{ wall, wall, wall,		  wall,		  wall,		  room,		  wall,   wall,   wall,		wall },
		{ wall, wall, wall,		  wall,		  wall,		  ring,		  wall,   wall,   sword,    wall },
		{ wall, wall, wall,		  wall,		  wall,		  tunnel,	  tunnel, tunnel, princess, wall },
		{ wall, wall, wall,		  wall,		  wall,		  wall,		  wall,   wall,   wall,		wall }
		};*/
		for (int x = 0; x < 10; x++) {
			vector<MapObj> rowVector;
			for (int y = 0; y < 10; y++) {
				rowVector.push_back(wall); // set the walls
			}
			map.push_back(rowVector); // set a row to the 2D Vector.
		}

		map[0][5] = corridor; /* and start point */
		map[1][2] = dragonRoom;
		map[1][3] = dragonRoom;
		map[1][5] = corridor;
		map[2][2] = dragon;
		map[2][3] = dragonRoom;
		map[2][4] = openedDoor;
		map[2][5] = corridor;
		map[3][2] = dragonRoom;
		map[3][3] = dragonRoom;
		map[3][5] = corridor;
		map[3][6] = tunnel;
		map[3][7] = keyMap;
		map[3][8] = dragon;
		map[4][5] = corridor;
		map[5][5] = closedDoor;
		map[6][5] = room;
		map[7][5] = moneyMap;
		map[7][8] = swordMap;
		map[8][5] = tunnel;
		map[8][6] = tunnel;
		map[8][7] = tunnel;
		map[8][8] = princess;
	}

	void askForUserName() {
		cout << "What's your name? ";
		string name;
		cin >> name;
		player.setName(name);
	}

	/* CORE FUNCTION. Where the game actually runs.*/
	void gameStart() {
		/* WELCOMING MESSAGES */
		cout << "Welcome " << player.getName() << endl;
		cout << "This is a game about rescuing a princess inside a cave. In the cave you can find unlocked and locked doors, a key, a ring, a dragon and a sword." << endl;
		cout << "Use 'n' for north, 's' for south, 'e' for east, 'w' for west. Other characters will NOT be recognized." << endl << endl << endl;
		cout << "Currently, you have " << player.getRemainingLives();
		(player.getRemainingLives() != 1) ? cout << " lives" : cout << " life"; // Check if the life is singular or plural
		cout << endl;
		cout << "Description of the position: " << map[player.getPlayerPositionY()][player.getPlayerPositionX()].getDescription() << endl;
		char userInput;
		/* FUN BEGINS */
		while (!exitGame) {
			cout << endl << "Make a move: ";
			cin >> userInput;
			cout << endl;
			/* First of all, we need to check if you can move. I pass a pointer to the function checkMove() because I need to modify the map.*/
			if (player.checkMove(*ptrMap, userInput, player.getInventory())) {
				MapObj tempMapPositionGrid = map[player.getPlayerPositionY()][player.getPlayerPositionX()]; // saved into another variable to save a bit of code.
				cout << "You have moved. Description of the new position: " << tempMapPositionGrid.getDescription() << endl;
				/* I check here what kind of grid you are facing. It can be: dragon, key, sword, princess or ring.*/
				/* If you pick up an item, the description of that position will be changed.*/
				if (tempMapPositionGrid.getName() == "dragon") {
					if (player.getInventory().hasItem("sword")) {
						cout << "Congratz, you killed the dragon, you can pass now." << endl;
					}
					else {
						player.die(); // player dies so they lose a life and the inventory should be emptied.
						createMap(); //restored the map to its default values
						hasPrincess = false;
						if (player.checkRemainingLives() == true) {
							gameStart();
						}
						else {
							exitGame = true;// ends the game
						}
					}
				}
				else if (tempMapPositionGrid.getName() == "key") {
					if (tempMapPositionGrid.getPickedStatus() == true) {
						map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("You already got the key. Please continue your journey"); /* Description changed */
					}
					else {
						cout << "Do you want to pick up the key?('y' for yes, whatever else for no :    ";
						cin >> userInput;
						if (userInput == 'y') {
							player.setItemInInventory(key);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setPicked(true);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("There used to be a key here."); /* Description changed */
						}
					}
				}
				else if (tempMapPositionGrid.getName() == "sword") {
					if (tempMapPositionGrid.getPickedStatus() == true) {
						map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("You already got the sword. Please continue your journey"); /* Description changed */
					}
					else {
						cout << "Do you want to pick up the sword?('y' for yes, whatever else for no :    ";
						cin >> userInput;
						if (userInput == 'y') {
							player.setItemInInventory(sword);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setPicked(true);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("There used to be a sword here."); /* Description changed */
							map[2][5].setDescription("You have a sword now, fight him!."); // it changes the display message of the dragon object.
						}
					}
				}
				else if (tempMapPositionGrid.getName() == "ring") {
					if (tempMapPositionGrid.getPickedStatus() == true) {
						map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("You already got the ring. Please continue your journey"); /* Description changed */
					}
					else {
						cout << "Do you want to pick up the ring?('y' for yes, whatever else for no :    ";
						cin >> userInput;
						if (userInput == 'y') {
							player.setItemInInventory(ring);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setPicked(true);
							map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("There used to be a ring here."); /* Description changed */
						}
					}
				}
				else if (tempMapPositionGrid.getName() == "princess") {
					if (tempMapPositionGrid.getPickedStatus() != true) {
						cout << "Good job, you found the princess. Now you should get out of the cave." << endl;
						map[player.getPlayerPositionY()][player.getPlayerPositionX()].setDescription("The princess is following you. Please continue scort her to the exit."); /* Description changed */
						map[player.getPlayerPositionY()][player.getPlayerPositionX()].setPicked(true);
						/* TO MAKE THE GAME A BIT MORE DIFFICULT TO PLAY, I CHANGED THE DRAGON POSITION AND LOCKED THAT ROOM
							SO THE USER MUST FIND NOW THE SWORD TO KILL THE DRAGON WHICH IS IN THE WAY OUT.
						*/
						hasPrincess = true;
						map[2][4] = closedDoor;
						map[2][5] = dragon;
					}
				}
			} // end checkMove()
			/* CHECK IF HE RESCUED THE PRINCESS, PLUS IF HE PICKED UP THE RING, THE PRINCESS WILL MARRY HIM.*/
			if (hasPrincess && player.getPlayerPositionY() == 0 && player.getPlayerPositionX() == 5) {
				exitGame = true;
				cout << "CONGRATULATIONS, you finished the game.";
				if (player.getInventory().hasItem("ring")) cout << " And since you picked up the ring, the princess decided to marry you.";
				cout << endl;
			}
			
		} // end while
	}
};

/* MAIN PROGRAM*/
int main()
{	
	Game newGame(5);
	newGame.askForUserName();
	newGame.gameStart();
	
    return 0;
}
