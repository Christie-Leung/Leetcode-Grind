/**
 * Link: https://leetcode.com/problems/valid-triangle-number/description
 * Tags: Array, Two Pointers, Binary Search, Greedy, Sorting
 * Difficulty: Medium
 * Date: 2025-09-26
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;

        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                int sum = nums[i] + nums[j];

                for (int k = j + 1; k < nums.size(); k++) {
                    if (sum <= nums[k]) break;
                    if (sum > nums[k]) {
                        count++;
                    }
                }
            }
        }

        return count;
        
    }
};