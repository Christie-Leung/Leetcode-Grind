/**
 * Link: https://leetcode.com/problems/find-closest-person/description/
 * Tags: Math
 * Difficulty: Easy
 * Date: 2025-09-04
 */

impl Solution {
    pub fn find_closest(x: i32, y: i32, z: i32) -> i32 {
        let zTox = (z-x).abs();
        let zToy = (z-y).abs();
        if (zTox < zToy) {
            return 1;
        } else if (zToy < zTox) {
            return 2;
        } else {
            return 0;
        }
    }
}