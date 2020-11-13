#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <vector <int> > matrix_to_edl(vector <vector <int> > &matrix) { // конвертируем матрицу в список смежности
    int n = matrix.size();
    vector <vector <int> > edl(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (matrix[i][j]) {
                edl[i].push_back(j);
            }
        }
    }
    return edl;

}

void DFS(int u, vector <vector <int> > &edl, vector<int> &vis) { // самый обычный DFS
    if (vis[u])
        return;
    vis[u] = true;
    for(int i = 0; i < edl[u].size(); i++) {
        DFS(edl[u][i], edl, vis);
    }
    return;
}

int main()
{
    int n, v;
    cin >> n >> v;
    vector <vector <int> > matrix(n);
    vector <int> visited(n);
    for(int i = 0; i < n; i++) {
        matrix[i].resize(n);
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    vector <vector <int> > edl = matrix_to_edl(matrix);
    DFS(v - 1, edl, visited); // запускаем дфс для вершины v с 0-индексацией
    cout << count(visited.begin(), visited.end(), 1) << '\n'; // выводим кол-во посещённых вершин
    return 0;
}
