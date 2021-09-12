/** 
 * n个元素的数组，值在[1, n]的区间中，数组中有些元素出现2次，其余元素只出现1次，找出出现2次的所有元素
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    int n = nums.size();
    vector<int> res;
    int i = 0;
    // i位置应该放i+1的数
    for (int i = 0; i < n; ++i) {
        if(nums[i] == i + 1) { // 位置已放正确
            continue;
        }
        // -1标记已发现的重复数字
        while (nums[i] != -1 && nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]) {
            swap(nums[nums[i] - 1], nums[i]);
        }
        if (nums[i] != -1 && nums[i] != i + 1) { // 说明nums[nums[i] - 1] == nums[i],重复了
            res.push_back(nums[i]);
            nums[i] = -1; 
        }
    }

    for (int& num : res) {
        cout << num << endl;
    }
}