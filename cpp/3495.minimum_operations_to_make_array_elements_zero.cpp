/**
 * Link: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/description
 * Tags: Array, Math, Bit Manipulation
 * Difficulty: Hard
 * Date: 2025-09-06
 */

#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
    long long expSum4[18]={1};
    
    long long expSum(int i){
        if (i == 0) return 0;
        int logval =  floor(log(i) / log(4));
        int r = i - (1 << (2 * logval));
        return expSum4[logval]+r*(logval+1LL);
    }

    long long minOperations(vector<vector<int>>& queries) {
        for(int i = 1; i < 18; i++){
            expSum4[i] = expSum4[i-1] + 3LL * i * (1LL << (2 * (i - 1))) + 1;
        }
        long long ops = 0;

        for (int i = 0; i < queries.size(); i++) {
            int l = queries[i][0] - 1;
            int r = queries[i][1];

            ops += (expSum(r) - expSum(l) + 1) / 2;
        }
        return ops;
    }
};