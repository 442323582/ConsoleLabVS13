
#include"OptimalControlLib.h"

class MyDyna : public DynamicSystem
{
public:
	MyDyna(){}
	~MyDyna(){}
	double action(int row, int col){
		return 0.1;
	}

private:

};