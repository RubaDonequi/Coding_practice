// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{


	public:
	
	char keypad[4][3] = {{'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'},
                         {'*', '0', '#'}};
                         
	long long getCount(int n)
	{
		// Your code goes here
		if (keypad == NULL || n <= 0)
            return 0;
        if (n == 1)
            return 10;
     
        // odd[i], even[i] arrays represent count of numbers starting
        // with digit i for any length j
        long long odd[10], even[10];
        long long i = 0, j = 0, useOdd = 0, totalCount = 0;
     
        for (i = 0; i <= 9; i++)
            odd[i] = 1; // for j = 1
     
        for (j = 2; j <= n; j++) // Bottom Up calculation from j = 2 to n
        {
            useOdd = 1 - useOdd;
     
            // Here we are explicitly writing lines for each number 0
            // to 9. But it can always be written as DFS on 4X3 grid
            // using row, column array valid moves
            if (useOdd == 1)
            {
                even[0] = odd[0] + odd[8];
                even[1] = odd[1] + odd[2] + odd[4];
                even[2] = odd[2] + odd[1] + odd[3] + odd[5];
                even[3] = odd[3] + odd[2] + odd[6];
                even[4] = odd[4] + odd[1] + odd[5] + odd[7];
                even[5] = odd[5] + odd[2] + odd[4] + odd[8] + odd[6];
                even[6] = odd[6] + odd[3] + odd[5] + odd[9];
                even[7] = odd[7] + odd[4] + odd[8];
                even[8] = odd[8] + odd[0] + odd[5] + odd[7] + odd[9];
                even[9] = odd[9] + odd[6] + odd[8];
            }
            else
            {
                odd[0] = even[0] + even[8];
                odd[1] = even[1] + even[2] + even[4];
                odd[2] = even[2] + even[1] + even[3] + even[5];
                odd[3] = even[3] + even[2] + even[6];
                odd[4] = even[4] + even[1] + even[5] + even[7];
                odd[5] = even[5] + even[2] + even[4] + even[8] + even[6];
                odd[6] = even[6] + even[3] + even[5] + even[9];
                odd[7] = even[7] + even[4] + even[8];
                odd[8] = even[8] + even[0] + even[5] + even[7] + even[9];
                odd[9] = even[9] + even[6] + even[8];
            }
        }
     
        // Get count of all possible numbers of length "n" starting
        // with digit 0, 1, 2, ..., 9
        totalCount = 0;
        if (useOdd == 1)
        {
            for (i = 0; i <= 9; i++)
                totalCount += even[i];
        }
        else
        {
            for (i = 0; i <= 9; i++)
                totalCount += odd[i];
        }
        return totalCount;
	}


};

// { Driver Code Starts.
int main() 
{
   	
   
   	int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

       

	    Solution ob;
	    cout << ob.getCount(n) << "\n";
	     
    }
    return 0;
}
  // } Driver Code Ends