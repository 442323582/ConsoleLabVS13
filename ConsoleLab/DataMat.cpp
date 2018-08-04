
#include"DataMat.h"
#include<fstream>
#include<sstream> 
#include<iostream>

using namespace std;

void VarargSet::setVarValue(int index, double val){
	if (index >= 0 && index < nameList.size()){
		valueList[index] = val;
	}
}

string VarargSet::getVarName(int index){
	if (index >= 0 && index < nameList.size()){
		return nameList[index];
	}
	return "";
}

double VarargSet::findVal(string name){
	int i;
	for (i = 0; i < nameList.size(); i++){
		if (name == nameList[i])
			break;
	}
	if (i == nameList.size())
		return 0;

	return valueList[i];
}

NodeState::NodeState(string name)
{
	this->name = name;
	setMaxVal(1);
	setMinVal(0);
}

ControlMat::ControlMat(int cols)
{
	setCols(cols);
	this->name = "Control mat";
}

void DataMat::setInitValue(double val){
	if (val > maxVal)
		val = maxVal;
	else if (val < minVal)
		val = minVal;
	initValue = val;
}

void Topology::readTxt(string fileName){
	//��ȡ�ڽӾ���
	ifstream file;
	file.open(fileName, ios::_Nocreate | ios::in);
	if (!file){
		cout << "��ȡ�ڽӾ���ʧ��\n" << endl;;
		return;
	}
	int nLine = 0;
	char strbuff[256];
	while (file.getline(strbuff, 256)){ // ��ȡ�ڵ���
		nLine++;
	}
	file.clear();
	file.seekg(0, ios::beg);
	mat.setOnes(nLine, nLine);
	for (int i = 0; i < nLine; i++){
		for (int j = 0; j < nLine; j++){
			file >> mat(i, j);
		}
	}
	file.close();

	//��ڵ������
	for (int i = 0; i < nLine; i++){
		degreeList.push_back(mat.row(i).sum());
	}
	cout << "��ȡ�ڽӾ���ɹ�\n" << endl;
}
