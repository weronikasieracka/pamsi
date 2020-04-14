#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <time.h>
//clock_t time_begin,time_end;
//double time_s;
using namespace std;

template <typename T>
void merge(T tab[], int _begin, int _center, int _end, int j)
{
    int tab_help[_end];
    int i = _begin;
    int k = 0; 
    while (i <= _center && j <= _end) 
	{
		if (tab[j] < tab[i])
		{
			tab_help[k] = tab[j++];
		}
		else
		{
			tab_help[k] = tab[i++];
		}
		k++;
	}
    	if (i <= _center)
	{
		while (i <= _center)
		{
			tab_help[k] = tab[i++];
			k++;
		}
	}
	else
	{
		 while (j <= _end)
		 {
			  tab_help[k] = tab[j];
			  j++;
			  k++;
		 }
	}
	for (i = 0; i <= _end-_begin; i++)
    {
       	tab[_begin+i] = tab_help[i];   
    }

}
template <typename T>
void merge_sort(T tab[], int _begin, int _end)
{
    if (_begin<_end)
	{
		int _center=(_begin+_end)/2;
		merge_sort (tab, _begin, _center);
		merge_sort (tab, _center+1, _end);
		merge (tab, _begin,_center,_end,_center+1);
	}
}


template <typename T>
void quicksort(T tab[], int begin, int end) // sortowanie szybkie
{
    // i, j są indeksami w tabeli
	int i = begin, j = end;
    int pivot = (begin + end) / 2;
    int center=tab[pivot];
    int k;
    // dzielimy tablice na dwie czesci
    while(i<=j)
    {
        while (tab[j] > center) // do momentu, w którym elementy sa wieksze od center 
			j--;
		while (tab[i] < center) // do momentu, w którym elementy sa mniejsze od center
			i++;
        if (i <= j) // zamieniamy miejscami,sprawdzam, czy elementy się nie minęły
        {
            k = tab[i];
			tab[i] = tab[j];
			tab[j] = k;
			i++;
			j--;
        }
    }
    if (begin < j)
    {
        quicksort(tab, begin, j);
    }
    if(i < end)
    {
        quicksort(tab, i, end);
    }
}

template <typename T>
int part(T tab[], int l, int r)
{
	// i, j są indeksami w tabeli
    int i = l;
    int j = r;	
	int k;
	int pivot = (l + r) / 2;
    int center=tab[pivot];
	while (true)
	{
		while (tab[j] > center) // do momentu, w którym elementy sa wieksze od center 
			j--;
		while (tab[i] < center) // do momentu, w którym elementy sa mniejsze od center
			i++;
        if (i <= j) // zamieniamy miejscami,sprawdzam, czy elementy się nie minęły
        {
            k = tab[i];
			tab[i] = tab[j];
			tab[j] = k;
			i++;
			j--;
        }
		else
		{
			return j;
		}
	}

}

template <typename T>
void heapify(T tab[], int k, int i)
{
	int t;
	int largest = i;
	int l = 2*i;
    int r = 2*i + 1;
	if (l < k && tab[l] > tab[largest])
     largest = l;

   if (r < k && tab[r] > tab[largest])
     largest = r;
	 if (largest!=i)
	{
		t=tab[largest];
		tab[largest]=tab[i];
		tab[i]=t;
		heapify(tab, k, largest);
	}
}
template <typename T>
void Build_heap(T *tab, int size)
{
	for (int i=size/2;i>0;i--)
	{
		heapify(tab,size, i);
	}
}
template <typename T>
void sort(T *tab, int size)
{
	int t;
	Build_heap(tab, size);
	for (int i=size;i>1;i--)
	{
		t=tab[i];
		tab[i]=tab[1];
		tab[1]=t;
		size--;
		heapify(tab,size,1);
	}
}
template <typename T>
void insertionsort(T tab[], int begin_, int end_)  
{
	int j;
	int value;
	for (int i=begin_+1; i<=end_; i++)
	{
		value=tab[i];
		j=i;
		while (j>begin_ && tab[j-1]>value) //szukamy indeksu j, w posortowanym podzbiorze 
		{
			tab[j]=tab[j-1];
			j--;
		}

		tab[j]=value;
	}

}

template <typename T>
void introspective_sort (T tab[], int *Begin, int *End, int max_depth)
{
	if ((End-Begin)<16) 
	{
		insertionsort (tab, Begin-tab, End-tab);
	}
	else if (max_depth==0) 
	{
		sort (tab, End - Begin+1);
	}
	else 
	{
		int pivot=part(tab, Begin-tab, End-tab);
		introspective_sort(tab, Begin, tab+pivot-1, max_depth-1);
		introspective_sort(tab, tab+pivot+1, End, max_depth-1);
	}
}
void time_s (double tab_time[])
{
	long double average_time;
	long double least_time;
	long double big_time;

	long double sum_time=0;


	least_time=tab_time[0];
	big_time=tab_time[0];

	for(int i=0; i<100; i++)
	{
		sum_time=sum_time+tab_time[i];
		
		if(tab_time[i]<least_time)
		{
			least_time=tab_time[i];	
		}
		if(tab_time[i]>=big_time)
		{
			big_time=tab_time[i];
		}
	}
	average_time=sum_time/100;
	cout<<endl<<"Najmniejszy czas to : "<< least_time<<endl;
	cout<<"Sredni czas to : "<< average_time<<endl;
	cout<<"Najwiekszy czas to : " <<big_time<<endl;	
}
template <typename T>
bool check(T tab[], int size)
{
	for(int i=0; i<size; i++)
	{
		if(tab[i+1]<tab[i])
		{
			return false;
		} 
		else return true;
	}
	
}
template <typename T>
void create_tab (T tab[], int size)
{
	srand(time(NULL));
	for (int i=0; i<size; i++)
	{
		tab[i]=(rand()%100);
	}
}


template <typename T>
void reverse (T tab[], int size)
{
    int *tab_t;
	//int tab_t[size];
    tab_t=new int[size];
	for(int i=0; i<size; i++)
	{
		tab_t[i]=tab[size-1-i];
	}
	for(int j=0; j<size; j++)
	{
		tab[j]=tab_t[j];
	}
    delete[] tab_t;
}
int main()
{
	double tab_time[100];
	int tab[10000];
	int size = sizeof(tab)/sizeof(tab[0]);
	int max_depth = log(size) * 2;
	//time_begin=clock();


	for(int k=0; k<100; k++)
	{
		//funkcje dla quicksort oraz mergesort
		create_tab(tab, size);

		reverse (tab, size);
		//quicksort(tab,0, size*0.997);

		auto begin_time = chrono::high_resolution_clock::now();

		quicksort(tab,0, size);

		//merge_sort(tab,0, size);

		//introspective_sort (tab, tab, tab+size-1, max_depth);
		int p;
		p=check(tab,size);
		if(p==false) cout<<"blad " <<endl;
		auto end_time = chrono::high_resolution_clock::now();
		tab_time[k]= chrono::duration_cast<chrono::microseconds>(end_time - begin_time).count() ;
	}
	time_s (tab_time);
   // time_end=clock();
    //time_s=(double)(time_end-time_begin)/CLOCKS_PER_SEC;
    //cout << " Czas sortowania: " << time_s <<"  s " <<endl;
	return 0;
}