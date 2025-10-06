/**
 * Link: https://leetcode.com/problems/swim-in-rising-water/
 * Tags: Array, Binary Search, Depth-First Search, Heap (Priority Queue), Matrix, Union Find, Breadth-First Search, Graph
 * Difficulty: Hard
 * Date: 2025-10-06
 */

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> dirs = {{0,-1},{0,1},{-1,0},{1,0}};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int minTime = 0;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({grid[0][0], {0, 0}});

        while (!pq.empty()) {
            auto [waterLvl, coord] = pq.top();
            pq.pop();
            minTime = max(minTime, waterLvl);
            int x = coord.first, y = coord.second;

            if (x == n-1 && y == n-1) return minTime;
            if (visited[x][y]) continue;
            visited[x][y] = true;

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                    pq.push({grid[nx][ny], {nx, ny}});
                }
            }
        }

        return 0;
        
    }
   
};