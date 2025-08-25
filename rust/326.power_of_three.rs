/**
 * Link: https://leetcode.com/problems/power-of-three/description/
 * Date: 2025-08-24
 */

impl Solution {
    pub fn is_power_of_three(n: i32) -> bool {
        if (n <= 0) {
            return false;
        }
        let i: f64 = n as f64;
        if (i.log(3.0).fract() > 0.5) {
            return (1.0 - i.log(3.0).fract() - 0.0) < 0.0000000000001;
        }
        return (i.log(3.0).fract() - 0.0) < 0.0000000000001;
    }
}