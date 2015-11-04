//
//  main.cpp
//  leetcode_292_nim_num
//
//  Created by Yuyin Sun on 15-11-3.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

bool canWinNimV1(int n) {
//    1 1 1 0 1 1 1 0
    if (n % 4 == 0) return false;
    else return true;
}

bool canWinNim(int n) {
    if (n == 1) {
        return true;
    }
    if (n == 2) {
        return true;
    }
    if (n == 3) {
        return true;
    }
    
    bool * temp = new bool[n];
    temp[0] = true;
    temp[1] = true;
    temp[2] = true;
    
    
    for (int i = 3; i < n; ++i) {
        temp[i] = !temp[i - 3] || !temp[i - 2] || !temp[i - 1];
    }
    
    bool ret_val = temp[n - 1];
    
    delete[] temp;
    
    return ret_val;

}

int main(int argc, char * argv[]) {
    int count = 0;
    clock_t begin = clock();
    
    for (int i = 1; i <= 100; ++i) {
        if (canWinNimV1(i))
            ++count;
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << count << " " << elapsed_secs << endl;
    
    cout << canWinNim(1348820612) << endl;
}