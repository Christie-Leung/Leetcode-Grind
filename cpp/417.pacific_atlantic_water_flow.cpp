/**
 * Link: https://leetcode.com/problems/pacific-atlantic-water-flow/description
 * Tags: Depth-First Search, Breadth-First Search, Array, Matrix
 * Difficulty: Medium
 * Date: 2025-10-05
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> pacific(m, vector<int>(n));
        vector<vector<int>> atlanta(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            pacific[i][0] = 1;
            atlanta[i][n-1] = 1;
        }

        for (int i = 0; i < n; i++) {
            pacific[0][i] = 1;
            atlanta[m-1][i] = 1;
        }

        int updated = 1;

        while (updated > 0) {
            updated = 0;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    int height = heights[i][j];
                    if (!pacific[i][j]) {
                        if (i != m - 1 && pacific[i+1][j] && height >= heights[i+1][j]) {
                            pacific[i][j]++;
                            updated++;
                        } else if (i != 0 && pacific[i-1][j] && height >= heights[i-1][j]) {
                            pacific[i][j]++;
                            updated++;
                        } else if (j != n - 1 && pacific[i][j+1] && height >= heights[i][j+1]) {
                            pacific[i][j]++;
                            updated++;
                        } else if (j != 0 && pacific[i][j-1] && height >= heights[i][j-1]) {
                            pacific[i][j]++;
                            updated++;
                        }
                    }

                    if (!atlanta[i][j]) {
                        if (i != m - 1 && atlanta[i+1][j] && height >= heights[i+1][j]) {
                            atlanta[i][j]++;
                            updated++;
                        } else if (i != 0 && atlanta[i-1][j] && height >= heights[i-1][j]) {
                            atlanta[i][j]++;
                            updated++;
                        } else if (j != n - 1 && atlanta[i][j+1] && height >= heights[i][j+1]) {
                            atlanta[i][j]++;
                            updated++;
                        } else if (j != 0 && atlanta[i][j-1] && height >= heights[i][j-1]) {
                            atlanta[i][j]++;
                            updated++;
                        }
                    }
                }
            }
        }

        vector<vector<int>> result;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlanta[i][j]) result.push_back({i, j});
            }
        }


        return result;
        
    }
};