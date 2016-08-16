#ifndef GENEVANN_I_OBJECTIVEFUNCTION_H
#define GENEVANN_I_OBJECTIVEFUNCTION_H

class i_objectiveFunction
{
public:
	virtual double evaluate(void* solution) = 0;
private:

};

#endif //GENEVANN_I_OBJECTIVEFUNCTION_H
