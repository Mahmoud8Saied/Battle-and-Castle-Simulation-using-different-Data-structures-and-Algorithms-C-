#pragma once
#include "Enemy.h"
class Fighter : public Enemy
{
	//GUI* pGUI;
	int priFactor;

public:
	Fighter(int id,int arrTime, double health, double power, int RL, int speed);

	Fighter(int id, int arrTime);

	void Act(Castle* castle, int currTimeStep);

	void Move();

	int GetPriFactor() const;

	~Fighter(void);
};

