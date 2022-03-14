#pragma once
#include "..\Defs.h"
#include "..\Generic_DS\PrtQueue.h"
#include "..\Generic_DS\Stack.h"
#include "..\Generic_DS\Queue.h"

#include "..\Enemies\Healer.h"
#include "..\Enemies\Freezer.h"
#include "..\Enemies\Fighter.h"


class Castle
{
	double OrgHealth;
	double Health;
	int MaxEnemies;		// the maximum number of enemies a castle can attack at any time step
	double Power;
	double Threshold;
	CSL_STATUS status;
	double IceAmount;
	int FirstFreezeStep;


public:
	Castle();
	Castle(double ch, int n, double cp);

	void SetHealth(double h);
	void SetMaxEnemies(int n);
	void SetPower(double p);
	void SetThreshold(double th);
	void SetStatus(CSL_STATUS stat);
	void SetIceAmount(double amount);

	double GetOrgHealth() const;
	double GetHealth() const;
	int GetMaxEnemies() const;
	double GetPower() const;
	double GetThreshold() const;
	CSL_STATUS GetStatus() const;
	double GetIceAmount() const;

	void Act(Enemy * enemy, int currTimeStep);
	void ShootBullets(Enemy* enemy, int currTimeStep);
	void ShootIce(Enemy* enemy, int currTimeStep);
};

