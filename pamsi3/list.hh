#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include "graf.hh"
 class List
 {
    public:
    std::shared_ptr<Graph> graph; //graf 
    Edge **list; //lista sasiedztwa
    int *street; //tablica drogi dojscia do wierzcholka
    int *cost; //tablica kosztow
    void create_list(); // tworzy liste sasiedztwa
    void display_list(); // wyswietla liste sasiedztwa
    bool BellmanFord(); //realizuje algorytm Bellmana-Forda
    void display_BF(); //wyswietla wynik algorytmu
    void save_BF(std::string filename); //zapisuje wynik algorytmu do pliku 
    List(std::shared_ptr<Graph> element)
    { 
        graph=element;
        int vertices =graph->many_vertices;
        list = new Edge *[vertices]; 
        for (int i=0; i<vertices; i++)
        {
            list[i] = nullptr; 
        }
        street = new int[vertices];
        cost = new int[vertices]; 
    }
    ~List()
    {
        int vertices =graph->many_vertices;
        for (int i=0; i<vertices; i++)
        {
            delete list[i];    
        }
         delete [] list;
         delete [] street;
         delete [] cost;
    }
 };