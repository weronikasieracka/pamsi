#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include "graf.hh"
class Matrix
{
    public:
    std::shared_ptr<Graph> graph; //graf
    Edge **matrix; // macierz sasiedztwa
    int *matrix_cost;  //tablica kosztow
    int *matrix_street; //tablica drogi dojscia do wierzcholka
    void create_matrix(); // tworzy macierz
    void display_matrix(); // wyswietla macierz  
    bool BellmanFord();  // wykonanie algorytmu 
    void display_BF();  //wyswietla wynik algorytmu
    void save_BF(std::string filename); //zapisuje wynik algorytmu do pliku 
    Matrix(std::shared_ptr<Graph> element)
    { 
        graph=element;
        int vertices =graph->many_vertices;
        matrix = new Edge *[vertices]; 
        for (int i=0; i<vertices; i++){
            matrix[i] = new Edge[vertices]; 
        }
        matrix_cost = new int[vertices]; 
        matrix_street = new int[vertices];
    }
    ~Matrix()
    {
        int vertices =graph->many_vertices;
        for (int i = 0; i < vertices;i++)
        {
            delete [] matrix[i];
        }
        delete [] matrix;
        delete [] matrix_cost;
        delete [] matrix_street;
    }
};