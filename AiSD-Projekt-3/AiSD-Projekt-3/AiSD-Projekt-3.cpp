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
#include <vector>


using namespace std;


void adding_edges(vector<int>* graph_list , int edge_start, int edge_end);

void print_edge_list(vector<int>* graph_list, int nodes);


void all_neighbours(vector<int>* graph_list, int nodes);


void everyones_neighbour(vector<int>* graph_list, int nodes);

void find_degree_of_nodes(vector<int>* graph_list, int nodes);

void find_loops(vector<int>* graph_list, int nodes);
void find_2way_edges(vector<int>* graph_list, int nodes);

void find_isolated(vector<int>* graph_list, int nodes);

int main()
{/*

    int nodes; 
    int edges;


    int* edge_begin;
    int* edge_end;
    
    
    

    cout << "Podaj ilosc wezlow: ";    cin >> nodes;
    cout << "Podaj ilosc krawedzi : "; cin >> edges;


    edge_begin = new int[edges];
    edge_end   = new int[edges];
    
    int** adjacency_matrix = new int* [nodes];

    for (int i = 0; i < nodes; ++i)
        adjacency_matrix[i] = new int[nodes];


    */
    vector<int>* graph_list;

    int nodes;
    int edges;
    int a, b;

    cout << "podaj ilosc wezlow: "; cin >> nodes;
    cout << "podaj ilosc krawedzi: "; cin >> edges;


    graph_list = new vector<int>[nodes];
    
    bool is_valid = true;

    for (int i = 0; i < edges; i++)
    {
        is_valid = true;

        cin >> a >> b;
        if (a > nodes) { cout << "brak wezla: " << a << "podaj poprawny wezel"; is_valid = false; i--; }
        else
            if (b > nodes) { cout << "brak wezla: " << b << "podaj poprawny wezel"; is_valid = false; i--; }

        if(is_valid) adding_edges(graph_list, a, b);
    }

    //cout << endl << "g0: " << graph_list[0].size() << "g1: " << graph_list[1].size() << endl;



    print_edge_list(graph_list, nodes);




    //all_neighbours(graph_list, nodes);

    cout << endl;

    //everyones_neighbour(graph_list, nodes);

    //find_degree_of_nodes(graph_list, nodes);

    //find_loops(graph_list, nodes);
    //find_2way_edges(graph_list, nodes);
    find_isolated(graph_list, nodes);

    system("pause");
    return 0;
}

void adding_edges(vector<int>* graph_list, int edge_start, int edge_end)
{
graph_list[edge_start - 1].push_back(edge_end);   
}

void print_edge_list(vector<int> *graph_list, int nodes)
{
    cout << endl << "lista krawedzi: ";

    for (int i = 0; i < nodes; i++)
    {
        cout << "\n wezly '" << i + 1 << "' : ";
        for (int j = 0; j < graph_list[i].size(); j++)
            cout << graph_list[i][j] << setw(3);
        cout << endl << setw(-5);
    }
}

void all_neighbours(vector<int>* graph_list, int nodes)
{
    for (int i = 0; i < nodes; i++)
    {
        cout << endl << "Sasiedzi wezla " << i+1 << " : ";
        for (int j = 0; j < nodes; j++)
        {
            for (int k = 0; k < graph_list[j].size(); k++)
            {
                if (graph_list[j][k] == i + 1) cout << j + 1 << ", ";
            }
        }
    }
}

void everyones_neighbour(vector<int>* graph_list, int nodes)
{
    bool is_everyones_neighbour = true;

    cout << endl << "Wezel sasiadujacy ze wszystkimi: ";

    for (int i = 0; i < nodes; i++)
    {
        is_everyones_neighbour = true;

        if (graph_list[i].size() == nodes - 1)
        {
            //cout << "szukam dla " << i+1 << endl;
           //cout << endl << "size : " << graph_list[i].size() << " nodes - 1 : " << nodes - 1;

            for (int j = 0; j < graph_list[i].size(); j++)
            {
                if (graph_list[i][j] == i+1) is_everyones_neighbour = false;
                break;
            }

            if (is_everyones_neighbour)cout << i + 1;
        }

        
    }
}
    
void find_degree_of_nodes(vector<int> *graph_list, int nodes)
{
    int incoming_edges = 0;
    int outgoing_edges = 0;
    

    for (int i = 0; i < nodes; i++)
    {
        incoming_edges = 0;
        outgoing_edges = graph_list[i].size();

        for (int j = 0; j < nodes; j++)
        {   for (int k = 0; k < graph_list[j].size(); k++)
            {
                if (graph_list[j][k] == i+1) { incoming_edges++; }
            }
        }

    
        cout << "\n Stopien wchodzacy wierzcholka "  << i+1 << ":" << incoming_edges;
        cout << "\n Stopien wychodzacy wierzcholka " << i+1 << ":" << outgoing_edges;
        

    }
}

void find_loops(vector<int>* graph_list, int nodes)
{
    cout << "\n Wierzcholki posiadajace petle: ";

    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < graph_list[i].size(); j++)
        {
            if (graph_list[i][j] == i + 1)
            {
                cout << i + 1 << ", ";
                break;
            }
        }
}

void find_2way_edges(vector<int>* graph_list, int nodes)
{
    for (int i = 0; i < nodes; i++)  //wszystkie wezly
    {
        for (int j = 0; j < graph_list[i].size(); j++)  //wszystkie krawedzie od danego wezla
        {
            for (int k = 0; k < graph_list[graph_list[i][j]-1].size(); k++)  //czy wezel otrzymujacy krawedz ma krawedz w przeciwnym kierunku
            {
                if (graph_list[graph_list[i][j]-1][k] == i+1)
                {
                    cout << endl << "Znaleziono krawedz dwukierunkowa miedzy wezlami: " << i + 1 << " i " << graph_list[i][j];
                }
            }
        }
    }
}

void find_isolated(vector<int>* graph_list, int nodes)
{
    cout << endl << "Wierzcholki izolowane: ";

    for (int i = 0; i < nodes; i++)
    {
        if (graph_list[i].size()==0)
        {
            cout << i + 1 << ", ";
        }
    }
}