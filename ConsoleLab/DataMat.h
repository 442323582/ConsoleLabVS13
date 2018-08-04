
#pragma once


#include <Eigen\Dense>
#include<string>
#include<vector>

using namespace std;
using namespace Eigen;

class VarargSet{
public:
	VarargSet(){}
	~VarargSet(){}
	void addVar(string name){ nameList.push_back(name); valueList.push_back(0); }
	void setVarValue(int index, double val);
	string getVarName(int index);
	double findVal(string name);
	int getnVar(){ return nameList.size(); }
	void getVar(int index, string &name, double& val){
		name = nameList[index];
		val = valueList[index];
	}
	//void readFlagTxt(string fileName);
private:
	vector<double> valueList;
	vector<string> nameList;
	VectorXi flag;
};

class DataMat
{
public:
	DataMat(){}
	~DataMat(){}

	void setRows(int val){ rows = val; }
	void setCols(int val){ cols = val; }
	void createMat(){
		mat.setOnes(rows, cols);
		mat = mat * initValue;
	}
	double getInitValue(){ return initValue; }
	string getName(){ return name; }
	virtual void setValue(int row, int col, double val) = 0;
	double getValue(int row, int col){ return mat(row, col); }
	int getRows(){ return rows; }
	int getCols(){ return cols; }
	void setMaxVal(double val){ maxVal = val; }
	double getMaxVal(){ return maxVal; }
	void setMinVal(double val){ minVal = val; }
	double getMinVal(){ return minVal; }
	void setInitValue(double val);
protected:
	MatrixXd mat;
	string name;
	double maxVal;
	double minVal;
	int rows;
	int cols;
	double initValue;
};

class Topology{
public:
	Topology(){}
	~Topology(){}
	void readTxt(string fileName);
	int getValue(int row, int col){ return mat(row, col); }
	int getDegree(int index){ return degreeList[index]; }
	int getnNode(){ return mat.rows(); }
private:
	MatrixXi mat;
	vector<int> degreeList;
};

class AdjointMat :
	public DataMat
{
public:
	AdjointMat(string name){ this->name = name; }
	~AdjointMat(){}
	void setValue(int row, int col, double val){
		mat(row, col) = val;
	}
};

class NodeState :
	public DataMat
{
public:
	NodeState(string name);
	~NodeState(){}
	void setValue(int row, int col, double val){
		if (val > maxVal)
			val = maxVal;
		else if (val < minVal)
			val = minVal;
		mat(row, col) = val;
	}
};

class ControlMat :
	public DataMat
{
public:
	ControlMat(int cols);
	~ControlMat(){}
	void setValue(int row, int col, double val){
		if (val > maxVal)
			val = maxVal;
		else if (val < minVal)
			val = minVal;
		mat(row, col) = val;
	}
};