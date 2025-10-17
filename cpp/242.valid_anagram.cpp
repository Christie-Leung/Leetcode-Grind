/**
 * Link: https://leetcode.com/problems/valid-anagram/
 * Tags: Hash Table, String, Sorting
 * Difficulty: Easy
 * Date: 2025-10-17
 */

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {

        if (s.size() != t.size()) return false;

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) return false;
        }

        return true;
        
    }
};

// assume s, t can contain unicode characters