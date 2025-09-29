/**
 * Link: https://leetcode.com/problems/minimum-score-triangulation-of-polygon/description
 * Tags: Array, Dynamic Programming
 * Difficulty: Medium
 * Date: 2025-09-29
 */

#include <vector>
using namespace std;

class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        vector<vector<int>> dp(values.size(), vector<int>(values.size(), 0));
        for (int i = values.size() - 1; i >= 0; i--) {
            for (int j = i + 1; j < values.size(); j++) {
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = min(dp[i][j] == 0 ? INT_MAX : dp[i][j],
                        dp[i][k] + values[i] * values[k] * values[j] + dp[k][j]);
                }
            }
        }
        return dp[0][values.size() - 1];
    }
};