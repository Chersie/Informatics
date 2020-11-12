#include <iostream>
#include <vector>
#include <queue> // читается как кьюеюе

using namespace std;
const int inf = 101; // всего вершин может быть 100 => длина пути, равная 101 - недостижима

struct vertex { // состояние вершины
    bool vis;
    int pr, dist;
};


void rec(int u, vector <vertex> &a) { // функция для вывода ответа (спускаемся по предкам, выводим с самого нижнего, т.е. с v1 и поднимаясь до v2)
    if (a[u].pr != u) {
        rec(a[u].pr, a); // если ещё можно спускаться, спускаемся
        cout << u + 1 << ' '; // потом выводим
    }
    else {
        cout << u + 1 << ' '; // если уже некуда спускаться, просто выводим
    }
}

vector <vector <int> > matrix_to_edl(vector <vector <int> > &matrix) { // конвертируем матрицу в список смежности
    int n = matrix.size();
    vector <vector <int> > edl(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (matrix[i][j]) {
                edl[i].push_back(j);
                edl[j].push_back(i);
            }
        }
    }
    return edl;

}
int main() {
    int n;
    cin >> n;
    vector <vector <int> > matrix(n); // матрица, в ней и буду работать
    for(int i = 0; i < n; i++) {
        matrix[i].resize(n);
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    auto edl = matrix_to_edl(matrix);
    int v1, v2;
    cin >> v1 >> v2;
    v1--; v2--; // чтобы не ломались индексы
    queue <int> q;
    q.push(v1);
    vertex def; def.vis = false; def.pr = -1; def.dist = inf; // хз как нормально заполнить вектор своей структурой, поэтому делаю вот так вот калечно
    vector <vertex> a(n, def); // вектор состояний каждой вершинки, записываю в структуру, пушто удобно добавлять параметры вершинам, если это нужно будет в других вариантах такой же задачи
    a[v1].pr = v1; a[v1].dist = 0; a[v1].vis = true; // предок первоначальной вершины - сама эта вершина(мне так проще, чем делать -1 здесь и -2 в случае отсутствия пути_
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for(int i = 0; i < edl[curr].size(); i++) {
            if (!a[edl[curr][i]].vis) { // если вершина не посещена
                a[edl[curr][i]].dist = a[curr].dist + 1; // бфсик
                a[edl[curr][i]].vis = true;
                a[edl[curr][i]].pr = curr;
                q.push(edl[curr][i]);
            }
        }
    }
    if (a[v2].pr != -1) { // костыли для разных вариантов (если путь есть)
        if (v1 == v2) { // если длина пути равна 0 (18-ый тест :) )
            cout << 0;
            return 0;
        }
        cout << a[v2].dist << '\n';
        rec(v2, a);
    }
    else { // если пути нет
        cout << -1;
    }
    return 0;
}
