#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>
#include <bits/stdc++.h>

//#define CHAR_DEBUG

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;

class Debugger {
public:
#ifdef CHAR_DEBUG

    static char convertIntToChar(int x) {
        return (char)(x-'a'-1);
    }

#else
    static int convertIntToChar(int x) {
        return x;
    }
#endif

};

class Node {
public:
    Node() {
        this->x = 0;
        this->y = 0;
        this->ind = -1;
    }

    Node(int x, int y, int ind) {
        this->x = x;
        this->y = y;
        this->ind = ind;
    }

    void addAdjs(Node *n) {
        adjs.push_back(n);
    }

    int dist(Node *n) {
        int xd = x - n->getX();
        int yd = y - n->getY();

        return (int)(sqrt(xd*xd + yd*yd) + 0.5);
    }

    int getInd() {
        return ind;
    }

    int getX(){
        return x;
    }

    int getY() {
        return y;
    }

    vector<Node*> getAdjs() {
        return adjs;
    }

    void print() {
        cout << "(" << x << ", " << y << ")";
    }

private:
    int x, y;
    int ind;
    vector<Node*> adjs;
};

class Edge {
public:
    Edge(int i, int j, int tam) {
        vertices = make_pair(i, j);
        this->tam = tam;
    }

    ii getVertices() {
        return vertices;
    }

    int getTam() {
        return tam;
    }

private:
    ii vertices;
    int tam;
};

class Graph {
public:
    Graph(const string &fileName) {
        ifstream input;
        string file = "../" + fileName;
        input.open(file);

        n = 0;

        if (input.is_open()) {
            input >> n;

            nodes.resize((unsigned long) n+1);

            while (!input.eof()) {
                int i, x, y;
                input >> i >> x >> y;
                nodes[i] = new Node(x, y, i);
            }

            dist.resize((unsigned long) n+1);
            for(int i = 1; i <= n; i ++) {
                dist[i].resize((unsigned long) n + 1);
                for(int j = 1; j <= n; j ++) {
                    dist[i][j] = nodes[i]->dist(nodes[j]);
                }
            }
        }
        else {
            cout << "File input not found" << endl;
            input.close();
            exit(1);
        }
        input.close();
    }

    ~Graph () {
        for(int i = 0; i <= n; i ++) {
            dist[i].clear();
            delete(nodes[i]);
        }
        dist.clear();
        nodes.clear();
        edges.clear();
    }

    void prim() {
        int cost[n+1]; // The minimum cost for one subtree to a given vertice
        int inSubTree[n+1]; // Checks if a given vertice is already on the prim's subtree
        priority_queue<ii, vector<ii>, greater<ii> > pq;

        for(int i = 1; i <= n; i ++) {
            inSubTree[i] = false;
            cost[i] = INF;
        }
        inSubTree[1] = true;
        pq.push(make_pair(cost[1], 1));
        int parent[n+1];

        while(!pq.empty()) {
            ii p = pq.top();
            pq.pop();
            int d = p.first;
            int u = p.second;

            inSubTree[u] = true;

            for(int v = 1; v <= n; v ++) {
                if(!inSubTree[v] && cost[v] > dist[u][v]) {
                    cost[v] = dist[u][v];
                    pq.push(make_pair(cost[v], v));
                    parent[v] = u;
                }
            }
        }

        for(int i = 2; i <= n; i ++) {
            edges.emplace_back(Edge(i, parent[i], dist[i][parent[i]]));
            nodes[i]->addAdjs(nodes[parent[i]]);
            nodes[parent[i]]->addAdjs(nodes[i]);
        }

    }

    void printAllNodes() {
        cout << endl;

        for(int i = 1; i <= n; i ++) {

            cout << "Node #" << (char)(i+'a'-1) << ": ";
            nodes[i]->print();
            cout << ", with adjs = ";

            for(int j = 0; j < nodes[i]->getAdjs().size(); j ++) {
                if(j != nodes[i]->getAdjs().size()-1)
                    cout << (char)(nodes[i]->getAdjs()[j]->getInd()+'a'-1) << " ";
                else
                    cout << (char)(nodes[i]->getAdjs()[j]->getInd()+'a'-1) << endl;
            }
        }

        cout << endl;
    }

    void printAllDists() {
        cout << endl;
        cout << "Printing all dists" << endl;
        cout << "  ";
        for(int i = 1; i <= n; i ++) {
            if(i != n)
                cout << (char)(i+'a'-1) << " ";
            else
                cout << (char)(i+'a'-1) << endl;
        }

        for(int i = 1; i <= n; i ++) {
            cout << (char)(i+'a'-1) << " ";
            for(int j = 1; j <= n; j ++) {
                if(j != n)
                    cout << dist[i][j] << " ";
                else
                    cout << dist[i][j] << endl;
            }
        }
    }

    void printAllEdges() {
        cout << endl << "Number of edges = " << edges.size() << endl;
        for(int i = 0; i < edges.size(); i ++) {
            cout << "Edge #" << i+1 << ": " <<(char)(edges[i].getVertices().first + 'a' - 1) << " - "
                 << (char)(edges[i].getVertices().second + 'a' - 1)
                << " with distance = " << edges[i].getTam() << endl;
        }
    }

private:
    int n;
    vector<Node*> nodes;
    vector<Edge> edges;
    vector<vector<int> > dist;
};

int main() {
    ios_base::sync_with_stdio(false);

    Graph graph = Graph("input.txt");
    graph.prim();
    graph.printAllDists();

    graph.printAllEdges();
    graph.printAllNodes();


    return 0;
}