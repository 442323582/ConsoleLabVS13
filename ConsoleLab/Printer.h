#pragma once

#include"OptimalControlLib.h"

#include<iostream>
using namespace std;

class Printer
{
public:
	Printer();
	~Printer();
	
	void printVar(Mediator * mediator);
	void printDataMat(DataMat * mat);
	void printTopology(Topology * topo);
	void printPerform(Performance * perf);
};

