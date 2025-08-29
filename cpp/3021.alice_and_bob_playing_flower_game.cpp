/**
 * Link: https://leetcode.com/problems/alice-and-bob-playing-flower-game/description/
 * Tags: Math
 * Difficulty: Medium
 * Date: 2025-08-29
 */

using namespace std;

class Solution {
public:
    long long flowerGame(int n, int m) {

        if (n + m % 2 == 0) {
            return 0;
        }

        long long x = n;
        long long y = m;

        long long ans =  x * y / 2;
        return ans;
    }
};