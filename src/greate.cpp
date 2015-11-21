#include "greate.h"

bool Greate::operator()(State *s1, State *s2){
	if (s1->getEvaluation() < s2->getEvaluation())
		return true;
	return false;
}