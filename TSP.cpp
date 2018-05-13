#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>
#include <bits/stdc++.h>

//#define CHAR_DEBUG
#define DEBUG

#define INF 10000000

using namespace std;

typedef pair<int, int> ii;

class Debugger {
public:
#ifdef CHAR_DEBUG

    static char convertIntToChar(int x) {
        return (char)(x+'a'-1);
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

    Node(float x, float y, int ind) {
        this->x = x;
        this->y = y;
        this->ind = ind;
    }

    ~Node() {
        adjs.clear();
    }

    void addAdjs(Node *n, int dist, int index) {
        adjs.push_back(make_pair(dist, make_pair(index, n)));
    }

    int dist(Node *n) {
        float xd = x - n->getX();
        float yd = y - n->getY();

        return (int)(sqrt(xd*xd + yd*yd) + 0.5);
    }

    int getInd() {
        return ind;
    }

    float getX(){
        return x;
    }

    float getY() {
        return y;
    }

    vector<pair<int, pair<int, Node*> > > getAdjs() {
        return adjs;
    }

    Node* getAdjNode(int i) {
        return adjs[i].second.second;
    }

    void sortAdjs() {
        sort(adjs.begin(), adjs.end());
    }

    void print() {
        cout << "(" << x << ", " << y << ")";
    }

private:
    float x, y;
    int ind;
    vector<pair<int, pair<int, Node*> > > adjs; // dist, index, node
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
    explicit Graph(const string &fileName) {
        ifstream input;
        input.open(fileName.c_str(), ifstream::in);
        n = 0;

        if (input.is_open()) {
            input >> n;

            nodes.resize((unsigned long) n+1);
            if(n != 0) {
                while (!input.eof()) {
                    float i, x, y;
                    input >> i >> x >> y;
                    nodes[i] = new Node(x, y, i);
                }
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
            cout << "File with name: " << fileName << endl;
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
        priority_queue<pair<ii, int>, vector<pair<ii, int> >, greater<pair<ii, int> > > pq; // cost, parent, node
        int parent[n+1];

        for(int i = 1; i <= n; i ++) {
            inSubTree[i] = false;
            cost[i] = INF;
        }
        if(n != 0) {
            inSubTree[1] = true;
            pq.push(make_pair(make_pair(cost[1], -1), 1));
        }

        while(!pq.empty()) {
            ii p = pq.top().first;
            int u = pq.top().second;
            int d = p.first;
            int dad = p.second;
            pq.pop();

            inSubTree[u] = true;

            for(int v = 1; v <= n; v ++) {
                if(inSubTree[v]) continue;
                if(cost[v] > dist[u][v]) {
                    cost[v] = dist[u][v];
                    parent[v] = u;
                    pq.push(make_pair(make_pair(cost[v], u), v));
                }
                if(cost[v] == dist[u][v] and u < dad) {
                    cost[v] = dist[u][v];
                    parent[v] = u;
                    pq.push(make_pair(make_pair(cost[v], u), v));
                }
            }
        }

        for(int i = 2; i <= n; i ++) {
            int d = dist[i][parent[i]];
            edges.push_back(Edge(i, parent[i], d));
            nodes[i]->addAdjs(nodes[parent[i]], d, parent[i]);
            nodes[parent[i]]->addAdjs(nodes[i], d, i);
        }
    }

    void travelingSalesman() {
        bool visited[n+1];
        stack<int> pilha;

        for(int i = 1; i <= n; i ++) {
            visited[i] = false;
        }
        if(n != 0)
            pilha.push(1);

        while(!pilha.empty()) {
            int u = pilha.top();
            pilha.pop();
            visited[u] = true;
            visitedOrder.push_back(u);

            for(int i = 0; i < (int)nodes[u]->getAdjs().size(); i ++) {
                int ind = nodes[u]->getAdjNode(i)->getInd();

                if(!visited[ind]) {
                    pilha.push(ind);
                }
            }
        }
        if(n != 0)
            visitedOrder.push_back(1); // Going back to the beginning
    }

    void printBestPath() {
        cout << endl;
        for(int i = 0; i < (int)visitedOrder.size(); i ++) {
            if(i != (int)visitedOrder.size()-1)
                cout << Debugger::convertIntToChar(visitedOrder[i]) << "->";
            else
                cout << Debugger::convertIntToChar(visitedOrder[i]) << endl << endl;
        }
    }

    void printBestCostToFile(ofstream &output) {
        long long int totalCost = 0;

        if(n != 0) {
            for (int i = 0; i < (int) visitedOrder.size() - 1; i++) {
                totalCost += dist[visitedOrder[i]][visitedOrder[i + 1]];
            }
            totalCost += dist[visitedOrder[visitedOrder.size() - 1]][visitedOrder[0]];
        }
        output << totalCost << endl;
    }

    void printAllNodes() {
        cout << endl;

        for(int i = 1; i <= n; i ++) {
            cout << "Node #" << Debugger::convertIntToChar(nodes[i]->getInd()) << ": ";
            nodes[i]->print();
            cout << ", with adjs (dist, node) = ";

            for(int j = 0; j < (int)nodes[i]->getAdjs().size(); j ++) {
                if(j != (int)nodes[i]->getAdjs().size()-1)
                    cout << "(" << nodes[i]->getAdjs()[j].first << ")(" <<
                         Debugger::convertIntToChar(nodes[i]->getAdjNode(j)->getInd()) << ") ";
                else
                    cout << "(" << nodes[i]->getAdjs()[j].first << ")(" <<
                         Debugger::convertIntToChar(nodes[i]->getAdjNode(j)->getInd()) << ")" << endl;
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
                cout << Debugger::convertIntToChar(i) << " ";
            else
                cout << Debugger::convertIntToChar(i) << endl;
        }

        for(int i = 1; i <= n; i ++) {
            cout << Debugger::convertIntToChar(i) << " ";
            for(int j = 1; j <= n; j ++) {
                if(j != n)
                    cout << dist[i][j] << " ";
                else
                    cout << dist[i][j] << endl;
            }
        }
    }

    void printAllEdges() {
        cout << endl << "Number of edges = " << (int)edges.size() << endl;
        for(int i = 0; i < (int)edges.size(); i ++) {
            cout << "Edge #" << i+1 << ": " <<Debugger::convertIntToChar(edges[i].getVertices().first) << " - "
                 << Debugger::convertIntToChar(edges[i].getVertices().second)
                << " with distance = " << edges[i].getTam() << endl;
        }
    }

    void printAllVisitedOrders() {
        cout << "Visited Orders with size = " << (int) visitedOrder.size() << ":" << endl;
        for(int i = 0; i < (int) visitedOrder.size(); i ++) {
            if(i != (int) visitedOrder.size()-1)
                cout << Debugger::convertIntToChar(visitedOrder[i]) << " -> ";
            else
                cout << Debugger::convertIntToChar(visitedOrder[i]) << endl;
        }
        cout << endl;
    }

private:
    int n;
    vector<Node*> nodes;
    vector<Edge> edges;
    vector<vector<int> > dist;
    vector<int> visitedOrder;
};

string getInputString(int i) {
//    return "../ent10.txt";
    string input = "ent";
    ostringstream s;
    s << i;

    if(i < 10)
        input += "0";

    input += s.str() + ".txt";
    return input;
}

int main(int argc, char *argv[]) {
    Graph *graph;
    ofstream output("saida.txt", std::ofstream::out);
    int numeroDeEntradas = 99;

    if(argc == 2) {
        try {
            numeroDeEntradas = atoi(argv[1]);
        } catch (...) {
            std::cout << "Invalid number of inputs m" << std::endl;
        }
    }

    for(int i = 0; i < numeroDeEntradas; i ++) {
        graph = new Graph(getInputString(i+1));

        graph->prim();
        graph->travelingSalesman();
        graph->printBestCostToFile(output);
#ifdef DEBUG
        graph->printAllNodes();
        graph->printAllVisitedOrders();
        graph->printAllEdges();
#endif


        delete(graph);
    }
    output.close();
    return 0;
}