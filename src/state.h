#ifndef __STATE_H_
#define __STATE_H_
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <queue>
#include "rule.h"
#include "greate.h"
using namespace std;

class Rule;
class State{
private:
	string stateString;
	bool minMax;                // True is max, false is min.
	int alphaBetaValue;
	bool alphaBetaValueEmptyFlag;
	bool terminalState;
	int evaluation;
	State *bestMove;
	void setXOEvaluation(char cell0, char cell1, char cell2, int &evaluation, int &xEvaluation, int &oEvaluation);
	string rotate90Degree(string &stateString);
	string rotate180Degree(string &stateString);
	string rotate270Degree(string &stateString);
	void swapForOponentKillerMove(vector<State *> *states);
	void swapForWinKillerMove(vector<State *> *states);
public:
	State();
	State(string stateString);
	int countDash();
	void resetStateAlphaBetaValue();
	void setStateString(string stateString);
	string getStateString();
	void setMin();
	void setMax();
	bool isMin();
	bool isMax();
	void setAlphaBetaValue(int value);
	int getAlphaBetaValue();
	void setAlphaBetaValueFlag();
	bool isAlphaBetaValueEmpty();
	void setAsTerminalState();
	bool isTerminalState();
	int calculateEvaluation();
	int getEvaluation();
	void setBestMove(State *bestMove);
	State *getBestMove();
	string toOutputString();
	bool isSameState(State *otherState);
	bool isSameState(string otherStateString);
	State *hasSameState(map<string, State *> &states, string stateString);
	State *hasSameStateRotation(map<string, State *> &states, string stateString);
	vector<State *> *generateChildStates(map<string, State *> &states, vector<State *> &leafStates);
	vector<State *> *generateChildStatesND();
	vector<State *> *generateChildStatesKiller(map<string, State *> &states);
	vector<State *> *generateChildStatesCheckRotation(map<string, State *> &states);
};
#endif
