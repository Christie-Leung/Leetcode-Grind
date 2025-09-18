/**
 * Link: https://leetcode.com/problems/design-task-manager/description
 * Tags: Hash Table, Design, Heap, Ordered Set
 * Difficulty: Medium
 * Date: 2025-09-19
 */

#include <queue>
#include <unordered_map>
using namespace std;

class TaskManager {
public:
    priority_queue<pair<int, int>> tasks;
    unordered_map<int, int> taskPriority;
    unordered_map<int, int> taskOwner;

    TaskManager(vector<vector<int>>& tasks) {
        for (vector<int> task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        tasks.push({priority, taskId});
        taskPriority[taskId] = priority;
        taskOwner[taskId] = userId;
    }
    
    void edit(int taskId, int newPriority) {
        tasks.push({newPriority, taskId});
    taskPriority[taskId] = newPriority;
    }
    
    void rmv(int taskId) {
        taskPriority[taskId] = -1;
    }
    
    int execTop() {
        while (!tasks.empty()) {
            const auto task = tasks.top();
            tasks.pop();
            if (task.first == taskPriority[task.second]) {
                taskPriority[task.second] = -1;
                return taskOwner[task.second];
            }
        }
        return -1;
    }

};
