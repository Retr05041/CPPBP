// Davis Bit Hill Climbing heuristic

#ifndef DAVISBITHC_HPP
#define DAVISBITHC_HPP

#include <vector>
#include <string>
#include "../problem/Problem.hpp"

class DavisBitHC{
    public:
        DavisBitHC(int givenSeed) {
            srand(givenSeed);
        };
        ~DavisBitHC() {};

        void useHeuristic(Problem *givenProblem) {
            int bestOV = givenProblem->getObjectiveValue();
            int tempOV = -1;
            std::vector<int> perm = createRandomPermutaion(givenProblem);
            
            for (int i = 0; i < perm.size(); i++) {
                givenProblem->bitFlip(perm[i]);
                tempOV = givenProblem->getObjectiveValue();
                
                if (tempOV < bestOV && givenProblem->acceptanceCheck()) {
                    bestOV = tempOV;
                } else {
                    givenProblem->bitFlip(perm[i]);
                }
            }
            
        };

        std::string getName() {
            return "DavisBitHC";
        };

    private:

        /**
         * Creates random permutation
         * @param givenProblem
         * @return perm
         */
        std::vector<int> createRandomPermutaion(Problem *givenProblem) {
            std::vector<int> tempArray;
            for (int i = 1; i < givenProblem->getNumOfSubsets(); i++) {
                tempArray.at(i) = i;
            }
            givenProblem->shuffleGivenArray(tempArray);
            
            return tempArray;
        }
    
};

#endif