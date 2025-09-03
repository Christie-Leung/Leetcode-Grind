/**
 * Link: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/description
 * Tags: Array, Math, Geometry, Sorting, Enumeration
 * Difficulty: Hard
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[0] == rhs[0] ? lhs[1] > rhs[1] : lhs[0] < rhs[0];
        });


        int count = 0;
        for (int i = 0; i < points.size() - 1; i++) {
            int highestsf = INT_MIN;
            for (int j = i + 1; j < points.size(); j++) {
                int lowerLeft = points[j][1];
                if (lowerLeft > points[i][1] || lowerLeft <= highestsf) continue;

                highestsf = lowerLeft;
                count++;
                if (lowerLeft == points[i][1]) break;
            }
        }

        return count;
    }
};