#ifndef __RULE_H_
#define __RULE_H_
//#include <string>
#include "state.h"
using namespace std;

class State;
class Rule{
private:
	static int countType(char cell0, char cell1, char cell2);
	static int countDash(char cell0, char cell1, char cell2);
	static bool hasOponent(char cell0, char cell1, char cell2, char oponent);
	static bool isTerminal(char cell0, char cell1, char cell2);
	static bool isNoDash(State *state);
	static bool xWin(State *state);
	static bool oWin(State *state);
public:
	static void setLeafWinCondition(State *state);
	static bool isPreWinState(State *state, char oponent);
	static void setWinConditionAndEvaluation(State *state);
	static bool isTerminalState(State *state);
};
#endif
