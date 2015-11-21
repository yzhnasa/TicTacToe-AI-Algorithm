#ifndef __STATE_EXPANSION_H_
#define __STATE_EXPANSION_H_
#include <iostream>
#include <vector>
//#include <map>
#include <string>
#include "state.h"
using namespace std;

class StateExpansion{
private:
	static map<string, State *> states;
	/****************************************/
	static vector<State *> leafStates;
	/****************************************/
	static int findMaxNormal(State *state, int &stateCount);
	static int findMinNormal(State *state, int &stateCount);
	static int findMaxAlphaBeta(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMinAlphaBeta(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMaxHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMinHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMaxKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMinKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMaxRotationKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
	static int findMinRotationKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount);
public:
	static int normalSearch(string &stateString, int &stateCount);
	static int alphaBetaSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount);
	static int heuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount);
	static int killerHeuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount);
	static int killerRotationHeuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount);
};
#endif
