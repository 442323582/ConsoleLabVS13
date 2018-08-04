


#include"Printer.h"
#include"OptimalControlLib.h"
#include"UserDefined.h"
#include"Client.h"


int main(){

	Client client;
	client.startup();

	char ch;
	cin >> ch;
	return 0;
}

void Client::initDefined(){
	
	addVar("beta_i");
	addVar("beta_p");
	addVar("gamma_p");
	addVar("delta");

	addNodeState("I");
	addNodeState("P");
	addAdjointMat("Lambda");
	addAdjointMat("Mu");
	setControl(1);

	DiffIterator * diff = new EulerIterator();
	setDiffIterator(diff);

	DynamicSystem * dyna = new MyDyna();
	addNodeRule(dyna);
	addNodeRule(dyna);
	addAdjointRule(dyna);
	addAdjointRule(dyna);
	setControlRule(dyna);

	setTopology("smallworld.txt");
	
}

void Performance::calCost(int index ){
	cost[index] = 0.1;
}

void Performance::calLoss(int index){
	loss[index] = 0.2;
}