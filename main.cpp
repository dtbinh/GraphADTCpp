#include <unordered_map>
#include <iostream>
#include <set>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>

#include "MyGraph.cpp"


int main(int argc, char *argv[]) {

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

    MyGraph g1;
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

    printSet(g3.vertices());


    MyGraph g5,g4;

    g4.insertVertex("v");
    std::cout<<(g3.isEqual(g4)?"Graphs are identical":"Graphs are different")<<std::endl;
    std::cout<<(g4.isEqual(g3)?"Graphs are identical":"Graphs are different")<<std::endl;




    //my_set barf = g1.endVertices("E2");
  //  printSet(barf);
    std::cout<<g1.areAdjacent("u","w")<<std::endl;
    std::cout<<g1.areAdjacent("u","v")<<std::endl;

    Edge catched = g1.getEdge("u","v");

    printEdge(catched);

    printSet(g1.incidentEdges("X"));
    printSet(g1.incidentEdges("v"));

    std::string v = "v";
    std::string e = "E2";

    std::cout<<v<<" is the opposite of "<<g1.opposite(v,e)<<" by "<<e<<std::endl;


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

    printSet(gx.edges());

    std::cout<<"gx union gy"<<std::endl;
    MyGraph gu = gx.graph_union(gy);
    gu.printGraph();

    std::cout<<"gx intersection gx"<<std::endl;
    gx.graph_intersection(gx).printGraph();

    std::cout<<"gx intersection gy"<<std::endl;
    gx.graph_intersection(gy).printGraph();

    std::cout<<"gy intersection gx"<<std::endl;
    gy.graph_intersection(gx).printGraph();

    std::cout<<"gy intersection gy"<<std::endl;
    gy.graph_intersection(gy).printGraph();



    gx.graph_difference(gy).printGraph();
    gy.graph_difference(gy).printGraph();

    gy.graph_difference(gx).printGraph();
    gx.graph_difference(gx).printGraph();


    std::cout<<"Graph X"<<std::endl;
    gx.printGraph();
    std::cout<<"and it's complement"<<std::endl;
    gx.graph_complement().printGraph();


    std::cout<<"Graph Y"<<std::endl;
    gy.printGraph();
    std::cout<<"and it's complement"<<std::endl;
    gy.graph_complement().printGraph();

    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("GraphADT");
    QSpinBox *spinbox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);

    spinbox->setRange(0,130);
    slider->setRange(0,130);

    QObject::connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));

    spinbox->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout;


    QLabel *label = new QLabel("<h2><i>Test2</i>" "<font color=green> QT!</font></h2>");
    QPushButton *button = new QPushButton("Quit program");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    QTextFormat


    layout->addWidget(spinbox);
    layout->addWidget(slider);
    layout->addWidget(button);
    layout->addWidget(label);

    window->setLayout(layout);

    window->show();

//    button->show();
//    label->show();
    return app.exec();
    //return 0;
}

