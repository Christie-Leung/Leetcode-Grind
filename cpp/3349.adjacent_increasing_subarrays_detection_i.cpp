/**
 * Link: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/
 * Tags: Array
 * Difficulty: Easy
 * Date: 2025-10-14
 */

#include <vector>
using namespace std;

class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {

        if (k == 1) return true;

        int curr = 1;
        int last = -1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i-1] < nums[i]) {
                curr++;
            } else {
                if (last >= k && curr >= k) {
                    return true;
                } else {
                    if (curr / 2 >= k) return true;
                    last = curr;
                    curr = 1;
                }
            }
        }

        if (last >= k && curr >= k) return true;
        if (last / 2 >= k || curr / 2 >= k) return true;


        return false;
        
    }
};