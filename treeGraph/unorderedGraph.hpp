#include<unordered_set>
#include<unordered_map>
#include<string>
#include<list>
#include<utility>

template<typename T>
class unordered_tree{

    std::unordered_set< T > allKeys;
    bool directed;
    std::unordered_map< T, std::list< T > > adjList;

    public:
        bool contains(const T& val);
        // bool contains(const T&& val);

        bool push( const T& parent ,const T& val);
        // bool push( const T& parent ,const T&& val);
        unordered_tree(){}
        unordered_tree(const std::vector< std::pair<T,T> >& edges){
            for(auto &_Edge : edges){
                this->allKeys.insert(_Edge.first);
                this->allKeys.insert(_Edge.second);

                this->adjList.insert({_Edge.first, {}});
                this->adjList[_Edge.first].push_back(_Edge.second);
                if(!this->directed)
                    this->adjList[_Edge.second].push_back(_Edge.first);

            }
        }

};

template<typename T>
bool contains(const _Vertex<T>& val){
    return this->allKeys.find(val) != this->allKeys.end();
}

template<typename T>
bool push(const T& parent, const T& val){
    if(!this->contains(parent)){
        this->allKeys.insert(parent);
    }
    if(!this->contains(val)){
        this->allKeys.insert(val);
    }

    this->adjList[parent].push_back(val);
    if(!this->directed)
        this->adjList[val].push_back(parent);

    return true;

}






























#include<bits/stdc++.h>

using namespace std;

typedef unsigned long ul;
vector<bool> visited;

class graph{

    std::unordered_set< ul > allKeys;
    bool directed;
    std::unordered_map< ul, std::list< ul > > adjList;

    public:
        bool contains(ul val);
        // bool contains(const T&& val);

        bool push(ul parent ,ul val);
        bool canReach();
        bool isConnected();
        // bool push( const T& parent ,const T&& val);
        graph(){}

};

bool graph::contains(ul val){
    return this->allKeys.find(val) != this->allKeys.end();
}

bool graph::push(ul parent, ul val){
    if(!this->contains(parent)){
        this->allKeys.insert(parent);
    }
    if(!this->contains(val)){
        this->allKeys.insert(val);
    }

    this->adjList[parent].push_back(val);
    if(!this->directed)
        this->adjList[val].push_back(parent);

    return true;

}

bool graph::isConnected(){
    return true;
}

bool graph::canReach(unsigned long a, unsigned long b){
    return find(this->adjList[a].begin(), this->adjList[a].end(), b) && find(this->adjList[b].begin(), this->adjList[b].end(), a);
}

int main(){
    graph myGraph;

    unsigned long n, m, a, b, p;
    vector<unsigned long> av , bv;
    auto alwaysUnhappy = true;

    cin>>n>>m;

    visited.reserve(n);
    av.reserve(m);
    bv.reserve(m);

    while(m--){
        cin>>a>>b;
        av.push_back(a);
        bv.push_back(b);
        myGraph.push(a,b);
    }

    cin>>q;

    if(!myGraph.isConnected()){
        alwaysUnhappy = true;
        while(q--)
            cout<<"Unhappy\n";
        return 0;
    }
    while(q--){
        cin>>p;
        myGraph.remove(av[p-1], bv[p-1]);
        if(myGraph.canReach(av[p-1], bv[p-1])){
            cout<<"Happy\n";
        }else
            cout<<"Unhappy\n";
        myGraph.push(av[p-1], bv[p-1]);
    }
    return 0;
}