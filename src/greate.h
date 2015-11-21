#ifndef __GREATE_H_
#define __GREATE_H_
#include "state.h"
using namespace std;

class State;
class Greate{
public:
	bool operator()(State *s1, State *s2);
};
#endif