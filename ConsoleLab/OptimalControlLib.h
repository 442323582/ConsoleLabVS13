
#pragma once

#include"DataMat.h"

class Calculator;
class DiffIterator;
class DynamicSystem;
class Performance;

class Mediator
{
public:
	Mediator(){}
	~Mediator(){}

	int getnState(){ return nodeStateList.size(); }
	void addNodeState(NodeState* mat){ nodeStateList.push_back(mat); }
	NodeState * getNodeState(int index){ return nodeStateList[index]; }
	void addAdjointMat(AdjointMat* mat){ adjointMatList.push_back(mat); }
	AdjointMat* getAdjointMat(int index){ return adjointMatList[index]; }
	void setControlMat(ControlMat * mat){ contorlMat = mat; }
	ControlMat* getControlMat(){ return contorlMat; }
	void setTopology(Topology * topo){ this->topo = topo; }
	Topology * getTopology(){ return topo; }
	void setCalculator(Calculator* cal){ calculator = cal; }
	Calculator* getCalculator(){ return calculator; }
	void setDiffIterator(DiffIterator * diff){ diffIterator = diff; }
	DiffIterator* getDiffIterator(){ return diffIterator; }
	void addNodeRule(DynamicSystem* rule){ nodeRuleList.push_back(rule); }
	DynamicSystem * getNodeRule(int index){ return nodeRuleList[index]; }
	void addAdjointRule(DynamicSystem* rule){ adjointRuleList.push_back(rule); }
	DynamicSystem * getAdjointRule(int index){ return adjointRuleList[index]; }
	void setControlRule(DynamicSystem* rule){ controlRule = rule; }
	DynamicSystem * getControlRule(){ return controlRule; }
	void setVarargSet(VarargSet * varargSet){ this->varargSet = varargSet; }
	VarargSet * getVarargSet(){ return varargSet; }
	void setPerform(Performance * perform){ this->perform = perform; }
	Performance * getPerform(){ return perform; }
private:
	vector<NodeState*> nodeStateList;
	vector<AdjointMat*> adjointMatList;
	ControlMat * contorlMat;
	Topology * topo;
	Calculator * calculator;
	DiffIterator * diffIterator;
	vector<DynamicSystem*> nodeRuleList;
	vector<DynamicSystem*> adjointRuleList;
	DynamicSystem* controlRule;
	VarargSet * varargSet;
	Performance * perform;
};

class Performance
{
public:
	Performance(int length);
	~Performance(){}
	void action();
	void setMediator(Mediator * mediator){ this->mediator = mediator; }
	int getLength(){ return length; }
	double getLoss(int index){ return loss[index]; }
	double getCost(int index){ return cost[index]; }
	double getTotal(int index){ return total[index]; }
	double getCumuTotal(int index){ return cumuTotal[index]; }
private:
	double * loss;
	double * cost;
	double * total;
	double * cumuLoss;
	double * cumuCost;
	double * cumuTotal;
	void calLoss(int index);
	void calCost(int index);
	int length;
	Mediator * mediator;
};



class Calculator
{
public:
	Calculator(int maxIterTime,double totalTime, double stepLength);
	~Calculator(){}
	double getTotalTime(){ return totalTime; }
	double getStepLength(){ return stepLength; }
	void setMediator(Mediator * mediator){ this->mediator = mediator; }
	int getMaxIterTime(){ return maxIterTime; }
	void action();
private:
	int maxIterTime;
	double totalTime;
	double stepLength;
	Mediator * mediator;
};

class DiffIterator
{
public:
	DiffIterator(){}
	~DiffIterator(){}
	virtual double action(double oriVal, int iTime, int iNode, 
		double stepLength, int direct, DynamicSystem * dyna) = 0;
private:

};

class DynamicSystem
{
public:
	DynamicSystem(){}
	~DynamicSystem(){}
	virtual double action(int row, int col) = 0;
	void setMediator(Mediator * mediator){ this->mediator = mediator; }
private:
	Mediator * mediator;
};

class EulerIterator : public DiffIterator
{
public:
	EulerIterator(){}
	~EulerIterator(){}
	double action(double oriVal, int iTime, int iNode,
		double stepLength, int direct, DynamicSystem * dyna){
		double val;
		if (direct == 0){
			val = oriVal - stepLength * dyna->action(iTime, iNode);
		}
		else{
			val = oriVal + stepLength * dyna->action(iTime, iNode);
		}
		return val;
	}
private:

};




