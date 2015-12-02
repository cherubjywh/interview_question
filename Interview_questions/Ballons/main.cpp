//
//  main.cpp
//  Ballons
//
//  Created by Yuyin Sun on 15/12/1.
//  Copyright © 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void print_matrix(vector<vector<int>>& dp) {
    for (auto & row : dp) {
        for (auto i : row) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int maxCoinsDP(vector<int> &iNums) {
    vector<int> nums(iNums.size() + 2, 0);
    int n = 1;
    for (int x : iNums) if (x > 0) nums[n++] = x;
    nums[0] = nums[n++] = 1;
    
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int k = 2; k < n; ++k) {
        for (int left = 0; left < n - k; ++left) {
            int right = left + k;
            for (int i = left + 1; i < right; ++i) {
                dp[left][right] = max(dp[left][right], nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
            }
//            print_matrix(dp);
        }
    }
    
    print_matrix(dp);
    
    return dp[0][n - 1];
}

int main(int argc, const char * argv[]) {
    
    vector<int> nums = {3, 1, 5, 8};
    maxCoinsDP(nums);
    
    std::cout << "Hello, World!\n";
    return 0;
}
