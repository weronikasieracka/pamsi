#ifndef MAP_HH
#define MAP_HH

#include<iostream>
#include <cmath>
using namespace std;
#define CAP 20
template < typename KeyType , typename ValueType >
class HashNode
{
    public:
    KeyType key;
    ValueType value;
    HashNode(KeyType key, ValueType value); //konstruktor
};
template < typename KeyType , typename ValueType >
HashNode<KeyType,ValueType>::HashNode(KeyType key, ValueType value)
{
        this->key = key;
        this->value = value;
}
template < typename KeyType , typename ValueType >
class Map // Tablica z h a s z o w a n i e m
{   public :
    HashNode<KeyType,ValueType> **b; //tablica
    int capacity;
    int size;
    HashNode<KeyType,ValueType> *model;

    void insert ( const KeyType& key , const ValueType& value);
    ValueType& operator[]  ( const KeyType& key);
    void remove ( const KeyType& key);
    ValueType SearchKey(KeyType key);
    void display_hn();
    int hashCode(KeyType key);
    bool _Empty();
    int _sizeMap();
    Map(); //konstruktor
    Map(const Map & nowy); //konstruktor
    ~Map(); //destruktor
};

  template < typename KeyType , typename ValueType >
 ValueType& Map<KeyType,ValueType>::operator[]  ( const KeyType& key)
  {
         for(int i=0 ; i<capacity ; i++)
   {
        if(b[i]->key ==key)
           return b[i]->value;

   }
  }

template < typename KeyType , typename ValueType >
 Map<KeyType,ValueType>::Map(const Map & nowy)
 {
        b=nowy.b; //tablica
     capacity=nowy.capacity;
     size=nowy.size;
    model=nowy.model;
 }

template < typename KeyType , typename ValueType >
Map<KeyType,ValueType>::Map()
{
        capacity = CAP;
        size=0;
        b = new HashNode<KeyType,ValueType>*[capacity];
        //inicjujemy wszystkie elementy w tablicy jako NULL
        for(int i=0 ; i < capacity ; i++)
        {
            b[i] = NULL;
        }
        model = new HashNode<KeyType,ValueType>(-1, -1);

}
template < typename KeyType , typename ValueType >
Map<KeyType,ValueType>::~Map()
{
    capacity = CAP;
    for (int i = 0; i < capacity; i++)
        {
            if (b[i] != NULL)
            delete b[i];
            delete[] b;
         }

}


template < typename KeyType , typename ValueType >
int Map<KeyType,ValueType>::hashCode(KeyType key) //Dla znalezienia indeksu k
{
    return key % capacity;
}
template < typename KeyType , typename ValueType >
bool Map<KeyType,ValueType>::_Empty()
{
    return size == 0;
}
template < typename KeyType , typename ValueType >
int Map<KeyType,ValueType>::_sizeMap()
{
    return size;
}
template < typename KeyType , typename ValueType >
void Map<KeyType,ValueType>::insert(const KeyType& key, const ValueType& value)
{
    HashNode<KeyType,ValueType> *temp = new HashNode<KeyType,ValueType>(key, value);
    int hashIndex = hashCode(key); //definiujemy, aby znaleźć indeks dla danego klucza
         while(b[hashIndex] != NULL && b[hashIndex]->key != key && b[hashIndex]->key != -1) //szukamy wolne miejsce
         {
            hashIndex++;
            hashIndex %= capacity;
         }
         // jeśli nowy element, który ma zostać wstawiony, zwiększ bieżący rozmiar
         if(b[hashIndex] == NULL || b[hashIndex]->key == -1)
            size++;
        b[hashIndex] = temp;
}
template < typename KeyType , typename ValueType >
void Map<KeyType,ValueType>::remove( const KeyType& key)
{
    int hashIndex = hashCode(key);
    while (b[hashIndex] != NULL)
         {
            if (b[hashIndex]->key == key)
               break;
            hashIndex = hashCode(hashIndex + 1);
         }
         if (b[hashIndex] == NULL)
         {
            cout<<"nie znaleziono "<<key<<endl;
            return;
         }
         else
         {
            delete b[hashIndex];
         }
         cout<<"Element usuniety"<<endl;
}
template < typename KeyType , typename ValueType >
ValueType Map<KeyType,ValueType>::SearchKey(KeyType key)
{
    int hashIndex = hashCode(key);
    while (b[hashIndex] != NULL && b[hashIndex]->key != key)
    {
        hashIndex = hashCode(hashIndex + 1);
    }
    if (b[hashIndex] == NULL)
    {
        return -1;
    }
    else
    {
        return b[hashIndex]->value;
    }

}
template < typename KeyType , typename ValueType >
void Map<KeyType,ValueType>::display_hn()
{
   for(int i=0 ; i<capacity ; i++)
   {
       if(b[i] != NULL)
        cout << "key = " << b[i]->key <<"  value = "<< b[i]->value << endl;
   }
}

#endif
