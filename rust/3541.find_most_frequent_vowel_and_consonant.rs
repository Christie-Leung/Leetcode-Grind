/// Link: https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description
/// Difficulty: Easy
/// Topic: Hash Table, String
/// Date: 2025-09-13

use std::cmp;

impl Solution {
    pub fn max_freq_sum(s: String) -> i32 {
        let mut alphabets = [0; 26];
        let vowels = [0, 4, 8, 14,20];

        for c in s.chars() {
            let ascii: usize  = (c as u32 - 97) as usize;
            alphabets[ascii] += 1;
        }

        let mut vowelFreq = 0;
        for v in vowels {
            vowelFreq = cmp::max(vowelFreq, alphabets[v]);
            alphabets[v] = 0;
        }
        alphabets.sort();
        return vowelFreq + alphabets[25];
        
    }
}
  