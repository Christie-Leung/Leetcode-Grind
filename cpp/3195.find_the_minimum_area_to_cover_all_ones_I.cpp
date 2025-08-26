/**
 * Link: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-I/description
 * Tags: Array, Matrix
 * Difficulty: Medium
 * Date: 2025-08-24
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {

        int n = grid.size(), m = grid[0].size();
        int li = 0, ri = n;
        int lj = 0, rj = m;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    li = max(li, i);
                    ri = min(ri, i);
                    lj = max(lj, j);
                    rj = min(rj, j);
                }
            }
        }

        return (li - ri + 1) * (lj - rj + 1);
        
    }
};