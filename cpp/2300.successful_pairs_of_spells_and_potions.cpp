/**
 * Link: https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
 * Tags: Array, Binary Search, Sorting
 * Difficulty: Medium
 * Date: 2025-10-08
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> result;
        sort(potions.begin(), potions.end());


        for (int i = 0 ; i < spells.size(); i++) {
            int res = -1;
            int start = 0, end = potions.size() - 1;

            while (start <= end) {
                int mid = (start + end) / 2;
                if (((long long) spells[i] * potions[mid]) >= success) {
                    res = mid;
                    end = mid - 1;
                } else {
                    start = mid + 1;
                }
            }
            result.push_back(res == -1 ? 0 : potions.size() - res);
        }

        return result;
    }
};