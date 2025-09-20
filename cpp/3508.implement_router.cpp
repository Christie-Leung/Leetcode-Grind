/**
 * Link: https://leetcode.com/problems/implement-router/description
 * Tags: Design, Hash Table, Queue
 * Difficulty: Medium
 * Date: 2025-09-21
 */

using namespace std;
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>

class Router {
public:
    map<int, vector<int>> timemap;
    set<string> keyset;
    queue<vector<int>> router;
    int limit;
    Router(int memoryLimit) {
        limit = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        string key = getKey(source, destination, timestamp);

        if (keyset.count(key)) return false;

        if (router.size() >= limit) {
            forwardPacket();
        }
        router.push({source, destination, timestamp});
        keyset.insert(key);
        timemap[destination].push_back(timestamp);
        return true;
    }
    
    vector<int> forwardPacket() {
        if (router.size() == 0) return {};

        vector<int> packet = router.front();
        router.pop();
        keyset.erase(getKey(packet[0], packet[1], packet[2]));
        timemap[packet[1]].erase(timemap[packet[1]].begin());

        return packet;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        auto it = timemap.find(destination);
        if (it == timemap.end() || it->second.empty()) return 0;

        vector<int>& list = it->second;
        
        auto start = lower_bound(list.begin(), list.end(), startTime);
        auto end = upper_bound(list.begin(), list.end(), endTime);
        
        return distance(start, end);
    }

    string getKey(int source, int destination, int timestamp) {
        string key;
        key += to_string(source);
        key += '-';
        key += to_string(destination);
        key += '-';
        key += to_string(timestamp);
        return key;
    }
};
