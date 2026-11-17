class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        for (int v = 0; v< nums.size(); v++){
            hashmap[nums[v]]=v;
        }
        for (int v = 0; v< nums.size(); v++){
            int t = target-nums[v];
            bool found = (hashmap.find(t) != hashmap.end() && v != hashmap[t]);
            if (found)
                return {v, hashmap[t]};
        }
        return {};
    }
};
