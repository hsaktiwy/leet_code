class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        result.reserve(500);
        if (nums.size() < 3) return result; 
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (nums[i] > 0) break; 
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    left++;
                    right--;
                } 
                else if (sum < 0) {
                    left++;
                } 
                else {
                    right--;
                }
            }
        }
        return result;
    }
};
/*
 * ============================================================================
 * LeetCode 15: 3Sum
 * ============================================================================
 *
 * [Approach: Sort + Two-Pointer Squeeze with Duplicate Skipping]
 * Sorting `nums` first lets us fix one element `nums[i]` and reduce the
 * remaining problem to a classic O(N) Two-Sum search on the subarray to its
 * right using `left` and `right` pointers:
 *   - Early Exit: If `nums[i] > 0`, no three positive numbers can sum to 0.
 *   - Deduplication: Skip adjacent identical values for `i`, `left`, and
 *     `right` so every triplet in `result` is unique without using a hash set.
 *
 * [Visual Walkthrough: nums = [-1, 0, 1, 2, -1, -4] -> sorted: [-4, -1, -1, 0, 1, 2]]
 *
 *   i=1 (-1):  [-4, -1, -1,  0,  1,  2]
 *                    i   L           R   -> sum = -1 + (-1) + 2 = 0 (save [-1,-1,2])
 *                        -> L++, R--
 *                    i       L   R       -> sum = -1 + 0 + 1    = 0 (save [-1, 0,1])
 *
 *   i=2 (-1):  nums[2] == nums[1] -> skip duplicate anchor `i`!
 *
 * [Complexity]
 * - Time:  O(N^2) -> O(N log N) sort + O(N) outer loop * O(N) two-pointer scan.
 * - Space: O(1)   -> In-place sort (O(log N) stack space), excluding output.
 * ============================================================================
 */
