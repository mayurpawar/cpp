#include <iostream>
#include <list>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

class Graph {
    int V;                                              // Number of vertices of a graph
    list<pair<int, int> > *adjList;                     // List to store vertices
    bool *visitedBFS, *visitedDFS, *visitedDIJ;         // Boolean pointer to mark vertices if they are visted
    queue<int> Q;                                       // Queue ADT to store vertices
    pair<int, int> *dijPath;                            // Vector to store visited shortest paths and predeccessors
    int *dist, *pre;
public:
    Graph(int v){                                       // Constructer
        this->V = v;                                    // Assigning number of vertices to current object
        adjList = new list<pair<int, int> >[V];         // Creating array of list in heap
        visitedBFS = new bool[V];                       // Creating array of bool in heap for visited points - BFS
        visitedDFS = new bool[V];                       // Creating array of bool in heap for visited points - DFS
        visitedDIJ = new bool[V];                       // Creating array of bool in heap for visited points - Dijkstra
        for (int i=0; i<V; i++) visitedBFS[i] = false;  // Marking all vertices as visited initially for BFS
        for (int i=0; i<V; i++) visitedDFS[i] = false;  // Marking all vertices as visited initially for DFS
        for (int i=0; i<V; i++) visitedDIJ[i] = false;  // Marking all vertices as visited initially for Dijkstra
        dist = new int[V];                              // Array of integers to hold final distance from source
        pre = new int[V];                               // Array of integers to hold predessor of vertices
        for (int i=0; i<V; i++) dist[i] = INT_MAX;      // Initializing all distances as infinity
        for (int i=0; i<V; i++) pre[i] = -1;            // Initializing all predessors as nothing i.e. -1
    }
    
    void addEdge(int s, int d, int w){                  // Function accepting source, destination and weight
        adjList[s].push_back(make_pair(d, w));          // Pushing edge for source. Note use of make_pair
    }
    
    void BFS(int s){
        visitedBFS[s] = true;                           // Marking source as visited
        Q.push(s);                                      // Once visited, pushing source onto queue
        
        while (!Q.empty()) {                            // Looping over queue till it has atleast one element
            s = Q.front();                              // New source is now first element of queue
            cout << s << ' ';                           // Printing the element
            Q.pop();                                    // Removing first element. Below: Looping over list starting from source
            for (list<pair<int, int> >::iterator it=adjList[s].begin(); it!=adjList[s].end(); ++it) {
                if(visitedBFS[(*it).first]==false) {    // If that vertex is not alreday visited
                    Q.push((*it).first);                // Once visited, pushing that vertex in a queue
                    visitedBFS[(*it).first] = true;     // Marking same vertex as visited
                }
            }
        }
    }
    
    void DFS(int s){
        cout << s << ' ';                               // Marking source as visited
        visitedDFS[s] = true;                           // Once visited, pushing source onto queue
        list<pair<int, int> >::iterator i;              // Iterator declared. Below: Loop recursively to find all possible vertexes
        for (i = adjList[s].begin(); i != adjList[s].end(); ++i) if (!visitedDFS[(*i).first]) DFS((*i).first);
    }
    
    int findMinVertex(){                                // Utility function return the vertex index for which distance is minimun
        int minVal = INT_MAX;                           // A veriable declared and intitiated with infinity value
        int out = 0;                                    // Variable initiated with index as 0
        for (int i=0; i<V; i++) {                       // Loop for all vertexes
            if (visitedDIJ[i]==false && dist[i]<minVal) { //If vertex is unvisited and has diatance from previous min value
                minVal = dist[i];                       // Setting new minimum value if found
                out = i;                                // Setting index of new minimun distance
            }
        }
        return out;                                     // Return index(vertex) of minimum distance
    }
    
    void dijkstra(int s){
        dist[s]=0;                                      // Distance from source to source is 0
        for (int i=0; i<V-1; i++) {                     // For all vertices from 0 till V-1
            int vertex = findMinVertex();               // Find current vertex that has minimum valve
            visitedDIJ[vertex]=true;                    // Mark above vertex as visited
            list<pair<int, int> >::iterator itr;        // Iterator to visit list of pairs for above found minimum vertex
            for (itr=adjList[vertex].begin(); itr!=adjList[vertex].end(); ++itr) { // Loopig over all pairs (vertex and weight)
                if (visitedDIJ[(*itr).first]==false && dist[vertex]+(*itr).second<dist[(*itr).first]) {
                    dist[(*itr).first]=dist[vertex]+(*itr).second; // If that vertex is unvisited and relax the edge if possible
                    pre[(*itr).first]=vertex;           // Setting up predessor for relaxed vertex
                }
            }
        }
        for (int i=0; i<V; i++) {                       // Loop over all vertices
            cout << i << ' ' << dist[i] << "  Path: ";  // Print vertex and its distance from source
            stack<int> path;                            // Stack to store path of shortest distance
            int n = i;                                  // Printing destination
            while (n!=-1) {                             // Untill we reach predesessor as -1 that is for source
                path.push(n);                           // Adding current vertex in vector
                n=pre[n];                               // Changing predessor as new vertex
            }
            if (!path.empty()) {                        // If path has no element then the destination is not reachable
                while (!path.empty()) {                 // Printing all elements in a path
                    if (path.top()==i) cout << path.top();
                    else cout << path.top() << "-";     // Adding '-' when current element that is printed is not destination
                    path.pop();                         // Once printed popping out element.
                }
            }
            else cout << "No path";
            cout << endl;
        }
    }
    
    void bellmonFord(int s){
        int *dist = new int[V];
        for (int i=0; i<V; i++) dist[i]=INT_MAX;
        int *pre = new int[V];
        for (int i=0; i<V; i++) pre[i]=-1;
        dist[s]=0;
        int count=0;
        for (int i=0; i<V-1; i++) {
            bool change = false;
            for (int j=0; j<V; j++) {
                list<pair<int, int> >::iterator it;
                for (it=adjList[j].begin(); it!=adjList[j].end(); ++it) {
                    if (dist[j]!=INT_MAX && dist[j]+(*it).second < dist[(*it).first]) {
                        dist[(*it).first] = dist[j]+(*it).second;
                        pre[(*it).first]=j;
                        change=true;
                    }
                    count++;
                }
            }
            if (change==false) break;
        }
        
        for (int i=0; i<V; i++) {                       // Loop over all vertices
            cout << i << ' ' << dist[i] << "  Path: ";  // Print vertex and its distance from source
            stack<int> path;                            // Stack to store path of shortest distance
            int n = i;                                  // Printing destination
            while (n!=-1) {                             // Untill we reach predesessor as -1 that is for source
                path.push(n);                           // Adding current vertex in vector
                n=pre[n];                               // Changing predessor as new vertex
            }
            if (!path.empty()) {                        // If path has no element then the destination is not reachable
                while (!path.empty()) {                 // Printing all elements in a path
                    if (path.top()==i) cout << path.top();
                    else cout << path.top() << "-";     // Adding '-' when current element that is printed is not destination
                    path.pop();                         // Once printed popping out element.
                }
            }
            else cout << "No path";
            cout << endl;
        }
        cout << "Total count: " << count << endl;
    }
};

int main(){
    Graph gh(10);
    gh.addEdge(0, 2, 4);
    gh.addEdge(1, 2, 2); gh.addEdge(1, 3, 3);
    gh.addEdge(2, 0, 4); gh.addEdge(2, 1, 2); gh.addEdge(2, 3, 5); gh.addEdge(2, 8, 8);
    gh.addEdge(3, 1, 3); gh.addEdge(3, 2, 5); gh.addEdge(3, 4, 7);
    gh.addEdge(4, 3, 7); gh.addEdge(4, 5, 5);
    gh.addEdge(5, 4, 5); gh.addEdge(5, 6, 6); gh.addEdge(5, 7, 2);
    gh.addEdge(6, 5, 6); gh.addEdge(6, 9, 4);
    gh.addEdge(7, 5, 2); gh.addEdge(7, 8, 7); gh.addEdge(7, 9, 3);
    gh.addEdge(8, 2, 8); gh.addEdge(8, 7, 7);
    gh.addEdge(9, 6, 4); gh.addEdge(9, 7, 3);
    //gh.DFS(9); // Prints 9 6 5 4 3 1 2 0 8 7
    //gh.BFS(9); // Prints 9 6 7 5 8 4 2 3 0 1
    gh.bellmonFord(9);
}