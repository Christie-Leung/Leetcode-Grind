/**
 * Link: https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/
 * Tags: Array, Hash Table, String, Sorting
 * Difficulty: Easy
 * Date: 2025-10-13
 */

using namespace std;
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> anagrams;
        string last = "";

        for (string& word : words) {
            string temp = word;
            sort(temp.begin(), temp.end());
            if (last != temp) {
                anagrams.push_back(word);
            }
            last = temp;
        }

        return anagrams;
        
    }
};