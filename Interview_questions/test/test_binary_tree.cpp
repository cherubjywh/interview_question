//
//  test_binary_tree.cpp
//  Interview_questions
//
//  Created by Yuyin Sun on 15-11-2.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include "core.h"
#include "BinaryTree.h"
#include <iostream>

using namespace std;


BOOST_FIXTURE_TEST_SUITE(BTreeTest, TreeNode<int>)

BOOST_AUTO_TEST_CASE(parseString)
{
    vector<string> tokens;
    parse_string("1,#,2,3", tokens);
    BOOST_CHECK_EQUAL(tokens.size(), 4);

    TreeNode<int>* head;
    build_int_tree("1,#,2,#,3", &head);
    
    BOOST_CHECK_EQUAL(head->val, 1);
//    BOOST_CHECK_EQUAL(head->left, nullptr);
    BOOST_CHECK_EQUAL(head->right->val, 2);
    BOOST_CHECK_EQUAL(head->right->right->val, 3);

}

BOOST_AUTO_TEST_SUITE_END()