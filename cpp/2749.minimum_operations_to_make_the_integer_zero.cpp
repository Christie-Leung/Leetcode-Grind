/**
 * Link: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/description/
 * Tags: Bit Manipulation
 * Difficulty: Medium
 * Date: 2025-09-05
 */

using namespace std;
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int i = 1; i <= 60; i++) {
            long long s = (long long) num1 - (long long) i * num2;
            if (s < 0 || s < i) continue;
            int bits = __builtin_popcountll(s);
            if (bits <= i) return i;
        }
        return -1;
    }
};