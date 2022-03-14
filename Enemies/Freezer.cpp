#include "../Castle/Castle.h"
#include "Freezer.h"
#include "../Defs.h"
#include <cmath>

Freezer::Freezer(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, FREEZER, health, power, RL, speed)
{
}

Freezer::Freezer(int id, int arrTime)
	: Enemy(id, arrTime)
{
	Enemy_Type = FREEZER;
}

void Freezer :: Act(Castle * castle, int currTimeStep)
{
	if ((currTimeStep - ArrvTime) % ReloadTime + 1)		// to check if the freezer is at reload period
		return;

	if (status == ACTV && castle->GetStatus() == CSL_ACTV) {
		double rateOfIncrease = ((Health < 0.5 * OrgHealth ? 0.5 : 1) / Distance) * Power;
		if (castle->GetIceAmount() + rateOfIncrease < castle->GetThreshold())
			castle->SetIceAmount(castle->GetIceAmount() + rateOfIncrease);
		else {
			castle->SetIceAmount(0);
			castle->SetStatus(CSL_FRST);
		}

	}
}

void Freezer :: Move()
{
	if (status == ACTV)
		MoveForward();

}

Freezer::~Freezer(void)
{
}
