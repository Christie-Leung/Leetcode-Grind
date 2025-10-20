/**
 * Link: https://leetcode.com/problems/final-value-of-variable-after-performing-operations
 * Tags: Simulation, Array, String
 * Difficulty: Easy
 * Date: 2025-10-20
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int res = 0;
        for (string& op : operations) {
            if (op == "X++" || op == "++X") {
                res++;
            } else {
                res--;
            }
        } 
        return res;
    }
};
