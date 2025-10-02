/**
 * Link: https://leetcode.com/problems/water-bottles-ii/description
 * Tags: Math, Simulation
 * Difficulty: Medium
 * Date: 2025-10-02
 */

using namespace std;

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        return numBottles + exchange(numBottles, numExchange);
        
    }

    int exchange(int numBottles, int numExchange) {
        if (numBottles < numExchange) return 0;
        return 1 + exchange(numBottles - numExchange + 1, numExchange + 1);
    }
};