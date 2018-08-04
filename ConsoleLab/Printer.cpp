#include "Printer.h"


Printer::Printer()
{
}


Printer::~Printer()
{
}

void Printer::printVar(Mediator * mediator){
	double t = mediator->getCalculator()->getTotalTime();
	double h = mediator->getCalculator()->getStepLength();
	double maxt = mediator->getCalculator()->getMaxIterTime();
	double maxVal = mediator->getControlMat()->getMaxVal();
	double minVal = mediator->getControlMat()->getMinVal();
	cout << "显示参数：" << endl;
	cout << "1.\t控制最大值：" << maxVal << endl;
	cout << "2.\t控制最小值：" << minVal << endl;
	int nState = mediator->getnState();
	string name;
	double val;
	for (int i = 0; i < nState; i++){
		name = mediator->getNodeState(i)->getName();
		val = mediator->getNodeState(i)->getInitValue();
		cout << i + 3 << ".\t" << name << "初始值：" << val << endl;
	}
	int nVar = mediator->getVarargSet()->getnVar();
	for (int i = 0; i < nVar; i++){
		mediator->getVarargSet()->getVar(i, name, val);
		cout << i + 2 + nState + 1 << ".\t" << name << "：" << val << endl;
	}
	cout << 1+2+nState+nVar+1 << ".\t*迭代总时间*：" << t << endl;
	cout << 1 + 2 + nState + nVar+1+1 << ".\t*迭代步长*：" << h << endl;
	cout << 1 + 2 + nState + nVar + 1 + 1+1 << ".\t*最大迭代次数*：" << maxt << endl;
}

void Printer::printDataMat(DataMat * mat){
	int rows = mat->getRows();
	int cols = mat->getCols();
	cout << mat->getName() << endl;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			cout << mat->getValue(i, j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Printer::printTopology(Topology * topo){
	int nNode = topo->getnNode();
	int val;
	cout << "邻接矩阵：" << endl;
	for (int i = 0; i < nNode; i++){
		for (int j = 0; j < nNode; j++){
			val = topo->getValue(i, j);
			cout << val << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void Printer::printPerform(Performance * perf){
	int length = perf->getLength();
	cout << "cost performance：" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getCost(i) << endl;
	}
	cout << endl;

	cout << "loss performance：" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getLoss(i) << endl;
	}
	cout << endl;

	cout << "total performance：" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getTotal(i) << endl;
	}
	cout << endl;

	cout << "CumuTotal performance：" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getCumuTotal(i) << endl;
	}
	cout << endl;
}

