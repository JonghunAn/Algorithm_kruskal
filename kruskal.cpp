#include <stdio.h>
#include<iostream>
#include <time.h>
#include <stdlib.h>
#include<iomanip>

#define Numberofvertex 5
#define INF 999

using namespace std;

const int N = Numberofvertex;

typedef int index;
typedef index set_pointer;
typedef index universe[N];

typedef struct edge {
    int vertex1;
    int vertex2;
    int weight;
}edge;

universe U;

void kruskal(int, int, edge[], edge[]);
void makeset(index);
set_pointer find(index);
void merge(set_pointer, set_pointer);
bool equal(set_pointer, set_pointer);
void initial(int);
void quicksort(int, int, edge[]);
void partition(int, int, int&, edge[]);
void GraphSet(int[N][N], edge[]);
void print_kruskal(int W[][N],edge F[]);

int main() {

        const int n = N;  //vertex num
        const int m = 7;  //edge num

        int W[N][N];
        edge F[N - 1] = {};
        edge E[N * N] = {};
        
        GraphSet(W, E); //초기 그래프 data 설정
        
        kruskal(n, m, E, F); 

        print_kruskal(W,F);

        return 0;
}
void GraphSet(int W[N][N], edge E[])
{
    int i = 0;
    int j = 0;
    int k = 0;

    int weight;

    //int data[N][N] = { {0,1,3,INF,INF}, {1,0,3,6,INF}, {3,3,0,4,2}, {INF,6,4,0,5}, {INF,INF,2,5,0}};    //4.7 graph data
    int data[N][N] = { {0,8,5,INF,INF}, {8,0,9,11,INF}, {5,9,0,15,10}, {INF,11,15,0,7}, {INF,INF,10,7,0} };    //self data

    for (i = 0; i < N; i++) {
        for (j = i; j < N; j++) {
            if (i == j)
                W[i][j] = data[i][j];
            else {

                weight = data[i][j];

                if (data[i][j] != INF)
                {
                    E[k].vertex1 = i;
                    E[k].vertex2 = j;
                    E[k].weight = weight;
                    k++;
                }
                    W[i][j] = W[j][i] = weight;
            }
        }
    }  
}

void kruskal(int n, int m, edge E[], edge F[]) 
{
    index i = 0;
    index j = 0;
    index fi = 0;
    index ei = 0;

    set_pointer p, q;
    edge e;

    quicksort(0, m, E);

    initial(n);

    while (fi < n - 1) {
        e = E[ei++];
        i = e.vertex1;
        j = e.vertex2;
        p = find(i);
        q = find(j);
        if (!equal(p, q)) {
            merge(p, q);
            F[fi++] = e;
        }
    }
}

void makeset(index i) {
    U[i] = i;
}

set_pointer find(index i) {
    index j;

    j = i;
    while (U[j] != j)
        j = U[j];
    return j;
}

void merge(set_pointer p, set_pointer q) {
    if (p < q)
        U[q] = p;
    else
        U[p] = q;
}

bool equal(set_pointer p, set_pointer q) {
    if (p == q)
        return true;
    else
        return false;
}

void initial(int n) {
    index i;

    for (i = 0; i < n; i++)
        makeset(i);
}

void quicksort(int low, int high, edge E[]) {
    int pivotpoint;

    if (high > low) {
        partition(low, high, pivotpoint, E);
        quicksort(low, pivotpoint - 1, E);
        quicksort(pivotpoint + 1, high, E);
    }
}

void partition(int low, int high, int& pivotpoint, edge E[]) {
    int i, j;
    int pivotitem;
    edge tmp;

    pivotitem = E[low].weight;
    j = low;
    for (i = low + 1; i <= high; i++)
        if (E[i].weight < pivotitem) {
            j++;
            tmp = E[i];
            E[i] = E[j];
            E[j] = tmp;
        }

    pivotpoint = j;

    tmp = E[low];
    E[low] = E[pivotpoint];
    E[pivotpoint] = tmp;
}

void print_kruskal(int W[][N],edge Kruskal[])
{
    cout << "F SET Print.\n\n";
    for (int i = 0; i < N - 1; i++)
        cout<<"F["<<i+1<<"] : V"<< Kruskal[i].vertex1 + 1<<" -- V"<< Kruskal[i].vertex2 + 1<<" Weight "<< Kruskal[i].weight<<endl;
}