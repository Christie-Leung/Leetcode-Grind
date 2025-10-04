/**
 * Link: https://leetcode.com/problems/container-with-most-water/description
 * Tags: Array, Two Pointers, Greedy
 * Difficulty: Medium
 * Date: 2025-10-04
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater = 0;
        int begin = 0;
        int end = height.size() - 1;

        while (begin != end) {
            int minHeight = min(height[begin], height[end]);
            maxWater = max(minHeight * (end - begin), maxWater);
            if (height[begin] <= height[end]) {
                begin++;
            } else {
                end--;
            }
        }

        return maxWater;
        
    }
};