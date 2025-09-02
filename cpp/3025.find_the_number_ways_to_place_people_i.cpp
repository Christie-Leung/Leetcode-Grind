/**
 * Link: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/description
 * Tags: Array, Math, Geometry, Sorting, Enumeration
 * Difficulty: Medium
 * Date: 2025-09-02
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        
        sort(points.begin(), points.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            if (lhs[0] == rhs[0]) {
                return lhs[1] > rhs[1];
            }
            return lhs[0] < rhs[0];
        });


        int count = 0;
        for (int i = 0; i < points.size() - 1; i++) {
            int highestsf = -1;
            for (int j = i + 1; j < points.size(); j++) {
                if (points[j][1] > points[i][1]) continue;

                if (points[j][1] <= highestsf) continue;

                highestsf = points[j][1];
                count++;
            }
        }

        return count;
    }
};