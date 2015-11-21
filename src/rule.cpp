#include "rule.h"

int Rule::countType(char cell0, char cell1, char cell2){
	//int count = 0;
	if (cell0 == cell1 && cell0 == cell2 && cell1 == cell2)
		return 1;
	if ((cell0 == cell1 && cell0 != cell2 && cell1 != cell2)
		|| (cell0 != cell1 && cell0 != cell2 && cell1 == cell2)
		|| (cell0 != cell1 && cell0 == cell2 && cell1 != cell2))
		return 2;
	if (cell0 != cell1 && cell0 != cell2 && cell1 != cell2)
		return 3;
	return 0;
}

bool Rule::isTerminal(char cell0, char cell1, char cell2){
	if (1 == countType(cell0, cell1, cell2)
		&& 0 == countDash(cell0, cell1, cell2))
		return true;
	return false;
}

bool Rule::isNoDash(State *state){
	for (unsigned int i = 0; i < state->getStateString().size(); i++){
		if (state->getStateString().at(i) == '_')
			return false;
	}
	return true;
}

bool Rule::isTerminalState(State *state){
	if (isTerminal(state->getStateString().at(0), state->getStateString().at(1), state->getStateString().at(2))
		|| isTerminal(state->getStateString().at(3), state->getStateString().at(4), state->getStateString().at(5))
		|| isTerminal(state->getStateString().at(6), state->getStateString().at(7), state->getStateString().at(8))
		|| isTerminal(state->getStateString().at(0), state->getStateString().at(3), state->getStateString().at(6))
		|| isTerminal(state->getStateString().at(1), state->getStateString().at(4), state->getStateString().at(7))
		|| isTerminal(state->getStateString().at(2), state->getStateString().at(5), state->getStateString().at(8))
		|| isTerminal(state->getStateString().at(0), state->getStateString().at(4), state->getStateString().at(8))
		|| isTerminal(state->getStateString().at(2), state->getStateString().at(4), state->getStateString().at(6))
		|| isNoDash(state)){
		return true;
	}
	return false;
}

int Rule::countDash(char cell0, char cell1, char cell2){
	int count = 0;
	if (cell0 == '_')
		count++;
	if (cell1 == '_')
		count++;
	if (cell2 == '_')
		count++;
	return count;
}

bool Rule::hasOponent(char cell0, char cell1, char cell2, char oponent){
	if (cell0 == oponent)
		return true;
	if (cell1 == oponent)
		return true;
	if (cell2 == oponent)
		return true;
	return false;
}

bool Rule::isPreWinState(State *state, char oponent){
	if (2 == countType(state->getStateString().at(0), state->getStateString().at(1), state->getStateString().at(2))
		&& 1 == countDash(state->getStateString().at(0), state->getStateString().at(1), state->getStateString().at(2))
			&& hasOponent(state->getStateString().at(0), state->getStateString().at(1), state->getStateString().at(2), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(3), state->getStateString().at(4), state->getStateString().at(5))
		&& 1 == countDash(state->getStateString().at(3), state->getStateString().at(4), state->getStateString().at(5))
			&& hasOponent(state->getStateString().at(3), state->getStateString().at(4), state->getStateString().at(5), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(6), state->getStateString().at(7), state->getStateString().at(8))
		&& 1 == countDash(state->getStateString().at(6), state->getStateString().at(7), state->getStateString().at(8))
			&& hasOponent(state->getStateString().at(6), state->getStateString().at(7), state->getStateString().at(8), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(0), state->getStateString().at(3), state->getStateString().at(6))
		&& 1 == countDash(state->getStateString().at(0), state->getStateString().at(3), state->getStateString().at(6))
			&& hasOponent(state->getStateString().at(0), state->getStateString().at(3), state->getStateString().at(6), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(1), state->getStateString().at(4), state->getStateString().at(7))
		&& 1 == countDash(state->getStateString().at(1), state->getStateString().at(4), state->getStateString().at(7))
			&& hasOponent(state->getStateString().at(1), state->getStateString().at(4), state->getStateString().at(7), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(2), state->getStateString().at(5), state->getStateString().at(8))
		&& 1 == countDash(state->getStateString().at(2), state->getStateString().at(5), state->getStateString().at(8))
			&& hasOponent(state->getStateString().at(2), state->getStateString().at(5), state->getStateString().at(8), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(0), state->getStateString().at(4), state->getStateString().at(8))
		&& 1 == countDash(state->getStateString().at(0), state->getStateString().at(4), state->getStateString().at(8))
			&& hasOponent(state->getStateString().at(0), state->getStateString().at(4), state->getStateString().at(8), oponent))
			return true;

	else if (2 == countType(state->getStateString().at(2), state->getStateString().at(4), state->getStateString().at(6))
		&& 1 == countDash(state->getStateString().at(2), state->getStateString().at(4), state->getStateString().at(6))
			&& hasOponent(state->getStateString().at(2), state->getStateString().at(4), state->getStateString().at(6), oponent))
			return true;

	else
		return false;
}

bool Rule::xWin(State *state){
	if ((state->getStateString().at(0) == 'X' && state->getStateString().at(1) == 'X' && state->getStateString().at(2) == 'X')
		|| (state->getStateString().at(3) == 'X' && state->getStateString().at(4) == 'X' && state->getStateString().at(5) == 'X')
		|| (state->getStateString().at(6) == 'X' && state->getStateString().at(7) == 'X' && state->getStateString().at(8) == 'X')
		|| (state->getStateString().at(0) == 'X' && state->getStateString().at(3) == 'X' && state->getStateString().at(6) == 'X')
		|| (state->getStateString().at(1) == 'X' && state->getStateString().at(4) == 'X' && state->getStateString().at(7) == 'X')
		|| (state->getStateString().at(2) == 'X' && state->getStateString().at(5) == 'X' && state->getStateString().at(8) == 'X')
		|| (state->getStateString().at(0) == 'X' && state->getStateString().at(4) == 'X' && state->getStateString().at(8) == 'X')
		|| (state->getStateString().at(2) == 'X' && state->getStateString().at(4) == 'X' && state->getStateString().at(6) == 'X'))
		return true;
	return false;
}

bool Rule::oWin(State *state){
	if ((state->getStateString().at(0) == 'O' && state->getStateString().at(1) == 'O' && state->getStateString().at(2) == 'O')
		|| (state->getStateString().at(3) == 'O' && state->getStateString().at(4) == 'O' && state->getStateString().at(5) == 'O')
		|| (state->getStateString().at(6) == 'O' && state->getStateString().at(7) == 'O' && state->getStateString().at(8) == 'O')
		|| (state->getStateString().at(0) == 'O' && state->getStateString().at(3) == 'O' && state->getStateString().at(6) == 'O')
		|| (state->getStateString().at(1) == 'O' && state->getStateString().at(4) == 'O' && state->getStateString().at(7) == 'O')
		|| (state->getStateString().at(2) == 'O' && state->getStateString().at(5) == 'O' && state->getStateString().at(8) == 'O')
		|| (state->getStateString().at(0) == 'O' && state->getStateString().at(4) == 'O' && state->getStateString().at(8) == 'O')
		|| (state->getStateString().at(2) == 'O' && state->getStateString().at(4) == 'O' && state->getStateString().at(6) == 'O'))
		return true;
	return false;
}

void Rule::setLeafWinCondition(State *state){
    if (isTerminalState(state)){
		if (xWin(state))
			state->setAlphaBetaValue(1);
		else if (oWin(state))
			state->setAlphaBetaValue(-1);
		else
			state->setAlphaBetaValue(0);
		state->setAsTerminalState();
		state->setAlphaBetaValueFlag();
	}
}

