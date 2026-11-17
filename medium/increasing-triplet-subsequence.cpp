bool increasingTriplet(int* nums, int numsSize) {
    if (numsSize < 3) return false;

    int a = INT_MAX;
    int b = INT_MAX;

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        if (x <= a) {
            a = x;
        } else if (x <= b) {
            b = x;
        } else {
            return true;
        }
    }
    return false;
}
/*
 * ============================================================================
 * LeetCode 334: Increasing Triplet Subsequence
 * ============================================================================
 *
 * [Approach: Greedy Two-Threshold Scan (Patience Sorting of Size 3)]
 * This is a specialized O(1)-space case of Patience Sorting (LIS) where we
 * only track the smallest possible tails of length 1 (`a`) and length 2 (`b`):
 *   - `a` = smallest value seen so far.
 *   - `b` = smallest value seen so far that is strictly greater than `a`.
 *   - If any element `x` exceeds both (`x > b`), an increasing triplet exists.
 *
 * Chaining `if / else if / else` and caching `x = nums[i]` in a register keeps
 * comparisons to at most 2 per element with zero redundant memory reads.
 *
 * [Visual Walkthrough: nums = [2, 1, 5, 0, 4, 6]]
 *
 *   x = 2 -> x <= a (INT_MAX) -> a = 2, b = INF
 *   x = 1 -> x <= a (2)       -> a = 1, b = INF
 *   x = 5 -> x <= b (INT_MAX) -> a = 1, b = 5    (pair [1, 5] locked)
 *   x = 0 -> x <= a (1)       -> a = 0, b = 5    (even though a=0 comes after
 *                                                 b=5, `b` still guarantees a
 *                                                 prior value < 5 existed!)
 *   x = 4 -> x <= b (5)       -> a = 0, b = 4    (improved pair [0, 4])
 *   x = 6 -> x >  b (4)       -> return true!    (triplet: [0, 4, 6])
 *
 * [Complexity]
 * - Time:  O(N) -> Single linear pass with at most 2 comparisons per element.
 * - Space: O(1) -> Only two integer state variables (`a`, `b`), zero heap use.
 * ============================================================================
 */
