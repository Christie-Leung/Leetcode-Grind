/**
 * Link: https://leetcode.com/problems/largest-triangle-area/description
 * Tags: Geometry, Math, Array
 * Difficulty: Easy
 * Date: 2025-09-27
 */

#include <vector>
using namespace std;

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {

        double largest = 0;

        for (int i = 0; i < points.size() - 1; i++) {
            for (int j = i + 1; j < points.size(); j++) {
                for (int k = j + 1; k < points.size(); k++) {
                    int x1 = points[i][0];
                    int y1 = points[i][1];
                    int x2 = points[j][0];
                    int y2 = points[j][1];
                    int x3 = points[k][0];
                    int y3 = points[k][1];

                    largest = max(largest, (double) abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)));
                }
            }
        }

        return largest / 2;
        
    }
};