// AiSD-Projekt-3.cpp
/*
# AiSD - Projekt-3
Zadanie 6. Napisz program, który dla zadanego grafu skierowanego reprezentowanego przy pomocy 
listy krawędzi zapisanych przy pomocy dwóch tablic wyznaczy i wypisze następujące informacje :
- 1) wszystkich sąsiadów dla każdego wierzchołka grafu(sąsiad wierzchołka wi, to ten wierzchołek do którego prowadzi krawędź z wi)
- 2) wszystkie wierzchołki, które są sąsiadami każdego wierzchołka
- 3) stopnie wychodzące wszystkich wierzchołków
- 4) stopnie wchodzące wszystkich wierzchołków
- 5) wszystkie wierzchołki izolowane
6) wszystkie pętle
7) wszystkie krawędzie dwukierunkowe
Każdy z powyższych podpunktów powinien być realizowany jako oddzielna funkcja.
W funkcji main() należy przedstawić działanie napisanej przez siebie biblioteki na reprezentatywnym przykładzie.
Kod powinien być opatrzony stosownymi komentarzami.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <list>

using namespace std;

void edges_from_file(int edge_begin, int edge_end);
void adding_edges(int edge_begin[], int edge_end[], int nodes, int size);

//macierz w komórkach n będzie przechowywała węzły o wartości n+1
//void fill_adjacency_matrix(int edge_begin[], int edge_end[], int **adjacency_matrix, int nodes, int size);
//void print_adj_matrix(int** adjacency_matrix, int nodes);


void all_neighbours(int edge_begin[], int edge_end[], int nodes, int size);
void everyones_neighbour(int edge_begin[], int edge_end[], int nodes, int size);

void find_degree_of_edges(int edge_begin[], int edge_end[], int nodes, int size);

void find_loops(int edge_begin[], int edge_end[], int nodes, int size);
void find_2way_edges(int edge_begin[], int edge_end[], int nodes, int size);

void find_isolated_node(int edge_begin[], int edge_end[], int nodes, int size);


int main()
{
    //std::list<int> krawedzie[10];

    //krawedzie->push_back(1);

    int nodes; 
    int edges;


    int* edge_begin;
    int* edge_end;
    
    

    cout << "Podaj ilosc wezlow: ";    cin >> nodes;
    cout << "Podaj ilosc krawedzi : "; cin >> edges;


    edge_begin = new int[edges];
    edge_end   = new int[edges];
    

    adding_edges(edge_begin, edge_end, nodes, edges);


    all_neighbours(edge_begin, edge_end, nodes, edges);

    cout << endl;

    everyones_neighbour(edge_begin, edge_end, nodes, edges);

    find_degree_of_edges(edge_begin, edge_end, nodes, edges);

    find_loops(edge_begin, edge_end, nodes, edges);
    find_2way_edges(edge_begin, edge_end, nodes, edges);


    system("pause");
    return 0;
}

void edges_from_file(int edge_begin, int edge_end)
{
    {
        /* ifstream edges;
           edges.open("edges.txt", ios::in);
           string line;
           while (!edges.eof()){cout << "xD";}
           edges.close();*/
    }
}

void adding_edges(int edge_begin[], int edge_end[], int nodes, int size)
{
    int add_edge;
    bool flag;


    cout << "\n dostepne wezly : "; for (int i = 0; i < nodes; i++) cout << " " << i + 1;
    cout << "\n";



    for (int i = 0; i < size; i++)
    {
        flag = false;

        cout << "\n Podaj wezel poczatku i konca (2 liczby oddzielone spaja) krawedzi  '" << i + 1 << "': "; 
        
        cin >> add_edge;
        if (add_edge <1 || add_edge>nodes)
        {
            flag = true;
            cout << "\n brak wezla: " << add_edge;
        }
        edge_begin[i] = add_edge;
        
        
        cin >> add_edge; edge_end[i]   = add_edge;
        if (add_edge <1 || add_edge>nodes)
        {
            flag = true;
            cout << "\n brak wezla: " << add_edge;
        }

        if (flag) i--;
    }

    cout << endl;

    for (int i = 0; i < size; i++)
    {cout << edge_begin[i] << "->" << edge_end[i] <<"\n"; }
}

void all_neighbours(int edge_begin[], int edge_end[], int nodes, int size)
{


    for (int i = 0; i < nodes; i++) 
    {
        cout << "\n Wszyscy sasiedzi wierzcholka " << i + 1 << ": ";

        for (int j = 0; j < size; j++)
        {
            if (edge_end[j] == (i + 1))//np [2][1] to znaczy że z 1 do 2 jest '->' czyli 1 jest sąsiadem 2
            {
                cout << edge_begin[j] << ", ";
            }
        }

    }
}

void everyones_neighbour(int edge_begin[], int edge_end[], int nodes, int size)
{
    bool is_neighbour = true;

    int* unikalne = new int[nodes];

    for (int i = 0; i < nodes; i++)
    {
        unikalne[i] = 0;
    }

    cout << "\n Wierzcholki sasiadujace ze wszystkimi innymi wierzcholkami: ";

    for (int i = 0; i < size; i++)
    {
        is_neighbour = true;

        for (int j = 0; j < size; j++)
        {
            if (edge_begin[j] == (i + 1))
            {
                unikalne[edge_end[j] - 1]=1;
            }
        }

        for (int j = 0; j < nodes; j++)
        {
            if (unikalne[j]!=1 && j != i)
                is_neighbour = false;
        }

        if (is_neighbour) cout << i + 1 << ", ";
    }

    delete[] unikalne;
}


void find_degree_of_edges(int edge_begin[], int edge_end[], int nodes, int size)
{
    int outgoing_edges = 0;
    int incoming_edges = 0;


    for (int i = 0; i < nodes; i++)
    {
        outgoing_edges = 0;
        incoming_edges = 0;


        for (int j = 0; j < size; j++)
        {
            if (edge_begin[j]==(i+1))
            {
                outgoing_edges++;
            }

            if (edge_end[j] == (i+1))
            {
                incoming_edges++;
            }
        }

        cout << "\n Stopien wychodzacy wierzcholka " << i+1 << ":" << outgoing_edges;
        cout << "\n Stopien wchodzacy wierzcholka "  << i+1 << ":" << incoming_edges;

    }
}


void find_loops(int edge_begin[], int edge_end[], int nodes, int size)
{
    cout << "\n Wierzcholki posiadajace petle: ";

    for (int i = 0; i < size; i++)
        if (edge_begin[i]==edge_end[i]) cout << i+1 << ", ";
}

void find_2way_edges(int edge_begin[], int edge_end[], int nodes, int size)
{
    bool is_2way_edge = false;

    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (edge_begin[j]==i+1)
            {
                for (int k=0; k<size; k++)
                {
                    if (edge_begin[k] == edge_end[j])
                        if (edge_end[k] == i + 1)
                            cout << "\n Znaleziono 2kierunkowa miedzy: " << i + 1 << " i " << edge_begin[k];
                }
            }
        }
    }
}

void find_isolated_node(int edge_begin[], int edge_end[], int nodes, int size)
{
    bool is_isolated = true;
    for (int i = 0; i < nodes; i++)
    {
        is_isolated = true;

        for (int j = 0; j < size; j++)
        {
            if (edge_begin[j] == (i + 1) || edge_end[j] == (i + 1))
                is_isolated=false;
        }

        if (is_isolated) cout << "\n Wezel " << i + 1 << "jest izolowany";
    }
}
