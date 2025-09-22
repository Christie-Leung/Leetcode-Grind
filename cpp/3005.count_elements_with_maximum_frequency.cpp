/**
 * Link: https://leetcode.com/problems/count-elements-with-maximum-frequency/description
 * Tags: Hash Table, Counting, Array
 * Difficulty: Easy
 * Date: 2025-09-22
 */

#include <vector>
using namespace std;

class Solution {
public:
    int elems[101];
    int maxFrequencyElements(vector<int>& nums) {
        int freq = 0;
        int mul = 1;
        for (int& n : nums) {
            int i = ++elems[n];
            if (i > freq) {
                freq = i;
                mul = 1;
            } else if (i == freq) {
                mul++;
            }
        }

        return freq * mul;
    }
};