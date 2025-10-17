/**
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * Tags: Array, Dynamic Programming
 * Difficulty: Easy
 * Date: 2025-10-17
 */

#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {

        if (prices.size() <= 1) return 0;

        int maxP = 0; 

        int start = 0;
        int end = 1;
        while (end != prices.size()) {
            maxP = max(maxP, prices[end] - prices[start]);

            if (prices[start] > prices[end]) {
                start = end;
            } 
            end++;
        }

        return maxP;
        
    }
};