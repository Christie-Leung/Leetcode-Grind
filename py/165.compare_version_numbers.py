"""
Link: https://leetcode.com/problems/compare-version-numbers/description
Tags: String, Two Pointers
Difficulty: Medium
Date: 2025-09-23
"""

class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        v1 = [int(x) for x in version1.split('.')]
        v2 = [int(x) for x in version2.split('.')]

        size = min(len(v1), len(v2))

        for i in range(size):
            print(v1[i], v2[i])
            if v1[i] > v2[i]:
                return 1
            if v1[i] < v2[i]:
                return -1

        if len(v1) < len(v2):
            return -1 if any(v2[i] > 0 for i in range(size, len(v2))) else 0
        
        if len(v1) > len(v2):
            return 1 if any(v1[i] > 0 for i in range(size, len(v1))) else 0

        return 0