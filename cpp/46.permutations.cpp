/**
 * Link: https://leetcode.com/problems/permutations
 * Tags: Array, Backtracking
 * Difficulty: Medium
 * Date: 2025-10-19
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res = {};
        permuteRecurr(nums, 0, res);
        return res;
    }

    void permuteRecurr(vector<int>& nums, int first, vector<vector<int>>& res) {
        int n = nums.size();
        if (first == n) {
            res.push_back(nums);
            return;
        }

        for (int i = first; i < n; i++) {
            swap(nums[first], nums[i]);
            permuteRecurr(nums, first + 1, res);
            swap(nums[first], nums[i]);
        }
    }
};


