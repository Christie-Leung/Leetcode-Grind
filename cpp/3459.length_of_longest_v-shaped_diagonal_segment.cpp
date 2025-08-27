/**
 * Link: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/
 * Tags: Array, Dynamic Programming, Memoization, Matrix
 * Difficulty: Hard
 * Date: 2025-08-27
 */

#include <vector>

using namespace std;

constexpr int dir[5] = {1, 1, -1, -1, 1};
int dp[500][500][4][2];

class Solution {
public:
    int n, m;
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        int longestsf = 0;

        for (int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                memset(dp[i][j], -1, sizeof(dp[i][j]));
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (int d = 0; d < 4; d++) {
                        longestsf = max(longestsf, lenOfVDiagRecurr(grid, i, j, d, false, true) + 1);
                    }
                }
            }
        }
        return longestsf;
    }

    int isInGrid(int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < m;
    }

    int lenOfVDiagRecurr(vector<vector<int>>& grid, int i, int j, int lastDir, bool hasTurned, bool isTwo) {
        if (dp[i][j][lastDir][hasTurned] != -1) {
            return dp[i][j][lastDir][hasTurned];
        }
        int longestsf = 0;
        int x = grid[i][j];

        int find = isTwo ? 2 : 0;

        int newi = i + dir[lastDir];
        int newj = j + dir[lastDir+1];
        if (isInGrid(newi, newj) && grid[newi][newj] == find) {
            longestsf = max(longestsf, 1 + lenOfVDiagRecurr(grid, newi, newj, lastDir, hasTurned, !isTwo)); 
        }

        if (!hasTurned) {
            int newDir = (lastDir + 1) % 4;
            int turni = i + dir[newDir];
            int turnj = j + dir[newDir];
            if (isInGrid(turni, turnj) && grid[turni][turnj] == find) {
                longestsf = max(longestsf, 1 + lenOfVDiagRecurr(grid, turni, turnj, newDir, true, !isTwo)); 
            }
        }

        return dp[i][j][lastDir][hasTurned] = longestsf;
    }

};

/* Attempt 1
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int longestsf = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    int diag = lenOfVDiagHelper(grid, i, j, true) + 1;
                    if (diag > longestsf) {
                        longestsf = diag;
                    }
                }
            }
        }
        return longestsf;
    }

    int lenOfVDiagHelper(vector<vector<int>>& grid, int i, int j, bool isOdd) {
        int longestDiag = 0;

        if (upleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, -1}, i-1, j-1, !isOdd, false);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (upright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, 1}, i-1, j+1, !isOdd, false);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

         if (bottomleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, -1}, i+1, j-1, !isOdd, false);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

         if (bottomright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, 1}, i+1, j+1, !isOdd, false);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        return longestDiag;

    }

    int clockwiseTurn(vector<vector<int>>& grid, vector<int> lastDir, int i, int j, bool isOdd, bool hasTurned) {
        int n = grid.size(), m = grid[0].size();
        int longestDiag = 0;

        if (lastDir[0] == -1 && lastDir[1] == -1 && !hasTurned && upright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, 1}, i-1, j+1, !isOdd, true);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == -1 && lastDir[1] == -1 && upleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, -1}, i-1, j-1, !isOdd, hasTurned);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == -1 && lastDir[1] == 1 && !hasTurned && bottomright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, 1}, i+1, j+1, !isOdd, true);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

         if (lastDir[0] == -1 && lastDir[1] == 1 && upright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, 1}, i-1, j+1, !isOdd, hasTurned);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == 1 && lastDir[1] == -1 && !hasTurned && upleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {-1, -1}, i-1, j-1, !isOdd, true);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == 1 && lastDir[1] == -1 && bottomleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, -1}, i+1, j-1, !isOdd, hasTurned);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == 1 && lastDir[1] == 1 && !hasTurned && bottomleft(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, -1}, i+1, j-1, !isOdd, true);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        if (lastDir[0] == 1 && lastDir[1] == 1 && bottomright(grid, i, j, isOdd)) {
            vector<vector<int>> copy = grid;
            copy[i][j] = -1;
            int diag = 1 + clockwiseTurn(copy, {1, 1}, i+1, j+1, !isOdd, hasTurned);
            if (diag > longestDiag) {
                longestDiag = diag;
            }
        }

        return longestDiag;
    }

    bool upright(vector<vector<int>>& grid, int i, int j, bool isOdd) {
        int n = grid.size(), m = grid[0].size();
        int find = isOdd ? 2 : 0;
        return i - 1 >= 0 && j + 1 < m && grid[i-1][j+1] == find;
    }

    bool upleft(vector<vector<int>>& grid, int i, int j, bool isOdd) {
        int n = grid.size(), m = grid[0].size();
        int find = isOdd ? 2 : 0;
        return i - 1 >= 0 && j - 1 >= 0 && grid[i-1][j-1] == find;
    }

    bool bottomleft(vector<vector<int>>& grid, int i, int j, bool isOdd) {
        int n = grid.size(), m = grid[0].size();
        int find = isOdd ? 2 : 0;
        return i + 1 < n && j - 1 >= 0 && grid[i+1][j-1] == find;
    }

    bool bottomright(vector<vector<int>>& grid, int i, int j, bool isOdd) {
        int n = grid.size(), m = grid[0].size();
        int find = isOdd ? 2 : 0;
        return i + 1 < n && j + 1 < m && grid[i+1][j+1] == find;
    }
};
*/