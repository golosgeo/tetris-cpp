#ifndef THE_GAME_PCC_UTILS_H
#define THE_GAME_PCC_UTILS_H

#include <random>

// Is a simple counter class that can be used to count down from a given value.
class DecreasingCycleCounter {
private:
    const int initial_value;
    int value;

public:
    DecreasingCycleCounter(int initial_value = 5);

    bool is_zero() const;

    DecreasingCycleCounter operator--(int);
};

// Is a simple random number generator class that can be used to generate random numbers in a given range.
class RandomGenerator {
private:
    std::random_device device;
    std::minstd_rand generator;
    std::uniform_int_distribution<int> distribution;

public:
    RandomGenerator(int, int);

    int operator()();
};


#endif //THE_GAME_PCC_UTILS_H