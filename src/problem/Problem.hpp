// Problem class

#ifndef PROBLEM_HPP_
#define PROBLEM_HPP_

#include <memory>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>

class Problem {
    public:
        Problem(std::string file, int seed);
        ~Problem();

        // Read file
        void readFile();

        // Setup problem
        void setupProblem();

        // Getters
        int getNumOfSubsets();
        int getMaxNum();
        std::vector<int> getSubset(int index);
        std::vector<int> getSolution();
        int getSolutionBit(int index);
        int getObjectiveValue();
        int getBestSubsetIndex();

        // Methods
        void bitFlip(int index);
        void updateBin(int subsetIndex, bool remove);
        bool checkElemCoverage(int elem, int ignoredSubset);
        void printSolution();
        void printObjectiveValue();
        bool acceptanceCheck();
        void shuffleGivenArray(std::vector<int> &givenArray);


    private:
        // File name & File
        std::string m_fileName;
        // Solution vector & Objective function
        std::vector<int> m_solution;
        int m_objectiveValue = 0;
        // First line vector
        std::vector<int> m_firstLine;
        // Subset vector
        std::vector<std::vector<int>> m_subsets;
        // Bin
        std::vector<int> m_bin;
        // Seed
        int m_seed;
    
};

#endif // PROBLEM_HPP_

