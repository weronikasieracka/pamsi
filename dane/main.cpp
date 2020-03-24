#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include "lista.hh"
#include "stack.hh"
#include "map.hh"
#include "queue.hh"
#include "pq.hh"

int main()
{
    int priority;
    int newElement;
    int index;
    int element;
    int key;
    int value;
    list < int > l;
    List<int> *base = new List<int>;	//tworzymy liste
    Stack<int> *p = new Stack<int>;
    stack<int> ms;
    Queue<int> *q = new Queue<int>;
    queue<int> myqueue;
    PriorityQueue<int> *n = new PriorityQueue<int>;
    priority_queue<int> mypq;
    Map<int, int> *h = new Map<int, int>;
    map<int, int> mymap;
    int a;
    cout<<"1-Dodaj element do końca listy"<<endl;
    cout<<"2-Dodaj element do początku listy"<<endl;
    cout<<"3-Dodaj element do listy"<<endl;
    cout<<"4-Wyświetl listę"<<endl;
    cout<<"5-wielkość listy"<<endl;
    cout<<"6-usuń element z listy"<<endl;
    cout<<"7-Stwórz listę za pomocą stl"<<endl;
    cout<<"8-Dodaj element na początek listy za pomocą stl"<<endl;
    cout<<"9-Dodaj element na koniec listy za pomocą stl"<<endl;
    cout<<"10-Dodaj element do listy za pomocą stl"<<endl;
    cout<<"11-Usuń z listy za pomoca stl"<<endl;
    cout<<"38-Wyświel wyswietl za pomoca stl"<<endl;
    cout<<"12-Dodaj element do stosu"<<endl;
    cout<<"13-Usuń element ze stosu"<<endl;
    cout<<"14-Wyświel stos"<<endl;
    cout<<"15-Dodaj element do stosu za pomoca stl"<<endl;
    cout<<"16-Usuń element ze stosu za pomoca stl"<<endl;
    cout<<"17-Wyświel stos za pomoca stl"<<endl;
    cout<<"18-Dodaj element do kolejki"<<endl;
    cout<<"19-Usuń element z kolejki"<<endl;
    cout<<"20-Wyświel kolejkę"<<endl;
    cout<<"21-Dodaj element do kolejki za pomoca stl"<<endl;
    cout<<"22-Usuń element z kolejki za pomoca stl"<<endl;
    cout<<"23-Wyświel kolejkę za pomoca stl"<<endl;
    cout<<"24-Dodaj element do kolejki priorytetowej"<<endl;
    cout<<"25-Usuń element z kolejki priorytetowej"<<endl;
    cout<<"26-Wyświel kolejkę priorytetową"<<endl;
    cout<<"27-Dodaj element do kolejki priorytetowej za pomoca stl"<<endl;
    cout<<"28-Usuń element z kolejki priorytetowej za pomoca stl"<<endl;
    cout<<"29-Wyświel kolejkę priorytetową za pomoca stl"<<endl;
    cout<<"30-Dodaj element do map"<<endl;
    cout<<"31-Usuń element z map"<<endl;
    cout<<"32-Znajdz element po key"<<endl;
    cout<<"33-Wyświel map"<<endl;
    cout<<"34-Dodaj element do map za pomoca stl"<<endl;
    cout<<"35-Usuń element z map za pomoca stl"<<endl;
    cout<<"36-Znajdz element po key z map za pomoca stl"<<endl;
    cout<<"37-Wyświel map za pomoca stl"<<endl;

    while(1)
    {
        cin>>a;
        switch(a)
        {
        case 1:

            cout<<"Podaj wartość elementu";
            cin>>newElement;
            base->pushBack(newElement);
            break;
        case 2:
            cout<<"Podaj wartość elementu";
            cin>>newElement;
            base->pushFront(newElement);
            break;
        case 3:
            cout<<"Podaj wartość elementu oraz indeks w po spacji";
            cin>>newElement;
            cin>>index;
            base->_insert(newElement, index);
            break;
        case 4:
            base->view_list();
            break;
        case 6:
            cout<<"Podaj wartość elementu";
            cin>>element;
            base->remove(element);
            break;
        case 5:
            base->list_size();
        case 7:
            cout << "Podaj kolejne elementy listy, podaj zero aby zakonczyc:\n";
            while(cin >> newElement && newElement != 0)
                l.push_back(newElement);
            break;
        case 8:
            cout<<"Podaj wartość elementu";
            cin>>newElement;
            l.push_front(newElement);
            break;
        case 9:
            cout<<"Podaj wartość elementu";
            cin>>newElement;
            l.push_back(newElement);
            break;
        case 10:
        {

            cout<<"Podaj wartość elementu oraz indeks ";
            cin>>newElement;
            cin>>index;
            std::list<int>::iterator ind=l.begin();
            for(int k=0; k<index; k++)
                ind++;
            l.insert( ind,newElement);
            break;
        }
        case 11:
        {

            cout<<"Podaj wartość indeks ";
            cin>>index;
            std::list<int>::iterator ind=l.begin();
            for(int k=0; k<index; k++)
                ind++;
            l.erase( ind);
            break;
        }
        case 12:
            cout<<"Podaj wartość elementu";
            cin>>newElement;
            p->push(newElement);

            break;
        case 13:
            p->pop();
            break;
        case 14:
            cout << "Elementy stosu " << p->view()<<endl;
            break;
        case 15:
            cout<<"Podaj wartość elementu";
            cin>>newElement;
            ms.push(newElement);
        case 16:
            ms.pop();
        case 17:
            while( !ms.empty() )
            {
                cout << ms.top()<<endl;
                ms.pop();
            }
            break;
        case 18:
            cout<<"Podaj wartość elementu: ";
            cin>>newElement;
            q->enqueue(newElement);
            break;
        case 19:
            q->dequeue();
            break;
        case 20:
            q->display();
            break;
        case 21:
            cout<<"Podaj wartość elementu: ";
            cin>>newElement;
            myqueue.push(newElement);
            break;
        case 22:
            myqueue.pop();
            break;
        case 23:
            while(myqueue.size()!=0)

            {

                cout<<myqueue.front();
                myqueue.pop();

            }
            break;
        case 24:
            cout<<"Podaj wartość elementu: ";
            cin>>newElement;
            cout<<"Podaj jaki jest prorytet elementu: ";
            cin>>priority;
            n->enqueue(newElement,priority);
            break;
        case 25:
            n->dequeue();
            break;
        case 26:
            n->view_dQ();
            break;
        case 27:
                        cout<<"Podaj wartość elementu: ";
            cin>>newElement;
            mypq.push(newElement);
            break;
        case 28:
            mypq.pop();
            break;
        case 29:
                        while(mypq.size()!=0)

            {

                cout<<mypq.top();
                mypq.pop();

            }
        break;
        case 30:
            cout<<"Podaj wartość elementu: ";
            cin>>value;
            cout<<"Podaj jaki jest key elementu: ";
            cin>>key;
            h->insert(key,value);
            break;
        case 31:
            cout<<"Podaj jaki jest key elementu: ";
            cin>>key;
            h->remove(key);
            break;
        case 32:
            cout<<"Podaj jaki jest key elementu: ";
            cin>>key;
            h->SearchKey(key);
            cout<<"Element to: "<<value<<endl;
            break;
        case 33:
            h->display_hn();
            break;
                   case 34:
                    cout<<"Podaj wartość elementu: ";
            cin>>value;
            cout<<"Podaj jaki jest key elementu: ";
            cin>>key;
            mymap.insert(pair<int,int>(key,value));
            break;
                   case 35:
        {

            cout<<"Podaj wartość indeks ";
            cin>>index;
            std::map<int,int>::iterator ind=mymap.begin();
            for(int k=0; k<index; k++)
                ind++;
            mymap.erase( ind);
            break;
        }
                   case 36:
                       int klucz;
        cout<<"Podaj klucz ";
            cin>>klucz;
            cout<<mymap[klucz];


            break;
                   case 37:

    for (map<int, int>::iterator ind = mymap.begin(); ind != mymap.end(); ++ind) {
        cout << '\t' << ind->first << '\t' << ind->second << endl;
    }
            break;
        case 38:
            for(std::list<int>::iterator ind=l.begin(); ind!=l.end(); ind++)
            {
                cout << *ind<<endl;
            }


            break;
        default:
            cout<<"KONIEC :(";
            return 0;
            break;

        }
    }
    return 0;

}
