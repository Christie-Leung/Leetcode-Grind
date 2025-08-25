"""
Link: https://leetcode.com/problems/happy-number/description/
Date: 2025-08-24
"""

class Solution:
    def isHappy(self, n: int) -> bool:
        return self.isHappyRecurr(n, -1, 0)

    def isHappyRecurr(self, n: int, prev: int, count: int) -> bool:
        if n == prev:
            return True
        
        sum = 0
        string = list(str(n))
        for i in string:
            sum += int(i)**2
        if sum == 1:
            return True
        if count > 5:
            return False
        return self.isHappyRecurr(sum, n, count + 1)

