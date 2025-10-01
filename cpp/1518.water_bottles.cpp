/**
 * Link: https://leetcode.com/problems/water-bottles/description
 * Tags: Math
 * Difficulty: Easy
 * Date: 2025-10-01
 */

#include <cmath>
using namespace std;

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {

        int sum = numBottles;
        while (numBottles >= numExchange) {
            int exchanged = floor(numBottles / numExchange);
            sum += exchanged;
            numBottles = (numBottles % numExchange) + exchanged;
        }
        return sum;
        
    }
};