/*
© 2020 Aditya Gupta (aka. Aditya_G15)

Feel free to modify any much portion, or asking me for something newer/better implementing
Since most audience using this might be beginners, much like i was also
This is an ordered graph, and i will be developing further on it mainly... the unordered_map variant is just an option to the user/me
*/

#include<unordered_set>
#include<map>
#include<string>
#include<list>
#include<utility>

template<typename T>
class Graph{

    // T must have operator < overloaded, if it doesn't support less<>

    std::unordered_set< T > allKeys;
    bool directed;
    size_t numEdges = 0;
    std::map< T, std::list< T > > adjList;

    public:
        bool contains(const T& val);
        // bool contains(const T&& val);

        bool push( const T& parent ,const T& val);
        // bool push( const T& parent ,const T&& val);
        Graph(){}
        Graph(const std::vector< std::pair<T,T> >& edges){
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
bool contains(const T& val){
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
