// 152 ms, faster than 49.10% of C++ online submissions for 3Sum.
class Solution {
public:
    static constexpr int MAX_NUM = 100000;
    static constexpr int BUF_SIZE = MAX_NUM * 2 + 1;

    static vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> ans;
        const int n = (int) nums.size();
        std::sort(nums.begin(), nums.end());
        int lastAppear[BUF_SIZE];
        memset(lastAppear, 0x3f, sizeof(lastAppear));
        for (int i = 0; i < n; ++i) {
            lastAppear[nums[i] + MAX_NUM] = i;
        }
        int preA = INT_MIN, preB = INT_MIN;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] == preA) continue;
            for (int j = i + 1; j < n - 1; ++j) {
                if (nums[j] == preB) continue;
                preA = nums[i], preB = nums[j];
                const int target = 0 - nums[i] - nums[j];
                int unsignedTarget = target + MAX_NUM;
                if (unsignedTarget >= BUF_SIZE || unsignedTarget < 0) continue;
                auto lastTargetIndex = lastAppear[unsignedTarget];
                if (lastTargetIndex <= j || lastTargetIndex > n) continue;
                ans.push_back({nums[i], nums[j], nums[lastTargetIndex]});
            }
        }
        return ans;
    }
};
