/**
 * Link: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/description
 * Tags: Array, Math
 * Difficulty: Easy
 * Date: 2025-09-07
 */

 impl Solution {
    pub fn sum_zero(n: i32) -> Vec<i32> {
        let mut arr: Vec<i32> = vec![];

        if (n % 2 != 0) {
            arr.push(0);
        }

        let mut currSum: i32 = 0;
        for i in 1..n {
            let val = i/2 + 1;
            if (i % 2 == 0) {
                arr.push(-val + 1);
                currSum = currSum - val + 1;
            } else {
                arr.push(val);
                currSum = currSum + val;
            }
        }

        if (currSum != 0) {
            arr.push(-currSum);
        }
        return arr;
        
    }
}