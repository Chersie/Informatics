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

bool DFS(int u, int pr, vector <vector <int> > &edl, vector<int> &vis) { // dfs, но храним предка для нашей вершины, чтобы проверять их по цветам и находить циклы
    if (vis[u] == 1) { // пришли в незавершённую вершину, значит, есть цикл
        //cout << u + 1 << '\n';
        return false;
    }
    vis[u] = 1;
    //cout << u + 1  << ' ';
    bool answ = true;
    for(int i = 0; i < edl[u].size(); i++) {
        if (vis[edl[u][i]] != 2 && edl[u][i] != pr) { // проверка, чтобы не ходить в уже завершённые вершины и предков
            answ = answ && DFS(edl[u][i], u, edl, vis); // если для каждой вершины, с которой есть ребро, ответ будет true, то и для текущей вершины ответ будет true
        }
    }
    vis[u] = 2; // завершаем вершину, красим её в 2
    return answ;
}

int main()
{
    int n;
    cin >> n;
    vector <vector <int> > matrix(n);
    vector <int> visited(n, 0);
    for(int i = 0;i < n; i++) {
        matrix[i].resize(n);
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    auto edl = matrix_to_edl(matrix);
    if(DFS(0, -1, edl, visited) && count(visited.begin(), visited.end(), 2) == n) { // если нет циклов и все вершины посещены, то граф = дерево
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    return 0;
}
