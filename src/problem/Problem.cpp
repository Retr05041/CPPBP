// Problem class

#include "Problem.hpp"
#include <sstream>

/**
 * Constructor
 * @param file
*/
Problem::Problem(std::string file, int seed) {
    m_fileName = file;
    srand(seed);

    // Read file
    readFile();

    // Setup problem
    setupProblem();
}

/**
 * Destructor
*/
Problem::~Problem() {
    // Nothing to do
}

/**
 * Read file
*/
void Problem::readFile() {
    // Open file
    std::ifstream file(m_fileName);

    // Read file
    if (file.is_open()) {
        // Read first line
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (token != ",") {
                m_firstLine.push_back(std::stoi(token));
            }
        }


        // Read subsets variables
        int numOfElementsInCurrentSubset = 0;
        std::vector<int> currentSubset;
        int subsetIndex = 0;
        int subsetIterator = 0;

        // While the file has lines
        while (subsetIterator < m_firstLine.front()) {
            // Go to the next line to begin
            std::getline(file, line);

            numOfElementsInCurrentSubset = std::stoi(line);

            // Add the current subset to the subsets vector
            while (subsetIndex < numOfElementsInCurrentSubset) {
                std::getline(file, line);
                std::stringstream ss(line);
                std::string token;
                while (std::getline(ss, token, ',')) {
                    if (token != ",") {
                        currentSubset.push_back(std::stoi(token));
                        subsetIndex++;
                    }
                }
            }

            // Add current subset to the subsets vector & reset
            m_subsets.push_back(currentSubset);
            subsetIndex = 0;
            numOfElementsInCurrentSubset = 0;
            currentSubset.clear();
            subsetIterator++;
        }

        // Close file
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}

/**
 * Setup problem
*/
void Problem::setupProblem() {

    // Setup bin (index 0 will always remain 0)
    for (int i = 1; i <= m_firstLine.back()+1; i++) {
        m_bin.push_back(-1);
    }
    
    // Setup random base solution (after populating with 0's)
    for (int j = 0; j < m_firstLine.front(); j++) {
        m_solution.push_back(0);
    }

    while (!acceptanceCheck()) {
        for (int h = 0; h < m_solution.size(); h++) {
            // 50% chance to flip bit
            if ((rand() % 2) == 1) {
                bitFlip(h);
            }
        }
    }
}

/**
 * Get number of subsets
 * @return int
*/
int Problem::getNumOfSubsets() {
    return m_firstLine.front();
}

/**
 * Get max number
 * @return int
*/
int Problem::getMaxNum() {
    return m_firstLine.back();
}

/**
 * Get subset
 * @param index
 * @return std::vector<int>
*/
std::vector<int> Problem::getSubset(int index) {
    return m_subsets.at(index);
}

/**
 * Get solution
 * @return std::vector<int>
*/
std::vector<int> Problem::getSolution() {
    return m_solution;
}

/**
 * Get solution bit
 * @param index
 * @return int
*/
int Problem::getSolutionBit(int index) {
    return m_solution.at(index);
}

/**
 * Get objective value
 * @return int
*/
int Problem::getObjectiveValue() {
    return m_objectiveValue;
}

/**
 * Get best subset index
 * @return int
*/
int Problem::getBestSubsetIndex() {
    int numOfElemThisSubCanProvide = 0;
    int bestNumOfElem = 0;
    int bestSub = 0;
    
    // Loop through each subset
    for (int i = 0; i < m_firstLine.front(); i++) {
        // If the subset is already in the solution, skip it
        if (m_solution.at(i) == 1) {
            continue;
        }
        // Loop through each element in the subset
        for (int j = 0; j < m_subsets.at(i).size(); j++) {
            // If the element is not in the bin, increment the number of elements this subset can provide
            if (m_bin.at(m_subsets.at(i).at(j)) == -1) {
                numOfElemThisSubCanProvide++;
            }
        }
        
        // If the number of elements this subset can provide is greater than the current best, update the best
        if (numOfElemThisSubCanProvide >= bestNumOfElem) {
            bestSub = i;
            bestNumOfElem = numOfElemThisSubCanProvide;
        }
        // Reset
        numOfElemThisSubCanProvide = 0;
    }
    return bestSub;
}

/**
 * Bit flip
 * @param index
*/
void Problem::bitFlip(int index) {
    if (m_solution.at(index) == 0) {
        m_solution.at(index) = 1;
        updateBin(index, false);
    } else {
        m_solution.at(index) = 0;
        updateBin(index, true);
    }
}

/**
 * Update bin
 * @param subsetIndex
 * @param remove
*/
void Problem::updateBin(int subsetIndex, bool remove) {
    // If we are removing the subset from the solution
    if (remove) {
        // Loop through each element in the subset
        for (int i = 0; i < m_subsets.at(subsetIndex).size(); i++) {
            // If the element is not covered by any other subset, remove it from the bin
            if (!checkElemCoverage(m_subsets.at(subsetIndex).at(i), subsetIndex)) {
                m_bin.at(m_subsets.at(subsetIndex).at(i)) = -1;
            }
        }
        // Decrement the objective value
        m_objectiveValue--;
    } else {
        // Loop through each element in the subset
        for (int i = 0; i < m_subsets.at(subsetIndex).size(); i++) {
            // Add each element to their repsective index within in the bin
            m_bin.at(m_subsets.at(subsetIndex).at(i)) = subsetIndex;
        }
        // Increment the objective value
        m_objectiveValue++;
    }
}

/**
 * Check element coverage
 * @param elem
 * @param ignoredSubset
 * @return bool
*/
bool Problem::checkElemCoverage(int elem, int ignoredSubset) {
    // Loop through each subset
    for (int i = 0; i < m_firstLine.front(); i++) {
        // If the subset is not the ignored subset and it is in the solution
        if (m_solution.at(i) == 1 && i != ignoredSubset) {
            // Loop through each element in the subset
            for (int j = 0; j < m_subsets.at(i).size(); j++) {
                // If the element is in the subset, return true
                if (m_subsets.at(i).at(j) == elem) {
                    return true;
                }
            }
        }
    }

	return false;
}

/**
 * Print solution
*/
void Problem::printSolution() {
    std::cout << "[";
    for (int i = 0; i < m_solution.size(); i++) {
        std::cout << m_solution.at(i);
    }
    std::cout << "]";
    std::cout << "\n";
}

/**
 * Print objective value
*/
void Problem::printObjectiveValue() {
    std::cout << m_objectiveValue << "\n";
}

/**
 * Acceptance check
 * @return bool
*/
bool Problem::acceptanceCheck() {
    // If any element in bin is -1, return false
    for (int i = 1; i < m_bin.size(); i++) {
        if (m_bin.at(i) == -1) {
            return false;
        }
    }
    return true;
}

/**
 * Shuffle given array
 * @param givenArray
*/
void Problem::shuffleGivenArray(std::vector<int> &givenArray) {
    int randomIndex;
    int hold;
    
    for (int i = 0; i < givenArray.size(); i++) {
        randomIndex = rand() % givenArray.size();
        hold = givenArray.at(randomIndex);
        givenArray.at(randomIndex) = givenArray.at(i);
        givenArray.at(i) = hold;
    }
}