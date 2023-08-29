// Greedy heuristic

#ifndef GREEDY_HPP
#define GREEDY_HPP

#include <string>
#include "../problem/Problem.hpp"

class Greedy{
    public:
        Greedy(int givenSeed) {
            srand(givenSeed);
        };
        ~Greedy() {};

        void useHeuristic(Problem *givenProblem) {
            while (!givenProblem->acceptanceCheck()) {
                givenProblem->bitFlip(givenProblem->getBestSubsetIndex());
            }
        };

        std::string getName() {
            return "Greedy";
        };
    
};

#endif