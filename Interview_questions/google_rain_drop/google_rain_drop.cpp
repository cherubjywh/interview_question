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
#include <set>


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
    random::uniform_int_distribution<>dist(1, 1000);
    return (dist(gen) * total_length)/1000 - 0.5;
}

bool is_intersect(double raindrop_start_point, double raindrop_length, double seg_start_point, double seg_end_point) {
    double raindrop_end_point = raindrop_start_point + raindrop_length;
    
    if (seg_end_point >= raindrop_start_point && seg_end_point <= raindrop_end_point) {
        return true;
    }
    
    if (raindrop_end_point >= seg_start_point && raindrop_end_point <= seg_end_point) {
        return true;
    }
    
    return false;
}

void process_dry_segments(map<double, double>& dry_segments, map<double, double>::iterator& iter, double raindrop_start_point, double raindrop_length, map<double, double>& temp, set<double>& temp_erase, double total_length) {
    double left = max(raindrop_start_point, iter -> first);
    double right = min(min(raindrop_start_point + raindrop_length, iter -> second), total_length);

    
    if (left >= iter -> first && right <= iter -> second) {
        temp_erase.insert(iter -> first);
        temp[iter -> first] = left;
        temp[right] = iter -> second;
        return;
    }
    
    if (left >= iter -> first) {
        temp_erase.insert(iter -> first);
        dry_segments[iter -> first] = raindrop_start_point;
        return;
    }
    
    temp_erase.insert(iter -> first);
    temp[raindrop_start_point + raindrop_length] = iter -> second;
    
}

void raindrop_simulation(double raindrop_length, double total_length, random::mt19937& gen) {
    map<double, double> dry_segments;
    dry_segments.insert(pair<double, double>(0.0, total_length));
    
    size_t iteration = 0;
    while (!dry_segments.empty()) {
        
//        cout << "iter " << iteration << ": " << dry_segments.size() << endl;
        ++iteration;
        
        
        double raindrop_start_point = random_raindrop(gen, total_length);

        
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
         
        auto iter = dry_segments.lower_bound(raindrop_start_point);
        map<double, double> temp;
        set<double> temp_remove;
        
        if (iter != dry_segments.begin())
            --iter;
        
        if (!is_intersect(raindrop_start_point, raindrop_length, iter -> first, iter -> second)) {
            ++iter;
        }
        
        
        for (; iter != dry_segments.end(); ++iter) {
            bool flag_intersect = is_intersect(raindrop_start_point, raindrop_length, iter -> first, iter -> second);
            if (!flag_intersect)
                break;
            
            /*
             case 1: raindrop covers the whole segment, then the whole segment will removed from the map
             case 2: raindrop is fully covered in the segment, then the segment will be divided into two regions
             case 3: raindrop has intersection with the segment, then update the segment size
             */
            
            process_dry_segments(dry_segments, iter, raindrop_start_point, raindrop_length, temp, temp_remove, total_length);
        }
        
        for (auto val:temp_remove) {
            dry_segments.erase(val);
        }
        
        for (auto & p:temp) {
            if (p.first == p.second)
                continue;
            dry_segments[p.first] = p.second;
         
        }
        
        if (iteration % 10 == 0)
            cout << "==============================" << endl;
        
        cout << iteration << ": " << raindrop_start_point << endl;
        for (auto& s : dry_segments) {
            cout << s.first << "--" << s.second << " ";
        }
        cout << endl;
        
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
    
    raindrop_simulation(1, 10, gen);
    return 0;
}
