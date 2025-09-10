/**
 * Link: https://leetcode.com/problems/minimum-number-of-people-to-teach/description
 * Tags: Array, Hash Table, Greedy
 * Difficulty: Medium
 * Date: 2025-09-10
 */

#include <vector>
#include <bitset>
using namespace std;

class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {

        vector<bitset<500>> know = vector<bitset<500>>(languages.size());
        for (int i = 0; i < languages.size(); i++) {
            for (int l : languages[i]) {
                know[i][l-1] = 1;
            }
        }

        bitset<500> learn;

        for (int i = 0; i < friendships.size(); i++) {
            int p1 = friendships[i][0] - 1;
            int p2 = friendships[i][1] - 1;
            if ((know[p1] & know[p2]).any()) continue;
            learn[p1] = learn[p2] = 1;
        }

        if (learn.count() == 0) return 0;

        int ans = 1000000000;
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < languages.size(); j++) {
                if (learn[j] & !know[j][i]) count++;
            }
            ans = min(ans, count);
        }

         
        return ans;
    }
};