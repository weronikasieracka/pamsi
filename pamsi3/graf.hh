#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector> 
const int range_p= 50; // zakres liczb w jakim sa losowane wagi krawedzi
const int no_exist=-10;
const int exist=10;
const int infinity = 2147483647;
//klasa krawędzi
using namespace std; 
class Edge
{
public:
    int priority; // waga krawedzi
    int vertex_begin; //wierzcholek poczatkowy
    int vertex_end; //wierzcholek koncowy
    Edge *next;
int get_priority()
{
    return priority;  
} 
int get_vertex_begin()
{ 
    return vertex_begin; 
} 
int get_vertex_end()
{ 
    return vertex_end;
} 
void set_value_priority(int value) 
{
    priority=value;
}
void set_value_vertex_begin(int value) 
{
    vertex_begin=value;
}
void set_value_vertex_end(int value) 
{
    vertex_end=value;
}
void set_rand_priority()
{ 
    priority=rand()%range_p;
} 
void set_rand_vertex_begin(int vertices)
{ 
    vertex_begin=rand()%vertices;
} 
void set_rand_vertex_end(int vertices)
{
     vertex_end=rand()%vertices;
}

    friend ostream& operator<<(ostream& out, const Edge & edge)
    {
        out <<edge.vertex_begin <<"  "<<edge.vertex_end<<"   "<<edge.priority<<"   "<<endl;
        return out;
    }
    bool operator==(const Edge &edge)
    {
        if(this->vertex_begin==edge.vertex_begin && this->vertex_end==edge.vertex_end)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Edge()
    {
        priority=0; 
        vertex_begin=0; 
        vertex_end=0; 
        next=nullptr;
    }
    ~Edge()
    { 
        delete next;
    }
    Edge(int first_, int end_, int priority_edge){
        vertex_begin=first_; 
        vertex_end=end_;
        priority=priority_edge;
        next=nullptr;
    }
    Edge(const Edge & edge){
        vertex_begin=edge.vertex_begin;
        vertex_end=edge.vertex_end;
        priority=edge.priority;
        next=edge.next;
    }

};
class Graph
{
public:    
    int first_ver; // wierzcholek startowy
    int many_edges;    //liczba krawedzi
    int many_vertices;  // liczba wierzcholkow
    vector<shared_ptr<Edge>> edge_list;  //lista krawedzi 
    shared_ptr<Edge> get_edge(int i) 
    {
        return edge_list[i];
    }
    void make_graph(int vertices,int edges,double density); // funkcja generujaca graf w pamieci RAM
    void read_file(string filename); // funkcja odczytujaca graf z pliku
    void save_file(string filename,int vertices,int edges,double density); //dunkcja generujaca graf i zapisujaca go do pliku

};



