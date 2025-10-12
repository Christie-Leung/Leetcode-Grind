/**
 * Link: https://leetcode.com/problems/find-lucky-integer-in-an-array/
 * Tags: Array, Hash Table, Counting
 * Difficulty: Easy
 * Date: 2025-10-12
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findLucky(vector<int>& arr) {
        sort(arr.begin(), arr.end(), greater<int>());

        int freq = 1;
        int curr = -1;

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == curr) {
                freq++;
            } else {
                if (freq == curr) {
                    return freq;
                } else {
                    freq = 1;
                    curr = arr[i];
                }
            }
        }

        if (freq == curr) return freq;

        return -1;
        
    }
};