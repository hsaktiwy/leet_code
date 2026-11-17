class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        size_t m = nums1.size(); size_t n = nums2.size();
        size_t i1 = 0, i2 = 0;
        size_t t = m+n;
        int curr = 0, prev = 0;
        for(int count = 0; count <= t/2; count++) {
            prev = curr;
            if (i1 < m && i2 < n) {
                curr  = (nums1[i1] <= nums2[i2]) ? nums1[i1++] : nums2[i2++];
            } else if (i1 < m) {
                curr = nums1[i1++];
            } else {
                curr = nums2[i2++];
            }
        }
        if (t % 2 == 0){
            return static_cast<double>(curr + prev)/2.0;
        }
        return static_cast<double>(curr);
    }
};
/*
 * ============================================================================
 * LeetCode 4: Median of Two Sorted Arrays
 * ============================================================================
 *
 * [Approach: Two-Pointer Merge Simulation (O(1) Space)]
 * Instead of merging both arrays into a new O(M + N) vector, we simulate the
 * merge using two pointers (`i1`, `i2`) and stop halfway at index `t / 2`.
 * Tracking just the last two seen elements (`prev` and `curr`) is enough to
 * compute the median for both odd and even total lengths (`t = m + n`).
 *
 * [Visual Walkthrough: nums1 = [1, 3], nums2 = [2, 4]  (t = 4, stop at 2)]
 *
 *   count=0:  nums1: [1, 3]   nums2: [2, 4]   -> pick 1  (prev=0, curr=1)
 *                     ^               ^
 *   count=1:  nums1: [1, 3]   nums2: [2, 4]   -> pick 2  (prev=1, curr=2)
 *                        ^            ^
 *   count=2:  nums1: [1, 3]   nums2: [2, 4]   -> pick 3  (prev=2, curr=3)
 *                        ^               ^
 *
 *   t is even -> median = (prev + curr) / 2.0 = (2 + 3) / 2.0 = 2.5
 *
 * [Complexity]
 * - Time:  O((M + N) / 2) = O(M + N) -> Walks half of the combined elements.
 * - Space: O(1) -> Only scalar pointers and two tracking variables (`prev`, `curr`).
 *   (Note: Binary search on the smaller array achieves O(log(min(M, N))) time.)
 * ============================================================================
 */
