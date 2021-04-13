class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        def sol(nums, index):
            if index > len(nums)-1:
                return 1
            c = []
            for i in range(index+1, len(nums)):
                if nums[index] < nums[i]:
                    c.append(1+sol(nums, i))
            if c != []:
                return max(c)
            else:
                return 1
        
        nums.insert(0, -sys.maxsize)
        return sol(nums, 0)-1
