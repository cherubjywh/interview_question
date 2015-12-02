//
//  main.cpp
//  alien_language
//
//  Created by Yuyin Sun on 15/11/29.
//  Copyright © 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    string alienOrder(vector<string>& words) {
        
        if (words.empty()) return "";
        
        unordered_map<char, unordered_set<char>> graph;
        
        for (int i = 0; i < words.size() - 1; ++i) {
            add_edge(words[i], words[i + 1], graph);
        }
        
        int F = graph.size() - 1;
        unordered_set<char> not_visited;
        for (auto & e : graph) {
            not_visited.insert(e.first);
        }
        
        unordered_map<char, int> order;
        
        while(!not_visited.empty()) {
            char current_node = *not_visited.begin();
            DFS(current_node, not_visited, graph, F, order);
        }
        
        for (auto & n1 : graph) {
            for (auto & n2 : n1.second) {
                if (order[n1.first] > order[n2]) return "";
            }
        }
        
        string ret(graph.size(), '0');
        for (auto &i : order) {
            ret[i.second] = i.first;
        }
        
        return ret;
        
    }
    
private:
    
    void DFS(char current_node, unordered_set<char>& not_visited, unordered_map<char, unordered_set<char>>& graph, int & F, unordered_map<char, int>& order) {
        if (not_visited.find(current_node) == not_visited.end()) {
            return;
        }
        
        not_visited.erase(current_node);
        
        for (auto i : graph[current_node]) {
            DFS(i, not_visited, graph, F, order);
        }
        
        order[current_node] = F--;
        
    }
    
    void add_edge(string word1, string word2, unordered_map<char, unordered_set<char>>& graph) {
        for (int i = 0; i < min(word1.size(), word2.size()); ++i) {
            if (word1[i] != word2[i]) {
                
                if (graph.find(word2[i]) == graph.end()) {
                    graph[word2[i]] = unordered_set<char>();
                }
                
                if (graph.find(word1[i]) == graph.end()) {
                    graph[word1[i]] = unordered_set<char>();
                }
                graph[word1[i]].insert(word2[i]);
                break;
            }
        }
    }
    
};

int main(int argc, const char * argv[]) {
    
        Solution sl;
    
    
    
    vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    
    cout << sl.alienOrder(words) << endl;
    
    return 0;
}
