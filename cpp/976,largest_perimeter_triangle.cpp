/**
 * Link: https://leetcode.com/problems/largest-perimeter-triangle/description
 * Tags: Array, Greedy, Sorting, Math
 * Difficulty: Easy
 * Date: 2025-09-28
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());

        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                for (int k = j + 1; k < nums.size(); k++) {
                    int sum = nums[j] + nums[k];
                    if (nums[i] >= sum) break;
                    return sum + nums[i];
                }
            }
        }
        return 0;
    }
};