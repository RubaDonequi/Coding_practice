# Striver's SWE cheat sheet [💻](https://docs.google.com/document/d/1SM92efk8oDl8nyVw8NHPnbGexTS9W-1gmTEYfEurLWQ/edit)

## Calender 📅

| Tuesday      | Wednesday | Thursday      | Friday | Saturday      | Sunday      | Monday      |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| [1](#day-1)| [2](#day-2)| [3](#day-3)| [4](#day-4)| [5](#day-5)| [6](#day-6)| [7](#day-7)      
| [8](#day-8)| [9](#day-9)| [10](#day-10)| [11](#day-11)| [12](#day-12)| [13](#day-13)| [14](#day-14)      
| [15](#day-15)| [16](#day-16)| [17](#day-17)| [18](#day-18)| [19](#day-19)| [20](#day-20)| [21](#day-21)      
| [22](#day-22)| [23](#day-23)| [24](#day-24)| [25](#day-25)| [26](#day-26)| [27](#day-27)| [28](#day-28)      
| [29](#day-29)| [30](#day-30)  


## Revision 👨🏼‍🎓🐱‍🏍

## [Day 1](#calender)

* Sort an array of 0’s 1’s 2’s without using extra space or sorting algo 

```
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int red, white, blue;
        red = white = blue = 0;
        
        for(auto val : nums)
        {
            if(val == 0) red++;
            else if(val == 1) white++;
            else blue++;
        }
        
        // cout<<red<<" "<<white<<" "<<blue<<endl;
        int i = 0;
        while(red--){
            nums[i] = 0;
            i++;
        }
        while(white--)
        {   
            nums[i] = 1;
            i++; 
        }
        while(blue--){
            nums[i] = 2;
            i++; 
        }
        
        // cout<<red<<" "<<white<<" "<<blue<<endl;

    }
};
```

* Repeat and Missing Number 
```
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long sum = accumulate(nums.begin(), nums.end(), 0);
        return (n*(n+1)/2) - sum;
        
        
    }
};

```
* Merge two sorted Arrays without extra space
```
/*

1. Gap algorithm; T(n) = O(N+M) x log(N+M); S(N) = O(1)
Pseudo code
- insert all elements in one array lets say v1
- take s = M + N, add keep on swapping v1[i + ceil(s/2)] and v1[i] for i : 0 to M+N
- now updated s = ceil(s/2) and do the above again until s > 0

*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i = 0; i<n; i++) 
            nums1[i+m] = nums2[i];

        int s = m + n;
        int tmp = ceil((double)s/2);
        while(tmp)
        {   
            int i = 0;
            while(i + tmp < s)
            {
                if(nums1[i] > nums1[i + tmp]) swap(nums1[i], nums1[i+tmp]);
                i++;
            }
            if(tmp == 1) break;
            tmp = ceil((double)tmp/2);
        }
        
    }
};

/*
2. T(n) = O(M+N), S(N) = O(N+M)
*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        vector<int> v(m + n);
        int i = 0, j = 0, k = 0;
        while(i<m and j<n)
        {   
            v[k++] = (nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
        }
        
        while(i<m) v[k++] = nums1[i++];
        while(j<n) v[k++] = nums2[j++];
        nums1 = v;
        return;
            
    }
};

/*
3. Insertion method T(N) = O(N*M) S(N) = O(1)
*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n == 0) return;
        if(m==0){
            nums1 = nums2;
            return;
        }
        int i = 0, j = 0;
        while(i<m)
        {
            if(nums1[i] <= nums2[j]) i++;
            else{
                swap(nums1[i], nums2[j]);
                int l = j;
                while(l+1<n)
                {    
                    if(nums2[l] > nums2[l+1]) swap(nums2[l], nums2[l+1]); 
                    l++;
                }            
            }
        }
        
        
        for(i = 0; i<n; i++) nums1[i+m] = nums2[i];
        return;
            
    }
};

```
* Kadane's Algorithm

```
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxx, curr_sum;
        maxx = curr_sum = nums[0];
        for(int i = 1; i<nums.size(); i++)
        {
            if(curr_sum <= 0) curr_sum = 0;
            curr_sum += nums[i];
            maxx = max(maxx, curr_sum);
        }
        return maxx;
        
    }
};
```
* Merge Overlapping Intervals
```
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        int minn, maxx;
        sort(intervals.begin(), intervals.end());
        
        int n = intervals.size();
        
        minn = intervals[0][0];
        maxx = intervals[0][1];
        vector<int> tmp;
        for(int i = 1; i<n; i++)
        {
            if(maxx < intervals[i][0])
            {   
                tmp = {minn, maxx};
                ans.push_back(tmp);
                minn = intervals[i][0];
                maxx = intervals[i][1];
            }
            
            else if(maxx >= intervals[i][0]) maxx = max(maxx, intervals[i][1]);
        }
        
        tmp = {minn, maxx};
        ans.push_back(tmp);
        return ans;
        
    }
};
```
* Find the duplicate in an array of N+1 integers. 
```
/* 
    Floyd's rabbit and turtle algorithm     
    T(N) = O(N), S(N) = O(1) 
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), hare = 0, turtle = 0;
        // finding the first collision point
        while(true)
        {
            hare = nums[nums[hare]];
            turtle = nums[turtle];
            
            if(nums[hare] == nums[turtle]) break;
        }
        
        
        // Now we will slow down our hare, position it to start and start travelling 
        // with the same pace as of turtle
        hare = 0;
        while(nums[hare] != nums[turtle])
        {
            turtle = nums[turtle];
            hare = nums[hare];
        }
        
        return nums[hare];
    }
};
```
## [Day 2](#calender)

* Set Matrix Zeroes
```
/*
T(N) = O(N+M), S(N) = O(1)

Idea
====
- Use the first row and col to check whether the entire row or col should become 0 or not
- First, check for all values
- After that traverse from bottom right corner and for each value check whether the top row and col for the corresponding position is 0 or not
- if 0 then make the current element as zero
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        bool flag = false;
        for(int i = 0; i<rows; i++)
        {
            if (matrix[i][0] == 0) flag = true;
            for(int j = 1; j<cols; j++)
                if(matrix[i][j] == 0) matrix[0][j] = matrix[i][0] = 0;
        }
        
        for(int i = rows-1; i>=0; i--)
        {   
            for(int j = cols-1; j>=1; j--)
                if(matrix[0][j] == 0 or matrix[i][0] == 0) matrix[i][j] = 0;   
            if(flag) matrix[i][0] = 0;
        }
    }  
    
};
```
* Pascal triangle
```
/* T(N) = O(N*N) S(N) = O(N*N)*/
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        ans.push_back({1});
        for(int i = 2; i<=numRows; i++)
        {
            vector<int> tmp(i);
            for(int j = 0; j<i; j++)
            {   
                tmp[j] = (j == 0 || j == i-1) ? 1 : ans[i-2][j-1] + ans[i-2][j];
            }
            
            ans.push_back(tmp);
        }
        
        
        return ans;
        
    }
};
```
* Next Permutation
```
/*

T(N) = O(N), S(N) = O(1)
Idea
====
- Start traversing for the end (N-2 position) and find the first element at index i for which A[i] <= A[i+1]. The Save that i value.
- If we didn't get any element then we will simply return the reverse of the array.
- If we have a value then we will again iterate from the back to saved_i and try to find the first index for which A[saved_i] < A[j]. The saved this jth index.
- Swap A[saved_i] and A[saved_j]
- Then reverse A, from i+1 to end or (N-1)th position

*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), i, j;
        for(i = n-2; i>=0; i--)
        {
            if(nums[i] < nums[i+1]) break;
        }
        
        if(i<0)
        {
            reverse(nums.begin(), nums.end());
            return;
        }
        
        for(j=n-1; j>i; j--)
        {
            if(nums[j] > nums[i]) break;
        }
        
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        return;
    }
};

```

* Stock Buy and Sell
```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n == 1) return 0;
        
        int ans = 0;
        for(int i = 1; i<n; i++)
        {
            if(prices[i] > prices[i-1])
            {
                ans = max(ans, prices[i] - prices[i-1]);
                prices[i] = prices[i-1];
            }
        }
        
        return ans;
        
        
    }
};
```

* Rotate Matrix
```
/*
T(N) = O(N*N), S(N) = O(1)

Idea
====
- First rotate the matrix wrt leading diagonal 
- Then, rotate the matrix wrt vertical mid axis
*/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // Rotation wrt leading diagonal
        for(int i = 0; i<n; i++)
            for(int j = 0; j<i; j++)
                if(i!=j) swap(matrix[i][j], matrix[j][i]);
        // Rotation wrt vertical axis
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n/2; j++)
                swap(matrix[i][j], matrix[i][n-1-j]);
        
        return;
    }
};
```

* Inversion count
```
#include <bits/stdc++.h>
using namespace std;


int merge(int arr[], int temp[], int left, int mid, int right)
{
	int i, j, k;
	int inv_count = 0;

	i = left; j = mid; k = left; 
	while ((i <= mid - 1) && (j <= right)) {
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else {
			temp[k++] = arr[j++];
			inv_count = inv_count + (mid - i);
		}
	}
	while (i <= mid - 1) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];
    
	for (i = left; i <= right; i++) arr[i] = temp[i];
	return inv_count;
}

int _mergeSort(int arr[], int temp[], int left, int right)
{
	int mid, inv_count = 0;
	if (right > left) {
		mid = (right + left) / 2;
        
		inv_count += _mergeSort(arr, temp, left, mid);
		inv_count += _mergeSort(arr, temp, mid + 1, right);
		inv_count += merge(arr, temp, left, mid + 1, right);
	}
	return inv_count;
}

int mergeSort(int arr[], int array_size)
{
	int temp[array_size];
	return _mergeSort(arr, temp, 0, array_size - 1);
}

int main()
{
	int arr[] = { 1, 20, 6, 4, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int ans = mergeSort(arr, n);
	cout << " Number of inversions are " << ans;
	return 0;
}
```

## [Day 3](#calender)

* Search in a 2D matrix 
```
/* Binary search approach*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(), cols = matrix[0].size();
        int l = 0, r = rows*cols - 1;
        while(l<=r)
        {   
            int mid = l + (r-l)/2;
            int curr_ele = matrix[mid/cols][mid%cols];
            if(curr_ele == target) return true;
            else if(curr_ele > target) r = mid - 1;
            else l = mid + 1;
        }
        return false;
    }
};
```
* Pow(x, n)
```
/* T(N) = O(log(N) */
class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
	// storing it int long long because n lies between -2**31 to 2**31 - 1
	// if we are making n positive and n == -2**31 then we will get integer overflow error
        long long nn = (n<0) ? -1*n : n; 
        while(nn > 0)
        {
            if(nn&1)
            {
                nn -= 1;
                ans *= x;
            }else{
                x *= x;
                nn /= 2;                
            }            
        }
        
        if(n<0) ans = (double)(1.0)/(double)(ans);
        return ans;
    }
};
```

* Majority element n/2
```
/*
T(N) = O(N), S(N) = O(N)

Idea
====
- We will use Moore's voting algorithm. Below is the implementation
- Intuition: since the required number occurs n/2 times we will always end up with the number via the following steps of the alogrithm
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ele = 0, cnt = 0;
        for(auto i: nums)
        {
            if(cnt == 0) ele = i;
            if(i == ele) cnt++;
            else cnt--;
        }
        
        return ele;
        
        
    }
};
```
* Majority element n/3
```
/*
T(N) = O(N), S(N) = O(1)

Idea
====
- We will ue Boyer Moore Algorithm which is an modification of Moore's algorithm
- Here, since we have to find element has frequency is greater then floor(N/3)
- So, we will have at max 2 elements (at max 2 => 2 is included)
- Thus the procedure is similar as above with little modification like now we will search for 2 elements instead of one
- In the end, we will again check if our answers have the appropriate frequency

*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int num1 = -1, num2 = -1, cnt1 = 0, cnt2 = 0;
        for(auto i: nums)
        {   
            if(num1 == i) cnt1++;
            else if(num2 == i) cnt2++;
            
            else if(cnt2 == 0){ num2 = i; cnt2 = 1; }
            else if(cnt1 == 0){ num1 = i; cnt1 = 1; }
            
            else{ cnt1--; cnt2--; }
        }
        
        int freq = nums.size()/3;
        if(count(nums.begin(), nums.end(), num1) > freq) ans.push_back(num1);
        if(num1 != num2 and count(nums.begin(), nums.end(), num2) > freq) 
            ans.push_back(num2);
        return ans;
    }
};
```

* Unique paths
```
/*Dynamic programming approach*/
class Solution {
public:
    
    int updateAns(int m, int n, int i, int j, vector<vector<int>> &dp)
    {
        if(i>=m or j>=n) return 0;
        if((i == m-1) and (j == n-1)) return 1;
        return dp[i][j] = (dp[i][j] != -1) ? dp[i][j] : updateAns(m, n, i+1, j, dp) + updateAns(m, n, i, j+1, dp);        
    }
    
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));        
        return updateAns(m, n, 0, 0, dp);
    }
};

/* 
- Most optimal approach is to use combinatrics 
- Here total number of directions we can take (m-1) for right and (n-1) for down, thus total is m + n - 2
- Formula used here is C(m+n-2, n-1) + C(m+n-2, m-1)
- Below is the away we optimally caluculate Combination

*/
class Solution {
public:

    int uniquePaths(int m, int n) {
        int N = m + n - 2;
        int r = m - 1;
        double res = 1;
        for(int i = 1; i<=r; i++) res *= (N - r + i)/i;
        return (int)res;
    }
};
```
* Reverse pairs
```

/* T(N) = O(N x log(N), S(N) = O(N) */
class Solution {
public:
    
    int merge(vector<int> &nums, int low, int mid, int high)
    {
        int cnt = 0;
        int j = mid+1;
        for(int i = low; i<=mid; i++)
        {
            while(j<=high and nums[i] > 2LL * nums[j]) j++;
            cnt += (j - (mid + 1));
        }   
        
        vector<int> tmp;
        int left = low, right = mid + 1;
        while(left<=mid and right<=high)
        {
            if(nums[left]<=nums[right]) tmp.push_back(nums[left++]);
            else tmp.push_back(nums[right++]);
        }
        
        while(left<=mid) tmp.push_back(nums[left++]);
        while(right<=high) tmp.push_back(nums[right++]);
        
        for(int i = low; i<=high; i++) nums[i] = tmp[i - low];
        return cnt;
        
    }
    
    int mergeSort(vector<int> &nums, int low, int high)
    {
        if(low>=high) return 0;
        int mid = low + (high - low)/2;
        int inv = mergeSort(nums, low, mid);
        inv += mergeSort(nums, mid+1, high);
        inv += merge(nums, low, mid, high);
        return inv;
    }
    
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};
```

## [Day 4](#calender)
* Two Sum
```
/* T(N) = O(NlogN), S(N) = O(1) */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        int n = nums.size();        
        vector<int> tmp(nums.begin(), nums.end());
        sort(nums.begin(), nums.end());
        int l = 0, r = n-1;
        vector<int> ans;
        while(l<=r)
        {
            int sum = nums[l] + nums[r];
            if(sum == target and l != r) break;
            else if(sum < target) l++;
            else r--;
        }
        
        int save_l;
        for(int i = 0; i<n; i++) if(tmp[i] == nums[l]){ save_l = i; ans.push_back(i); break;}
        for(int i = 0; i<n; i++) if(tmp[i] == nums[r] and save_l != i){ ans.push_back(i); break;}
        
        return ans;
        
        
    }
};
```
* 4Sum
```
/* T(N) = O(N^3), S(N) = O(1)*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        vector<vector<int>> ans;
        int n = nums.size();
        if(n == 0) return ans;
        
        
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        
        for(int i = 0; i<n; i++)
        {    
            for(int j = i+1; j<n; j++)
            {   
                int l = j+1, r = n-1;
                long long two_sum1 = target - nums[i] - nums[j];
                while(l < r)
                {   
                    long long two_sum2 = nums[l] + nums[r];
                    if(two_sum2 < two_sum1) l++;
                    else if(two_sum2 > two_sum1) r--;
                    else{
                        tmp = {nums[i], nums[j], nums[l], nums[r]};
                        ans.push_back(tmp);
                        
                        while(l < r and nums[l] == tmp[2]) ++l;
                        while(l < r and nums[r] == tmp[3]) --r;
                    }
                }
                
                while(j + 1 < n and nums[j+1] == nums[j]) ++j;
            }
            while(i + 1 < n and nums[i+1] == nums[i]) ++i;
        }
        
        return ans;
    }
};
```
* Longest Increasing Subsequence
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> finder;
        for(auto i: nums) finder.insert(i);
        int maxx = 0;
        for(auto i: nums)
        {   
            int cnt = 0;
            if(finder.find(i-1) == finder.end())
            {   
                int tmp = i;
                while(finder.find(tmp++) != finder.end()) cnt++;
                maxx = max(maxx, cnt);
            }
        }
        
        return maxx;
    }
};
```
* Largest subarray with zero sum
```
/* T(N) = O(N), S(N) = O(1) */
class Solution{
    public:
    int maxLen(vector<int>&A, int n)
    {   
        // Your code here
        unordered_map<int, int> finder;
        int sum = 0, ans = 0;
        for(int i = 0; i<n; i++)
        {
            sum += A[i];
            if(sum == 0) ans = i + 1;
            else{ 
                if(finder.find(sum) != finder.end()) ans = max(ans, i - finder[sum]);
                else finder[sum] = i;
            }
        }
        
        return ans;
    }
};
```
* Count number of subarrays with zero xor
```
/* T(N) = O(N) S(N) = O(1) */
int solve(vector<int> &A, int B)
{
	map<int, int> freq;
	int cnt = 0, xorr = 0;
	for(auto i: A)
	{
		xorr = xorr ^ i;
		if(xor == B) cnt++;
		if(freq.find(xorr^B) != freq.end()) cnt += freq[xorr^B];
		
		freq[xorr] += 1;
	}
	return cnt;
}
```
* Longest substring without repeat
```
/* T(N) = O(N) S(N) = O(N) */
![image](https://user-images.githubusercontent.com/56304060/135723727-e2e96cb2-083e-4a44-bece-84c8e02e117a.png)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        int n = s.size(), ans = 0;
        
        vector<int> finder(256, -1); // finder is here a hashSet
        while(right < n)
        {
            if(finder[s[right]] != -1) 
                left = max(finder[s[right]] + 1, left);
            
            finder[s[right]] = right;
            ans = max(right - left + 1, ans);     
            right++;
        }
        
        return ans;
    }
};

```

## [Day 5](#calender)

* Reverse a linked list
```
/* T(N) = O(N), S(N) = O(N) */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        int n = s.size(), ans = 0;
        
        vector<int> finder(256, -1); // finder is here a hashSet
        while(right < n)
        {
            if(finder[s[right]] != -1) 
                left = max(finder[s[right]] + 1, left);
            
            finder[s[right]] = right;
            ans = max(right - left + 1, ans);     
            right++;
        }
        
        return ans;
    }
};
```
* Find the middle element of the linked list
```
/* T(N) = O(N), S(N) = O(1) */

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int n = 0;
        ListNode *tmp = head;
        while(tmp != NULL)
        {
            n++;
            tmp = tmp->next;
        }
        
        
        int mid = n/2;
        tmp = head;
        while(mid--)
        {
            tmp = tmp->next;
        }
        
        return tmp;
        
    }
};
```
* Merge two sorted arrays
```
/* T(N) = O(N), S(N) = O(1) */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL and l2 == NULL) return NULL;
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        
        ListNode* curr;
        if(l1->val < l2->val){
            curr = new ListNode(l1->val);
            l1 = l1->next;
        }else{
            curr = new ListNode(l2->val);
            l2 = l2->next;
        }
        
        ListNode* to_return = curr;
        while(l1 != NULL and l2 != NULL)
        {
            if(l1->val < l2->val)
            {
                curr->next = new ListNode(l1->val);
                l1 = l1->next;
            }
            else{
                curr->next = new ListNode(l2->val);
                l2 = l2->next;
            }            
            curr = curr->next;
        }
        
        
        curr->next = (l1 == NULL) ? l2 : l1;
        return to_return;
        
    }
};
```
* Remove Nth node from the end of a linked list
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int N) {
        ListNode* tmp = head;
        int n = 1;
        while(tmp->next){
            ++n;
            tmp = tmp->next;
        }
        
        if(n==1) return NULL;
        if(n == N)
        {
            head = head->next;
            return head;
        }
        
        cout<<"n "<<n<<endl;
        
        int i = 0;
        tmp = head;
        while(i != n - N - 1)
        {
            tmp = tmp->next;
            i++;
        }
        
        ListNode* tmp2 = tmp->next->next;
        tmp->next = NULL;
        tmp->next = tmp2;
        return head;
        
    }
};
```
* Delete a node in constant time
```
/* T(N) = O(1), S(N) = O(1) */
class Solution {
public:
    void deleteNode(ListNode* node) {
        *node = *node->next;        
        node = NULL;
    }
};
```

* Add two numbers represented in linked list
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0, sum = 0;       

        ListNode* curr = new ListNode(0), *ans;
        ans = curr;
        while(l1 != NULL and l2 != NULL)
        {   
            sum = l1->val + l2->val + carry;
            carry = sum/10; sum %= 10;
            curr->next = new ListNode(sum);
            l1 = l1->next; l2 = l2->next; 
            curr = curr->next;
        }
        
        if(carry>0 or l1!=NULL or l2!= NULL){
            ListNode* tmp = ans;
            while(tmp->next != NULL) tmp = tmp->next;
            
            if(l1 == NULL)
            {
                while(l2 != NULL)
                {   
                    sum = l2->val + carry;
                    carry = sum/10; sum %= 10;
                    tmp->next = new ListNode(sum);
                    tmp = tmp->next;
                    l2 = l2->next;
                }
            }
            else{
                while(l1 != NULL)
                {   
                    sum = l1->val + carry;
                    carry = sum/10; sum %= 10;
                    tmp->next = new ListNode(sum);
                    tmp = tmp->next;
                    l1 = l1->next;
                }
            }
            
            if(carry > 0) tmp->next = new ListNode(carry);
            
        }
        
        return ans->next;
        
    }
};
```

## [Day 6](#calender)
* Intersection point in a linkedlist
```
"""
T(N) = O(N), S(N) = O(1)
 
Definition for singly-linked list.
class ListNode:
     def __init__(self, x):
         self.val = x
         self.next = None
"""
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if(headA == None or headB == None): return NULL;
        startA = headA; startB = headB;
        while(startA != startB):        
            startA = headB if (startA == None) else startA.next
            startB = headA if (startB == None) else startB.next
             
        return startA
        
	
/* T(N) = O(N), S(1) */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == NULL || headB == NULL) return NULL;
        ListNode* startA = headA, *startB = headB;
        while(startA != startB)
        {   
            startA = (startA == NULL) ? headB : startA->next;
            startB = (startB == NULL) ? headA : startB->next;
        }
        
        return startA;
    }
};
        
```

* Linked List Cycle
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL) return false;
        ListNode* hare, *turtle;
        hare = turtle = head;
        
        while(true)
        {
            if(hare->next == NULL or turtle == NULL or hare->next->next == NULL) 
                return false;
            hare = hare->next->next;
            turtle = turtle->next; 
            
            if(hare == turtle) return true;          
                      
        }

    }
};
```
* Reverse a LinkedList in groups of size k. 
```
/* T(N) = O(N), S(N) = O(1) */
/*
Idea:
====
- The idea is to reverse k-1 connections for every group
- Use a dummy node for prev node
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        if(head == NULL || k == 1) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* curr, *next, *prev;
        curr = next = prev = dummy;
        
        int n = 0;
        while(curr->next != NULL)
        {
            n++;
            curr = curr->next;
        }
        
        while(n >= k)
        {
            curr = prev->next;
            next = curr->next;
                
            for(int i = 1; i<k; i++)
            {
                curr->next = next->next;
                next->next = prev->next;
                prev->next = next;
                next = curr->next;               
            }
            
            prev = curr;
            n -= k;        
        }
        
        return dummy->next;
        
        
    }
};
```
* Palindromic Linked list
```
/* T(N) = O(N), S(N) = O(1) */

/*
Idea
====
- Use Flyod's rabbit and turtle algoithm to place the turtle at a that node whose next node is the ending of the 2nd half the palindrome
- The reverse the 2nd half
- Move the rabbit to the head node or Use the head itself and check it with the turtle whether the LL is a palindrome or not
*/
class Solution {
public:
    ListNode* reverse(ListNode* tmp)
    {
        ListNode* curr = NULL;
        while(tmp)
        {
            ListNode* next = tmp->next;
            tmp->next = curr;
            curr = tmp;
            tmp = next;            
        }
        
        return curr;
        
    }
    
    bool isPalindrome(ListNode* head) {
        
        ListNode *turtle, *rabbit;
        turtle = rabbit =  head;
        
        while(rabbit->next != NULL and rabbit->next->next != NULL)
        {
            turtle = turtle->next;
            rabbit = rabbit->next->next;
        }
        
        
        turtle->next = reverse(turtle->next);
        turtle = turtle->next;
        
        while(turtle != NULL)
        {
            if(turtle->val != head->val) return false;
            turtle = turtle->next;
            head = head->next;
        }
        
        return true;        
        
    }
};
```
* Find the starting node of the cycle in a LinkedList
![image](https://user-images.githubusercontent.com/56304060/135771645-5b604c0d-8b4e-4ded-a6c5-82d2ea0b098c.png)
```
/* T(N) = O(N), S(N) = O(1) */
/*
Idea
====
- Use Flyod's turtle and rabbit algorithm to check whether the LL contains a loop
- Stop at collision point and place the rabbit to head node
- Now start moving rabbit and turtle one step at a time, the point where they collide will be our ans
*/

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL || head->next == NULL) return NULL;
        
        ListNode* turtle, *rabbit;
        turtle =  rabbit = head;
        
        while(rabbit->next != NULL and rabbit->next->next != NULL)
        {   
            turtle = turtle->next;
            rabbit = rabbit->next->next;
            if(rabbit == turtle) 
            {
                rabbit = head;
                while(rabbit != turtle)
                {
                    rabbit = rabbit->next;
                    turtle = turtle->next;
                }

                return turtle;
            }           
        }
        
        return NULL;
    }
};

```
* Rotate a LinkedList
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL || head->next == NULL || k == 0)
            return head;
        int cnt = 1;
        ListNode* curr = head;
        while(curr->next != NULL and ++cnt) curr = curr->next;

        curr->next = head;
        k = cnt - (k % cnt);        
        while(k--) curr = curr->next;

        head = curr->next;
        curr->next = NULL;
        
        return head;
        
    }
};
```
* Flatten LinkedList
```
T(N) = O(N), S(N) = O(1)
struct Node{
	int data;
	struct Node * next;
	struct Node * bottom;
	
	Node(int x){
	    data = x;
	    next = NULL;
	    bottom = NULL;
	}
	
};
*/   
    
Node* merge(Node* a, Node* b)
{

    if (a == NULL)
        return b;

    if (b == NULL)
        return a;
 

    Node* result;
 
    if (a->data < b->data)
    {
        result = a;
        result->bottom = merge(a->bottom, b);
    }
 
    else
    {
        result = b;
        result->bottom = merge(a, b->bottom);
    }
    result->next = NULL;
    return result;
}

Node* flatten(Node *root)
{
   // Your code here
    if (root == NULL || root->next == NULL) return root;


    root->next = flatten(root->next);

    root = merge(root, root->next);

    return root;
 
```

## [Day 7](#calender)

* Clone a linkedList
<table>
  <tr align="center">
    <td>Make copies of each node adjacent to them</td>
    <td>Assign the random pointers</td>
    <td>Get the deep copy and retrive the original</td>
    <td>T(N) and S(N)</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/56304060/135890289-929ab59b-a761-4399-88d3-96efb4262fca.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/135890106-dc853c27-fc46-4cab-b2dd-b3ae0eae7dc3.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/135889965-4a455c06-b222-418d-8f12-05c1282676e5.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/135889819-2f74b3f2-2ef4-4759-aa21-d7dd9b7d0434.png" width=500 height=200></td>
  </tr>
 </table>

```
# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
"""

class Solution:
    def copyRandomList(self, head: 'Node') -> 'Node':
        if(head == None):
            return None
        
        # Step 1:  Make copies of nodes adjacent to each node
        start = front = head
        while(start != None):
            front = start.next
            newNode = Node(start.val)
            start.next = newNode
            newNode.next = front
            start = front
        
        # Step 2: Make connections with random pointers
        start = head
        while(start != None):
            if(start.random != None):
                start.next.random = start.random.next
            start = start.next.next
        
        # Step 3: Extract the deep copy and retrieve the original
        start = head
        front = start.next
        to_return = front
        while(True):
            if(front.next == None):
                break
            start_next = front.next
            start.next = start_next
            front.next = start_next.next           
            
            start = start.next
            front = front.next
        
        return to_return

```
* 3SUM
```
/* T(N) = O(N^2), S(N) = O(1) */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;        
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i<n-2; i++)
        {    
            if(i == 0 || (i>0 and nums[i] != nums[i-1]))
            {   
                int l = i + 1, r = n-1;
                int target = 0 - nums[i];
                while(l < r)
                {   
                    int sum = nums[l] + nums[r];
                    if(sum == target)
                    {
                        vector<int> tmp = {nums[i], nums[l], nums[r]};
                        ans.push_back(tmp);
                        
                        while(l<r and nums[l] == nums[l+1]) l++;
                        while(l<r and nums[r] == nums[r-1]) r--;
                        
                        l++; r--;
                    }
                    else if(sum < target) l++;
                    else r--;
                }
            }
        }
        
        return ans;
    }
};
```
* Tapping rain water
```
/* T(N) = O(N), S(N) = O(N) */
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n==0) return 0;
        
        int left[n], right[n];        
        left[0] = height[0]; right[n-1] = height[n-1];
        
        for(int i = 1; i<n; i++)        
            left[i] = max(left[i-1], height[i]);

        for(int i = n-2; i>=0; i--)          
            right[i] = max(right[i+1], height[i]);

        int total_water_content = 0;
        for(int i = 0; i<n; i++)
            total_water_content += min(left[i], right[i]) - height[i];

        return total_water_content;
    }
};
```

* Remove duplicates from a sorted array
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    
    int MAX = 1000;
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return n;
        
        int ptr = nums[0];        
        for(int i = 1; i<n; i++) 
        {
            if(nums[i] == ptr) nums[i] = MAX;
            else ptr = nums[i];
        }
        
        sort(nums.begin(), nums.end());        
        int ans = 0, i = 0;
        while(i<n)
        {
            if(nums[i++] != MAX) ans++;
        }
        return ans;
        
    }
};
```
* Max consecutive ones
```
/* T(N) = O(N), S(N) = O(1) */
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int maxx = 0, sum = 0;
        for(int i = 0; i<n; i++)
        {
            if(nums[i] == 0)
            {
                maxx = max(sum, maxx);
                sum = 0;
                
            }else sum++;
        }
        
        return max(maxx, sum);
    }
};
```
## [Day 8](#calender)
* N meeting in one room
```
/* T(N) = O(N), S(N) = O(N) */
class Solution
{
    public:
    static bool cmp_times(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second < b.second;
    }
    
    int maxMeetings(int start[], int end[], int n)
    {
        vector<pair<int, int>> times;
        for(int i = 0; i<n; i++)
        {
            pair<int,int> tmp = {start[i], end[i]};
            times.push_back(tmp);
        }
        
        sort(times.begin(), times.end(), cmp_times);
        int cnt = 1;
        pair<int, int> curr_meet = times[0];
        for(int i = 1; i<n; i++)
        {
            if(curr_meet.second < times[i].first)
            {
                cnt++;
                curr_meet = times[i];
            }
        }
        
        return cnt;
        
    }
};
```
* Minimum number of platforms required for a railway
```
/* 
T(N) = O(N), S(N) = O(1)

Idea
====
- Sort arrival and departure times in increasing order
- Initially, our answer will be 1
- Use two-pointer approach, one starting at i = 1 index for arrival times and another starting at j = 0 for departure time
- Now, simply check for current instance, how many plaform we require
- lets say if a train's arrival times is less the current departure time then we can say that we require another platform because rest of the will be filled with other trains
- Now, in the opposite case, we will be requiring less than 1 platform than the current number
*/
class Solution{
    public:
    int findPlatform(int arr[], int dep[], int n)
    {
    	sort(arr, arr + n); sort(dep, dep + n);    	
    	int i = 1, j = 0, cnt = 1, maxx = 1;
    	while(i < n)
    	{
    	    if(arr[i] <= dep[j])
    	    {   
    	        cnt++; i++;
    	    }else{
    	        cnt--;
    	        j++;
    	    }    	    
    	    if(cnt > maxx) maxx = cnt;
    	}    	
    	return maxx;    	
    }
};
```
* Maximum Profit in Job Scheduling
```
/*
T(N) = O(N * logN), S(N) = O(N) 
Idea
====
- Use struct/class to create a data type that consist of startTime, endTime and profit
- Use it to store the jobs in an array
- Sort the elements of the array wrt endTime
- Create a look up table to store the maximum profit for each i : 0 to n-1 jobs
- The look up table will store the maximum profit that we got for a particular ending time T
- Now, traverse the jobs and for each index 'i' find the maximum profit we can obtain if we have i jobs
- Use binary search to look for those profits stored between 0 to i-1 indices in the look up table; that are not colliding with the current job startTime
- After each finding the maximum profit update the look up table; it is basically : max(profit w/o adding current job, profit with adding current job)
- The main thing to catch is that when we say 'profit with adding current job', it might happen that we may not get any jobs before the current job to add-on
- That's why, in that case we require to insert the maximum profit we got w/o adding the job in the look up table.
- In the end, return the last element profit from the look up table

class Solution {
public:
    
    struct job{
        int stime, etime, profit; 
        job(int st, int et, int p){
            stime = st; etime = et;
            profit = p;
        }
    };
    
    
    static bool comp(job j1, job j2){
        return j1.etime < j2.etime; 
    }
    
    
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = profit.size();
        vector<job> jobs;
        
        for(int i=0; i<n; i++){
            job jb (startTime[i], endTime[i], profit[i]);
            jobs.push_back(jb);
        }
        
        /* Sort jobs according to their ending time */
        
        sort(jobs.begin(), jobs.end(), comp);
        
        vector<pair<int,int>> dp;       // --> vector of pair {endTime, profit}
        
        dp.push_back({jobs[0].etime, jobs[0].profit});
        
        /* Since jobs vector is sorted by endtime, we can use binary search to find max profit so far */
        
        for(int i=1; i<n; i++){
            
            /* 
                start and end defines the range of binary search as we need to find max profit 
                before the start time of current job
            */
            
            int start = 0, end = i-1;
            int maxProfit = 0;
            
            while(start<=end){
                int mid = start + (end-start)/2;
                
                if(dp[mid].first <= jobs[i].stime){
                    maxProfit = dp[mid].second;
                    start = mid+1;
                }
                else
                    end = mid-1;
            }
            
            /* Max profit =  max (profit including this job, profit with incuding this job so far) */
            
            maxProfit = max({maxProfit+jobs[i].profit, dp.back().second});
            
            dp.push_back({jobs[i].etime, maxProfit});
        }
        
        return dp.back().second;
    }
};

*/
```
* Fractional KnapSack
```
/*
	T(N) = O(N), S(N) = O(1)
*/
class Solution
{
    public:
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        sort(arr, arr + n, [](Item a Item b){
            return (double)a.value/(double)a.weight > (double)b.value/(double)b.weight;
        });
        int i = 0; double ans = 0;
        while(i<n)
        {   
            if(W>=arr[i].weight)
            {
	    	ans += arr[i].value;
                W -= arr[i].weight;
            }else{
                ans += W*(double)arr[i].value/(double)arr[i].weight;
                break;
            }
            i++;
        }
        return ans;
    }        
};

```
* Greedy algorithm to find minimum number of coins
```
/* 

Idea
====
- This is not a coin change dp problem
- Here, the twist is that the coins which we have follows greedy prinicple i.e when we will sort this coins in increasing order we will not find any two consecutive pair sum for which the third consecutive coin is less
- e.g : [1, 2, 5, 10, 20] follows greedy principle where as [1, 5, 6, 9, 10] doesn't (here we will use dp approach)
- In greedy approach, we will set a counter variable to 0 and sort the coins array in decreasing order then we will go to that index for which the current coin amount is less than the target amount
- We will increament target amount by the coin amount and increment counter
*/


#include <bits/stdc++.h>
using namespace std;

int deno[] = { 1, 2, 5, 10, 20, 50, 100, 500, 1000 };
int n = sizeof(deno) / sizeof(deno[0]);

void findMin(int V)
{
	sort(deno, deno + n);
	vector<int> ans;
	for (int i = n - 1; i >= 0; i--)
	{
		while (V >= deno[i]) 
		{
			V -= deno[i];
			ans.push_back(deno[i]);
		}
	}

	// Print result
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}

int main()
{
	int n = 93;
	cout << "Following is minimal number of change for " << n << ": ";
	findMin(n);
	return 0;
}
```
* (Not in List) Coin Change - find the minimum number of coins for getting a target amount
```
/* 

T(N) = O(Target * #Coins), S(N) = O(Target) 

Idea
====
- Idea is to use Recursion/Dynamic Programming
- Set a look up table whose size is equal to target + 1
- Now, for target == 0 we dont need any coins so the answer is 0
- We will fill minimum amount of coins required for a particular amounts from i = 1 to target
- We will traverse over all the coins for the given amount and we will update dp[current_amount] = min(1 + dp[current_amount - current_coin], dp[current_amount])
- We are including dp[current_amount] in the comparision because if we are getting any minimum result for a particular coin, we will save that amount in dp[current_amount] 
*/
class Solution {
public:   
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        vector<int> dp(amount + 1, INT_MAX);
        
        dp[0] = 0;
        for(int i = 1; i<=amount; i++)
            for(auto c : coins) 
                if((i >= c) and (dp[i-c]) != INT_MAX) dp[i] = min(1 + dp[i-c], dp[i]);

        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }
};
```
* Activity Selection (it is same as N meeting in one room) 
```
"""
T(N) = O(N * logN), S(N) = O(N)

Idea
====
- Make a struct(only for C/C++) or class (for OOP languages) for each activity and store them in a array
- Sort them by the end time and store the first value in a variable let's say current_activity
- Set a counter to 1 and traverse the array from i : 1 to #activities - 1
- For each activity check whether they are colliding with current_activity or not
- If not increment the counter and set the current_activity to the ith activity of array 
"""
class Activity:
    def __init__(self, start, end):
        self.start = start
        self.end = end

class Solution:
    def activitySelection(self,n,start,end):
        if(n == 1):
            return 1
        activities = []
        n = len(start)
        for i in range(n):
            activities.append(Activity(start[i], end[i]))
        
        activities = sorted(activities, key = lambda x : x.end)
        
        ans = 1
        curr_activity = activities[0]
        for i in range(1, n):
            if(curr_activity.end < activities[i].start):
                ans += 1
                curr_activity = activities[i]
        
        
        return ans

```

## [Day 9](#calender)
* Subset sums

![image](https://user-images.githubusercontent.com/56304060/136274762-a9bb5d50-2005-4f8f-87a5-ade5579f6746.png)

```
/* 

T(N) = O(2^N), S(N) = O(2^N)

Idea
====
- Idea is to use recursion, for each index we will decide whether to pick that element or not
- PsuedoCode:
	f(i, A, N, sum, sum_array)
	{
		if(i == N)
			sum_array.add(sum)
			return;
		f(i+1, A, N, sum + A[i], sum_array)
		f(i+1, A, N, sum, sum_array)
	}
*/
class Solution
{
public:    
    void update(int i, vector<int> arr, int N, int sum, vector<int> &ans)
    {
        if(i == N)
        {
            ans.push_back(sum);
            return;
        }
        
        update(i+1, arr, N, sum + arr[i], ans);
        update(i+1, arr, N, sum, ans);
    }
    
    vector<int> subsetSums(vector<int> arr, int N)
    {
        // Write Your Code here
        vector<int> ans;
        update(0, arr, N, 0, ans);
        
        sort(ans.begin(), ans.end());
        return ans;
    }
};
```
* Subset-II

![image](https://user-images.githubusercontent.com/56304060/136285093-8c209b17-2ecb-4902-86ec-b1632cebfcb5.png)
```
/*  
T(N) = O(N * 2^N)
S(N) = O(2^K)
Auxillary space = O(N) <- ds vector

Idea
=====
- Sort the array
- Now use recursion, to generate all subsets
- Idea is to use the above algorithm i.e Subset sum algorithm but here we will ignore the already occured ith index for ith length vector
- once we do that we can simply perform the pick and not pick recursive call

*/
class Solution {
    private:
        void updateDS(int idx, vector<int> nums, int n, vector<int> ds, vector<vector<int>> &ans)
        {
            ans.push_back(ds);
            for(int i = idx; i<n; i++)
            {	
	    	// Here, i != idx basically handles the poping out case
		// imagine we have [ 1, 2, 2 ] and we have taken i = 1 position 2 in our recursive call.
		// After the recursive call, we are then poping it out so to avoid using the same 2 at 
		// the i = 1 position we are using this condition
		
                if(i != idx and (nums[i] == nums[i-1])) continue;
                
                ds.push_back(nums[i]);
                updateDS(i + 1, nums, n, ds, ans);
                ds.pop_back();
            }
        }
    
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            vector<vector<int>> ans;
            vector<int> tmp;
            updateDS(0, nums, nums.size(), tmp, ans);
            
            return ans;
        }
};

```
* Combination Sum-I
```
/*
T(N) = O(2^N), S(N) = O(N)

Idea
====
- Idea is to use pick and not pick algorithm 
- Here base conditions we will be if my target < 0 or idx >= len(array) then otherwise if target == 0 then add the current DS/vector inside the ans vector of vector 
*/
class Solution {
    private:
        void update(int idx, vector<int> candidates, vector<int> ds, vector<vector<int>> &ans, int target)
        {   
            if(target < 0 || idx == candidates.size()) return;            
            if(target == 0)
            {
                ans.push_back(ds);
                return;
            } 
            update(idx + 1, candidates, ds, ans, target);

            ds.push_back(candidates[idx]);
            update(idx, candidates, ds, ans, target - candidates[idx]);

        }
    
    
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            vector<vector<int>> ans;
            vector<int> tmp;
            update(0, candidates, tmp, ans, target);
            
            return ans;
        }
};
```
* Combination Sum - II

![image](https://user-images.githubusercontent.com/56304060/136407761-9bf80e61-b50b-4d93-9f56-5992982d834b.png)

```
/*

T(N) = O(K * 2^N), S(N) = O(K)

Idea
====
- Idea is similar to subset sum
*/

class Solution {
    private:
        void update(int idx, vector<int> candidates, vector<int> ds, vector<vector<int>> &ans, int target)
        {
            if(target == 0)
            {
                ans.push_back(ds);
                return;
            }
            
            for(int i = idx; i<candidates.size(); i++)
            {
                if(i > idx and (candidates[i] == candidates[i-1])) continue;
                if(candidates[i] > target) break;
                
                ds.push_back(candidates[i]);
                update(i + 1, candidates, ds, ans, target - candidates[i]);
                ds.pop_back();
            }
        }
    
    
    public:
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
            sort(candidates.begin(), candidates.end());
            vector<int> ds;
            vector<vector<int>> ans;
            update(0, candidates, ds, ans, target);
            
            return ans;
        }
};
```
* Palindrome Partitioning

![image](https://user-images.githubusercontent.com/56304060/136415744-72c23391-88c9-40a4-8fb5-e3f1f04bab3c.png)

```
/* 

T(N) = O(K * 2^N), S(N) = O(N)
Idea
====
- We will start at the 0th position and we will check whether we are getting a palindrome substring by doing a partiton or not
- We will use a loop to do the above step where for every position we will check
- Now, if we are getting a substring which is a palindrome then we will increase our index (initially it will be at 0), add it to a DS and check again
- the above step will be done by recursion and the base cases will be when we are getting index >= len(substring) and also when e are not getting a palindrome
- Now once we reach len(substring) we will backtrack and check for other cases
- We are using the same pick and not pick algorithm

*/
class Solution {
public:
    
    bool isPalindrome(string s, int start, int end)
    {
        while(start <= end)
            if(s[start++] != s[end--]) return false;
        
        return true;
    }
    
    void update(int idx, vector<vector<string>> &ans, vector<string> ds, string s)
    {
        if(idx == s.size())
        {
            ans.push_back(ds);
            return;
        }
        
        for(int i = idx; i<s.size(); i++)
        {
            if(isPalindrome(s, idx, i))
            {
                ds.push_back(s.substr(idx, i - idx + 1));
                update(i + 1, ans, ds, s);
                ds.pop_back();
            }
        }
    }
    
    vector<vector<string>> partition(string s) {
        vector<string> ds;
        vector<vector<string>> ans;
        update(0, ans, ds, s);
        
        return ans;
    }
};

```

* kth permutation

![image](https://user-images.githubusercontent.com/56304060/136451735-a0118d61-0b0f-40a9-a04b-b439d38cd135.png)

```
/*
T(N) = O(N*N), S(N) = O(N)

Idea:
====
- Idea is to apply the "find the index of the word in the dictionary" math problem approach
- We will first find fact = (N-1)!, this will give us the idea which is our first number
- We will also decrement k by 1 because we will generating the permutation wrt 0 based indexing
- then we will delete that number from the array (i.e. [1, 2, ....N]) and we will update the fact and also k
- fact will be fact/len(array) because array length will be reduced after deletion
- also after getting the idea about the first element our search area that is k will be reduce
- we will do this above repeatedly until array is not empty

*/
class Solution {
public:
    string getPermutation(int n, int k) {
        string ans;
        vector<int> v(n);
        int fact = 1;
        for(int i = 1; i<n; i++)
        {
            fact*=i; v[i-1] = i;
        }
        
        v[n-1] = n;
        k -= 1;
        while(true)
        {
            ans += to_string(v[k/fact]);
            v.erase(v.begin() + k/fact);
            
            if(v.size() == 0) break;
            k %= fact;
            fact /= v.size();
        }
        
        return ans;
    }
};
```


## [Day 10](#calender)
* Print all permutation of a sting/array
```
/* 
T(N) = O(N * N!), S(N) = O(N) 

Idea
====
- The idea is similar to pick/not pick algorithm but instead we will swap elements
*/
class Solution {    
    private:
        void update(int idx, vector<int> nums, vector<vector<int>> &ans)
        {
            if(idx == nums.size())
            {
                ans.push_back(nums);
                return;
            }    
            for(int i = idx; i<nums.size(); i++)
            {
                swap(nums[idx], nums[i]);
                update(idx + 1, nums, ans);
            }            
        }
    
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            vector<vector<int>> ans;

            update(0, nums, ans);            
            return ans;
        }
};
```
* N Queen problem

<table>
  <tr align="center">
    <td>Only Direction we have to check</td>
    <td>Simple check for left</td>
    <td>Check for lower diagonal</td>
    <td>Check for upper diagonal</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/56304060/136667757-a13e9bee-e829-4be9-9b1d-940a88006320.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/136667786-e1dd613f-cab8-4914-8230-83f770db1c54.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/136667824-ec419662-9d75-4620-9734-3cf3c5007cbf.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/136667836-6d0c5b12-3285-4e10-a755-9fb06774c2a9.png" width=500 height=200></td>
  </tr>
 </table>


```
/* 

T(N) = O(N!), S(N) = O(N)

*/
void printBoard(vector<string> chess)
{   
    for(auto i:  chess) cout<<"==";
    cout<<"\n";
    for(auto i: chess)
    {
        for(auto j : i)
        {
            cout<<j<<" ";
        }
        cout<<"\n";
    }
    
    for(auto i:  chess) cout<<"==";
    cout<<"\n";
}

class Solution {
    private:        
        void update(int n, int col, vector<vector<string>> &ans, vector<string> board, vector<int> &left, vector<int> &upperDiagonal, vector<int> &lowerDiagonal)
        {
            if(col == n)
            {
                // save ans
                ans.push_back(board);
                return;
            }
            
            for(int row = 0; row<n; row++)
            {
                if(left[row] == 0 and lowerDiagonal[row + col] == 0 and upperDiagonal[n - 1 + col - row] == 0)
                {   
                    board[row][col] = 'Q';
                    left[row] = 1;
                    lowerDiagonal[row + col] = 1;
                    upperDiagonal[n-1+col-row] = 1;
                    
                    update(n, col + 1, ans, board, left, upperDiagonal, lowerDiagonal);
                    
                    left[row] = 0;
                    lowerDiagonal[row + col] = 0;
                    upperDiagonal[n-1+col-row] = 0;
                    board[row][col] = '.';     
                }
            }
            
            return;
        }
    
    public:
        vector<vector<string>> solveNQueens(int n) {
            
            string s(n, '.');
            vector<string> board(n, s);            
            vector<vector<string>> ans;
            
            int placed = 0;
            vector<int> left(n, 0), upperDiagonal(2*n - 1, 0), lowerDiagonal(2*n - 1, 0);
            update(n, 0, ans, board, left, upperDiagonal, lowerDiagonal);
            
            // for(auto i : ans) printBoard(i);
            
            return ans;
        }
};
```
* Sudoko solver
```
class Solution 
{
    public:
    //Function to find a solved Sudoku.
    bool isValid(vector<vector<char>>& board, int row, int col, int ch, int N){
        for(int i =0; i<N; i++){
            if(board[row][i] == ch){
                return false;
            }
            if(board[i][col] == ch){
                return false;
            }
            if(board[N/3*(row/(N/3)) + i/(N/3)][N/3*(col/(N/3)) + i%(N/3)] == ch){
                return false;
            }
        }
        return true;
    }
    bool solve(vector<vector<char>>& board, int i, int j, int N){
        if(i==N) return true;
        if(j==N) return solve(board, i+1, 0, N);
        if(board[i][j] != '.') return solve(board, i, j+1, N);
        
        for(char ch = '1'; ch <='9' ; ch++){
            if(isValid(board,i,j,ch, N)){
                board[i][j] = ch;
                if(solve(board, i, j+1, N)){
                    return true;
                }
                board[i][j] = '.';
            }
        }
        return false;
    }
    
    
    void solveSudoku(vector<vector<char>>& board)  
    { 
        solve(board,0,0,board.size());
    }
    
};

```
* M Coloring problem
```
bool isSafe(int v, bool graph[101][101], int V, int color[], int c)
{
    for(int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i]) 
		return false;             
    return true;
}

bool graphColoringUtil(bool graph[101][101], int m, int V, int color[], int v)
{
     
    /* base case: If all vertices are assigned a color then return true */
    if (v == V)
        return true;
 
    /* Consider this vertex v and try different colors */
    for(int c = 1; c <= m; c++)
    {
         
        /* Check if assignment of color c to v is fine*/
        if (isSafe(v, graph, V, color, c))
        {
            color[v] = c;
 
            /* recur to assign colors to rest of the vertices */
            if (graphColoringUtil(graph, m, V, color, v + 1) == true)
                return true;
 
            /* If assigning color c doesn't lead to a solution then remove it */
            color[v] = 0;
        }
    }
 
    /* If no color can be assigned to this vertex then return false */
    return false;
}


bool graphColoring(bool graph[101][101], int m, int V)
{
    // your code here
    // Initialize all color values as 0.
    // This initialization is needed
    // correct functioning of isSafe()
    int color[V];
    for(int i = 0; i < V; i++)
        color[i] = 0;
 
    // Call graphColoringUtil() for vertex 0
    return graphColoringUtil(graph, m, V, color, 0);

}
```
* Rat in a Maze
```
# Python3 implementation of the above approach
from typing import List

MAX = 5

# Function returns true if the
# move taken is valid else
# it will return false.
def isSafe(row: int, col: int,
		m: List[List[int]], n: int,
		visited: List[List[bool]]) -> bool:

	if (row == -1 or row == n or
		col == -1 or col == n or
		visited[row][col] or m[row][col] == 0):
		return False

	return True

# Function to print all the possible
# paths from (0, 0) to (n-1, n-1).
def printPathUtil(row: int, col: int,
				m: List[List[int]],
				n: int, path: str,
				possiblePaths: List[str],
				visited: List[List[bool]]) -> None:

	# This will check the initial point
	# (i.e. (0, 0)) to start the paths.
	if (row == -1 or row == n or
		col == -1 or col == n or
		visited[row][col] or m[row][col] == 0):
		return

	# If reach the last cell (n-1, n-1)
	# then store the path and return
	if (row == n - 1 and col == n - 1):
		possiblePaths.append(path)
		return

	# Mark the cell as visited
	visited[row][col] = True

	# Try for all the 4 directions (down, left,
	# right, up) in the given order to get the
	# paths in lexicographical order

	# Check if downward move is valid
	if (isSafe(row + 1, col, m, n, visited)):
		path += 'D'
		printPathUtil(row + 1, col, m, n,
					path, possiblePaths, visited)
		path = path[:-1]

	# Check if the left move is valid
	if (isSafe(row, col - 1, m, n, visited)):
		path += 'L'
		printPathUtil(row, col - 1, m, n,
					path, possiblePaths, visited)
		path = path[:-1]

	# Check if the right move is valid
	if (isSafe(row, col + 1, m, n, visited)):
		path += 'R'
		printPathUtil(row, col + 1, m, n,
					path, possiblePaths, visited)
		path = path[:-1]

	# Check if the upper move is valid
	if (isSafe(row - 1, col, m, n, visited)):
		path += 'U'
		printPathUtil(row - 1, col, m, n,
					path, possiblePaths, visited)
		path = path[:-1]

	# Mark the cell as unvisited for
	# other possible paths
	visited[row][col] = False

# Function to store and print
# all the valid paths
def printPath(m: List[List[int]], n: int) -> None:

	# vector to store all the possible paths
	possiblePaths = []
	path = ""
	visited = [[False for _ in range(MAX)]
					for _ in range(n)]
					
	# Call the utility function to
	# find the valid paths
	printPathUtil(0, 0, m, n, path,
				possiblePaths, visited)

	# Print all possible paths
	for i in range(len(possiblePaths)):
		print(possiblePaths[i], end = " ")

# Driver code
if __name__ == "__main__":
	
	m = [ [ 1, 0, 0, 0, 0 ],
		[ 1, 1, 1, 1, 1 ],
		[ 1, 1, 1, 0, 1 ],
		[ 0, 0, 0, 0, 1 ],
		[ 0, 0, 0, 0, 1 ] ]
	n = len(m)
	
	printPath(m, n)

# This code is contributed by sanjeev2552

```
* Word Break
```
class Solution{
public:
    
    unordered_map<string, vector<string>> mp;
    unordered_set<string> word_dict;
    
    vector<string> combine(vector<string> prev, string word)
    {
        for(int i=0; i<prev.size(); ++i)
        {
            prev[i] += " " + word;
        }
        
        return prev;
    }
    
    
    vector<string> wordBreakUtil(string s)
    {
        if(mp.find(s) != mp.end())
        {
            return mp[s];
        }
        
        vector<string> res;
        if(word_dict.find(s) != word_dict.end()) res.push_back(s);
        
        for(int i = 0; i<s.size(); ++i)
        {
            string word = s.substr(i);
            if(word_dict.find(word) != word_dict.end())
            {
                string rem = s.substr(0, i);
                vector<string> prev = combine(wordBreakUtil(rem), word);
                
                res.insert(res.end(), prev.begin(), prev.end());
            }
        }
        
        mp[s] = res;
        return res;
    }
    
    vector<string> wordBreak(int n, vector<string>& dict, string s)
    {   
       mp.clear();
       word_dict.clear();
       word_dict.insert(dict.begin(), dict.end());
       return wordBreakUtil(s);
    }
};
```

## [Day 11](#calender)

* Nth root of a number
```
/*

T(N) = O(logN * logM)

Idea
====
- Use BS to search the Nth root
- Find the Nth power of a number using binary exponention (myPow function in Day-3)

*/
class Solution{
    private:
        double myPow(double x, int n)
        {
            long long nn = (n < 0) ? -1*n : n;
            double ans = 1;
            while(nn > 0)
            {
                if(nn&1)
                {
                    ans *= x; nn--;
                }else{
                    x *= x; nn/=2;
                }
            }
            
            return (n < 0) ? (double)(1.0)/(double)(ans) : ans;
        }
        
	public:
	int NthRoot(int n, int m)
	{
	    // Code here.
	    int l = 1, r = m;
	    while(l<=r)
	    {   
	        int mid = l + (r - l)/2;
	        double val = myPow(mid, n);

	        if(val == m) return mid;
	        else if(val > m) r = mid - 1;
	        else l = mid + 1;
	    }
	    
	    return -1;
	}  
};
```
* Mediam matrix
```
/*	
	MAXX = MAX element in matrix; MINN = MIN element in matrix
	T(N) = O(log(MAX-MIN) * N * log(M))
Idea
=====
- We will find the min and max element in the matrix, the min to max will be our search space
- Now we will apply binary search to find the median in the search space
- For each value we will again apply binary search in all rows to find the no of elements which are smaller than the current potential ans (mid from 1st binary search)
- Idea is that the median will have N*M/2 elements smaller than it

*/

class Solution{   
    private:
        int countSmallerElements(vector<vector<int>> matrix, int mid)
        {
            int cnt = 0;
            int n = matrix.size(), m = matrix[0].size();
            for(int i = 0; i<n; i++)
            {   
                int l = 0, r = m-1;
                while(l<=r)
                {
                    int mid_idx = l + (r-l)/2;
                    if(matrix[i][mid_idx] <= mid) l = mid_idx + 1;
                    else r = mid_idx - 1;
                }
                
                cnt += l;
            }
            
            return cnt;
        }
    
    public:
        int median(vector<vector<int>> &matrix, int rows, int cols){
            int l = INT_MAX, r = INT_MIN;
            for(int i = 0; i<rows; i++)
            {
                l = min(l, matrix[i][0]);
                r = max(r, matrix[i][cols-1]);
            }
            
            
            int half_eles = rows*cols/2;
            while(l<=r)
            {
                int mid = l + (r-l)/2;
                int cnt = countSmallerElements(matrix, mid);
                // cout<<"cnt: "<<cnt<<", mid: "<<mid<<endl;
                if(cnt > half_eles) r = mid - 1;
                else l = mid + 1;
            }
            
            return l;
        }
};
```
* Find the single element in a sorted array where rest all appear exactly twice
```
/*

T(N) = O(logN), S(N) = O(1)

Idea
====
- XOR property:
	=> EvenNo ^ 1 = EvenNo + 1
	=> OddNo ^ 1 = OddNo - 1
- We will use this property and binary search to find out whether the current element is appearing twice or not
- For every index we will check A[mid] == A[mid^1], since A is in sorted order so every twice occuring element will be adjacent
- Now for every index/mid if we apply this property and shift left pointer and right pointer approrpiately, then our left pointer will be our answer
- 

*/

class Solution {    
    public:
        int singleNonDuplicate(vector<int>& nums) {
            int l = 0, r = nums.size()-2;
            while(l<=r)
            {
                int mid = l + (r-l)/2;
                if(nums[mid] == nums[mid^1])
                    l = mid + 1;
                else r = mid - 1;
            }
            
            return nums[l];
        }
};
```
* Search in a rotated array
```
T(N) = O(logN), S(N)=  O(1)

class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int l = 0, r = nums.size()-1;       
        
        while(l <= r)
        {   
            int mid = l + (r-l)/2;
            if(nums[mid] == target) return mid;
            
            // Left half is sorted
            if(nums[l] <= nums[mid])
            {   
                // Check if target lies in the interval or not
                if(target >= nums[l] and target <= nums[mid]) r = mid - 1;
                else l = mid + 1;
            }
            
            // Right half is sorted
            else{
                
                if(target >= nums[mid] and target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            }     
        }     
        
        return -1;
    }
};
```

* Median of 2 Sorted Arrays


<table>
  <tr align="center">
	<td>Partition Logic</td>
  	<td>Binary Search Logic</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/56304060/136844259-038b1601-9194-4453-9b02-c3ac8d42f7e8.png" width=500 height=200></td>
    <td><img src="https://user-images.githubusercontent.com/56304060/136844382-2be9f45e-9f87-42ba-bd80-18bf10b0dac9.png" width=500 height=200></td>
  </tr>
 </table>

```
/* T(N) = O(log(min(N, M)), S(N) = O(1) */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if(n>m) return findMedianSortedArrays(nums2, nums1);
        
        int low = 0, high= n;
        while(low <= high)
        {
            int cut1 = low + (high-low)/2;
            int cut2 = (n + m + 1)/2 - cut1;
            
            int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            
            int r1 = (cut1 == n) ? INT_MAX : nums1[cut1];
            int r2 = (cut2 == m) ? INT_MAX : nums2[cut2];

            if(l1 <= r2 and l2<=r1)
            {
                if ((n + m)&1)
                    return max(l1, l2);
                return (max(l1, l2) + min(r1, r2))/2.0;
            }
            
            // Shifting l1 to the right side
            else if(l1 > r2) high = cut1 - 1;
            
            // Shifting l2 to the right side
            else low = cut1 + 1;   
        }
        
        return 0.0;
        
    }
};
```
* Kth element of two sorted array

```
/* 
T(N) = O(logN + logM), S(N) = O(1) 

Idea
=====
- We take a mid between [L,R] using the formula mid = (L+R)/2.
- Check if the middle can be the kth element using upper_bound() function
- Find the sum of upper_bound() for both the arrays and if the sum is >= K, It’s a possible value of kth element.
- If sum is >= K then we assign R = mid – 1.
- Else if sum <k then the current mid is too small and we assign L = mid+1.
- Repeat from top
- Return the smallest value found.

*/

class Solution{
    public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        long long int l = 1, r = 1e10, ans = 1e10;
        while(l<=r)
        {
            long long int mid = l + (r-l)/2;
            int cnt = upper_bound(arr1,arr1+n, mid) - arr1;
            cnt += upper_bound(arr2, arr2 + m, mid) - arr2;
            
            if(cnt >= k)
            {
                ans = min(ans, mid);
                r = mid - 1;
            }
            else l = mid + 1;
        }
        
        return ans;
    }
};
```
* Minimum allocation number of pages
```
/* T(N) = O(N * logN), S(N) = O(1) */
class Solution {
  public:
    bool isPossible(int arr[], int n, int m, int curr_min)
{
    int studentsRequired = 1;
    int curr_sum = 0;
  
    // iterate over all books
    for (int i = 0; i < n; i++)
    {
        // check if current number of pages are greater than curr_min that means we will get the result after mid no. of pages
        if (arr[i] > curr_min)
            return false;
  
        // count how many students are required to distribute curr_min pages
        if (curr_sum + arr[i] > curr_min)
        {
            // increment student count
            studentsRequired++;
  
            // update curr_sum
            curr_sum = arr[i];
  
            // if students required becomes greater than given no. of students,return false
            if (studentsRequired > m)
                return false;
        }
  
        // else update curr_sum
        else
            curr_sum += arr[i];
    }
    return true;
}
  
// function to find minimum pages
int findPages(int arr[], int n, int m)
{
    long long sum = 0;
  
    // return -1 if no. of books is less than no. of students
    if (n < m)
        return -1;
  
    // Count total number of pages
    for (int i = 0; i < n; i++)
        sum += arr[i];
  
    // initialize start as 0 pages and end as
    // total pages
    int start = 0, end = sum;
    int result = INT_MAX;
  
    // traverse until start <= end
    while (start <= end)
    {
        // check if it is possible to distribute books by using mid as current minimum
        int mid = (start + end) / 2;
        if (isPossible(arr, n, m, mid))
        {
            // if yes then find the minimum distribution
            result = min(result, mid);
  
            // as we are finding minimum and books are sorted so reduce end = mid -1 that means
            end = mid - 1;
        }
  
        else
            // if not possible means pages should be increased so update start = mid + 1
            start = mid + 1;
    }
  
    // at-last return minimum no. of  pages
    return result;
}
};
```
* Aggressive Cows
```
/*
	T(N) = O(N * log N), S(N) = O(1)
	Idea
	=====
	- Sort the array
	- Apply binary search to from l = 1 to A[n-1] - A[0] <- max value possible
	- For every mid value check whether that is a potential answer or not -> linear check

*/

#include <bits/stdc++.h>

using namespace std;

void print(vector<int> v)
{
    for (auto i : v)
        cout << i << " ";
    cout << "\n";
}

bool isOk(vector<int> v, int c, int d)
{
    int lastPlaced = v[0];
    c--;
    for (int i = 1; i < v.size(); i++)
    {
        if ((v[i] - lastPlaced) >= d)
        {
            c--;
            lastPlaced = v[i];
        }

        if (c == 0)
            return true;
    }

    return false;
}

int main()
{
    int tcs;
    cin >> tcs;
    while (tcs--)
    {
        int n, c;
        cin >> n >> c;
        vector<int> v(n);
        for (int i = 0; i < n; i++)
            cin >> v[i];

        sort(v.begin(), v.end());
        // cout << n << " " << c << endl;
        // print(v);

        int l = 1, r = v[v.size() - 1] - v[0];
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            // printf("l : %d, r : %d, mid : %d\n", l, r, mid);
            if (isOk(v, c, mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        cout << ans << endl;
    }
}

```

## [Day 12](#calender)
* Check whether a no is power of 2
```
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return (n<=0) ? 0 : ((n&(n-1)) == 0);   
    }
};
```
* Count total sets bits for every number between 0 to N (included)
```
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1, 0);
        for(int i = 1; i<=n; i++)
            dp[i] = dp[i&(i-1)] + 1;
        return dp;
    }
};
```
* Divide integers w/o division operator
```
class Solution:

    def divide(self, dividend, divisor):
        positive = (dividend < 0) is (divisor < 0)
        dividend, divisor = abs(dividend), abs(divisor)
        res = 0
        while dividend >= divisor:
            temp, i = divisor, 1
            while dividend >= temp:
                dividend -= temp
                res += i
                i <<= 1
                temp <<= 1
        if not positive:
            res = -res
        return min(max(-2147483648, res), 2147483647)
```
* Power Set
```
/*
T(N) = O(N * 2^N), S(N) = O(N)

Idea
====
- Total sets will be 2^N
- We can represent every set as a binary representation of a number from 0 to 2^N - 1
- We can generate sets by using the current binary representation and using another loop for traversing the array elements
- Now for each element we will use its index number to check whether to pick it up or not
*/

class Solution {
public:
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        long total_eles = (1<<n);
        for(int i = 0; i<total_eles; i++)
        {   
            vector<int> tmp;
            for(int j = 0; j<n; j++)
                if((i&(1<<j)) == 0) tmp.push_back(nums[j]);
            
            ans.push_back(tmp);
        }
        
        return ans;
    }
};
```
* Find the MSB in O(1)
```
// CPP program to find MSB number for given n.
#include <iostream>
using namespace std;

int setBitNumber(int n)
{
	// Below steps set bits after
	// MSB (including MSB)

	// Suppose n is 273 (binary
	// is 100010001). It does following
	// 100010001 | 010001000 = 110011001
	n |= n >> 1;

	// This makes sure 4 bits
	// (From MSB and including MSB)
	// are set. It does following
	// 110011001 | 001100110 = 111111111
	n |= n >> 2;

	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;

	// Increment n by 1 so that
	// there is only one set bit
	// which is just before original
	// MSB. n now becomes 1000000000
	n = n + 1;

	// Return original MSB after shifting.
	// n now becomes 100000000
	return (n >> 1);
}

// Driver code
int main()
{
	int n = 273;
	cout << setBitNumber(n);
	return 0;
}

```
* Square of a no. w/o using multiplication and division
```
/*

T(N) = O(logN), S(N) = O(1)

Idea
====
- If n is even, it can be written as
	  n = 2*x 
	  n^2 = (2*x)2 = 4*x^2
- If n is odd, it can be written as 
	  n = 2*x + 1
	  n^2 = (2*x + 1)2 = 4*x^2 + 4*x + 1

*/

// Square of a number using bitwise operators 
#include<iostream> 
using namespace std; 
  
int square(int n) 
{ 
    // Base case 
    if (n==0) return 0; 
  
    // Handle negative number 
    if (n < 0) n = -n; 
  
    // Get floor(n/2) using right shift 
    int x = n>>1; 
  
    // If n is odd 
    if (n&1) 
        return ((square(x)<<2) + (x<<2) + 1); 
    else // If n is even 
        return (square(x)<<2); 
} 

```

## [Day 13](#calender)
```
<-Nothing->
```

## [Day 14](#calender)
```
<-Nothing->
```

## [Day 15](#calender)
```
<-Nothing->
```

## [Day 16](#calender)
```
<-Nothing->
```

## [Day 17](#calender)
```
<-Nothing->
```

## [Day 18](#calender)
```
<-Nothing->
```

## [Day 19](#calender)
```
<-Nothing->
```

## [Day 20](#calender)
```
<-Nothing->
```

## [Day 21](#calender)
```
<-Nothing->
```

## [Day 22](#calender)
```
<-Nothing->
```

## [Day 23](#calender)
```
<-Nothing->
```

## [Day 24](#calender)
```
<-Nothing->
```

## [Day 25](#calender)
```
<-Nothing->
```

## [Day 26](#calender)
```
<-Nothing->
```

## [Day 27](#calender)
```
<-Nothing->
```

## [Day 28](#calender)
```
<-Nothing->
```

## [Day 29](#calender)
```
<-Nothing->
```

## [Day 30](#calender)
```
<-Nothing->
```
