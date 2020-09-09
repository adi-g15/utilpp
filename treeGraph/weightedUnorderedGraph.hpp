#include<unordered_set>
#include<unordered_map>
#include<string>
#include<list>
#include<utility>

template<typename T>
struct _Edge{
    T& from;
    T& to;
    unsigned weight;

    bool operator<(const _Edge& e) const{
        if(this->from == e.from)
            return this->weight < e.weight;
        return this->from < e.from;
    }
};

template<typename T>
class weighted_unordered_tree{

    // T must have operator < overloaded, if it doesn't support less<>

    std::unordered_set< T > allKeys;
    bool directed;
    std::unordered_map< T, std::list< std::pair<T, unsigned> > > adjList;

    public:
        bool contains(const T& val);
        // bool contains(const T&& val);

        bool push( const T& parent ,const T& val);
        // bool push( const T& parent ,const T&& val);
        weighted_unordered_tree(bool isDirected = false) : directed(isDirected){}
        weighted_unordered_tree(const std::vector< _Edge >& edges, bool isDirected = false) : directed(isDirected){
            for(auto &_Edge : edges){
                this->allKeys.insert(_Edge.from);
                this->allKeys.insert(_Edge.to);

                this->adjList.insert({_Edge.from, {}});
                this->adjList[_Edge.from].push_back({_Edge.to, _Edge.weight});
                if(!this->directed)
                    this->adjList[_Edge.to].push_back({_Edge.from, _Edge.weight});

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
