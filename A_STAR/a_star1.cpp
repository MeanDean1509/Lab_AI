#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 1000;

struct Canh {
    int d, dke, trongso;
};

int nDinh, nCanh, BatDau, KetThuc;
int* h;
Canh* c;

struct Node {
    int dinh;
    int g, h;

    Node(int d, int g, int h) : dinh(d), g(g), h(h) {}

    bool operator>(const Node& other) const {
        return g + h > other.g + other.h;
    }
};

void docfile() {
    ifstream file("Graphot1.txt");
    file >> nDinh >> nCanh;
    file >> BatDau >> KetThuc;

    h = new int[nDinh + 1];
    c = new Canh[nCanh];

    for (int i = 0; i < nCanh; i++) {
        file >> c[i].d >> c[i].dke >> c[i].trongso;
    }

    for (int i = 1; i <= nDinh; i++) {
        file >> h[i];
    }
}

pair<int, int*> AStar() {
    int* dist = new int[nDinh + 1];
    for (int i = 0; i <= nDinh; ++i) {
        dist[i] = MAX;
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(BatDau, 0, h[BatDau]));
    dist[BatDau] = 0;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        int u = cur.dinh;
        int g = cur.g;

        if (u == KetThuc) {
            int* path = new int[nDinh];
            path[0] = u;
            int distance = 0;
            int count = 1;
            while (u != BatDau) {
                for (int i = 0; i < nCanh; i++) {
                    if (c[i].dke == u && dist[c[i].d] == dist[u] - c[i].trongso) {
                        u = c[i].d;
                        distance += c[i].trongso;
                        path[count++] = u;
                        break;
                    }
                }
            }
            reverse(path, path + count);
            cout << "Duong di: ";
            for (int i = 0; i < count; ++i) {
                cout << path[i] << " ";
            }
            cout << "\nKhoang cach: " << distance << endl;
            delete[] path;
            return {distance, dist};
        }

        for (int i = 0; i < nCanh; i++) {
            if (c[i].d == u) {
                int v = c[i].dke;
                int cost = c[i].trongso;

                int new_g = g + cost;
                int new_h = h[v];

                if (new_g < dist[v]) {
                    dist[v] = new_g;
                    pq.push(Node(v, new_g, new_h));
                }
            }
        }
    }

    return {MAX, nullptr};
}

int main() {
    docfile();
    auto result = AStar();


    delete[] h;
    delete[] c;

    return 0;
}
