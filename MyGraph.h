#ifndef GRAPHADTCPP_MYGRAPH_H
#define GRAPHADTCPP_MYGRAPH_H
#endif //GRAPHADTCPP_MYGRAPH_H

//
// Created by Adrianne Diaz on 15-05-17.
//

struct Edge{
    std::string edgename;
    std::string element;
    int weight;
};

typedef std::unordered_map<std::string, Edge> node_hashmap;
typedef std::unordered_map<std::string, node_hashmap> graph_hashmap;
typedef std::set<std::string> my_set;


class MyGraph{
private:
    int number_of_nodes;
    int number_of_edges;
    graph_hashmap thegraph;
    my_set set_of_vertices;
    my_set set_of_edges;
public:
    MyGraph(): number_of_edges(0), number_of_nodes(0) {} //using initialization list
    MyGraph(const MyGraph&);
    my_set vertices() const;
    my_set edges() const;
    int countAllVertices() const;
    int countAllEdges() const;
    Edge getEdge(std::string, std::string) const;
    my_set incidentEdges(std::string v) const;
    std::string opposite(std::string, std::string) const;
    my_set endVertices(std::string edge) const;
    bool areAdjacent(std::string v, std::string w) const;
    void insertVertex(std::string);
    void removeVertex(std::string vertexname);
    void insertEdge(std::string, std::string, std::string);
    void removeEdge(std::string, std::string);
    std::string getEdgeElem (std::string) const;
    void replaceEdgeElem(std::string, std::string);
    bool isEqual(const MyGraph&) const;
    bool emptyGraph();
    MyGraph graph_intersection(const MyGraph&) const;
    MyGraph graph_difference(const MyGraph&) const;
    MyGraph graph_union(const MyGraph&) const;
    void printGraph() const;
    void insertEdge(std::string v, std::string w);
};


//17 Pretty-printing the set.
void printSet(const std::set<std::string>& set){
    int c=0;
    std::cout<<"< ";
    std::set<std::string>::const_iterator setiter = set.begin();
    while( setiter != set.end() ){
        std::cout<<((c++>0)?", ":"")<<*setiter++;}
    std::cout<<" >"<<std::endl;}

void printEdge(const Edge& e){
    std::cout<<"\nEdgename: "<<e.edgename<<"\nElement: "<<e.element<<std::endl;}
