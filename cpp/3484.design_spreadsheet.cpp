/**
 * Link: https://leetcode.com/problems/design-spreadsheet/description
 * Tags: Array, Hash Table, String, Design, Matrix
 * Difficulty: Medium
 * Date: 2025-09-19
 */

#include <map>
#include <string>
using namespace std;

class Spreadsheet {
public:
    map<string, int> sheet;
    Spreadsheet(int rows) {
    }
    
    void setCell(string cell, int value) {
        sheet[cell] = value;
    }
    
    void resetCell(string cell) {
        sheet[cell] = 0;
    }
    
    int getValue(string formula) {
        int index = formula.find('+');
        string first = formula.substr(1, index - 1);
        string second = formula.substr(index+1);

        int val1 = first[0] >= 'A' && first[0] <= 'Z' ? sheet[first] : stoi(first);
        int val2 = second[0] >= 'A' && second[0] <= 'Z' ? sheet[second] : stoi(second);

        return val1 + val2;
    }
};