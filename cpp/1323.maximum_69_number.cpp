/**
 * Link: https://leetcode.com/problems/maximum-69-number/description
 * Tags: Math
 * Difficulty: Easy
 * Date: 2025-08-24
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximum69Number (int num) {
        int i = num % 10, j = num;
        vector<int> nums;
        while (j > 0) {
            nums.push_back(i);
            j = floor(j / 10);
            i = j % 10;
        }

        int flip = 0;
        int finalNum = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            int digit = nums[i];
            if (digit == 6 && flip == 0) {
                flip++;
                digit = 9;
            }

            finalNum += digit * pow(10, i);
        }

        return finalNum;

    }
};