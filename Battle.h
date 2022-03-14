#pragma once
#include <string>
#include "GUI\GUI.h"
#include "Castle\Castle.h"
#include "Enemies\Enemy.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS/PriorityQ.h"
#include "Generic_DS/Stack.h"


// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyDeal;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
											// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies

	Queue<Freezer *> Q_ActiveFreezers;	//queue for active freezers
	Queue<Enemy*> Q_Killed;		//queue for killed enemies

	PrtQueue<Fighter*> PQ_ActiveFighters; //priorityQ for active fighters
	PrtQueue<Enemy*> PQ_Frozen;		//priorityQ for frozen enemies
	Stack<Healer*> S_ActiveHealers; //stack for active healers


	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>

	string gamestatus;				//The state of the game whether WIN, LOSS and DRAWN
	// TODO: Add More Data Members As Needed
	//
	bool castleFrosted;
	int activeFightersNum;
	int activeHealersNum;
	int activeFreezersNum;
	int frostedFighters;
	int frostedHealers;
	int frostedFreezers;
	int killedFighters;
	int killedHealers;
	int killedFreezers;


public:

	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived


	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	//void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)
	void UpdateFighters();
	//
	// TODO: Add More Member Functions As Needed
	//
	void ReadFile(); //to read the input file
	void OutputFile(); //Function to write output file
	//game modes
	void Interactive_Mode();
	void Silent_Mode();
	void Step_Mode();

	void PrintParams();
};

