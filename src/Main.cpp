// Runner

#include <iostream>
#include "problem/Problem.hpp"
#include "heuristics/Greedy.hpp"
#include "heuristics/DavisBitHC.hpp"
#include "heuristics/RAR.hpp"

int main(int argc, char const *argv[]) {
    int iom = 5;


    std::cout << "Setting up problem... ";
    Problem *problem = new Problem("../TestInstances/d1_50_500.txt", 80); // 30 25
    std::cout << "Done!\n";

    std::cout << "Setting up heuristics... ";
    Greedy *greedy = new Greedy(1);
    DavisBitHC *davisBitHC = new DavisBitHC(1);
    RAR *rar = new RAR(1, iom, greedy);
    std::cout << "Done!\n";


    std::cout << "Running trails... \n";
    for (int i = 1; i < 5; i++) {
        std::cout << "Trial #" << i << ":\n";
        davisBitHC->useHeuristic(problem);
        rar->useHeuristic(problem);
        problem->printSolution();
        problem->printObjectiveValue();
    }
    std::cout << "Done!\n";

    // Cleanup
    delete problem;
    delete greedy;
    delete davisBitHC;
    delete rar;

    return 0;
}
