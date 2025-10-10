/**
 * Link: https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/
 * Tags: Array, Prefix Sum
 * Difficulty: Medium
 * Date: 2025-10-10
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        int maxEnergy = INT_MIN;

        for (int i = n - 1; i >= 0; i--) {
            int curr = i - k;
            if (curr >= 0) {
                energy[curr] += energy[i];
            }
            maxEnergy = max(maxEnergy, energy[i]);
        }
        return maxEnergy;
    }
};