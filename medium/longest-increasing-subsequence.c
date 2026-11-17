int lengthOfLIS(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int tails[numsSize];
    int len = 0;

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        
        // Binary search for the first element in tails >= x (lower_bound)
        int left = 0, right = len;
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (tails[mid] < x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        // Either extends tails (when left == len) or updates an existing tail
        tails[left] = x;
        if (left == len) {
            len++;
        }
    }

    return len;
}

/*
 * ============================================================================
 * LeetCode 300: Longest Increasing Subsequence
 * ============================================================================
 *
 * [Approach: Patience Sorting (Greedy + Binary Search)]
 * Instead of O(N^2) DP comparing every previous index, we maintain a strictly
 * increasing array `tails`, where `tails[k]` stores the smallest possible
 * ending value of an increasing subsequence of length `k + 1`.
 *
 * Because `tails` stays sorted, we use binary search (`lower_bound`) for each
 * number `x` to find the first element >= x:
 *   - If `x` is larger than all tails -> append `x` (extend LIS length `len`).
 *   - Otherwise -> overwrite `tails[left] = x` (keep future tails minimal).
 *
 * [Visual Walkthrough: nums = [10, 9, 2, 5, 3, 7, 101, 18]]
 *
 *   x = 10  -> [10]             (len = 1)
 *   x = 9   -> [9]              (replace 10 with smaller tail 9)
 *   x = 2   -> [2]              (replace 9 with smaller tail 2)
 *   x = 5   -> [2, 5]           (extend -> len = 2)
 *   x = 3   -> [2, 3]           (replace 5 with smaller tail 3)
 *   x = 7   -> [2, 3, 7]        (extend -> len = 3)
 *   x = 101 -> [2, 3, 7, 101]   (extend -> len = 4)
 *   x = 18  -> [2, 3, 7, 18]    (replace 101 with 18 -> final len = 4)
 *
 *   (Note: `tails` holds optimal endpoints, not the literal subsequence.)
 *
 * [Complexity]
 * - Time:  O(N log N) -> N elements, each performing an O(log N) binary search.
 * - Space: O(N)       -> Stack-allocated `tails[numsSize]` buffer.
 * ============================================================================
 */
