#include <bits/stdc++.h>
using namespace std;

void reverse(vector<int> &nums, int start, int end)
{
    while (start < end)
    {
        swap(nums[start], nums[end]);
        start++;
        end--;
    }
}
void nextPermutation(vector<int> &nums)
{
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }
    if (i >= 0)
    {
        int j = n - 1;
        while (j >= 0 && nums[j] <= nums[i])
        {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    reverse(nums, i + 1, n - 1);
}

int main()
{
    vector<int> nums = {5,1,3,4,2};
    nextPermutation(nums);
    for (int &x : nums)
    {
        cout << x << ",";
    }

    return 0;
}