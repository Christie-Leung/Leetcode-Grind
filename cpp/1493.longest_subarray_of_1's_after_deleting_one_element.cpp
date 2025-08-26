/**
 * Link: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description
 * Tags: Array, Sliding Window
 * Difficulty: Medium
 * Date: 2025-08-24
 */

#include <vector>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int zeroCount = 0;
        int longestsf = 0;

        int start = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                zeroCount++;
            }

            while (zeroCount > 1) {
                if (nums[start] == 0) zeroCount--;
                start++;
            }

            longestsf = max(i - start, longestsf);
        }

        return longestsf;
    }
};
