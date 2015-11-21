#include "state_expansion.h"

map<string, State *> StateExpansion::states;
/********************************************/
vector<State *> StateExpansion::leafStates;
/********************************************/
int StateExpansion::findMaxNormal(State *state, int &stateCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	//vector<State *> *newStates = state->generateChildStatesND();
	int maxValue = std::numeric_limits<int>::min();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMinNormal(newStates->at(i), stateCount);
		if (value > maxValue){
			maxValue = value;
			bestIndex = i;
		}
	}
	state->setAlphaBetaValue(maxValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	return maxValue;
}

int StateExpansion::findMinNormal(State *state, int &stateCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	//vector<State *> *newStates = state->generateChildStatesND();
	int minValue = std::numeric_limits<int>::max();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMaxNormal(newStates->at(i), stateCount);
		if (value < minValue){
			minValue = value;
			bestIndex = i;
		}
	}
	state->setAlphaBetaValue(minValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return minValue;
}

int StateExpansion::normalSearch(string &stateString, int &stateCount){
	states.clear();
	State *rootState = new State(stateString);
	states[stateString] = rootState;
	//stateCount = 1;
	int value;
	if (rootState->countDash() % 2 == 0){
		rootState->setMin();
		value = findMinNormal(rootState, stateCount);
	}
	else{
		rootState->setMax();
		value = findMaxNormal(rootState, stateCount);
	}
	return value;
}

int StateExpansion::findMaxAlphaBeta(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	//vector<State *> *newStates = state->generateChildStatesND();
	int maxValue = std::numeric_limits<int>::min();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMinAlphaBeta(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (maxValue > alpha)
			alpha = maxValue;
		if (value > maxValue){
			maxValue = value;
			bestIndex = i;
		}
		if (maxValue >= beta){
			state->setAlphaBetaValue(maxValue);
			state->setBestMove(newStates->at(i));
			//state->setAsTerminalState();
			betaCount++;
			//cout << state->toOutputString() << "  Beta cut" << endl;
			//cout << endl;
			return maxValue;
		}
		/*if (maxValue > alpha)
			alpha = maxValue;*/
	}
	state->setAlphaBetaValue(maxValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return maxValue;
}

int StateExpansion::findMinAlphaBeta(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	//vector<State *> *newStates = state->generateChildStatesND();
	int minValue = std::numeric_limits<int>::max();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMaxAlphaBeta(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (minValue < beta)
			beta = minValue;
		if (value < minValue){
			minValue = value;
			bestIndex = i;
		}
		if (minValue <= alpha){
			state->setAlphaBetaValue(minValue);
			state->setBestMove(newStates->at(i));
			//state->setAsTerminalState();
			alphaCount++;
			//cout << state->toOutputString() << "  Alpha cut" << endl;
			//cout << endl;
			return minValue;
		}
		/*if (minValue < beta)
			beta = minValue;*/
	}
	state->setAlphaBetaValue(minValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return minValue;
}

int StateExpansion::alphaBetaSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount){
	states.clear();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	State *rootState = new State(stateString);
	states[stateString] = rootState;
	//stateCount = 1;
	//alphaCount = 0;
	//betaCount = 0;
	int value;
	if (rootState->countDash() % 2 == 0){
		rootState->setMin();
		value = findMinAlphaBeta(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	else{
		rootState->setMax();
		value = findMaxAlphaBeta(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	return value;
}

int StateExpansion::findMaxHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	priority_queue<State, vector<State *>, Greate> newStatesQueue;
	for (int i = 0; i < newStates->size(); i++)
		newStatesQueue.push(newStates->at(i));
	int maxValue = std::numeric_limits<int>::min();
	int value;
	//int i = 0;
	State *tempState = NULL;
	State *bestMove = NULL;
	while (!newStatesQueue.empty()){
		tempState = newStatesQueue.top();
		value = findMinHeuristic(tempState, alpha, beta, stateCount, alphaCount, betaCount);
		if (maxValue > alpha)
			alpha = maxValue;
		if (value > maxValue){
			maxValue = value;
			bestMove = tempState;
		}
		if (maxValue >= beta){
			state->setBestMove(tempState);
			betaCount++;
			//cout << state->toOutputString() << "  Beta cut" << endl;
			//cout << endl;
			return maxValue;
		}
		/*if (maxValue > alpha)
			alpha = maxValue;*/
		newStatesQueue.pop();
	}
	state->setAlphaBetaValue(maxValue);
	state->setBestMove(bestMove);
	//state->setAsTerminalState();
	//stateCount++;
	return maxValue;
}

int StateExpansion::findMinHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStates(states, StateExpansion::leafStates);
	priority_queue<State, vector<State *>, Greate> newStatesQueue;
	for (int i = 0; i < newStates->size(); i++)
		newStatesQueue.push(newStates->at(i));
	int minValue = std::numeric_limits<int>::max();
	int value;
	State *tempState = NULL;
	State *bestMove = NULL;
	while (!newStatesQueue.empty()){
		tempState = newStatesQueue.top();
		value = findMaxHeuristic(tempState, alpha, beta, stateCount, alphaCount, betaCount);
		if (minValue < beta)
			beta = minValue;
		if (value < minValue){
			minValue = value;
			bestMove = tempState;
		}
		if (minValue <= alpha){
			state->setBestMove(tempState);
			alphaCount++;
			//cout << state->toOutputString() << "  Alpha cut" << endl;
			//cout << endl;
			return minValue;
		}
		/*if (minValue < beta)
			beta = minValue;*/
		newStatesQueue.pop();
	}
	state->setAlphaBetaValue(minValue);
	state->setBestMove(bestMove);
	//state->setAsTerminalState();
	//stateCount++;
	return minValue;
}

int StateExpansion::heuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount){
	states.clear();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	State *rootState = new State(stateString);
	states[stateString] = rootState;
	stateCount = 1;
	alphaCount = 0;
	betaCount = 0;
	int value;
	if (rootState->countDash() % 2 == 0){
		rootState->setMin();
		value = findMinHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	else{
		rootState->setMax();
		value = findMaxHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	return value;
}

int StateExpansion::findMaxKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStatesKiller(states);
	int maxValue = std::numeric_limits<int>::min();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMinKillerHeuristic(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (maxValue > alpha)
			alpha = maxValue;
		if (value > maxValue){
			maxValue = value;
			bestIndex = i;
		}
		if (maxValue >= beta){
			state->setBestMove(newStates->at(i));
			betaCount++;
			//cout << state->toOutputString() << "  Beta cut" << endl;
			//cout << endl;
			return maxValue;
		}
		/*if (maxValue > alpha)
			alpha = maxValue;*/
	}
	state->setAlphaBetaValue(maxValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return maxValue;
}

int StateExpansion::findMinKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStatesKiller(states);
	int minValue = std::numeric_limits<int>::max();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMaxKillerHeuristic(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (minValue < beta)
			beta = minValue;
		if (value < minValue){
			minValue = value;
			bestIndex = i;
		}
		if (minValue <= alpha){
			state->setBestMove(newStates->at(i));
			alphaCount++;
			//cout << state->toOutputString() << "  Alpha cut" << endl;
			//cout << endl;
			return minValue;
		}
		/*if (minValue < beta)
			beta = minValue;*/
	}
	state->setAlphaBetaValue(minValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return minValue;
}

int StateExpansion::killerHeuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount){
	states.clear();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	State *rootState = new State(stateString);
	states[stateString] = rootState;
	stateCount = 1;
	alphaCount = 0;
	betaCount = 0;
	int value;
	if (rootState->countDash() % 2 == 0){
		rootState->setMin();
		value = findMinKillerHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	else{
		rootState->setMax();
		value = findMaxKillerHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	return value;
}

int StateExpansion::findMaxRotationKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStatesCheckRotation(states);
	int maxValue = std::numeric_limits<int>::min();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMinRotationKillerHeuristic(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (maxValue > alpha)
			alpha = maxValue;
		if (value > maxValue){
			maxValue = value;
			bestIndex = i;
		}
		if (maxValue >= beta){
			state->setBestMove(newStates->at(i));
			betaCount++;
			//cout << state->toOutputString() << "  Beta cut" << endl;
			//cout << endl;
			return maxValue;
		}
		/*if (maxValue > alpha)
			alpha = maxValue;*/
		i++;
	}
	state->setAlphaBetaValue(maxValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return maxValue;
}

int StateExpansion::findMinRotationKillerHeuristic(State *state, int &alpha, int &beta, int &stateCount, int &alphaCount, int &betaCount){
	if (state->isTerminalState()){
		stateCount++;
		return state->getAlphaBetaValue();
	}
	vector<State *> *newStates = state->generateChildStatesCheckRotation(states);
	int minValue = std::numeric_limits<int>::max();
	int value;
	int bestIndex = 0;
	for (int i = 0; i < newStates->size(); i++){
		value = findMaxRotationKillerHeuristic(newStates->at(i), alpha, beta, stateCount, alphaCount, betaCount);
		if (minValue < beta)
			beta = minValue;
		if (value < minValue){
			minValue = value;
			bestIndex = i;
		}
		if (minValue <= alpha){
			state->setBestMove(newStates->at(i));
			alphaCount++;
			//cout << state->toOutputString() << "  Alpha cut" << endl;
			//cout << endl;
			return minValue;
		}
		/*if (minValue < beta)
			beta = minValue;*/
	}
	state->setAlphaBetaValue(minValue);
	state->setBestMove(newStates->at(bestIndex));
	//state->setAsTerminalState();
	//stateCount++;
	return minValue;
}

int StateExpansion::killerRotationHeuristicSearch(string &stateString, int &stateCount, int &alphaCount, int &betaCount){
	states.clear();
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();
	State *rootState = new State(stateString);
	states[stateString] = rootState;
	stateCount = 1;
	alphaCount = 0;
	betaCount = 0;
	int value;
	if (rootState->countDash() % 2 == 0){
		rootState->setMin();
		value = findMinRotationKillerHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	else{
		rootState->setMax();
		value = findMaxRotationKillerHeuristic(rootState, alpha, beta, stateCount, alphaCount, betaCount);
	}
	return value;
}
