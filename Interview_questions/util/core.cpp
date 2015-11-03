//
//  core.cpp
//  Interview_questions
//
//  Created by Yuyin Sun on 15-11-2.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include "core.h"
#include <cstdlib>
#include <queue>
#include <boost/tokenizer.hpp>


using namespace std;
using namespace boost;

void build_int_tree(string input, TreeNode<int> ** head)
{
    if (input.empty()) {
        *head = nullptr;
    }
    vector<string> tokens;
    parse_string(input, tokens);
    queue<TreeNode<int>*> q;
    *head = new TreeNode<int>(stoi(tokens[0]));
    q.push(*head);
    
    size_t index = 1;
    while (index < tokens.size()) {
        TreeNode<int>* current = q.front();
        q.pop();
        // left node
        if (tokens[index] != "#") {
            current -> left = new TreeNode<int> (stoi(tokens[index]));
            q.push(current -> left);
        }
        ++index;
        if (index >= tokens.size())
            break;
        // right node
        if (tokens[index] != "#") {
            current -> right = new TreeNode<int> (stoi(tokens[index]));
            q.push(current -> right);
        }
        ++index;
    }
}

void parse_string (string input, vector<string> &output)
{
    char_separator<char> sep(",");
    tokenizer<char_separator<char>> tokens(input, sep);
    for (const auto& t : tokens)
    {
        output.push_back(t);
    }
}