/**
 * Link: https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/
 * Tags: Array, Hash Table, Math, Greedy
 * Difficulty: Medium
 * Date: 2025-10-16
 */

#include <vector>
using namespace std;

class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> freq(value);
        for (int& n : nums) {
            n = n % value;
            if (n < 0) n += value;
            freq[n]++;
        }

        if (freq[0] == 0) return 0;

        int mex = 0;

        while(freq[mex % value]--) mex++;
        return mex;
        
    }
};