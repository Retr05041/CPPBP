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
        Problem(std::string file);
        ~Problem();

        // Read file
        void readFile();

        // Getters
        int getNumOfSubsets();
        int getMaxNum();
        std::vector<int> getSubset(int index);
        std::set<int> getSolution();
        int getSolutionBit(int index);
        int getObjectiveValue();
        int getBestSubsetIndex();

        // Methods
        void bitFlip(int index);
        void printSolution();
        void printObjectiveValue();
        void updateBin();
        bool checkElemCoverage(int elem, int ignoredSubset);
        bool acceptanceCheck();

    private:
        // File name & File
        std::string m_fileName;
        // Solution vector & Objective function
        std::vector<int> m_solution;
        int m_objectiveValue = 0;
        // First & Second line vector
        std::set<int> m_firstLine;
        // Subset vector
        std::vector<std::vector<int>> m_subsets;
        // Bin
        std::set<int> m_bin;
    
};

#endif // PROBLEM_HPP_

