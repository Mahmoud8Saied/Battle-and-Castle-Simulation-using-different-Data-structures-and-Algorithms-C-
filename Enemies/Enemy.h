#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Generic_DS\Queue.h"
#include <fstream>
#include <iostream>
class Castle;

// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:

	const int ID;  //Each enemy has a unique ID (sequence number)
	
	const int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, active, frosted, killed)
	
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	const double OrgHealth; // Enemy health at the start of the game

	double Speed;
	
	double Power;

	int FreezeTime;

	int FrstTimeFrosted;

	int ReloadTime;

	int FirstShotDelay;
	
	int FirstShotTime;
	
	int EnemyKilledTime;

	int KillDelay;
	
	int LifeTime;
	
	ENMY_TYPE Enemy_Type; // Type of the enemy (Fighter, Healer, Freezer)

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(int id, int arrTime, ENMY_TYPE type, double H, double P, int RL, double s, int d = MaxDistance);

	virtual ~Enemy();

	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );

	void SetHealth(double H);

	void SetSpeed(double s);

	void SetPower(double P);

	void SetFreezeTime(int t);

	void SetFrstTimeFrosted(int t);

	void SetReloadTime(int RL);

	void SetFirstShotDelay(int FSD);

	void SetKillDelay(int KD);

	void SetLifeTime(int LT);

	void SetEnemyKilledTime(int KT);

	void SetFirstShotTime(int FST);

// -----------------------------------------------------------
	int GetDistance() const;
	
	int GetArrvTime() const;
	
	double GetHealth() const;
	
	double GetOrgHealth() const;

	double GetSpeed() const;
	
	double GetPower() const;

	int GetFreezeTime() const;

	int GetFrstTimeFrosted() const;

	int GetReloadTime() const;
    
	int GetFirstShotDelay() const;
	
	int GetKillDelay() const;
	
	int GetLifeTime() const;
	
	int GetEnemyKilledTime() const;
	
	int GetFirstShotTime() const;

	int GetID() const;
	
	ENMY_STATUS GetStatus() const;

	void MoveForward();

	virtual void Move() = 0;	

	bool Freezed();

	bool Killed();

	ENMY_TYPE GetType() const;
};

