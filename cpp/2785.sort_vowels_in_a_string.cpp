/**
 * Link: https://leetcode.com/problems/sort-vowels-in-a-string/description
 * Tags: String, Sorting
 * Difficulty: Medium
 * Date: 2025-09-11
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string sortVowels(string s) {
        vector<char> chars;
        vector<int> loc;

        for (int i = 0; i < s.length(); i++) {
            if (isVowel(s[i])) {
                loc.push_back(i);
                chars.push_back(s[i]);
            }
        }

        sort(chars.begin(), chars.end());
        
        for (int i = 0; i < loc.size(); i++) {
            s[loc[i]] = chars[i];
        }

        return s;
        
    }

    bool isVowel(char c) {
        switch (char(tolower(c))) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }
};