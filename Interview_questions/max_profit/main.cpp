//
//  main.cpp
//  max_profit
//
//  Created by Yuyin Sun on 15-11-24.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
    
    if (prices.empty()) return 0;
    
    vector<int> buy{-prices[0]};
    vector<int> sell{0};
    vector<int> cool{0};
    vector<int> hold{numeric_limits<int>::min()};
    
    
    for (int i = 1; i < prices.size(); ++i) {
        
        buy.push_back(cool[i-1] - prices[i]);
        sell.push_back(max(buy[i - 1], hold[i-1]) + prices[i]);
        cool.push_back(max(sell[i - 1], cool[i - 1]));
        hold.push_back(max(buy[i - 1], hold[i - 1]));
        
    }
    auto last = buy.size() - 1;
    return max(max(buy[last], sell[last]), max(cool[last], hold[last]));
}


int main(int argc, const char * argv[]) {
    
    vector<int> prices = {1, 2, 3, 0, 2};
    cout << maxProfit(prices) << endl;
    return 0;
}
