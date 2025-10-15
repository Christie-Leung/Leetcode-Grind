/**
 * Link: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/
 * Tags: Array, Binary Search
 * Difficulty: Medium
 * Date: 2025-10-15
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int curr = 1;
        int last = -1;
        int maxArr = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i-1] < nums[i]) {
                curr++;
            } else {
                maxArr = max(maxArr, curr / 2);
                maxArr = max(maxArr, min(last, curr));
                last = curr;
                curr = 1;
            }
        }
        maxArr = max(maxArr, curr / 2);
        maxArr = max(maxArr, min(last, curr));

        return maxArr;
    }
};