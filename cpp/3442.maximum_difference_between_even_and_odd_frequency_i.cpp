/**
 * Link: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/description
 * Tags: Hash Table, String, Counting
 * Difficulty: Easy
 * Date: 2025-10-03
 */

#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    int occ[26];
    int maxDifference(string s) {
        int maxOdd = 0;
        int minEven = s.size();
        for (char & c : s) {
            occ[c - '0' - 49]++;
        }

        for (int i = 0; i < 26; i++) {
            if (occ[i] == 0) continue;
            if (occ[i] % 2 == 0) minEven = min(minEven, occ[i]);
            if (occ[i] % 2 != 0) maxOdd = max(maxOdd, occ[i]);
        }

        return maxOdd - minEven;
    }
};