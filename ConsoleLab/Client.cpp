#include "Client.h"
//
void int2str(const int &int_temp, string &string_temp);
void str2int(int &int_temp, const string &string_temp);

Client::Client()
{

}


Client::~Client()
{
}

void Client::setTopology(string fileName){
	Topology * topo = new Topology();
	mediator->setTopology(topo);
	topo->readTxt(fileName);
}

void Client::init(){
	//Mediator
	Mediator * mediator = new Mediator();
	setMediator(mediator);

	//VarargSet
	VarargSet *var = new VarargSet;
	mediator->setVarargSet(var);

	double totalTime;
	double stepLength;
	int maxTime;
	cout << "--------设置迭代参数--------" << endl;
	cout << "迭代总时间：";
	cin >> totalTime;
	cout << "迭代步长：";
	cin >> stepLength;
	cout << "最大迭代次数：";
	cin >> maxTime;
	cout << endl;

	
	//Calculator
	Calculator * cal = new Calculator(maxTime, totalTime, stepLength);
	mediator->setCalculator(cal);
	cal->setMediator(mediator);
	
	//init user defined
	initDefined();

	//Set mat
	int nTime = (int)(totalTime / stepLength);
	int nState = mediator->getnState();
	int nNode = mediator->getTopology()->getnNode();
	DataMat * mat;
	for (int i = 0; i < nState; i++){
		mat = mediator->getNodeState(i);
		mat->setRows(nTime + 1);
		mat->setCols(nNode);
		mat = mediator->getAdjointMat(i);
		mat->setRows(nTime + 1);
		mat->setCols(nNode);
	}
	mat = mediator->getControlMat();
	mat->setRows(nTime + 1);

	//Performance
	Performance * perform = new Performance(nTime + 1);
	mediator->setPerform(perform);
	perform->setMediator(mediator);
}

void Client::addNodeState(string name){
	NodeState * mat = new NodeState(name);
	mediator->addNodeState(mat);
}

void Client::addAdjointMat(string name){
	AdjointMat * mat = new AdjointMat(name);
	mediator->addAdjointMat(mat);
}

void Client::setControl(int cols){
	ControlMat * mat = new ControlMat(cols);
	mediator->setControlMat(mat);
}

void Client::mainfunc(){
	while (true){
		cout << "--------主界面--------" << endl;
		cout << "1. 单次计算" << endl;
		cout << "2. 参数测试" << endl;
		cout << "3. 综合计算" << endl;
		cout << "0. 退出" << endl;
		cout << endl;
		cout << "选择功能：" ;
		cin >> command;
		if (command == "1"){
			cout << endl;
			singleCalculate();
		}
		else if (command == "2"){

		}
		else if (command == "3"){

		}
		else if (command == "0"){

			break;
		}
		else {
			cout << "指令有误" << endl;
		}
		cout << endl;
	}
}

void Client::printInfo(){
	printer.printVar(mediator);
	printer.printTopology(mediator->getTopology());
	int nState = mediator->getnState();
	DataMat * mat;
	for (int i = 0; i < nState; i++){
		mat = mediator->getNodeState(i);
		printer.printDataMat(mat);
		mat = mediator->getAdjointMat(i);
		printer.printDataMat(mat);
	}
	mat = mediator->getControlMat();
	printer.printDataMat(mat);
	Performance * perf = mediator->getPerform();
	printer.printPerform(perf);
}

void Client::singleCalculate(){
	VarargSet* var = mediator->getVarargSet();
	while (true){
		cout << "--------单次计算--------" << endl;
		printer.printVar(mediator);
		cout << endl;
		cout << "功能列表：" << endl;
		cout << "1. 开始计算" << endl;
		cout << "2. 修改参数" << endl;
		cout << "3. 重置参数" << endl;
		cout << "0. 返回" << endl;
		cout << endl;
		cout << "选择功能：" ;
		cin >> command;
		if (command == "1"){
			run();
		}
		else if (command == "2"){
			cout << endl;
			setVarValue();
		}
		else if (command == "3"){
			cout << endl;
			resetVarValue();
		}
		else if (command == "0"){
			break;
		}
		else {
			cout << "指令有误" << endl;
		}
		cout << endl;
	}
}

void Client::resetVarValue(){
	string varname;
	double val;
	cout << "--------重置参数--------" << endl;
	cout << "控制最大值：";
	cin >> val;
	mediator->getControlMat()->setMaxVal(val);
	cout << endl;
	cout << "控制最小值：";
	cin >> val;
	mediator->getControlMat()->setMinVal(val);
	cout << endl;

	DataMat * mat;
	int nState = mediator->getnState();
	for (int i = 0; i < nState; i++){
		mat = mediator->getNodeState(i);
		varname = mat->getName();
		cout << varname << "初始值：";
		cin >> val;
		mat->setInitValue(val);
		cout << endl;
	}

	VarargSet * var = mediator->getVarargSet();
	int nVar = var->getnVar();
	for (int i = 0; i < nVar; i++){
		varname = var->getVarName(i);
		cout << varname << "：";
		cin >> val;
		var->setVarValue(i, val);
		cout << endl;
	}	
	cout << "参数重置完成" << endl;
}

void Client::setVarValue(){
	int nState = mediator->getnState();
	int nVarargSet = mediator->getVarargSet()->getnVar();
	int nVar = 2 + nState + nVarargSet;
	int iVar;
	string sVar;
	int2str(nVar, sVar);
	double val;
	while (true)
	{
		cout << "--------修改参数--------" << endl;
		printer.printVar(mediator);
		cout << "0.\t返回" << endl;
		cout << endl;
		cout << "选择参数序号：" ;
		cin >> command;
		if (command >= "0" && command <= sVar){
			if (command == "0"){
				break;
			}
			else{
				str2int(iVar, command);				
				if (iVar == 1){
					cout << "控制最大值：";
					cin >> val;
					mediator->getControlMat()->setMaxVal(val);
				}
				else if (iVar == 2){
					cout << "控制最小值：";
					cin >> val;
					mediator->getControlMat()->setMinVal(val);
				}
				else if (iVar >= 3 && iVar <= 2 + nState){
					iVar = iVar - 3;
					cout << mediator->getNodeState(iVar)->getName() << "：";
					cin >> val;
					mediator->getNodeState(iVar)->setInitValue(val);
				}
				else {
					iVar = iVar - 3 - nState;
					cout << mediator->getVarargSet()->getVarName(iVar) << "：";
					cin >> val;
					mediator->getVarargSet()->setVarValue(iVar, val);
				}
			}
		}
		else{
			cout << "指令有误" << endl;
		}
		cout << endl;
	}
}

void Client::addVar(string name){
	VarargSet * var = mediator->getVarargSet();
	var->addVar(name);
}

void Client::run(){
	int nState = mediator->getnState();
	DataMat * mat;
	for (int i = 0; i < nState; i++){
		mat = mediator->getNodeState(i);
		mat->createMat();
		mat = mediator->getAdjointMat(i);
		mat->createMat();
	}
	mat = mediator->getControlMat();
	mat->setInitValue(mat->getMaxVal());
	mat->createMat();

	mediator->getCalculator()->action();
	mediator->getPerform()->action();

	printInfo();
}

void int2str(const int &int_temp, string &string_temp)
{
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   //此处也可以用 stream>>string_temp  
}


void str2int(int &int_temp, const string &string_temp)
{
	stringstream stream(string_temp);
	stream >> int_temp;
}


void Client::startup(){
	init();
	mainfunc();
}