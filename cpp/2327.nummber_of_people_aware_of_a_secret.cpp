/**
 * Link: https://leetcode.com/problems/number-of-people-aware-of-a-secret/description/
 * Tags: Dynamic Programming
 * Difficulty: Medium
 * Date: 2025-09-09
 */

using namespace std;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        int secrets[1001];
        long long mod = 1000000007;

        secrets[1] = 1;
        long long ppl = 0;
        for (int i = 2; i <= n; i++) {
            if (i - delay > 0) {
                ppl = (ppl + secrets[i - delay] + mod) % mod;
            }
            if (i - forget > 0) {
                ppl = (ppl - secrets[i - forget] + mod) % mod;
            }

            secrets[i] = ppl;
        }

        long long ans = 0;
        for (int i = n - forget + 1; i <= n; i++) {
            ans = (ans + secrets[i]) % mod;
        }
        return ans;
    }
};