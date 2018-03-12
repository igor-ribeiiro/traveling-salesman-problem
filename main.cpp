#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>

#define INF 1000000000

using namespace std;

class Node {
public:
    Node() {
        this->x = 0;
        this->y = 0;
        adj = nullptr;
    }

    Node(int x, int y) {
        this->x = x;
        this->y = y;
        adj = nullptr;
    }

    void addAdj(Node *n) {
        adj = n;
    }

    int dist(Node *n) {
        int xd = x - n->getX();
        int yd = y - n->getY();

        return (int)(sqrt(xd*xd + yd*yd) + 0.5);
    }

    int getX(){
        return x;
    }

    int getY() {
        return y;
    }

    Node* getAdj() {
        return adj;
    }

    void print() {
        cout << "(" << x << ", " << y << ")";
    }

private:
    int x, y;
    Node *adj;
};

class Edge {
    Edge
};

class Graph {
public:
    Graph() {
        ifstream input;
        input.open("../input.txt");

        if (input.is_open()) {
            input >> n;

            nodes.resize((unsigned long) n+1);

            while (!input.eof()) {
                int i, x, y;
                input >> i >> x >> y;
                nodes[i] = new Node(x, y);
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
            nodes.clear();
        }
        dist.clear();
    }

    void prim() {
        int cost[n+1]; // The minimum cost for one subtree to a given vertice
        bool inSubTree[n+1]; // Checks if a given vertice is already on the prim's subtree

        for(int i=1; i <= n; i ++) {
            cost[i] = INF;
            inSubTree[i] = false;
        }
        cost[1] = 0;
        inSubTree[1] = true;
    }

    void printAllNodes() {
        for(int i = 1; i <= n; i ++) {

            cout << "Node #" << i << ": ";
            nodes[i]->print();
            cout << endl;
        }
    }

    void printAllDists() {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                cout << "dist[" << i << "][" << j << "] = " << dist[i][j] << endl;
            }
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

    Graph graph = Graph();
    graph.printAllNodes();
    graph.printAllDists();
    graph.prim();

    return 0;
}