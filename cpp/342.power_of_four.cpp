/**
 * Link: https://leetcode.com/problems/power-of-four/description
 * Date: 2025-08-24
 */

#include <cmath>

class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n == 0) return false;
        double logbase = log(n) / log(4);
        return floor(logbase) == logbase;
    }
};