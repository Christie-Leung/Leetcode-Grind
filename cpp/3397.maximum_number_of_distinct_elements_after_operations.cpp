/**
 * Link: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/
 * Tags: Array, Hash Table, Greedy, Sorting
 * Difficulty: Medium
 * Date: 2025-10-18
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int count = 0;
        int prev = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            int low = max(nums[i] - k, prev + 1);
            if (low <= nums[i] + k) {
                prev = low;
                count++;
            }
        }

        return count;
        
    }
};

