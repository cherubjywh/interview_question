//
//  BinaryTree.h
//  Interview_questions
//
//  Created by Yuyin Sun on 15-11-2.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#ifndef __Interview_questions__BinaryTree__
#define __Interview_questions__BinaryTree__

#include <iostream>
#include <string>
#include <vector>


template <class T> class TreeNode {
public:
    TreeNode(T v) : left(nullptr), right(nullptr), val(v)
    {
        // do nothing here
    }
    TreeNode(){} // default
    TreeNode* left;
    TreeNode* right;
    T val;
    
    std::string ToString();
    
private:

};


#endif /* defined(__Interview_questions__BinaryTree__) */
