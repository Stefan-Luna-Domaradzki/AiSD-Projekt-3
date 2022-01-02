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
void fill_adjacency_matrix(int edge_begin[], int edge_end[], int **adjacency_matrix, int nodes, int size);
void print_adj_matrix(int** adjacency_matrix, int nodes);


void all_neighbours(int** adjacency_matrix, int nodes);
void everyones_neighbour(int** adjacency_matrix, int nodes);

void find_degree_of_edges(int** adjacency_matrix, int nodes);

void find_loops(int** adjacency_matrix, int nodes);
void find_2way_edges(int** adjacency_matrix, int nodes);

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
    
    int** adjacency_matrix = new int* [nodes];

    for (int i = 0; i < nodes; ++i)
        adjacency_matrix[i] = new int[nodes];

    adding_edges(edge_begin, edge_end, nodes, edges);


    fill_adjacency_matrix(edge_begin, edge_end, adjacency_matrix, nodes, edges);
    print_adj_matrix(adjacency_matrix, nodes);

    all_neighbours(adjacency_matrix, nodes);

    cout << endl;

    everyones_neighbour(adjacency_matrix, nodes);

    find_degree_of_edges(adjacency_matrix, nodes);

    find_loops(adjacency_matrix, nodes);
    find_2way_edges(adjacency_matrix, nodes);


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

void fill_adjacency_matrix(int edge_begin[], int edge_end[], int** adjacency_matrix, int nodes, int size)
{
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            adjacency_matrix[i][j] = 0;

    for (int i = 0; i < size; i++)
        adjacency_matrix[edge_begin[i] - 1][edge_end[i] - 1] = 1;
}

void print_adj_matrix(int** adjacency_matrix, int nodes)
{
    cout << endl << "Macierz incydencji" << endl << setw(4);

    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
            cout << adjacency_matrix[i][j] << setw(4);
        cout << endl;
    }
}

void all_neighbours(int** adjacency_matrix, int nodes)
{
    bool izolowany;

    for (int i = 0; i < nodes; i++)
    {
        izolowany = true;

        cout << "\n Wszyscy sasiedzi wierzcholka " << i + 1 << ": ";

        for (int j = 0; j < nodes; j++)
        {
            if (adjacency_matrix[j][i] == 1)//np [2][1] to znaczy że z 1 do 2 jest '->' czyli 1 jest sąsiadem 2
            {
                cout << j + 1 << ", ";
                izolowany = false;
            }
        }

        if (izolowany) cout << " brak krawedzi wchodzacych. Wierzcholek izolowany";
    }
}

void everyones_neighbour(int** adjacency_matrix, int nodes)
{
    //można zmniejszyć ilość porównać dając break
    bool is_neighbour = true;
    bool exists = false;

    cout << "\n Wierzcholki sasiadujace ze wszystkimi innymi wierzcholkami: ";

    for (int i = 0; i < nodes; i++)
    {
        exists = is_neighbour;
        is_neighbour = true;

        for (int j = 0; j < nodes; j++)
        {
            if (adjacency_matrix[i][j] == 0 && j != i) //wtedy węzeł i nie jest sąsiadem wszystkich
            {
            is_neighbour = false;
            break;           
            }
        }

        if (is_neighbour) cout << i + 1 << ", ";
    }


    if (!exists) cout << "brak. \n";
}


void find_degree_of_edges(int** adjacency_matrix, int nodes)
{
    int outgoing_edges = 0;
    int incoming_edges = 0;


    for (int i = 0; i < nodes; i++)
    {
        outgoing_edges = 0;
        incoming_edges = 0;


        for (int j = 0; j < nodes; j++)
        {
            if (adjacency_matrix[i][j] == 1)
            {
                outgoing_edges++;
            }

            if (adjacency_matrix[j][i] == 1)
            {
                incoming_edges++;
            }
        }

        cout << "\n Stopien wychodzacy wierzcholka " << i+1 << ":" << outgoing_edges;
        cout << "\n Stopien wchodzacy wierzcholka "  << i+1 << ":" << incoming_edges;

    }
}

void find_loops(int** adjacency_matrix, int nodes)
{
    cout << "\n Wierzcholki posiadajace petle: ";

    for (int i = 0; i < nodes; i++)
        if (adjacency_matrix[i][i]) cout << i + 1 << ", ";
}

void find_2way_edges(int** adjacency_matrix, int nodes)
{
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (adjacency_matrix[i][j] && adjacency_matrix[j][i])
                cout << "\n Znaleziono dwukierunkowa krawedz miedzy: " << i + 1 << " i " << j + 1 << ".";
        }

    }
}
