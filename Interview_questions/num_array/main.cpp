//
//  main.cpp
//  num_array
//
//  Created by Yuyin Sun on 15-11-23.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include "../utils.h"
#include <cmath>


class SegmentationTree {
    friend class NumArrayMutable;
public:
    SegmentationTree(int _start, int _end, int _sum):start(_start), end(_end), sum(_sum), left(nullptr), right(nullptr) {}
    SegmentationTree(SegmentationTree* _left, SegmentationTree* _right):left(_left), right(_right), start(_left -> start), end(_right -> end), sum(_left -> sum + _right -> sum) {}
private:
    int start, end, sum;
    SegmentationTree* left, *right;
    
};

class NumArrayMutable {
public:
    NumArrayMutable(vector<int>& nums) {
        
        if (nums.empty()) {
            _root = nullptr;
            return;
        }
        
        vector<vector<SegmentationTree*>> temp(2, vector<SegmentationTree*>());
        int index = 0;
        for (int i = 0; i < nums.size(); ++i) {
            temp[index].push_back(new SegmentationTree(i, i, nums[i]));
        }
        
        
        while (temp[index].size() > 1) {
            index = 1 - index;
            for (int j = 0; j < temp[1 - index].size() - 1; j+=2) {
                temp[index].push_back(new SegmentationTree(temp[1 - index][j], temp[1 - index][j + 1]));
            }
            if (temp[1 - index].size()%2 != 0) {
                temp[index].push_back(temp[1 - index][temp[1 - index].size() - 1]);
            }
            temp[1 - index].clear();
        }
        _root = temp[index][0];
        
    }
    
    void update(int i, int val) {
        int C = 0;
        update_helper(i, val, _root, C);
    }
    
    int sumRange(int i, int j) {
        return sumRange_helper(i, j, _root);
    }
private:
    SegmentationTree *_root = nullptr;
    
    int sumRange_helper(int i, int j, SegmentationTree* root) {
        
        if (root == nullptr) {
            return 0;
        }
        
        if (i > j) return 0;
        
        if (i == root -> start && j == root -> end) return root -> sum;
        
        if (i > root -> end || j < root -> start) {
            return 0;
        }
        
        return sumRange_helper(i, min(j, root -> left -> end), root -> left) + sumRange_helper(max(i, root -> right -> start), j, root -> right);

    }
    
    void update_helper(int i, int val, SegmentationTree* root, int & C) {
        if (root == nullptr) {
            return;
        }
        if (i > root -> end || i < root -> start) {
            return;
        }
        if (root -> left == nullptr && root -> right == nullptr) {
            C = val - root -> sum;
            root -> sum = val;
            return;
        }
        update_helper(i, val, root -> left, C);
        update_helper(i, val, root -> right, C);
        root -> sum += C;
    }
    
};

class NumArray {
public:
    NumArray(vector<int> &nums) {

        dp.push_back(0);
        
        for (int i = 0; i < nums.size(); ++i) {
            dp.push_back(dp[i] + nums[i]);
        }
        
        /*
        dp.resize(nums.size(), vector<int>(nums.size(), 0));
        
        for (int i = 0; i < nums.size(); ++i) {
            dp[i][i] = nums[i];
            for (int j = i + 1; j < nums.size(); ++j) {
                dp[i][j] = dp[i][j - 1] + nums[j];
            }
        }
         */
    }
    
    int sumRange(int i, int j) {
        return dp[j + 1] - dp[i];
    }
private:
    vector<int> dp;
    
};

void test_num_array() {
    vector<int> nums;
    
    Utils::read_vector_from_file("/Users/sunyuyin/Documents/Workspace/CPP/interview_questions/Random_cpp/dp_test_case.txt", nums);
    
    NumArray numArray(nums);
    cout << numArray.sumRange(0, 1) << endl;
    cout << numArray.sumRange(1, 2) << endl;
    cout << numArray.sumRange(0, 800) << endl;
    
    cout << numArray.sumRange(0, 800) << endl;
    
}

void test_num_array_mutable() {
    
    vector<int> nums = {0, 9, 5, 7, 3};
    
//    Utils::read_vector_from_file("/Users/sunyuyin/Documents/Workspace/CPP/interview_questions/Random_cpp/dp_test_case.txt", nums);
    

    
    NumArrayMutable numArray(nums);
    
    cout << numArray.sumRange(4, 4) << endl;
    cout << numArray.sumRange(2, 4) << endl;
    
//    cout << numArray.sumRange(0, 1) << endl;
//    cout << numArray.sumRange(1, 2) << endl;
//    cout << numArray.sumRange(0, 800) << endl;
//    
//    cout << numArray.sumRange(0, 800) << endl;

    
}

int main(int argc, const char * argv[]) {
    
//    test_num_array();
    test_num_array_mutable();
    return 0;
}
