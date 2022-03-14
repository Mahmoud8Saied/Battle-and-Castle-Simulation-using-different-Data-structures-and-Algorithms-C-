//#include "../Defs.h"
#include "Healer.h"
#include <cmath>

Healer::Healer(int id, int arrTime, double health, double power, int RL, int speed) 
	: Enemy (id, arrTime, HEALER, health, power, RL, speed), isForward(true)
{
}

Healer::Healer(int id, int arrTime)
	: Enemy(id, arrTime), isForward(true)
{
	Enemy_Type = HEALER;
}

void Healer :: Act(Enemy * enemy, int currTimeStep)
{
	if ((currTimeStep - ArrvTime) % ReloadTime + 1)		// to check if the healer is at reload period
		return;

	if (isForward && enemy->GetDistance() < Distance - 2 
		|| !isForward && enemy->GetDistance() > Distance + 2)
		return;

		// Formulate an equation for healing other enemies
	if (status == ACTV && enemy->GetStatus() == ACTV) {
		double K = (enemy->GetHealth() > 0.5 * enemy->GetOrgHealth() ? 0.5 : 1);
		int dist = std::abs(Distance - enemy->GetDistance());
		double increament = (K * Power * Health) / ((dist == 0 ? 1 : dist) * enemy->GetHealth());

		if (enemy->GetHealth() + increament > enemy->GetOrgHealth())
			enemy->SetHealth(enemy->GetOrgHealth());
		else
			enemy->SetHealth(enemy->GetHealth() + increament);
	}
}

void Healer :: Move()
{

	if (status == ACTV) {
		if (Distance == MinDistance)
			isForward = false;
		else if (Distance == MaxDistance)
			isForward = true;

		if (isForward)
			MoveForward();
		else
			SetDistance(Distance + (Health < 0.5 * OrgHealth ? 0.5 * (int)Speed : Speed)); // Move Backward
	}

}

Healer::~Healer(void)
{
}
