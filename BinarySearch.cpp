#include<iostream>
#include<vector>

using namespace std;

int left_bound_Ropen(vector<int>& nums, int target){
    if(nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size();  // 搜索区间右开
    while(left < right){ //left == right时跳出循环
        int mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid;
        }else if(nums[mid] == target){
            right = mid;
        }
    }
    // target比所有数都小，如果没有以下两句判断，直接返回的left是刚好大于target的数的索引
    // if(left == 0) return -1;
    // return nums[left]==target ? left : -1;
    return left;

}

int left_bound_Rclose(vector<int>& nums, int target){
    if(nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size()-1; // 搜索区间右闭
    while(left <= right){ //left == right + 1时跳出循环
        int mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid - 1;
        }else if(nums[mid] == target){
            right = mid - 1;
        }
    }

    // nums[]中无target
    if(left >= nums.size() || nums[left] != target){
        return -1;
    }
    return left; 

}

int right_bound_Ropen(vector<int>& nums, int target){
    if(nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size();  // 搜索区间右开
    while(left < right){ //left == right时跳出循环
        int mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid;
        }else if(nums[mid] == target){
            left = mid + 1; //必须left = mid+1，收紧左边界，否则当left与right相邻时，mid一直等于left，left一直等于right-1，陷入死循环
        }
    }

    // nums[]中无target，如果没有以下两句判断，直接返回的left-1是刚好小于target的数的索引
    if(left == 0) return -1;
    return nums[left-1]==target ? (left-1) : -1;
    // return left-1;
}

int right_bound_Rclose(vector<int>& nums, int target){
    if(nums.size() == 0) return -1;
    int left = 0;
    int right = nums.size()-1; // 搜索区间右闭
    while(left <= right){ //left == right + 1时跳出循环
        int mid = left + (right - left) / 2;
        if(nums[mid] < target){
            left = mid + 1;
        }else if(nums[mid] > target){
            right = mid - 1;
        }else if(nums[mid] == target){
            left = mid + 1;
        }
    }

    // nums[]中无target
    // if(right < 0 || nums[right] != target){
    //     return -1;
    // }
    return right; 

}

int myLowerBound(vector<int>& nums, int target)
{
	int left = 0;
	int right = nums.size();
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] >= target)
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}
	return left;
}

int myUpperBound(vector<int>& nums, int target)
{
	int left = 0;
	int right = nums.size();
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] <= target)
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}
	return left;
}

int main(){
    int a[8] = {2,2,3,4,5};
    vector<int> nums(a,a+5);
    int target = 1;

    int lbound = left_bound_Ropen(nums, target);
    cout << lbound << endl;

    // int rbound = right_bound_Rclose(nums, target);
    // cout << rbound << endl;

    // int LowerBound = myLowerBound(nums, target);
    // cout << LowerBound << endl;

    // int UpperBound = myUpperBound(nums, target);
    // cout << UpperBound << endl;
    return 0;
}