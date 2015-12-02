//
//  main.cpp
//  bulls_and_cows
//
//  Created by Yuyin Sun on 15-11-23.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

string getHint(string secret, string guess) {
    // unordered_map<int, int> count1, count2;
    // int count_1[10];
    // int count_2[10];
    
    array<int, 10> count_1;
    array<int, 10> count_2;
    fill(count_1.begin(), count_1.end(), 0);
    fill(count_2.begin(), count_2.end(), 0);
    
    int count_A = 0;
    
    for (int i = 0; i < secret.size(); ++i) {
        if (secret[i] == guess[i])
            ++count_A;
        
        count_1[secret[i] - '0']++;
        count_2[guess[i] - '0']++;
    }
    
    int count_B = 0;
    
    for (int i = 0; i < 10; ++i) {
        count_B += min(count_1[i], count_2[i]);
    }
    
    count_B -= count_A;
    
    return to_string(count_A) + "A" + to_string(count_B) + "B";
}

int main(int argc, const char * argv[]) {
    cout << getHint("0", "1") << endl;
    
    return 0;
}
