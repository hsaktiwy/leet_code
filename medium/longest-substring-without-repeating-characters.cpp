#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool bitzero(unsigned int *vec, unsigned char c) {
    int index = c / 32;
    int shift = c % 32;
    return !(vec[index] & (1U << shift));
}

void setbitone(unsigned int *vec, unsigned char c) {
    int index = c / 32;
    vec[index] |= (1U << (c % 32)); 
}

void clearbitzero(unsigned int *vec, unsigned char c) {
    int index = c / 32;
    vec[index] &= ~(1U << (c % 32)); 
}

int lengthOfLongestSubstring(char* s) {
    unsigned int vec[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 
    int left = 0, maxLength = 0;
    
    for (int right = 0; s[right]; right++) {
        unsigned char currentChar = s[right];
        
        while (!bitzero(vec, currentChar)) {
            clearbitzero(vec, s[left]);
            left++;
        }
        setbitone(vec, currentChar);
        maxLength = MAX(maxLength, right - left + 1);
    }
    return maxLength;
}
/*
 * ============================================================================
 * LeetCode 3: Longest Substring Without Repeating Characters
 * ============================================================================
 *
 * [Approach: Sliding Window + 256-Bit Bitset]
 * Instead of a 256-byte array or hash set, we pack all 256 ASCII states into
 * `unsigned int vec[8]` (8 * 32 bits = 256 bits, just 32 bytes on the stack).
 *
 *   vec[0] -> ASCII   0..31    vec[4] -> ASCII 128..159
 *   vec[1] -> ASCII  32..63    vec[5] -> ASCII 160..191
 *   vec[2] -> ASCII  64..95    vec[6] -> ASCII 192..223
 *   vec[3] -> ASCII  96..127   vec[7] -> ASCII 224..255
 *
 *   For char `c`:  bucket = c / 32 (c >> 5),  bit = c % 32 (c & 31)
 *
 * [Visual Walkthrough: s = "abcab"]
 *
 *   Step 1: [a b c] a b   -> right='c', unique window, set bit 'c' (len = 3)
 *            L   R
 *
 *   Step 2: [a b c a] b   -> right='a', bit 'a' is already 1! (collision)
 *            L     R
 *
 *   Step 3:  a [b c a] b  -> clear bit s[L] ('a'), advance L, set bit 'a'
 *               L   R
 *
 * [Complexity]
 * - Time:  O(N) -> Each char is visited at most twice (once by R, once by L).
 * - Space: O(1) -> Fixed 32-byte bitset (8 x 4-byte ints), zero heap usage.
 * ============================================================================
 */
