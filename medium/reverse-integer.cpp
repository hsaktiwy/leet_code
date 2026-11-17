class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;

            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) {
                return 0;
            }
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) {
                return 0;
            }
            rev = rev * 10 + pop;
        }
        return rev;
    }
};
/*
 * ============================================================================
 * LeetCode 7: Reverse Integer
 * ============================================================================
 *
 * [Approach: Pure 32-Bit Math with Pre-Overflow Guard]
 * Instead of converting to a string or using 64-bit `long long`, we pop digits
 * using `% 10` and `/ 10` (which preserve sign in C++) and push them onto `rev`.
 * To prevent signed 32-bit overflow before `rev * 10 + pop` executes, we check
 * against `INT_MAX / 10` (214748364) and `INT_MIN / 10` (-214748364):
 *
 *   INT_MAX =  2147483647  -> overflow if rev >  214748364 or (== and pop >  7)
 *   INT_MIN = -2147483648  -> overflow if rev < -214748364 or (== and pop < -8)
 *
 * [Visual Walkthrough: x = -123]
 *
 *   Iter 1: pop = -3, x = -12  -> rev = 0 * 10 + (-3)   = -3
 *   Iter 2: pop = -2, x = -1   -> rev = -3 * 10 + (-2)  = -32
 *   Iter 3: pop = -1, x = 0    -> rev = -32 * 10 + (-1) = -321  (loop ends)
 *
 * [Complexity]
 * - Time:  O(log10(x)) -> Processes one digit per iteration (max 10 steps).
 * - Space: O(1)        -> Uses only two 32-bit integers, zero heap memory.
 * ============================================================================
 */
