/**
 * Link: https://leetcode.com/problems/24-game
 * Tags: Array, Backtracking, Math
 * Difficulty: Hard
 * Date: 2025-10-20
 */

#include <vector>
using namespace std;

class Solution {
  const double ep = 1e-6;
  public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        for (int i = 0 ; i < 4; i++) {
            nums.push_back((double) cards[i]);
        }

        return dfs(nums);
        
    }

    bool dfs(vector<double>& vals) {
        int n = vals.size();
        if (n == 1) return fabs(vals[0] - 24.0) < ep;

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (i == j) continue;

                vector<double> newVals;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    newVals.push_back(vals[k]);
                }

                for (double b : addBranches(vals[i], vals[j])) {
                    newVals.push_back(b);
                    if (dfs(newVals)) return true;
                    newVals.pop_back();
                }
            }
        }
        return false;
    }

    vector<double> addBranches(double x, double y) {
        vector<double> branches;
        branches.push_back(x+y);
        branches.push_back(x-y);
        branches.push_back(y-x);
        branches.push_back(x*y);
        if (fabs(y) > ep) branches.push_back(x/y);
        if (fabs(x) > ep) branches.push_back(y/x);
        return branches;
    }
};