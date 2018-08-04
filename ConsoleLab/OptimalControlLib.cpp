

#include"OptimalControlLib.h"

Performance::Performance(int length){
	loss = new double[length]();
	cost = new double[length]();
	total = new double[length]();
	cumuLoss = new double[length]();
	cumuCost = new double[length]();
	cumuTotal = new double[length]();
	this->length = length;
}

void Performance::action(){
	for (int i = 0; i < length; i++){
		calCost(i);
		calLoss(i);
		total[i] = loss[i] + cost[i];
	}
	for (int i = 1; i < length; i++){
		cumuLoss[i] = cumuLoss[i - 1] + loss[i];
		cumuCost[i] = cumuCost[i - 1] + cost[i];
		cumuTotal[i] = cumuTotal[i - 1] + total[i];
	}
}

Calculator::Calculator(int maxIterTime,double totalTime, double stepLength)
{
	this->maxIterTime = maxIterTime;
	this->totalTime = totalTime;
	this->stepLength = stepLength;
}

void Calculator::action(){
	int nTime = (int)(totalTime/stepLength);
	int nNode = mediator->getTopology()->getnNode();
	int nState = mediator->getnState();
	int nControl = mediator->getControlMat()->getCols();
	double oriVal;
	double val;
	DataMat * mat;
	DynamicSystem * rule;
	for (int iter = 0; iter < maxIterTime; iter++){
		for (int iTime = 0; iTime < nTime; iTime++){
			for (int iNode = 0; iNode < nNode; iNode++){
				for (int iState = 0; iState < nState; iState++){
					mat = mediator->getNodeState(iState);
					rule = mediator->getNodeRule(iState);
					oriVal = mat->getValue(iTime, iNode);
					val = mediator->getDiffIterator()->action(oriVal, iTime, iNode,
						stepLength, 1, rule);
					mat->setValue(iTime + 1, iNode, val);
				}
			}
		}
		for (int iTime = nTime; iTime > 0; iTime--){
			for (int iNode = 0; iNode < nNode; iNode++){
				for (int iAdjoint = 0; iAdjoint < nState; iAdjoint++){
					mat = mediator->getAdjointMat(iAdjoint);
					rule = mediator->getAdjointRule(iAdjoint);
					oriVal = mat->getValue(iTime, iNode);
					val = mediator->getDiffIterator()->action(oriVal, iTime, iNode,
						stepLength, 0, rule);
					mat->setValue(iTime-1, iNode, val);
				}
			}
		}
		mat = mediator->getControlMat();
		rule = mediator->getControlRule();
		for (int iTime = 1; iTime <= nTime; iTime++){
			for (int iControl = 0; iControl < nControl; iControl++){
				val = rule->action(iTime, iControl);
				mat->setValue(iTime, iControl, val);
			}
		}
	}
}