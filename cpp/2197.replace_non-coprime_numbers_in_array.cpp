/**
 * Link: https://leetcode.com/problems/replace-non-coprime-numbers-in-array/description
 * Tags: Array, Math, Stack, Number Theory
 * Difficulty: Hard
 * Date: 2025-09-16
 */

#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {

        int start = -1;
        for (int n : nums) {
            int curr = n;
            while (start != -1) {
                if (isCoprime(nums[start], curr)) break;
                curr = lcm(nums[start], curr);
                start--;
            }
            nums[++start] = curr;
        }
        nums.resize(start+1);
        return nums;
        
    }

    bool isCoprime(int x, int y) {
        if (x == 0 || y == 0) return false;
        if (x == 1 || y == 1 || x < 0 || y < 0) return true;

        int a = max(x, y);
        int b = min(x, y);

        int mul = floor(a/b);

        return isCoprime(a - mul*b, b);
    }

};