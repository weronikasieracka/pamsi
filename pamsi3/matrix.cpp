#include "matrix.hh"
using namespace std;
void Matrix::create_matrix()

{
    int vertices = graph->many_vertices;
    int edges =graph->many_edges;
    
    for (int i = 0; i < vertices;i++) {
        for (int j = 0; j < vertices; j++) {
            Edge elem;
            elem.set_value_vertex_begin(0);
            elem.set_value_vertex_end(0);
            elem.set_value_priority(0);
            matrix[i][j]=elem; 
        }
    }

    for (int i = 0; i < edges;i++)
    {
        int vertex_start=graph->get_edge(i)->get_vertex_begin();
        int vertex_end=graph->get_edge(i)->get_vertex_end();

        matrix[vertex_start][vertex_end]=(*graph->get_edge(i)); 
    }

}
/*
{
    int vertices = graph->many_vertices;
    int edges =graph->many_edges;
    for (int i = 0; i < vertices;i++) 
    {
        for (int j = 0; j < vertices; j++) 
        {
            Edge element;
            element.set_value_vertex_begin(0);
            element.set_value_vertex_end(0);
            element.set_value_priority(0);
            matrix[i][j]=element; 
        }
    }

    for (int i = 0; i < edges;i++)
    {
        int vertex_begin=graph->get_edge(i)->get_vertex_begin();
        int vertex_end=graph->get_edge(i)->get_vertex_end();
        matrix[vertex_begin][vertex_end]=(*graph->get_edge(i)); 
    }

}*/

void Matrix::display_matrix()
{
    int vertices = graph->many_vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices;j++){
            cout << "    " << matrix[i][j].get_priority();
        }
        cout <<endl;
    }
}
bool Matrix::BellmanFord()
{
    bool info;
    int vertices = graph->many_vertices;
    for (int i = 0; i < vertices; i++) 
    {
        matrix_cost[i] = infinity;    //tablice kosztow wypelniamy nieskonczonoscia
        matrix_street[i] = -1;  //wypelnienie tabic wartoscia -1
    }

    matrix_cost[graph->first_ver] = 0; // wierzcholek poczatkowy jako koszt 0;

    for (int i = 1; i < vertices;i++)
    {
        info = true;
        for (int j=0; j<vertices; j++) 
        {
            for (int g=0; g<vertices; g++) {
                Edge element=matrix[j][g];
                if (element.get_vertex_end()!= 0)
                {
                    if (matrix_cost[element.get_vertex_end()] > matrix_cost[j] + element.get_priority())
                    {
                        info = false;
                        matrix_cost[element.get_vertex_end()] = matrix_cost[j] + element.get_priority();
                        matrix_street[element.get_vertex_end()] = j;
                    }
                }
            }
        }
        if (info == true) 
        {
            return true;
        }
    }

    return true;
}
void Matrix::display_BF()
{
    int vertices=graph->many_vertices;
    int t=0;
    int *arr = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ":";
        for (int j= i; j!=-1; j=matrix_street[j]) 
        {
            arr[t++] = j;
        }

        while (t)
        {
            cout << arr[--t] << "  ";
        }
        cout << " koszt : " << matrix_cost[i] << endl;
    }
    delete[] arr;
}

void Matrix::save_BF(string filename)
{
    ofstream file;
    file.open(filename);
    int vertices=graph->many_vertices;
    int t=0;
    int *arr = new int[vertices];
    for (int i = 0; i < vertices; i++)
    {
        file << i << ":";
        for (int j= i; j!=-1; j=matrix_street[j]) 
        {
            arr[t++] = j;
        }
        while (t)
        {
            file << arr[--t] << "  ";
        }
        file << " koszt : " << matrix_cost[i] << endl;
    }
    delete[] arr;
    file.close();
}