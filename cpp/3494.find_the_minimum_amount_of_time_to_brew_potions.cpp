/**
 * Link: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/
 * Tags: Array, Prefix Sum, Simulation
 * Difficulty: Medium
 * Date: 2025-10-09
 */

using namespace std;
#include <vector>

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {

        int n = skill.size();
        int m = mana.size();

        vector<long long> freeTime(n+1);

        for (int j = 0; j < m; j++) {
            int currMana = mana[j];
            for (int i = 0; i < n; i++) {
                freeTime[i+1] = max(freeTime[i], freeTime[i+1]) + currMana * skill[i];
            }
            for (int i = n - 1; i > 0; i--) {
                freeTime[i] = freeTime[i+1] - currMana * skill[i];
            }
        }

        return freeTime[n];
    }
};

