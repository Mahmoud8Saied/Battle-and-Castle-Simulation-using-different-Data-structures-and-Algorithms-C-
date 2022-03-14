#include "Battle.h"
#include <time.h>
#include <fstream>
#include "Castle/Castle.h"
#include "Enemies/Fighter.h"
#include "Enemies/Healer.h"
#include "Enemies/Freezer.h"

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;

	bool castleFrosted = false;
	int activeFightersNum = 0;
	int activeHealersNum = 0;
	int activeFreezersNum = 0;
	int frostedFighters = 0;
	int frostedHealers = 0;
	int frostedFreezers = 0;
	int killedFighters = 0;
	int killedHealers = 0;
	int killedFreezers = 0;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive_Mode();
		break;
	case MODE_STEP:
		Step_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
		/*case MODE_DEMO:
		Just_A_Demo();*/

	}

	delete pGUI;

}

void Battle::ReadFile() {
	pGUI->PrintMessage("Please Enter The File Name");
	string Filename = pGUI->GetString(); //file name to be input by the user
	ifstream Input(Filename + ".txt");

	double ch, cp;
	int n;
	Input >> ch >> n >> cp;		//castle health and maximum number of enemies hit
	Castle pCastle(ch, n, cp);
	this->BCastle = pCastle;
	int enemyNumber;
	Input >> enemyNumber;
	EnemyCount = enemyNumber;
	EnemyDeal = n;

	int ID, TYP, AT, H, POW, RLD, SPD;
	Enemy* pE = NULL;

	//for each enemy get the enemy's info
	for (int i = 0; i < enemyNumber; i++)
	{
		//for now we will get the id and arrival time
		Input >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;

		switch (TYP) {
		case FIGHTER:
			pE = new Fighter(ID, AT,H,POW,RLD,SPD); //add cases for each type
			break;
		case HEALER:
			pE = new Healer(ID, AT, H, POW, RLD, SPD);
			break;
		case FREEZER:
			pE = new Freezer(ID, AT, H, POW, RLD, SPD);
			break;
		}

		if (H > 0) {

			pE->SetStatus(INAC); //initiall all enemies are inactive
		}
		else {
			// then the enemy will be dead already
			pE->SetStatus(KILD);
		}
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}
	AddAllListsToDrawingList();

	castleFrosted = false;
	activeFightersNum = 0;
	activeHealersNum = 0;
	activeFreezersNum = 0;
	frostedFighters = 0;
	frostedHealers = 0;
	frostedFreezers = 0;
	killedFighters = 0;
	killedHealers = 0;
	killedFreezers = 0;

	PrintParams();	//update the interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

}

void Battle::Silent_Mode() {
	pGUI->PrintMessage("Welcome to Silent Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();

	}
	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";

	OutputFile();
}

void Battle::Interactive_Mode() {
	pGUI->PrintMessage("Welcome to Interactive Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		PrintParams();
		//pGUI->UpdateInterface(CurrentTimeStep);
		pGUI->waitForClick();
	}

	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";

	OutputFile();

}

void Battle::Step_Mode() {
	pGUI->PrintMessage("Welcome to Step Mode");
	pGUI->waitForClick();
	this->ReadFile();
	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		//update enemies here
		UpdateFighters();

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();

		PrintParams();
		Sleep(50);
	}

	if (KilledCount >= EnemyCount)
		gamestatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		gamestatus = "LOSE";
	else
		gamestatus = "DRAWN";

	OutputFile();
}

/*
//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{

pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
pGUI->waitForClick();

CurrentTimeStep = 0;
//
// THIS IS JUST A DEMO Function
// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//

srand(time(NULL));
int Enemy_id = 0;
int ArrivalTime = 1;
Enemy* pE = NULL;
//Create Random enemies and add them all to inactive queue
for (int i = 0; i < EnemyCount; i++)
{
ArrivalTime += (rand() % 3);	//Randomize arrival time

// pE = new Enemy(++Enemy_id, ArrivalTime);
switch (TYP) {
case FIGHTER:
pE = new Fighter(++Enemy_id, ArrivalTime); //add cases for each type
case HEALER:
pE = new Healer(++Enemy_id, ArrivalTime);
case FREEZER:
pE = new Freezer(++Enemy_id, ArrivalTime);
}

pE->SetStatus(INAC); //initiall all enemies are inactive
Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
}

AddAllListsToDrawingList();
pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

pGUI->waitForClick();

while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
{
CurrentTimeStep++;
ActivateEnemies();

Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

pGUI->ResetDrawingList();
AddAllListsToDrawingList();
pGUI->UpdateInterface(CurrentTimeStep);
Sleep(250);
}
}
*/

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyListInactive = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyListInactive[i]);

	//Add other lists to drawing list
	int ActiveFreezersCount;
	Freezer* const * EnemyListActiveFreezers = Q_ActiveFreezers.toArray(ActiveFreezersCount);
	for (int i = 0; i < ActiveFreezersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFreezers[i]);
	}

	int KilledCount;
	Enemy* const * EnemyListKilled = Q_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++) {
		pGUI->AddToDrawingList(EnemyListKilled[i]);
	}

	int ActiveFightersCount;
	Fighter* const * EnemyListActiveFighters = PQ_ActiveFighters.toArray(ActiveFightersCount);
	for (int i = 0; i < ActiveFightersCount; i++) {
		pGUI->AddToDrawingList(EnemyListActiveFighters[i]);
	}

	int FrozenCount;
	Enemy* const * EnemyListFrozen = PQ_Frozen.toArray(FrozenCount);
	for (int i = 0; i < FrozenCount; i++) {
		pGUI->AddToDrawingList(EnemyListFrozen[i]);
	}

	int ActiveHealersCount;
	Healer* const * EnemyListHealers = S_ActiveHealers.toArray(ActiveHealersCount);
	for (int i = 0; i < ActiveHealersCount; i++) {
		pGUI->AddToDrawingList(EnemyListHealers[i]);
	}

	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	/*for (int i = 0; i < DemoListCount; i++)
	pGUI->AddToDrawingList(DemoList[i]);*/
}





//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		/*AddtoDemoList(pE);	*/	//move it to demo list (for demo purposes)
		switch (pE->GetType())		//add emeies to respective lists
		{
		case(FIGHTER):
			PQ_ActiveFighters.enqueuePriority(dynamic_cast<Fighter*>(pE)->GetPriFactor(), dynamic_cast<Fighter*>(pE));
			activeFightersNum++;
			break;
		case(HEALER):
			S_ActiveHealers.push(dynamic_cast<Healer*>(pE));
			activeHealersNum ++;
			break;
		case(FREEZER):
			Q_ActiveFreezers.enqueue(dynamic_cast<Freezer*>(pE));
			activeFreezersNum++;
			break;
		}
		ActiveCount++;
	}
}

/*
//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}
}
*/
void Battle::UpdateFighters() {

	// Initialze Temp Structures and Pointers to enemies

	Fighter* currentFighter;
	Healer* currentHealer;
	Freezer* currentFreezer;

	Queue<Fighter*> tempFighters;
	Stack<Healer*> tempHealers;
	Queue<Freezer*> tempFreezers;
	/*
	PQ_ActiveFighters.toArray(activeFightersNum);

	S_ActiveHealers.toArray(activeHealersNum);

	Q_ActiveFreezers.toArray(activeFreezersNum);
	*/

	//// Enemies should attack the castle
	for (int i = 0; i < ActiveCount; i++) {
		bool IsFoundFighter = PQ_ActiveFighters.dequeue(currentFighter);	//get the first enemy from each type
		bool IsFoundHealer = S_ActiveHealers.pop(currentHealer);
		bool IsFoundFreezer = Q_ActiveFreezers.dequeue(currentFreezer);

		if (IsFoundFighter) {
			tempFighters.enqueue(currentFighter);
			currentFighter->Act(GetCastle(), CurrentTimeStep);
			currentFighter->Move();
		}

		if(IsFoundFreezer){
			tempFreezers.enqueue(currentFreezer);
			currentFreezer->Act(GetCastle(), CurrentTimeStep);
			currentFreezer->Move();
		}

		if (IsFoundHealer) {
			tempHealers.push(currentHealer);
			Queue<Fighter*> tempFightersH;
			Stack<Healer*> tempHealersH;
			Queue<Freezer*> tempFreezersH;

			Fighter* tempCurrFighter;
			Healer* tempCurrHealer;
			Freezer* tempCurrFreezer;

			//// Add Active enemies to temp structures and let the Healer do his job
			while(PQ_ActiveFighters.dequeue(tempCurrFighter)){
				currentHealer->Act(tempCurrFighter, CurrentTimeStep);
				tempFightersH.enqueue(tempCurrFighter);
			}
			while(S_ActiveHealers.pop(tempCurrHealer)){
				currentHealer->Act(tempCurrHealer, CurrentTimeStep);
				tempHealersH.push(tempCurrHealer);
			}
			while(Q_ActiveFreezers.dequeue(tempCurrFreezer)){
				currentHealer->Act(tempCurrFreezer, CurrentTimeStep);
				tempFreezersH.enqueue(tempCurrFreezer);
			}

			//// Return them back to their original Structures
			while(tempFightersH.dequeue(tempCurrFighter))
				PQ_ActiveFighters.enqueuePriority(tempCurrFighter->GetPriFactor(), tempCurrFighter);

			while(tempHealersH.pop(tempCurrHealer))
				S_ActiveHealers.push(tempCurrHealer);

			while(tempFreezersH.dequeue(tempCurrFreezer))
				Q_ActiveFreezers.enqueue(tempCurrFreezer);

			//// Then Move the Healer 
			currentHealer->Move();

			//if the health of anyone of them is less than the full health then the healer should heal them
			/*if (currentFighter->GetHealth() < currentFighter->GetOrgHealth() || currentFreezer->GetHealth() < currentFreezer->GetOrgHealth()) {
			if (currentFighter->GetDistance() - currentHealer->GetDistance() <= 2) {
			currentHealer->Act(currentFighter, CurrentTimeStep);
			}
			if (currentFreezer->GetDistance() - currentHealer->GetDistance() <= 2) {
			currentHealer->Act(currentFreezer, CurrentTimeStep);
			}
			}*/
		}
	}

	
	// Return them back to their original DSs
	while (tempFighters.dequeue(currentFighter))
		PQ_ActiveFighters.enqueuePriority(currentFighter->GetPriFactor(), currentFighter);

	while (tempHealers.pop(currentHealer))
		S_ActiveHealers.push(currentHealer);

	while (tempFreezers.dequeue(currentFreezer))
		Q_ActiveFreezers.enqueue(currentFreezer);


	////////////////////////////////////////////////////////////////////////////////////
	//the castle should also attack enemies

	for (int i = 0; i < EnemyDeal; ++i) {
		if (!PQ_ActiveFighters.isEmpty()) {
			Fighter* fighterPtr;
			PQ_ActiveFighters.dequeue(fighterPtr);
			GetCastle() -> Act (fighterPtr, CurrentTimeStep);
			tempFighters.enqueue(fighterPtr);
		}
		else if (!S_ActiveHealers.isEmpty()) {
			Healer* healerPtr;
			S_ActiveHealers.pop(healerPtr);
			GetCastle() -> Act (healerPtr, CurrentTimeStep);
			if (healerPtr->GetDistance() <= 5 && healerPtr->GetHealth() == 0)
				GetCastle()->SetHealth(GetCastle()->GetHealth() * 1.03);
			tempHealers.push(healerPtr);
		}

		else if (!Q_ActiveFreezers.isEmpty()) {
			Freezer* freezerPtr;
			Q_ActiveFreezers.dequeue(freezerPtr);
			GetCastle() -> Act (freezerPtr, CurrentTimeStep);
			tempFreezers.enqueue(freezerPtr);
		}
		else
			break;
	}


	// Then it should return them back to their original structures, but after checking freezing and killing states

	while (tempFighters.dequeue(currentFighter)) {
		if (currentFighter->GetHealth() < 1) {
			currentFighter->SetStatus(KILD);
			Q_Killed.enqueue(currentFighter);
			KilledCount++;
			--ActiveCount;
			killedFighters++;
			activeFightersNum--;
		}
		else if (currentFighter->Freezed()) {
			currentFighter->SetStatus(FRST);
			PQ_Frozen.enqueuePriority(100 - currentFighter->GetFreezeTime(), currentFighter);
			FrostedCount++;
			--ActiveCount;
			activeFightersNum--;
			frostedFighters++;
		}
		else
			PQ_ActiveFighters.enqueuePriority(currentFighter->GetPriFactor(), currentFighter);
	}

	while (tempHealers.pop(currentHealer)) {
		if (currentHealer->GetHealth() < 1) {
			currentHealer->SetStatus(KILD);
			Q_Killed.enqueue(currentHealer);
			KilledCount++;
			--ActiveCount;
			killedHealers++;
			activeHealersNum--;
		}
		else if (currentHealer->Freezed()) {
			currentHealer->SetStatus(FRST);
			PQ_Frozen.enqueuePriority(100 - currentHealer->GetFreezeTime(), currentHealer);
			FrostedCount++;
			--ActiveCount;
			activeHealersNum--;
			frostedHealers++;
		}
		else
			S_ActiveHealers.push(currentHealer);
	}

	while (tempFreezers.dequeue(currentFreezer)) {
		if (currentFreezer->GetHealth() < 1) {
			currentFreezer->SetStatus(KILD);
			Q_Killed.enqueue(currentFreezer);
			KilledCount++;
			--ActiveCount;
			killedFreezers++;
			activeFreezersNum--;
		}
		else if (currentFreezer->Freezed()) {
			currentFreezer->SetStatus(FRST);
			PQ_Frozen.enqueuePriority(100 - currentFreezer->GetFreezeTime(), currentFreezer);
			FrostedCount++;
			--ActiveCount;
			activeFreezersNum--;
			frostedFreezers++;
		}
		else
			Q_ActiveFreezers.enqueue(currentFreezer);
	}


	////////////////////////////// BUG POSSIBLE FIX ///////////////////////////////////////////
	Enemy* enemy;
	while (PQ_Frozen.peekFront(enemy) && (enemy->GetFrstTimeFrosted() + enemy->GetFreezeTime() ) == CurrentTimeStep) {
		PQ_Frozen.dequeue(enemy);
		enemy->SetStatus(ACTV);

		switch (enemy->GetType()) {
		case FIGHTER:
			PQ_ActiveFighters.enqueuePriority(dynamic_cast<Fighter*>(enemy)->GetPriFactor(), dynamic_cast<Fighter*>(enemy));
			frostedFighters--;
			activeFightersNum++;

			FrostedCount--;
			++ActiveCount;
			break;
		case HEALER:
			S_ActiveHealers.push(dynamic_cast<Healer*>(enemy));
			frostedHealers--;
			activeHealersNum++;

			FrostedCount--;
			++ActiveCount;
			break;
		case FREEZER:
			Q_ActiveFreezers.enqueue(dynamic_cast<Freezer*>(enemy));
			frostedFreezers--;
			activeFreezersNum++;

			FrostedCount--;
			++ActiveCount;
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////

	//then move the current time step forward
	//	CurrentTimeStep++;

	if (GetCastle()->GetStatus() == 0)
		castleFrosted = false;
	else 
		castleFrosted = true;

}


void Battle::PrintParams() {

	string msg = "Castle Health = " + to_string(BCastle.GetHealth()) 
		+ " Castle State is (FRST/Active) : " + to_string(castleFrosted) 
		+ " Active fighters = " + to_string(activeFightersNum) 
		+ " Active Healears = " + to_string(activeHealersNum) 
		+ " Active Feezers = " + to_string(activeFreezersNum) 
		+ " Frosted fighters = " + to_string(frostedFighters) 
		+ " Frosted healers = " + to_string(frostedHealers) 
		+ " Frosted freezers = " + to_string(frostedFreezers) 
		+ " Killed fighters = " + to_string(killedFighters) 
		+ " Killed healers = " + to_string(killedHealers) 
		+ " Killed freezers = " + to_string(killedFreezers);

	pGUI->UpdateInterface(CurrentTimeStep,msg);
}

void Battle::OutputFile()
{
	ofstream out("Outputfile.txt");


	out << "Game is " + gamestatus << endl;
	out << "KTS\tID\tFD\tKD\tLT" << endl;

	int enemy_id;
	int enemyKDS;
	int enemyFD;
	int enemyKD;
	int enemyLT;
	int totalFD = 0;
	int totalKD = 0;

	while (!Q_Killed.isEmpty())
	{
		Enemy* killed_enemy;
		Q_Killed.dequeue(killed_enemy);
		enemy_id = killed_enemy->GetID();
		enemyKDS = killed_enemy->GetEnemyKilledTime();
		enemyFD = killed_enemy->GetFirstShotDelay();
		enemyKD = killed_enemy->GetKillDelay();
		enemyLT = killed_enemy->GetLifeTime();
		totalFD += enemyFD;
		totalKD += enemyKD;

		out << enemyKDS << "\t" << enemy_id << "\t" << enemyFD << "\t" << enemyKD << "\t" << enemyLT << endl;

	}

	//////////////////////////We have to print Castle Total Damage here/////////////////////////////////

	double average_FD = (double)totalFD / EnemyCount;
	double average_KD = (double)totalKD / EnemyCount;

	out << "Castle total damage= " << BCastle.GetOrgHealth() - BCastle.GetHealth() << endl; 
	if (gamestatus == "WIN")
	{
		out << "Total Enemies = " << EnemyCount << endl;

	}
	else
	{
		out << "Killed Enemies = " << KilledCount << endl;
		out << "Alive Enemies = " << EnemyCount - KilledCount << endl;
	}

	out << "Average First-Shot Delay = " << average_FD << endl;
	out << "Average Kill Delay = " << average_KD << endl;
	out.close();

}