/**
 * Link: https://leetcode.com/problems/vowel-spellchecker/description/
 * Tags: Array, Hash Table, String
 * Difficulty: Medium
 * Date: 2025-09-14
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> wordset(wordlist.begin(), wordlist.end());
        unordered_map<string, string> capital;
        unordered_map<string, string> vowel;

        for (auto w: wordlist) {
            string lower = lowercase(w);
            string noVowel = removeVowel(lower);
            if (!capital.count(lower)) capital[lower] = w;
            if (!vowel.count(noVowel)) vowel[noVowel] = w;
        }
        vector<string> checks;
        for (auto q : queries) {
            if (wordset.count(q)) {
                checks.push_back(q);
            } else {
                string lower = lowercase(q);
                string noVowel = removeVowel(lower);

                if (capital.count(lower)) {
                    checks.push_back(capital[lower]);
                } else if (vowel.count(noVowel)) {
                    checks.push_back(vowel[noVowel]);
                } else {
                    checks.push_back("");
                }
            }
        }
        return checks;
    }

    string lowercase(string s) {
        for (auto &c : s) {
            c = tolower(c);
        }
        return s;
    }

    string removeVowel(string s) {
        for (auto &c : s) {
            if (isVowel(c)) c = '*';
        }
        return s;
    }

    bool isVowel(char c) {
        c = tolower(c);
        switch (c) {
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