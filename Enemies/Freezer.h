#pragma once
#include "Enemy.h"


class Freezer : public Enemy
{
public:
	Freezer(int id, int arrTime, double health, double power, int RL, int speed);

	Freezer(int id, int arrTime);

	void Act(Castle * castle, int currTimeStep);

	void Move();


	~Freezer(void);
};

