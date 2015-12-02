//
//  main.cpp
//  minPath
//
//  Created by Yuyin Sun on 15/12/1.
//  Copyright © 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int minimumTotal(vector<vector<int>>& triangle) {
    
    if (triangle.empty()||triangle[0].empty()) return 0;
    
    if (triangle.size() == 1) return triangle[0][0];
    
    vector<vector<int>> dp(triangle.size(), vector<int>());
    
    dp[0].push_back(triangle[0][0]);
    
    int ret = numeric_limits<int>::max();
    
    for (int i = 1; i < triangle.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            int cand1 = j - 1;
            int cand2 = j;
            
            dp[i].push_back(numeric_limits<int>::max());
            
            if (cand1 >= 0) {
                dp[i][j] = dp[i-1][cand1] + triangle[i][j];
            }
            if (cand2 <= i - 1) {
                dp[i][j] = min(dp[i][j], dp[i-1][cand2] + triangle[i][j]);
            }
            if (i == triangle.size() - 1) {
                ret = min(ret, dp[i][j]);
            }
        }
    }
    
    return ret;
}

int main(int argc, const char * argv[]) {
    
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << minimumTotal(triangle)<< endl;
    
    
    return 0;
}
