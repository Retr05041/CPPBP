// Abstract Heuristic class for making metaheuristics

#ifndef HEURISTIC_H
#define HEURISTIC_H

class Heuristic {
    private:
        int m_seed;
    public:
        Heuristic(int givenSeed) : m_seed(givenSeed) {};
        ~Heuristic() {};

    protected:
        virtual void useHeuristic();
        virtual void getName();
    
};

#endif // HEURISTIC_H