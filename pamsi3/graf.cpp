#include "graf.hh"

using namespace std;

/*********************************************************************************************************************************/
/*                 FUNKCJE DO GRAFU                                                                                             */
/*******************************************************************************************************************************/
void Graph::save_file(string filename,int vertices,int edges,double density)
{
	Edge E;
    
    ofstream file;
	file.open(filename);
  
	file << edges << "\t" << vertices << "\t" << 0 << "\n"; // zapis liczby wierzcholkow, liczby krawedzi i wierzcholek poczatkowy jako 0 
    
    int k=1; // do odpowiedniego przyliczania wierzcholków
    int l=0; // do zliczania krawdedzi 
 
    if(density==1){  // lacze kazdy wierzcholek z kazdym
        for(int i=0; i< vertices-k; i++){ 
            l++;

            int vertex1=i; //daj pierwszy wierzcholek
            int vertex2=i+k; //daj drugi wierzcholek
            E.set_rand_priority();             // losuje wage krawedzi
            
            int weight=E.get_priority();

            if(weight==0){
            E.set_rand_priority();
            weight=E.get_priority();
            }
        
            file << vertex1 << "\t" << vertex2 << "\t" << weight << endl;

            if(i==vertices-k-1) { i=-1;  k++; }       
            if(k==vertices) break; 
            if(l==edges) break;  
        }   
    }

    if(density==0.25 || density==0.5 || density==0.75){ //polaczenia pomiedzy wierzcholkami sa losowe
        int **tab=new int*[vertices];
        for (int i=0; i<vertices; i++){
            tab[i] = new int[vertices]; 
        }
               
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                tab[i][j]=exist; //wypelnienie tablicy flaga -> krawedz nie istnieje
            }
        }        
        
        for(int i=0; i<vertices-1; i++){
            int vertex1=i; //losuje pierwszy wierzcholek
            int vertex2=i+1; //losuje drugi wierzcholek
            E.set_rand_priority();
            int weight=E.get_priority();  // przypisuje wage krawedzi 
            
            if(weight==0){
            E.set_rand_priority();
            weight=E.get_priority();
            }

             tab[vertex1][vertex2]=exist;
             file << vertex1 <<"\t" << vertex2 << "\t" << weight << endl;
        }
       
        for(int j=vertices-1; j<edges; j++){ 
            E.set_rand_vertex_end(vertices);
            E.set_rand_vertex_begin(vertices);
            E.set_rand_priority();

            int vertex1=E.get_vertex_begin(); //losuje pierwszy wierzcholek
            int vertex2=E.get_vertex_end(); //losuje drugi wierzcholek
            int weight=E.get_priority();  // losuje wage krawedzi

            if(weight==0){
            E.set_rand_priority();
            weight=E.get_priority();
            }
                //Sprawdzenie czy krawedz wystapila
                if((tab[vertex1][vertex2]==exist) || (vertex1==vertex2)) { j--; continue; }
                if(tab[vertex1][vertex2]==no_exist){
                    tab[vertex1][vertex2]=exist;
                
                    file << vertex1 <<"\t" << vertex2 << "\t" << weight << endl;
                }   
        }
        for (int i = 0; i < vertices;i++){
            delete [] tab[i];
        }
            delete [] tab;    
    }

	file.close();
}

void Graph::read_file(string filename)
{
    ifstream file; // uchwyt do pliku
	file.open(filename); //otwieranie pliku
    string line; // linijka pliku 
   
    int elem1,elem2,elem3;
    
		getline(file, line, '\t'); // zczytanie liczby krawedzi
        many_edges=stoi(line);
  
        getline(file, line, '\t'); // zczytanie liczby wierzcholkow
        many_vertices=stoi(line);
     
        getline(file, line, '\n'); // zczytanie wierzcholka startowego
        first_ver=stoi(line);
   
    for(int i=2; i<many_edges+2;i++ ) // bo liczymy od elementu drugiego jak od zera 
    {
        getline(file,line,'\t'); 
        elem1=stoi(line);
        
        getline(file,line,'\t'); 
        elem2=stoi(line);

        getline(file,line,'\n'); 
        elem3=stoi(line);

        shared_ptr<Edge> elem =make_shared<Edge>(elem1,elem2,elem3);
        edge_list.push_back(elem);
    }

    file.close();
}

void Graph::make_graph(int vertices,int edges,double density)
{
    Edge E;
    many_edges=edges;
    many_vertices=vertices;
    first_ver=0;

    int k=1; // do odpowiedniego przyliczania wierzcholków
    int l=0; // do zliczania krawdedzi 
 
    if(density==1){  // lacze kazdy wierzcholek z kazdym
        for(int i=0; i< vertices-k; i++){ 
            l++;

            int vertex1=i; //daj pierwszy wierzcholek
            int vertex2=i+k; //daj drugi wierzcholek
            E.set_rand_priority();             // losuje wage krawedzi
            
            int weight=E.get_priority();

            if(weight==0){
                E.set_rand_priority();
                weight=E.get_priority();
            }
        
            shared_ptr<Edge> elem =make_shared<Edge>(vertex1,vertex2,weight);
            edge_list.push_back(elem);

            if(i==vertices-k-1) { i=-1;  k++; }       
            if(k==vertices) break; 
            if(l==edges) break;  
     
        }   
    }

    if(density==0.25 || density==0.5 || density==0.75){ //polaczenia pomiedzy wierzcholkami sa losowe
        int **tab=new int*[vertices];
        for (int i=0; i<vertices; i++){
            tab[i] = new int[vertices]; 
        }
               
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                tab[i][j]=no_exist; //wypelnienie tablicy flaga -> krawedz nie istnieje
            }
        }        
        
        for(int i=0; i<vertices-1; i++){
            int vertex1=i; //losuje pierwsz wierzcholek
            int vertex2=i+1; //losuje drugi wierzcholek
            E.set_rand_priority();
            int weight=E.get_priority();  // przypisuje wage krawedzi 
            
            if(weight==0){
            E.set_rand_priority();
            weight=E.get_priority();
            }

             tab[vertex1][vertex2]=exist;
             shared_ptr<Edge> elem=make_shared<Edge>(vertex1,vertex2,weight);
             edge_list.push_back(elem);
        }
       
        for(int j=vertices-1; j<edges; j++){ 
            E.set_rand_vertex_begin(vertices);
            E.set_rand_vertex_end(vertices);
            E.set_rand_priority();

            int vertex1=E.get_vertex_begin(); //losuje pierwsz wierzcholek
            int vertex2=E.get_vertex_end(); //losuje drugi wierzcholek
            int weight=E.get_priority();  // losuje wage krawedzi

            if(weight==0){
            E.set_rand_priority();
            weight=E.get_priority();
            }

                if((tab[vertex1][vertex2]==exist) || (vertex1==vertex2)) { j--; continue; }
                if(tab[vertex1][vertex2]==no_exist){
                    tab[vertex1][vertex2]=exist;
                    
                    shared_ptr<Edge> elem=make_shared<Edge>(vertex1,vertex2,weight);
                    edge_list.push_back(elem);
                }   
        }
      
      for (int i = 0; i < vertices;i++){
        delete [] tab[i];
      }
      delete [] tab;    
    }
}