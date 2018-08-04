#pragma once
#include"OptimalControlLib.h"
#include"Printer.h"

class Client
{
public:
	Client();
	~Client();

	void setMediator(Mediator * mediator){ this->mediator = mediator; }
	void startup();
	void addNodeState(string name);
	void addAdjointMat(string name);
	void setControl(int cols);
	void setDiffIterator(DiffIterator * diff){ mediator->setDiffIterator(diff); }
	void addNodeRule(DynamicSystem * dyna){ mediator->addNodeRule(dyna); }
	void addAdjointRule(DynamicSystem * dyna) { mediator->addAdjointRule(dyna); }
	void setControlRule(DynamicSystem * dyna){ mediator->setControlRule(dyna); }
	void addVar(string name);
	void setTopology(string fileName);
	
private:
	string command;
	Mediator * mediator;
	Printer printer;
	void mainfunc();
	void singleCalculate();
	void setVarValue();
	void resetVarValue();
	void init();
	void initDefined();
	void run();
	void printInfo();
};

