/**
 * Link: https://leetcode.com/problems/perfect-squares/
 * Tags: Math, Dynamic Programming, Breadth-First Search
 * Difficulty: Medium
 * Date: 2025-10-17
 */

#include <vector>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i*i <= n; i++) {
            int sqr = i*i;
            for (int j = sqr; j < n+1; j++) {
                dp[j] = min(dp[j-sqr]+1, dp[j]);
            }
        }
        return dp[n];
        
    }

};


