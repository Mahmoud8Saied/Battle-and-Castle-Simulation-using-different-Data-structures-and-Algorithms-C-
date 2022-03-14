#pragma once
#include "Enemy.h"

class Healer : public Enemy
{
private:
	bool isForward;

public:
	Healer(int id, int arrTime, double health, double power, int RL, int speed);

	Healer(int id, int arrTime);

	void Act(Enemy * enemy, int currTimeStep);

	void Move();

	~Healer(void);
};

