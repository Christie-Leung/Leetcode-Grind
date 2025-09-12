/**
 * Link: https://leetcode.com/problems/vowels-game-in-a-string/description
 * Tags: Math, String, Game Theory
 * Difficulty: Medium
 * Date: 2025-09-12
 */

#include <string>
using namespace std;

class Solution {
public:
    bool doesAliceWin(string s) {
        for (auto c : s) {
            if (isVowel(c)) return true;
        }
        return false;
    }

    bool isVowel(char c) {
        switch(c) {
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