#include<unordered_set>
#include<unordered_map>
#include<map>
#include<string>
#include<list>
#include<deque>
#include<utility>
#include<any>

typedef long weight_t;

template<typename T>
struct _Vertex{
    private:
        T value;
        _Vertex<T>& parent;    //baap ka pata rhega beto ka nhi ... (*-*;) ☂

    public:
        _Vertex(_Vertex<T>& parent): parent(parent){}
        const T& operator*(){
            return &this->value;
        }
        bool operator<(const _Vertex<T>& n){
            return this->value < n.value;
        }
        bool operator==(const _Vertex<T>& n){
            return this->value == n.value;
        }
        static size_t hash(const _Vertex<T>& n){
            return std::hash(n.value);
        }

        friend class weightedGraph;
};

template<typename T>    //the template type in case of _Edge is the actual data type that _Vertex stores, not the _Vertex<> type itself
struct _Edge{
    const _Vertex<T>& from;   //the nodes can't be edited
    const _Vertex<T>& to;
    mutable weight_t weight;

    _Edge(const _Vertex<T>& from, const _Vertex<T>& to, weight_t weight = 0): 
        from(from),
        to(to),
        weight(weight){}
    bool operator<(const _Edge<T>& e) const{
        if(this->from == e.from)
            return this->weight < e.weight;
        return this->from < e.from;
    }

    friend class weightedGraph;
};

template<typename T>
class weightedGraph{

    // T must have operator < overloaded, if it doesn't support less<>

    typedef T value_type;
    std::unordered_map<std::string, std::any> __temp_graph_data__;

    typedef std::list<T> path_t;
    _Vertex<T> rootNode;
    std::unordered_set< _Vertex<T>, _Vertex<T>::hash > allKeys;
    bool directed;
    size_t numEdges = 0;
    std::map< _Vertex<T>, std::list< std::pair<_Vertex<T>, weight_t> > > adjList;

    public:
        bool contains(const value_type& val);    //takes value type of nodes
        void visitAll() const { return this->dfs(); }
        void dfs() const;
        bool dfs(const _Vertex<T>&, const value_type& val) const;
        bool dfs(const value_type& val) const;

        bool push( const _Vertex<T>& parent ,const _Vertex<T>& val, weight_t weight = 0);
        bool push( const _Edge<T>& e );
        // bool push( const T& parent ,const T&& val);
        weightedGraph(bool isDirected = false) : weightedGraph({},isDirected) {}
        weightedGraph(const std::vector< _Edge<T> >& edges, bool isDirected = false) : directed(isDirected){
            this->__temp_graph_data__["visited"] = vector<bool>();
            std::any_cast< std::vector<bool> >(this->__temp_graph_data__["visited"])

            for(auto &_Edge : edges){
                this->allKeys.insert(_Edge.from);
                this->allKeys.insert(_Edge.to);

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
bool weightedGraph<T>::push( const _Vertex<T>& parent ,const _Vertex<T>& val, weight_t weight = 0){
    return this->push( _Edge<T>(parent, val, weight) );
}

template<typename T>
bool weightedGraph<T>::push( const _Edge<T>& e ){
    if(!this->contains(e.from)){
        this->allKeys.insert(e.from);
    }
    if(!this->contains(e.to)){
        this->allKeys.insert(e.to);
    }

    this->adjList[e.from].push_back({e.to, e.weight});
    if(!this->directed)
        this->adjList[e.to].push_back({e.from, e.weight});

    return true;
}

template<typename T>
void weightedGraph<T>::dfs() const{

}

template<typename T>
bool weightedGraph<T>::dfs(const _Vertex<T>& v, const value_type& val) const{
    std::deque< _Vertex<T> > q;

    for(auto &i: q){
        if(i.value == val)
            return true;
        this->dfs()
    }

    return false;
}

template<typename T>
bool weightedGraph<T>::dfs(const value_type& val) const{
    return this->dfs(this->rootNode, val);
}

    //LEARNT -> We can't use the private typedef for non-member functions
template<typename T>
typename weightedGraph<T>::path_t maxSumPath(){
    
}

template<typename T>
typename weightedGraph<T>::path_t maxWeightPath(){

}