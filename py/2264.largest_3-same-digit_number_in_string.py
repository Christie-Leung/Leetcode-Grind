"""
Link: https://leetcode.com/problems/largest-3-same-digit-number-in-string/description/
Date: 2025-08-24
"""

class Solution:
    def largestGoodInteger(self, num: str) -> str:
        count = 0
        curr = -1
        valid = "-1"
        largest = -1
        for i, n in enumerate(num):
            if curr == n:
                count += 1
            else:
                curr = n
                count = 0
            if count >= 2:
                if int(n) > int(largest):
                    largest = int(n)
                    valid = num[i-2:i+1]

        if valid == "-1":
            return ""
        return valid
        
        