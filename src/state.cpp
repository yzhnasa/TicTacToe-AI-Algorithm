#include "state.h"

State::State(){
	this->minMax = false;
	this->stateString = "";
	this->alphaBetaValue = std::numeric_limits<int>::max();
	this->alphaBetaValueEmptyFlag = true;
	this->terminalState = false;
}

State::State(string stateString){
	this->minMax = false;
	this->stateString = stateString;
	this->alphaBetaValue = std::numeric_limits<int>::max();
	this->alphaBetaValueEmptyFlag = true;
	this->terminalState = false;
}

void State::setXOEvaluation(char cell0, char cell1, char cell2, int &evaluation, int &xEvaluation, int &oEvaluation){
	int count = 0;
	if (cell0 == cell1 && cell0 == cell2 && cell1 == cell2)
		count = 1;
	if ((cell0 == cell1 && cell0 != cell2 && cell1 != cell2)
		|| (cell0 != cell1 && cell0 != cell2 && cell1 == cell2)
		|| (cell0 != cell1 && cell0 == cell2 && cell1 != cell2))
		count = 2;
	if (cell0 != cell1 && cell0 != cell2 && cell1 != cell2)
		count = 3;
	if (count == 1){
		if (cell0 == 'X')
			evaluation = std::numeric_limits<int>::max();
		else if (cell0 == 'O')
			evaluation = std::numeric_limits<int>::min();
		else{
			xEvaluation++;
			oEvaluation++;
		}
	}
	if (count == 2){
		if (cell0 == '_' || cell1 == '_' || cell2 == '_'){
			if (cell0 == 'X' || cell1 == 'X' || cell2 == 'X')
				xEvaluation++;
			if (cell0 == 'O' || cell1 == 'O' || cell2 == 'O')
				oEvaluation++;
		}
	}
}

void State::resetStateAlphaBetaValue(){
	this->alphaBetaValue = std::numeric_limits<int>::max();
	this->alphaBetaValueEmptyFlag = true;
}

int State::countDash(){
	int count = 0;
	for (unsigned int i = 0; i < stateString.size(); i++){
		if (stateString.at(i) == '_')
			count++;
	}
	return count;
}

void State::setStateString(string stateString){
	this->stateString = stateString;
}

string State::getStateString(){
	return this->stateString;
}

void State::setMin(){
	this->minMax = false;
}

void State::setMax(){
	this->minMax = true;
}

bool State::isMin(){
	if (!this->minMax)
		return true;
	return false;
}

bool State::isMax(){
	if (this->minMax)
		return true;
	return false;
}

void State::setAlphaBetaValue(int value){
	this->alphaBetaValue = value;
}

int State::getAlphaBetaValue(){
	return alphaBetaValue;
}

void State::setAlphaBetaValueFlag(){
	alphaBetaValueEmptyFlag = false;
}

bool State::isAlphaBetaValueEmpty(){
	return this->alphaBetaValueEmptyFlag;
}

void State::setAsTerminalState(){
	this->terminalState = true;
}

bool State::isTerminalState(){
	return this->terminalState;
}

int State::calculateEvaluation(){
	int evaluation = 0;
	int xEvaluation = 0;
	int oEvaluation = 0;
	setXOEvaluation(stateString.at(0), stateString.at(1), stateString.at(2), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(3), stateString.at(4), stateString.at(5), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(6), stateString.at(7), stateString.at(8), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(0), stateString.at(3), stateString.at(6), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(1), stateString.at(4), stateString.at(7), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(2), stateString.at(5), stateString.at(8), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(0), stateString.at(4), stateString.at(8), evaluation, xEvaluation, oEvaluation);
	setXOEvaluation(stateString.at(2), stateString.at(4), stateString.at(6), evaluation, xEvaluation, oEvaluation);
	if (evaluation == std::numeric_limits<int>::max()
		|| evaluation == std::numeric_limits<int>::min())
		return evaluation;
	else
		return xEvaluation - oEvaluation;
}

int State::getEvaluation(){
	return evaluation;
}

void State::setBestMove(State *bestMove){
	this->bestMove = bestMove;
}

State *State::getBestMove(){
	return this->bestMove;
}

string State::toOutputString(){
	string tempString = stateString;
	tempString.insert(tempString.begin() + 3, '\n');
	tempString.insert(tempString.begin() + 7, '\n');
	return tempString;
}

bool State::isSameState(State *otherState){
	if (this->stateString.compare(otherState->getStateString()) == 0)
		return true;
	return false;
}

bool State::isSameState(string otherStateString){
	if (this->stateString.compare(otherStateString) == 0)
		return true;
	return false;
}

State *State::hasSameState(map<string, State *> &states, string stateString){
	if (states.find(stateString) != states.end())
		return states[stateString];
	return NULL;
}

string State::rotate90Degree(string &stateString){
	string tempString = "";
	tempString = tempString + stateString.at(6);
	tempString = tempString + stateString.at(3);
	tempString = tempString + stateString.at(0);
	tempString = tempString + stateString.at(7);
	tempString = tempString + stateString.at(4);
	tempString = tempString + stateString.at(1);
	tempString = tempString + stateString.at(8);
	tempString = tempString + stateString.at(5);
	tempString = tempString + stateString.at(2);
	return tempString;
}

string State::rotate180Degree(string &stateString){
	string tempString = "";
	tempString = tempString + stateString.at(8);
	tempString = tempString + stateString.at(7);
	tempString = tempString + stateString.at(6);
	tempString = tempString + stateString.at(5);
	tempString = tempString + stateString.at(4);
	tempString = tempString + stateString.at(3);
	tempString = tempString + stateString.at(2);
	tempString = tempString + stateString.at(1);
	tempString = tempString + stateString.at(0);
	return tempString;
}

string State::rotate270Degree(string &stateString){
	string tempString = "";
	tempString = tempString + stateString.at(2);
	tempString = tempString + stateString.at(5);
	tempString = tempString + stateString.at(8);
	tempString = tempString + stateString.at(1);
	tempString = tempString + stateString.at(4);
	tempString = tempString + stateString.at(7);
	tempString = tempString + stateString.at(0);
	tempString = tempString + stateString.at(3);
	tempString = tempString + stateString.at(6);
	return tempString;
}

State *State::hasSameStateRotation(map<string, State *> &states, string stateString){
	if (states.find(stateString) != states.end())
		return states[stateString];
	if (states.find(rotate90Degree(stateString)) != states.end())
		return states[rotate90Degree(stateString)];
	if (states.find(rotate180Degree(stateString)) != states.end())
		return states[rotate90Degree(stateString)];
	if (states.find(rotate270Degree(stateString)) != states.end())
		return states[rotate90Degree(stateString)];
	return NULL;
}

vector<State *> *State::generateChildStates(map<string, State *> &states, vector<State *> &leafStates){
	unsigned int dashCount = countDash();
	State *tempState = NULL;
	State *sameState = NULL;
	vector<State *> *newStates = new vector<State *>();
	unsigned int k = 0;
	string tempChildStateString = stateString;
	for (unsigned int i = k; i < dashCount; i++){
		for (; k < stateString.size(); k++){
			if (this->stateString.at(k) == '_'){
				if (this->isMax()){
					tempChildStateString.at(k) = 'X';
					sameState = hasSameState(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMin();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
						/********************************************/
						Rule::setLeafWinCondition(tempState);
						if (tempState->isTerminalState())
							leafStates.push_back(tempState);
						/********************************************/
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
				}
				else{
					tempChildStateString.at(k) = 'O';
					sameState = hasSameState(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMax();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
						/********************************************/
						Rule::setLeafWinCondition(tempState);
						if (tempState->isTerminalState())
							leafStates.push_back(tempState);
						/********************************************/
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
				}
			    newStates->push_back(tempState);
				tempChildStateString = stateString;
				k++;
				break;
			}
		}
	}
	return newStates;
}

vector<State *> *State::generateChildStatesND(){
	unsigned int dashCount = countDash();
	State *tempState = NULL;
	State *sameState = NULL;
	vector<State *> *newStates = new vector<State *>();
	unsigned int k = 0;
	string tempChildStateString = stateString;
	for (unsigned int i = k; i < dashCount; i++){
		for (; k < stateString.size(); k++){
			if (this->stateString.at(k) == '_'){
				if (this->isMax()){
					tempChildStateString.at(k) = 'X';
					tempState = new State(tempChildStateString);
					tempState->setMin();
					tempState->calculateEvaluation();
				}
				else{
					tempChildStateString.at(k) = 'O';
					tempState = new State(tempChildStateString);
					tempState->setMax();
					tempState->calculateEvaluation();
				}
				//tempState->setParentState(this);
				/********************************************/
				/*Rule::setLeafWinCondition(tempState);
				if (tempState->isTerminalState())
				leafStates.push_back(tempState);*/
				/********************************************/
				//this->childState.push_back(tempState);
				Rule::setLeafWinCondition(tempState);
				newStates->push_back(tempState);
				tempChildStateString = stateString;
				k++;
				break;
			}
		}
	}
	//evaluation = calculateEvaluation();
	return newStates;
}

/*bool State::preWinState(State *state, char oponent){

}*/

void State::swapForOponentKillerMove(vector<State *> *states){
	State *tempState = NULL;
	char oponent;
	if (this->isMax())
		oponent = 'O';
	else
		oponent = 'X';
	for (int i = 0; i < states->size(); i++){
		if (Rule::isPreWinState(states->at(i), oponent)){
			tempState = states->at(i);
			states->erase(states->begin() + i);
			states->insert(states->begin(), tempState);
			i++;
		}
	}
}

void State::swapForWinKillerMove(vector<State *> *states){
	State *tempState = NULL;
	for (int i = 0; i < states->size(); i++){
		if (states->at(i)->isTerminalState()){
			tempState = states->at(i);
			states->erase(states->begin()+i);
			states->insert(states->begin(), tempState);
			i++;
		}
	}
}

vector<State *> *State::generateChildStatesKiller(map<string, State *> &states){
	unsigned int dashCount = countDash();
	char oponent;
	State *tempState = NULL;
	State *sameState = NULL;
	vector<State *> *newStates = new vector<State *>();
	unsigned int k = 0;
	string tempChildStateString = stateString;
	for (unsigned int i = k; i < dashCount; i++){
		for (; k < stateString.size(); k++){
			if (this->stateString.at(k) == '_'){
				if (this->isMax()){
					tempChildStateString.at(k) = 'X';
					sameState = hasSameState(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMin();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
					oponent = 'O';
				}
				else{
					tempChildStateString.at(k) = 'O';
					sameState = hasSameState(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMax();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
					oponent = 'X';
				}
				Rule::setLeafWinCondition(tempState);
				if (Rule::isPreWinState(this, oponent) && !Rule::isPreWinState(tempState, oponent))
					newStates->insert(newStates->begin(), tempState);
				else
					newStates->push_back(tempState);
				tempChildStateString = stateString;
				k++;
				break;
			}
		}
	}
	swapForWinKillerMove(newStates);
	return newStates;
}

vector<State *> *State::generateChildStatesCheckRotation(map<string, State *> &states){
	unsigned int dashCount = countDash();
	char oponent;
	State *tempState = NULL;
	State *sameState = NULL;
	vector<State *> *newStates = new vector<State *>();
	unsigned int k = 0;
	string tempChildStateString = stateString;
	for (unsigned int i = k; i < dashCount; i++){
		for (; k < stateString.size(); k++){
			if (this->stateString.at(k) == '_'){
				if (this->isMax()){
					tempChildStateString.at(k) = 'X';
					sameState = hasSameStateRotation(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMin();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
					oponent = 'O';
				}
				else{
					tempChildStateString.at(k) = 'O';
					sameState = hasSameStateRotation(states, tempChildStateString);
					if (sameState == NULL){
						tempState = new State(tempChildStateString);
						tempState->setMax();
						tempState->calculateEvaluation();
						states[tempChildStateString] = tempState;
					}
					else{
						tempState = sameState;
						sameState = NULL;
					}
					oponent = 'X';
				}
				Rule::setLeafWinCondition(tempState);
			    if (Rule::isPreWinState(this, oponent) || !Rule::isPreWinState(tempState, oponent))
					newStates->insert(newStates->begin(), tempState);
				else
					newStates->push_back(tempState);
				tempChildStateString = stateString;
				k++;
				break;
			}
		}
	}
	swapForWinKillerMove(newStates);
	return newStates;
}
