class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        int target = totalSum - x;

        // If target is negative, impossible
        if (target < 0) {
            return -1;
        }

        // If target is 0, we remove the entire array
        if (target == 0) {
            return n;
        }

        int left = 0;
        int currSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {
            currSum += nums[right];

            // Shrink window if sum becomes too large
            while (currSum > target) {
                currSum -= nums[left];
                left++;
            }

            // Found a subarray with sum = target
            if (currSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        // Remove everything outside the longest valid subarray
        if (maxLen == -1) {
            return -1;
        }

        return n - maxLen;
    }
};