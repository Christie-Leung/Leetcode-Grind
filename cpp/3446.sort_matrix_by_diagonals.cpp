/**
 * Link: https://leetcode.com/problems/sort-matrix-by-diagonals/description
 * Tags: Array, Sorting, Matrix
 * Difficulty: Medium
 * Date: 2025-08-28
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int n;
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        n = grid.size();

        for (int j = 1; j < n-1; j++) {
            sortDiag(grid, 0, j, false);
        }

        for (int i = 0; i < n-1; i++) {
            sortDiag(grid, i, 0, true);
        }
        return grid;
    }

    void sortDiag(vector<vector<int>>& grid, int i, int j, bool isReversed) {
        vector<int> nums;

        int s = i, t = j;
        while (s < n && t < n) {
            nums.push_back(grid[s][t]);
            s++;
            t++;
        }

        sort(nums.begin(), nums.end());
        if (isReversed) {
            reverse(nums.begin(), nums.end());
        }

        int u = i, v = j;
        for (int n = 0; n < nums.size(); n++) {
            grid[u][v] = nums[n];
            u++;
            v++;
        }
    }
};