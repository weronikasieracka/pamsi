#include "list.hh"
using namespace std;
void List::create_list()
{   
    int edge_ = graph->many_edges;
    for (int i = 0; i < edge_; i++)
    {
        Edge *obj=new Edge;
        int vertex_begin=graph->get_edge(i)->get_vertex_begin();
        int vertex_end=graph->get_edge(i)->get_vertex_end();
        int priority=graph->get_edge(i)->get_priority();
        obj->set_value_vertex_begin(vertex_begin);
        obj->set_value_vertex_end(vertex_end);
        obj->set_value_priority(priority);
        obj->next = list[vertex_begin];
        list[vertex_begin] = obj;
    }
}

void List::display_list()
{
    Edge *p;
    int vertices = graph->many_vertices;
    for (int i = 0; i < vertices; i++)
    {
        cout << i <<":";
        p = list[i];
        while(p!=NULL){
            cout << setw(3) << p->get_vertex_end();
            p = p->next;
        }
        cout << endl;
    }
}
bool List::BellmanFord()
{
    int vertices=graph->many_vertices;
    bool info;
    for (int i = 0; i < vertices; i++) 
    { 
        cost[i] = infinity;  //tablice kosztow wypelniamy nieskonczonoscia
        street[i] = -1;     // wypelnienie tablicy -1
    }
    cost[graph->first_ver] = 0; // wierzcholek poczatkowy jako koszt 0;
    for (int i=1; i<vertices; i++)
    {
        info = true;
        for (int  j=0; j<vertices; j++) 
        {
           Edge  *obj=list[j];
             while(obj != nullptr)
             {
                if (cost[obj->get_vertex_end()] > cost[j]+obj->get_priority()) 
                {
                    info = false;
                    cost[obj->get_vertex_end()]=cost[j]+obj->get_priority();
                    street[obj->get_vertex_end()]=j;
                }
                 obj = obj->next;
            }
          }
        

        if (info == true) 
        {
            return true;
        }
    }

    return true;
}
void List::display_BF()
{
    int vertices=graph->many_vertices;
    int t=0;
    int *arr = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ":";
        for (int j= i; j!=-1; j=street[j]) 
                 arr[t++] = j;

        while (t){
            cout << arr[--t] << "  ";
        }
        cout  << " koszt : " << cost[i] << endl;
    }
    delete[] arr;
}
void List::save_BF(string filename)
{
    ofstream file;
    file.open(filename);
    int vertices=graph->many_vertices;
    int t=0;
    int *arr = new int[vertices];
    for (int i = 0; i < vertices; i++)
    {
        file << i << ":";
        for (int j= i; j!=-1; j=street[j]) 
        {
            arr[t++] = j;
        }
        while (t)
        {
            file << arr[--t] << "  ";
        }
        file << " koszt : " << cost[i] << endl;
    }
    delete[] arr;
 
    file.close();
}