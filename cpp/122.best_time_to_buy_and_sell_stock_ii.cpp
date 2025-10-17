/**
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * Tags: Array, Dynamic Programming, Greedy
 * Difficulty: Medium
 * Date: 2025-10-17
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int total = 0;

        for (int i = 1; i < prices.size(); i++) {
            if (prices[i-1] < prices[i]) {
                total += prices[i] - prices[i-1];
            }
        }
        return total;
        
    }
};