/**
 * Link: https://leetcode.com/problems/combination-sum-iv/
 * Tags: Array, Dynamic Programming
 * Difficulty: Medium
 * Date: 2025-10-18
 */

using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> dp(target+1);

        dp[0] = 1;

        for (int i = 1; i <= target; i++) {
            long long sum = 0;
            for (int& n : nums) {
                if (i - n >= 0) sum += dp[i-n];
            }
            dp[i] = (int) sum;
        }

        return dp[target];
        
    }
};