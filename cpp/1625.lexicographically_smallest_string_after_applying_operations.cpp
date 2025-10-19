/**
 * Link: https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations
 * Tags: String, Depth-First Search, Breadth-First Search, Enumeration
 * Difficulty: Medium
 * Date: 2025-10-19
 */

#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();

        unordered_set<string> seen;
        string smallest = s;
        queue<string> q;

        q.push(s);
        seen.insert(s);

        while (!q.empty()) {
            string front = q.front();
            q.pop();
            smallest = min(front, smallest);

            string adds = front;
            for (int i = 1; i < n; i+=2) adds[i] = ((adds[i] - '0' + a) % 10) + '0';

            string rots = front.substr(n-b) + front.substr(0, n-b);

            if (!seen.count(adds)) {
                seen.insert(adds);
                q.push(adds);
            }

            if (!seen.count(rots)) {
                seen.insert(rots);
                q.push(rots);
            }
        }

        return smallest;
        
    }
};