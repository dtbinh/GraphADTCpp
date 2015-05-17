#include <unordered_map>
#include <iostream>
#include <set>

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

    void insertEdge(std::string v, std::string w);
};

//02 ;; Return the set of all the vertices of the graph.
std::set<std::string> MyGraph::vertices() const{
    std::set<std::string> export_vertices(set_of_vertices);
    return export_vertices;}

//03 ;; Return the set of all the edges of the graph.
std::set<std::string> MyGraph::edges() const{
    std::set<std::string> export_edges(set_of_edges);
    return export_edges;}

//04 ;; Return the number of vertices currently present in the graph.
int MyGraph::countAllVertices() const {return number_of_nodes; }

//05 ;; Return the number of edges currently present in the graph.
int MyGraph::countAllEdges() const {return number_of_edges; }

//06 ;; Return the edge between vertices v and w;
// An error occurs if there is no such edge.
Edge MyGraph::getEdge(std::string v, std::string w) const{
    Edge save(thegraph.at(v).at(w));
    return save;}

//07 ;; Return the set of the edges incident on vertex v.
std::set<std::string> MyGraph::incidentEdges(std::string v) const{
    std::set<std::string> set_of_incidents;
    if( thegraph.find(v)!= thegraph.end()){
        node_hashmap::const_iterator node_iterator = thegraph.at(v).begin();
        while(node_iterator != thegraph.at(v).end()){
            set_of_incidents.insert(node_iterator->first);
            *node_iterator++;}}
    else
        std::cout<<"ERROR: Invalid node"<<std::endl;
    return set_of_incidents;}

//08 ;; Return the end-vertex of edge e distinct from vertex v
// an error occurs if e is not incident on v.
std::string MyGraph::opposite(std::string u, std::string e) const {
    node_hashmap::const_iterator node_iterator = thegraph.at(u).begin();
    while( node_iterator != thegraph.at(u).end()){
        if( std::strcmp( e.c_str(), thegraph.at(u).at(node_iterator->first).element.c_str() )==0 )
            return (node_iterator->first);
        *node_iterator++;}
    return std::string();}

//09 ;; Return the set of the end vertices of edge e.
std::set<std::string> MyGraph::endVertices(std::string edge) const{
    std::set<std::string> eVertices;
    graph_hashmap::const_iterator graphiter= thegraph.begin();
    while(graphiter != thegraph.end()){
        node_hashmap::const_iterator nodeiter = thegraph.at(graphiter->first).begin();
        while(nodeiter != thegraph.at(graphiter->first).end()){
            if( std::strcmp(thegraph.at(graphiter->first).at(nodeiter->first).edgename.c_str(), edge.c_str()) == 0){
                //std::cout<<"< "<<graphiter->first<<", "<<nodeiter->first<<" >";
                eVertices.insert(graphiter->first);
                eVertices.insert(nodeiter->first);
                return eVertices;}
            *nodeiter++;}
        *graphiter++;}
    return eVertices;}

//10 ;; Test whether vertices v and w are adjacent.
bool MyGraph::areAdjacent(std::string v, std::string w) const{
    if (set_of_vertices.find(v) != set_of_vertices.end() &&
            set_of_vertices.find(w) != set_of_vertices.end()){
        return ( thegraph.at(v).find(w) != thegraph.at(v).end() &&
                thegraph.at(w).find(v) != thegraph.at(w).end());}
    else
        std::cout<<"ERROR: Cannot find either vertex "<<v<<" or "<<w<<std::endl;
        return false;}

//11 ;; Insert a new vertex and
void MyGraph::insertVertex(std::string nodename) {
    if (thegraph.find(nodename) == thegraph.end()){
      //  node_hashmap x;
        thegraph[nodename]= node_hashmap(); //x
        number_of_nodes++;
        set_of_vertices.insert(nodename); }
    else
        std::cout<<"Error: Could not add vertex."<<std::endl;}

//12 ;; Remove vertex v and all its incident edges
void MyGraph::removeVertex(std::string vertexname){
    if ( set_of_vertices.find(vertexname) != set_of_vertices.end()){
        graph_hashmap::const_iterator graphiter = thegraph.begin();
        while (graphiter != thegraph.end()){
            std::string save = thegraph[graphiter->first][vertexname].edgename;
            set_of_edges.erase(save);
            number_of_edges--;
            thegraph[graphiter->first].erase(vertexname);
            *graphiter++;}
        thegraph.erase(vertexname);
        set_of_vertices.erase(vertexname);
        number_of_nodes--;}
    else
        std::cout<<"ERROR: Named vertex "<<vertexname<<" does not exist."<<std::endl;
}

void MyGraph::insertEdge(std::string v, std::string w) {
    this->insertEdge(v,w, std::to_string(this->number_of_edges+1));
}

//;13 ;; Create and insert a new undirected edge with
//end vertices v and w and storing element x and
void MyGraph::insertEdge(std::string v, std::string w, std::string x) {
    if( thegraph.find(v) != thegraph.end() && thegraph.find(w) != thegraph.end()){
        if(thegraph[v].find(w) == thegraph[v].end() && thegraph[w].find(v) == thegraph[w].end()){
            Edge e;
            e.edgename = x;
            e.element = x;
            (thegraph[v])[w]= e;
            (thegraph[w])[v]= e;
            set_of_edges.insert(x);
            number_of_edges++;}
        else
            std::cout<<"ERROR: The edge already exists."<<std::endl;}
    else
        std::cout<<"ERROR: Cannot proceed, one or more vertices don't exist."<<std::endl;}

//14 ;; Remove edge (v, w) and
void MyGraph::removeEdge(std::string v, std::string w) {
    if( thegraph.find(v) != thegraph.end() && thegraph.find(w) != thegraph.end()){
        std::string edge = thegraph[v][w].edgename;
        (thegraph[v]).erase(w);
        (thegraph[w]).erase(v);
        set_of_edges.erase(edge);
        number_of_edges--; }
    else
        std::cout<<"ERROR: Either "<<v<<" or "<<w<<" vertices were not found.";}

//;15 ;; Return the element associated with edge e.
std::string MyGraph::getEdgeElem(std::string edgename) const {
    std::unordered_map<std::string, std::unordered_map<std::string, Edge>>::const_iterator graphiter = thegraph.begin();
    std::string found = "Not found.";
    while(graphiter != thegraph.end()){
        std::unordered_map<std::string, Edge>::const_iterator node_iter = ((*graphiter).second).begin();
        while(node_iter != ((*graphiter).second).end()){
            if( std::strcmp(edgename.c_str(), (node_iter->second).edgename.c_str() ) == 0)
                return (node_iter->second).element;
            *node_iter++;}
        *graphiter++;}
    return found;}

//16 ;; Replace the element stored at edge e with x
void MyGraph::replaceEdgeElem(std::string edge, std::string x){
    std::unordered_map<std::string, std::unordered_map<std::string, Edge>>::const_iterator graphiter = thegraph.begin();
    while(graphiter != thegraph.end()){
        std::unordered_map<std::string, Edge>::const_iterator node_iter = ((*graphiter).second).begin();
        while(node_iter != ((*graphiter).second).end()){
            if( std::strcmp( edge.c_str(), (node_iter->second).edgename.c_str() ) == 0){
                thegraph[graphiter->first][node_iter->first].element= x;
                thegraph[node_iter->first][graphiter->first].element= x;
                return;}
            *node_iter++;}
        *graphiter++;}
    std::cout<<"ERROR: Edge not found.";}

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


/*
 * Copy constructor
 */
MyGraph::MyGraph(const MyGraph& other) {
    graph_hashmap::const_iterator g_iter = other.thegraph.begin();
    while (g_iter != other.thegraph.end()){
        thegraph[g_iter->first]= node_hashmap(g_iter->second);
        *g_iter++;
    }
    set_of_vertices = my_set(other.set_of_vertices);
    set_of_edges = my_set(other.set_of_edges);
    number_of_edges= other.number_of_edges;
    number_of_nodes= other.number_of_nodes;
}


bool MyGraph::isEqual(const MyGraph& graph2) const {
    graph_hashmap::const_iterator g_iter = this->thegraph.begin();
    std::set<std::string> notvisited(graph2.set_of_vertices);
    while(g_iter != thegraph.end()){
        if( graph2.set_of_vertices.find(g_iter->first) == graph2.set_of_vertices.end())
            return false;
        else{
            node_hashmap::const_iterator n_iter = thegraph.at(g_iter->first).begin();
            while (n_iter != thegraph.at(g_iter->first).end() ){// g_iter->second.end();
                Edge thisedge = this->thegraph.at(g_iter->first).at(n_iter->first);
                Edge otheredge = graph2.thegraph.at(g_iter->first).at(n_iter->first);
                if( graph2.set_of_edges.find(n_iter->second.edgename) == graph2.set_of_edges.end())
                    return false;
                else{
                    if ( strcmp(thisedge.edgename.c_str(),
                                otheredge.edgename.c_str())!=0 ||
                         strcmp(otheredge.element.c_str(),
                                thisedge.element.c_str())!=0  )
                        return false;
                }
                *n_iter++;
            }
        }
        notvisited.erase(g_iter->first);
        *g_iter++;
    }
    return (notvisited.size() == 0);
};

int main() {

 /*   typedef std::unordered_map<std::string, std::unordered_map<std::string, std::string>> mygraph;
   // typedef std::unordered_map<std::string, std::string> node_hashmap;

    mygraph numbers;

    node_hashmap t;
    numbers["t"] = t;

    node_hashmap u;
    numbers["u"] = u;

    node_hashmap v;
    numbers["v"] = v;

    node_hashmap w;
    numbers["w"]= w;

    node_hashmap z;
    numbers["z"]= z;

    std::hash<std::string> hashfunc = numbers.hash_function();
    for( mygraph::const_iterator i = numbers.begin(), e = numbers.end() ; i != e ; ++i ) {
       // std::cout << i->first << " -> " << i->second << " (hash = " << hashfunc( i->first ) << ")" << std::endl;
        std::cout<< i->first <<std::endl;
    }
*/
    std::cout<<"GraphADT implementation."<<std::endl;

   /* MyGraph g1;
    printSet(g1.vertices());

    g1.insertVertex("f");
    std::cout<<"Vertices: "<<g1.countAllVertices()<<std::endl;
    printSet(g1.vertices());

    g1.insertVertex("g");
    std::cout<<"Vertices: "<<g1.countAllVertices()<<std::endl;

    printSet(g1.vertices());

    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    g1.insertEdge("f","g","E1");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    g1.insertEdge("f","g","E1");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    printSet(g1.edges());

    g1.removeEdge("f","g");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    printSet(g1.edges());

    g1.insertEdge("f","g","E2");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    printSet(g1.edges());

    std::cout<<g1.getEdgeElem("E1")<<std::endl;
    std::cout<<g1.getEdgeElem("E2")<<std::endl;
    g1.replaceEdgeElem("E2","Ex2");
    std::cout<<g1.getEdgeElem("E2")<<std::endl;


    printSet(g1.edges());
    printSet(g1.vertices());
    g1.removeVertex("f");

    printSet(g1.edges());
    printSet(g1.vertices());

    g1.removeVertex("g");

    g1.insertVertex("v");
    g1.insertVertex("w");
    g1.insertVertex("u");
    g1.insertVertex("z");

    g1.insertEdge("u","v","E2");


    MyGraph g2;
    g2.insertVertex("v");
    g2.insertVertex("z");
    g2.insertVertex("u");
   // g2.insertVertex("u");
    g2.insertEdge("v","u","E2");
    g2.insertVertex("w");


    std::cout<<(g2.isEqual(g1)?"Graphs are identical":"Graphs are different")<<std::endl;

    MyGraph g3(g2);
    std::cout<<(g2.isEqual(g3)?"Graphs are identical":"Graphs are different")<<std::endl;

    printSet(g3.vertices());*/

    //  MyGraph g3,g4;

 //   g4.insertVertex("v");
   // std::cout<<(g3.isEqual(g4)?"Graphs are identical":"Graphs are different")<<std::endl;
   // std::cout<<(g4.isEqual(g3)?"Graphs are identical":"Graphs are different")<<std::endl;



/*
    std::set<std::string> barf = g1.endVertices("E2");
    printSet(barf);
    std::cout<<g1.areAdjacent("u","w")<<std::endl;
    std::cout<<g1.areAdjacent("u","v")<<std::endl;

    Edge catched = g1.getEdge("u","v");

    printEdge(catched);

    printSet(g1.incidentEdges("X"));
    printSet(g1.incidentEdges("v"));

    std::string v = "v";
    std::string e = "E2";

    std::cout<<v<<" is the opposite of "<<g1.opposite(v,e)<<" by "<<e<<std::endl;
*/

    MyGraph gx;
    gx.insertVertex("1");
    gx.insertVertex("2");
    gx.insertVertex("3");
    gx.insertVertex("4");
    gx.insertVertex("5");
    gx.insertEdge("1","2");
    gx.insertEdge("2","3");
    gx.insertEdge("3","5");
    gx.insertEdge("5","4");
    gx.insertEdge("2","4");

    MyGraph gy;
    gy.insertVertex("3");
    gy.insertVertex("4");
    gy.insertVertex("5");
    gy.insertVertex("6");
    gy.insertEdge("3","5");
    gy.insertEdge("6","4");
    gy.insertEdge("3","4");
    gy.insertEdge("5","6");

    MyGraph gu = gx.graph_intersection(gy);

    printSet(gx.edges());


    return 0;
}

bool MyGraph::emptyGraph() {
    return (number_of_nodes==0);
}

MyGraph MyGraph::graph_intersection(const MyGraph &graph) const {
    MyGraph output;

    return output;
}
