/**
 * Link: https://leetcode.com/problems/maximum-average-pass-ratio/description
 * Tags: Array, Greedy, Heap
 * Difficulty: Medium
 * Date: 2025-09-01
 */

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        auto gain = [](int pass, int total) {
            return (double) (pass + 1)/(total + 1) - (double) pass / total;
        };

        priority_queue<pair<double, int>> pq;
        for (int i = 0; i < classes.size(); i++) {
            pq.push({gain(classes[i][0], classes[i][1]), i});
        }

        for (int i = 0; i < extraStudents; i++) {
            auto [currGain, index] = pq.top();
            pq.pop();
            classes[index][0]++;
            classes[index][1]++;
            pq.push({gain(classes[index][0], classes[index][1]), index});
        }

        double sum = 0;
        for (int i = 0; i < classes.size(); i++) {
            sum += (double) classes[i][0] / classes[i][1];
        }

        return sum / classes.size();
    }
};