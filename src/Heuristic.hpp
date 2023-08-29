// Abstract Heuristic class for making metaheuristics

#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <string>
#include "problem/Problem.hpp"

class Heuristic {
    public:
        Heuristic() {};
        ~Heuristic() {};

    protected:
        virtual void useHeuristic(Problem givenProblem);
        virtual std::string getName();
    
};

#endif // HEURISTIC_H