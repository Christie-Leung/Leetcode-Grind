/**
 * Link: https://leetcode.com/problems/maximum-profit-in-job-scheduling
 * Tags: Array, Dynamic Programming, Sorting, Binary Search
 * Difficulty: Hard
 * Date: 2025-10-19
 */

#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();

        map<int, int> dp = {{0, 0}};
        vector<vector<int>> jobs;

        for (int i = 0; i < n; i++) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }

        sort(jobs.begin(), jobs.end());

        for (auto& j: jobs) {
            int start = j[1];

            int currProfit = prev(dp.upper_bound(start))->second + j[2];
            if (currProfit > dp.rbegin()->second) dp[j[0]] = currProfit;
        }

        return dp.rbegin()->second;
        
    }
};
