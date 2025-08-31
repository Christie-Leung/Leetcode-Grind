"""
Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/description
Tags: Hash Table, String, Sliding Window
Difficulty: Medium
Date: 2025-08-31
"""

class Solution:
  def lengthOfLongestSubstring(self, s: str) -> int:

    start = 0
    end = 0
    seen = []
    longestsf = 0
    while end < len(s):
      if s[end] in seen:
        longestsf = max(longestsf, end-start)
        idx = seen.index(s[end])
        seen = seen[idx+1:]
        start += idx + 1
      seen.append(s[end])
      end += 1
    longestsf = max(longestsf, end-start)

    return longestsf
        