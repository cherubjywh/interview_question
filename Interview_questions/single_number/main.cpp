//
//  main.cpp
//  single_number
//
//  Created by Yuyin Sun on 15-11-24.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

void print_bits(int num) {
    vector<int> temp;
    for (int i = 0; i < 32; ++i) {
        temp.push_back(num & 1);
        num = num >> 1;
    }
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        cout << *it;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    
    vector<int> nums = {1, 2, 1, 3, 2, 5};
    
    int n = nums[0];
    
    for (int i = 1; i < nums.size(); ++i) {
        n ^= nums[i];
    }
    
    print_bits(n);
    

    int last_digit = ((n - 1) & n) ^ n;
    print_bits(last_digit);
    

    int a = 0, b = 0;
    for (auto i : nums) {
        if ((i & last_digit) == 0) {
            a ^= i;
        } else {
            b ^= i;
        }
    }
    
    cout << a << " " << b << endl;
    
    return 0;
}
