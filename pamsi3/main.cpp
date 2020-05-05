#include <iostream>
#include <time.h>
#include <cmath>
#include "matrix.hh"
#include "list.hh"
using namespace std;
clock_t begin_time,end_time,time_b2,time_e2;
double time1,time2,time_list=0,time_matrix=0;
int main()
{
    srand(time(NULL));
    int many_vertices;
    double density;
    ofstream file;
    int a;
    cout <<"1 - uruchom wersje programu dla testu efektywnosci grafu (wynik zapisuje sie w pliku) "<<endl;
    cout <<"2 - utworzenie listy i macierzy sasiedzta poprzez zapis grafu w pliku i odczytania grafu z tego pliku, oraz wywolanie dla nich algorytmu Bellmana-Forda wraz z zapisem do pliku" <<endl;
    cout <<"Podaj cyfrę czynności:  ";
    cin >> a;
    switch(a)
    {
      case 1:
    cout <<" wykonuje testy ... wyniki zapisuje w pliku " <<endl;
    file.open("test.dat");
    for(int i=0; i<5; i++){
    int vertex[5]={10,50,100,500,1000};
    double d[4]={0.25,0.5,0.75,1};
    many_vertices=vertex[i];
    for(int j=0; j<4;j++){
        density=d[j];
         int  many_edge=0.5*density*many_vertices*(many_vertices-1);
          for(int k=0; k<100; k++){
              shared_ptr<Graph> graph=make_shared<Graph>();

              graph->make_graph(many_vertices,many_edge,density);
                
              Matrix matrix(graph);
              matrix.create_matrix();
            //  matrix.display_matrix();
              begin_time=clock();
              matrix.BellmanFord();
              end_time=clock();
              time1=(double)(end_time-begin_time)/CLOCKS_PER_SEC; 
              time_matrix=time_matrix+time1;
              begin_time=0;
              end_time=0;
              time1=0;

                
              List list(graph);
              list.create_list();
            //  list.display_list();
              time_b2=clock();          
              list.BellmanFord();
              time_e2=clock();
              time2=(double)(time_e2-time_b2)/CLOCKS_PER_SEC;
              time_list=time_list+time2;
              time_b2=0;
              time_e2=0;
              time2=0; 
          
          }
          double time_m_100=time_matrix/100;
          double time_l_100=time_list/100;

         file << "macierz sasiedztwa  liczba wierzcholkow : " << many_vertices << " gestosc: " << density << " czas: " << time_m_100 << " s" <<endl;
         file << "lista sasiedztwa  liczba wierzcholkow : " << many_vertices << " gestosc: " << density << " czas: " << time_l_100 << " s" <<endl;
  

          time_m_100=0;
          time_l_100=0;
    }
  }
  file.close();
  break;
case 2:
    cout << "Graf tworze i zapisuje do pliku graf.txt. Efekt algorytmu Bellmana-Forda dla listy zapisuje sie w pliku result_list.txt.  Efekt algorytmu Bellmana-Forda dla macierzy znajduje sie w pliku result_macierz.txt" <<endl;
    shared_ptr<Graph> graph3=make_shared<Graph>();
    cout << "Wybierz liczbe wierzcholkow : 10, 50, 100, 500, 1000. Wpisz wybrana liczbe :  ";
    cin >>many_vertices;
    cout << "Wybierz gestosc grafu : 0,25 , 0,5, 0,75, 1. Wpisz wybrana liczbe:   ";
    cin >> density;
    int  n_edge=0.5*density*many_vertices*(many_vertices-1);
    graph3->save_file("graf.txt",many_vertices,n_edge,density);
    graph3->read_file("graf.txt");
    List list2(graph3);
    list2.create_list();          
    //list2.displayList();
    bool l;
    l=list2.BellmanFord();
    if(l==true) list2.save_BF("result_list.txt");
    Matrix matrix2(graph3);
    matrix2.create_matrix();          
    //matrix2.displayMatrix();
    bool m;
    m=matrix2.BellmanFord();
    if(m==true) matrix2.save_BF("result_matrix.txt");
break;
}
 return 0;
}