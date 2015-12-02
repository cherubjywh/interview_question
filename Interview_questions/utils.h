//
//  utils.h
//  Interview_questions
//
//  Created by Yuyin Sun on 15-11-23.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#ifndef Interview_questions_utils_h
#define Interview_questions_utils_h

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Utils {
public:
    static void read_vector_from_file(const string file_name, vector<int> & A) {
        
        cout << file_name << endl;
        
        ifstream fs(file_name);
        
        string line;
        
        if (!fs.is_open()) {
            exit(-1);
        }
        
        if (!getline(fs, line)) {
            exit(-1);
        }
        
        istringstream ss(line);
        
        string num;
        while (getline(ss, num, ',')) {
            A.push_back(stoi(num));
        }
        
        fs.close();
        
    }
};

#endif
