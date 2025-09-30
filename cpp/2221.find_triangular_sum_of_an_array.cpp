/**
 * Link: https://leetcode.com/problems/find-triangular-sum-of-an-array/description
 * Tags: Array, Math, Simulation, Combinatorics
 * Difficulty: Medium
 * Date: 2025-09-30
 */

#include <vector>
using namespace std;

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        int n = nums.size() - 1;

        while (n != 0) {
            for (int i = 0; i < n; i++) {
                nums[i] = (nums[i] + nums[i+1]) % 10;
            }
            n--;
        }

        return nums[0];
        
    }
};