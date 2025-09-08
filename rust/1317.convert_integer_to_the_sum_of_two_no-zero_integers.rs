/**
 * Link: https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description/
 * Tags: Math
 * Difficulty: Easy
 * Date: 2025-09-08
 */

impl Solution {
    pub fn get_no_zero_integers(n: i32) -> Vec<i32> {
        let mut arr = vec![];
        let mut a = 1;
        
        while (n-a).to_string().contains('0') || a.to_string().contains('0') {
            a += 1;
        }

        arr.push(a);
        arr.push(n-a);
        return arr;
    }
}