class Solution {
public:
    string longestPalindrome(const string& st) {
        int m = st.size();
        if (m <= 1) return st;

        int n = m * 2 + 1;
        vector<int> raid(n, 0);
        int c = 0, r = 0;
        int max_s = 0, ind = 0;

        // Helper lambda to read virtual padded string without allocating it
        auto getChar = [&](int idx) -> char {
            return (idx & 1) ? st[idx >> 1] : '#';
        };

        for (int center = 0; center < n; center++) {
            // Early exit: no remaining center can beat max_s
            if (n - 1 - center <= max_s) break;

            if (center < r) {
                int mirror = (c << 1) - center;
                raid[center] = min(r - center, raid[mirror]);
            }

            int left = center - raid[center] - 1;
            int right = center + raid[center] + 1;

            while (left >= 0 && right < n && getChar(left) == getChar(right)) {
                raid[center]++;
                left--;
                right++;
            }

            if (center + raid[center] > r) {
                r = center + raid[center];
                c = center;
            }

            if (raid[center] > max_s) {
                max_s = raid[center];
                ind = center;
            }
        }

        // Map virtual center and radius directly back to original string indices
        return st.substr((ind - max_s) >> 1, max_s);
    }
};

/*
 * ============================================================================
 * LeetCode 5: Longest Palindromic Substring
 * ============================================================================
 *
 * [Approach: Manacher's Algorithm with Zero-Allocation Virtual Padding]
 * To handle odd and even palindromes uniformly without allocating a 2N + 1
 * padded string, we map virtual indices (0..2N) directly to `st` in O(1):
 *   - Even index (idx & 1 == 0) -> virtual '#'
 *   - Odd index  (idx & 1 == 1) -> st[idx >> 1]
 *
 * By tracking the rightmost palindrome boundary `r` and its center `c`, any
 * new center inside `r` reuses its mirror's radius (`2*c - center`) instead
 * of re-comparing characters from scratch.
 *
 * [Visual Walkthrough: st = "babad" -> virtual "#b#a#b#a#d#"]
 *
 *   Virtual idx:  0 1 2 3 4 5 6 7 8 9 10
 *   Virtual str:  # b # a # b # a # d #
 *   raid[i]:      0 1 0 3 0 3 0 1 0 1 0
 *                       ^   ^
 *                       c   center (mirror = 2*3 - 5 = 1, raid[1] = 1)
 *
 *   At center = 5 ('b'), it lies inside c = 3's boundary (r = 6).
 *   It starts with radius min(6 - 5, raid[1]) = 1 and expands to radius 3 ("aba").
 *   Mapping back: start = (ind - max_s) >> 1 = (3 - 3) >> 1 = 0, len = 3 -> "bab".
 *
 * [Complexity]
 * - Time:  O(N) -> Right boundary `r` advances monotonically at most 2N times.
 * - Space: O(N) -> Only the `raid` vector of size 2N + 1 (zero extra strings).
 * ============================================================================
 */
