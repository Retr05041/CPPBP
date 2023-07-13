// Problem class

#include "Problem.hpp"
#include <sstream>

/**
 * Constructor
 * @param file
*/
Problem::Problem(std::string file) {
    m_fileName = file;

    // Read file
    readFile();
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
        while (std::getline(ss, token, ' ')) {
            if (token != "") {
                m_firstLine.insert(std::stoi(token));
            }
        }


        // Read subsets
        int numOfElementsInCurrentSubset = 0;
        std::vector<int> currentSubset;
        int subsetIndex = 0;

        // While the file has lines -- CURRENTLY BROKEN (DOESN'T READ PAST FIRST LINE OF FIRST SUBSET)
        while (std::getline(file, line)) {
            // Get the number of elements in the current subset
            if (line.length() == 3) {
                numOfElementsInCurrentSubset = std::stoi(line);
                std::cout << "Number of elements in current subset: " << numOfElementsInCurrentSubset << "\n";
                
                // Add the current subset to the subsets vector
                while (subsetIndex != numOfElementsInCurrentSubset-1) {
                    std::getline(file, line);
                    std::stringstream ss(line);
                    std::string token;
                    for (int i = 0; i < line.length(); i++) {
                        std::getline(ss, token, ' '); // BROKEN AROUND HERE
                        if (token != " ") {
                            std::cout << "Token: " << token << "\n";
                            currentSubset.push_back(std::stoi(token));
                            subsetIndex++;
                        }
                    }
                }

            }

            // Add current subset to the subsets vector & reset
            m_subsets.push_back(currentSubset);
            subsetIndex = 0;
            numOfElementsInCurrentSubset = 0;
        }


        // Close file
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}