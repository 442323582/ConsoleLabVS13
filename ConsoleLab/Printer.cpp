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
	cout << "��ʾ������" << endl;
	cout << "1.\t�������ֵ��" << maxVal << endl;
	cout << "2.\t������Сֵ��" << minVal << endl;
	int nState = mediator->getnState();
	string name;
	double val;
	for (int i = 0; i < nState; i++){
		name = mediator->getNodeState(i)->getName();
		val = mediator->getNodeState(i)->getInitValue();
		cout << i + 3 << ".\t" << name << "��ʼֵ��" << val << endl;
	}
	int nVar = mediator->getVarargSet()->getnVar();
	for (int i = 0; i < nVar; i++){
		mediator->getVarargSet()->getVar(i, name, val);
		cout << i + 2 + nState + 1 << ".\t" << name << "��" << val << endl;
	}
	cout << 1+2+nState+nVar+1 << ".\t*������ʱ��*��" << t << endl;
	cout << 1 + 2 + nState + nVar+1+1 << ".\t*��������*��" << h << endl;
	cout << 1 + 2 + nState + nVar + 1 + 1+1 << ".\t*����������*��" << maxt << endl;
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
	cout << "�ڽӾ���" << endl;
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
	cout << "cost performance��" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getCost(i) << endl;
	}
	cout << endl;

	cout << "loss performance��" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getLoss(i) << endl;
	}
	cout << endl;

	cout << "total performance��" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getTotal(i) << endl;
	}
	cout << endl;

	cout << "CumuTotal performance��" << endl;
	for (int i = 0; i < length; i++){
		cout << perf->getCumuTotal(i) << endl;
	}
	cout << endl;
}

