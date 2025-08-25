/**
 * Link: https://leetcode.com/problems/diagonal-traverse/description
 * Date: 2025-08-25
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();

        vector<int> diag(n*m, 0);

        int i = 0, j = 0;
        int index = 0;
        int reverse = 0;
        while (index < n*m) {
            diag[index] = mat[i][j];
            
            if (reverse) {
                i++;
                j--;

                if (j < 0 && i >= n) {
                    i--;
                    j += 2;
                    reverse = 0;
                } else if (j < 0) {
                    j = 0;
                    reverse = 0;
                } else if (i >= n) {
                    i--;
                    j += 2;
                    reverse = 0;
                }

            } else {
                i--;
                j++;

                if (i < 0 && j >= m) {
                    j--;
                    i += 2;
                    reverse = 1;
                } else if (i < 0) {
                    i = 0;
                    reverse = 1;
                } else if (j >= m) {
                    j--;
                    i += 2;
                    reverse = 1;
                }
            }

            index++;
        }

        return diag;
        
    }
};