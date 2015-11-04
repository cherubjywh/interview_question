//
//  main.cpp
//  google_rain_drop
//
//  Created by Yuyin Sun on 15-11-3.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <map>


/*
 I don't have time to implement the problem today. I will just write down the problem roughly, and my idea of solving the problem
 
 A hallway: -----------------
 Uniform rain drop, each rain drop will wet x in length
 Decide when the whole hallway is wet
 
 I got this interview question from an undergrad who interviewed with Google
 
 */

using namespace boost;
using namespace std;



double random_raindrop(random::mt19937& gen, double total_length) {
    random::uniform_int_distribution<>dist(1, 100);
    return (dist(gen) * total_length)/100;
}

bool is_intersect(double raindrop_start_point, double raindrop_length, double seg_start_point, double seg_length) {
    double raindrop_end_point = raindrop_start_point + raindrop_length;
    double seg_end_point = seg_start_point + seg_length;
    
    if (seg_end_point >= raindrop_start_point && seg_end_point <= raindrop_end_point) {
        return true;
    }
    
    if (raindrop_end_point >= seg_end_point && raindrop_end_point <= raindrop_end_point) {
        return true;
    }
    
    return false;
}

void raindrop_simulation(double raindrop_length, double total_length, random::mt19937& gen) {
    map<double, double> dry_segments;
    dry_segments.insert(pair<double, double>(0.0, total_length));
    
    while (!dry_segments.empty()) {
        double raindrop_start_point = random_raindrop(gen, total_length);
        map<double, double>::iterator cand_seg = dry_segments.upper_bound(raindrop_start_point);
        /* 
         Here I need to start searching backward, as well as searching forward
         Originally I though about searching just one segment forward and one segment backward. However, it does not guaranteed to work if the raindrop size is too big, and it covers multiple dry segments
         The problem is quite tricky
         The most frequent operation here is lookup, searching next, and searching previous, insertion, and deletion
         Candidate data structures suitable for doing the previous operations include
         i) binary search tree, O(log(n)), O(log(n)), O(log(n)), O(log(n)), O(log(n))
         ii) sorted array, O(log(n)), O(1), O(1), O(n), O(n)
         iii) (double) linked list, O(n), O(1), O(1), O(1), O(1)
         iv) hash table, O(1), N/A, N/A, O(1), O(1)
         
         Such that option iv), i.e. hash table, is definitely not what we want
         Other data structures could be OK. Yet which one is optimal highly depends on different parameters. I can give some high-level intuition about when to use which.
         a) if raindrop size is big, which means search next, search previous could be very frequent operations. Meanwhile, it also means there are many deletions. It could also suggest that n should not be very large, in that case I would use linked list.
         b) if raindrop size is small, it suggests that lookup and insertion will be very frequent. On the other hand, searching next and searching previous would be fairly rare. In this situation, I will use binary search tree rather than linked list.
         c) It should be noted that we cannot use single-linked list. Double-linked list is more suitable here.
         
         */
         
         
         
        
    }
    
}

int main(int argc, const char * argv[]) {

    random::mt19937 gen;
    // Test the boost random number generator
/*
    for (size_t i = 0; i < 10; ++i) {
        cout << random_raindrop(gen, 10.0) << " ";
    }
    cout << endl;
  */
    return 0;
}
