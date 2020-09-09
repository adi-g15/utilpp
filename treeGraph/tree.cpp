#include<iostream>
#include<list>
// #include "./Graph.hpp"
#include "weightedGraph.hpp"

using namespace std;

template<typename T>
class trial{
        typedef std::list<T> myPath;
        public:
            myPath method();
};

template<typename T>
typename trial<T>::myPath method(){
    cout<<"Called"<<endl;
    return {};
}


int main(){
    ios::sync_with_stdio(false);

    weightedGraph<int> g;

    cout<<"Calling"<<endl;
    cout<<"Call Done"<<endl;

    // Graph< int > myTree;
    // myTree.push(0,1);
    // myTree.push(1,0);
    // myTree.push(2,1);
    // myTree.push(0,3);
    // myTree.push(3,4);
    // myTree.push(6,4);

    return 0;
}
