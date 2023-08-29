// Ruin and Recreate Mutational Heuristic

#ifndef RAR_HPP
#define RAR_HPP

#include <string>
#include "../problem/Problem.hpp"
#include "Greedy.hpp"

class RAR{
    public:
        RAR(int givenSeed, int IOM, Greedy *givenGreedy) {
            srand(givenSeed);
            intensityOfMutation = IOM;
            greedy = givenGreedy;
        };
        ~RAR() {};

        void useHeuristic(Problem *givenProblem) {
            for (int i = 0; i < intensityOfMutation; i++) {
                if (givenProblem->getObjectiveValue() == 1) {
                    break;
                }
                while (true) {
                    int j = rand() % givenProblem->getNumOfSubsets()-1;
                    if (givenProblem->getSolutionBit(j) == 1) {
                        givenProblem->bitFlip(j);
                        break;
                    }
                }
		    }
		    greedy->useHeuristic(givenProblem);
            
        };

        std::string getName() {
            return "RAR";
        };

    private:
        int intensityOfMutation;
        Greedy *greedy;
};

#endif