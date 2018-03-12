#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>

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
        }
        else {
            cout << "File input not found" << endl;
            input.close();
            exit(1);
        }
        input.close();
    }

    void printAllNodes() {
        for(int i = 1; i <= n; i ++) {

            cout << "Node #" << i << ": ";
            nodes[i]->print();
            cout << endl;
        }
    }

private:
    int n;
    vector<Node*> nodes;
};

int main() {
    ios_base::sync_with_stdio(false);

    Graph graph = Graph();
    
    graph.printAllNodes();

    return 0;
}