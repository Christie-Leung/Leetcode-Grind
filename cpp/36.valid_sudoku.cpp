/**
 * Link: https://leetcode.com/problems/valid-sudoku/description/
 * Tags: Array, Hash Table, Matrix
 * Difficulty: Medium
 * Date: 2025-08-30
 */

#include <vector>
using namespace std;

class Solution {
public:
    int hash[3][9][10]; // rows = 0, cols = 1, sqrs = 2

    bool isValidSudoku(vector<vector<char>>& board) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int val = board[i][j] - '0';

                if (hash[0][i][val]) return false;
                hash[0][i][val] = 1;

                if (hash[1][j][val]) return false;
                hash[1][j][val] = 1;

                int square = floor(i/3) * 3 + floor(j/3);
                if (hash[2][square][val]) return false;
                hash[2][square][val] = 1;
            }
        }

        return true;
    }
};