/**
 * Link: https://leetcode.com/problems/edit-distance/
 * Tags: String, Dynamic Programming
 * Difficulty: Medium
 * Date: 2025-10-18
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        if (m < n) {
            swap(word1, word2);
            swap(m, n);
        }

        vector<int> prev(n+1), curr(n+1);

        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            curr[0] = i;
            for (int j = 1; j <= n; j++) {
                if (word1[i-1] == word2[j-1]) {
                    curr[j] = prev[j-1];
                } else {
                    int insert = curr[j-1] + 1;
                    int del = prev[j] + 1;
                    int replace = prev[j-1] + 1;

                    curr[j] = min({insert, del, replace});
                }
            }
            swap(prev, curr);
        }

        return prev[n];
        
    }
};