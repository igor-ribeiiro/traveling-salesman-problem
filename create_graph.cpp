#include <iostream>
#include <cmath>
#include<fstream>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int size = rand() % 50 + 50;
    ofstream input("../input.txt", ofstream::out);
    vector<int> vertices;
    vector<int> xs;
    vector<int> ys;

    vertices.resize((unsigned long) size+1);
    xs.resize((unsigned long) size+1);
    ys.resize((unsigned long) size+1);

    for(int i = 1; i <= size; i ++) {
        vertices[i] = i;
        int rand1 = rand()%100000 + 2;
        int rand2 = rand()%100000 + 2;
        xs[i] = rand1;
        ys[i] = rand2;
    }

    random_shuffle(vertices.begin(), vertices.end());
    random_shuffle(xs.begin(), xs.end());
    random_shuffle(ys.begin(), ys.end());

    input << size << endl;
    for(int i = 1; i <= size; i ++) {
        input << vertices[i] << " " << xs[i] << " " << ys[i] << endl;
    }

    return 0;
}