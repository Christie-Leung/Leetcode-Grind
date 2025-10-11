/**
 * Link: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/
 * Tags: Array, Hash Table, Two Pointers, Binary Search, Dynamic Programming, Sorting, Counting
 * Difficulty: Medium
 * Date: 2025-10-11
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, long long> freq;
        for (int i = 0; i < power.size(); i++) {
            freq[power[i]]++;
        }

        vector<int> keys;
        for (auto& [k, v] : freq) {
            keys.push_back(k);
        }
        sort(keys.begin(), keys.end());
        int n = keys.size();

        vector<long long> dp(n);
        dp[0] = freq[keys[0]] * keys[0];

        for (int i = 1; i < n; i++) {
            long long temp = freq[keys[i]] * keys[i];
            int prev = upper_bound(keys.begin(), keys.begin() + i, keys[i] - 3) - keys.begin() - 1;
            if (prev >= 0) temp += dp[prev];
            dp[i] = max(dp[i-1], temp);
        }
        return dp[n-1];
    }
};