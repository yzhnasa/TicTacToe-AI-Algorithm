#include "state_expansion.h"

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "Please provide input file and output filename." << endl;
		return 1;
	}

	int result = 0;
	int stateCount = 0;
	int alphaCount = 0;
	int betaCount = 0;
	string inputStateString(argv[1]);
	result = StateExpansion::normalSearch(inputStateString, stateCount);
	cout << "Running without alpha-beta pruning" << endl;
	cout << "Game Result: " << result << endl;
	cout << "Moves considered without alpha-beta pruning: " << stateCount << endl;
	cout << "-----------------------------------------" << endl;

	result = 0;
	stateCount = 0;
	alphaCount = 0;
	betaCount = 0;
	result = StateExpansion::alphaBetaSearch(inputStateString, stateCount, alphaCount, betaCount);
	cout << "Running with alpha-beta pruning" << endl;
	cout << "Game Result: " << result << endl;
	cout << "Moves considered with alpha-beta pruning: " << stateCount << endl;
	cout << "Alpha cuts: " << alphaCount << endl;
	cout << "Beta cuts: " << betaCount << endl;
	cout << "-----------------------------------------" << endl;

	result = 0;
	stateCount = 0;
	alphaCount = 0;
	betaCount = 0;
	result = StateExpansion::heuristicSearch(inputStateString, stateCount, alphaCount, betaCount);
	cout << "Running with heuristic alpha-beta pruning" << endl;
	cout << "Game Result: " << result << endl;
	cout << "Moves considered with alpha-beta pruning: " << stateCount << endl;
	cout << "Alpha cuts: " << alphaCount << endl;
	cout << "Beta cuts: " << betaCount << endl;
	cout << "-----------------------------------------" << endl;

	result = 0;
	stateCount = 0;
	alphaCount = 0;
	betaCount = 0;
	result = StateExpansion::killerHeuristicSearch(inputStateString, stateCount, alphaCount, betaCount);
	cout << "Running with the killer heuristic" << endl;
	cout << "Game Result: " << result << endl;
	cout << "Moves considered with alpha-beta pruning: " << stateCount << endl;
	cout << "Alpha cuts: " << alphaCount << endl;
	cout << "Beta cuts: " << betaCount << endl;
	cout << "-----------------------------------------" << endl;

	result = 0;
	stateCount = 0;
	alphaCount = 0;
	betaCount = 0;
	result = StateExpansion::killerRotationHeuristicSearch(inputStateString, stateCount, alphaCount, betaCount);
	cout << "Running with the killer heuristic and using rotation invariance" << endl;
	cout << "Game Result: " << result << endl;
	cout << "Moves considered with alpha-beta pruning: " << stateCount << endl;
	cout << "Alpha cuts: " << alphaCount << endl;
	cout << "Beta cuts: " << betaCount << endl;
	cout << "-----------------------------------------" << endl;

	return 0;
}
