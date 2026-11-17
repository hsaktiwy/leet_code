class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int m = abs(nums[0] - nums[nums.size()-1]);
        for (int i = 1; i < nums.size(); i++){
            int k = abs(nums[i-1]-nums[i]);
            if (k> m)
                m = k;
        }
        return m;
    }
};

