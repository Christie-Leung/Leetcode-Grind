/**
 * Link: https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/description
 * Tags: Array
 * Difficulty: Easy
 * Date: 2025-08-26
 */

#include <vector>

using namespace std;

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        long double longestsf = 0;
        int area = 0;
        for (int i = 0; i < dimensions.size(); i++) {
            long long a = pow(dimensions[i][0], 2);
            long long b = pow(dimensions[i][1], 2);
            long long diag = a + b;
            if (diag >= longestsf) {
                int tempArea = dimensions[i][0] * dimensions[i][1];
                if (diag > longestsf || (diag == longestsf && tempArea > area)) {
                    area = tempArea;
                }
                longestsf = diag;
            }
        }
        return area;
    }
};