/**
 * Link: https://leetcode.com/problems/climbing-stairs/
 * Tags: Dynamic Programming, Math, Memoization
 * Difficulty: Easy
 * Date: 2025-10-17
 */

using namespace std;

class Solution {
public:
    int climbStairs(int n) {

        if (n == 1) return 1;

        int prev = 1;
        int prev2 = 1;
        
        for (int i = 1; i < n - 1; i++) {
            int temp = prev + prev2;
            prev2 = prev;
            prev = temp;
        }

        return prev + prev2;;
    }
};


