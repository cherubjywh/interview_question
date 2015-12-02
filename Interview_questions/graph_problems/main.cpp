//
//  main.cpp
//  graph_problems
//
//  Created by Yuyin Sun on 15/11/28.
//  Copyright (c) 2015年 Yuyin Sun. All rights reserved.
//

#include <iostream>
#include <vector>


using namespace std;


class Graph {
public:
    virtual Graph(int V) = 0;
    virtual Graph(int V, int E) = 0;
    virtual add_edge(int v, int w) = 0;
private:
    virtual ~Graph() = 0;
protected:
    int _V;
    int _E;
    
};

class Graph_edges : public Graph {
public:
    Graph(int V);
    Graph(int V, int E);
    void add_edge(int v, int w);
private:
    vector<pair<int, int>> edges;
};

Graph_edges::Graph(int V) : _V(V), _E(0) {
    
}

Graph_edges::Graph(int V, int E) : _V(V), _E(E) {
    
}

Graph_edges::add_edge(<#int v#>, <#int w#>) {
    edges.push_back(pair<int, int>(v, w));
}

class Graph_adj_matrix : public Graph {
    
};

class Graph_adj_list : public Graph {
    
};

class Graph_adj_set : public Graph {
    
};

int main(int argc, const char * argv[]) {
    return 0;
}
