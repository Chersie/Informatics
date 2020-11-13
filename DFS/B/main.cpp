#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
stringstream ss;

void DFS(int u, vector <vector <int> > &edl, vector<int> &vis) { // dfs, только записываем вершины, которые мы посещаем, в свой поток
    if (vis[u])
        return;
    vis[u] = true;
    ss << u + 1 << ' ';
    for(int i = 0; i < edl[u].size(); i++) {
        DFS(edl[u][i], edl, vis);
    }
    return;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector <vector <int> > edl(n);
    for(int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        f--; t--;
        edl[f].push_back(t);
        edl[t].push_back(f);
    }
    vector <int> visited(n, 0);
    int answ = 0;
    for(int i = 0; i < n; i++) {
        if (!visited[i]) {
            answ++;
            DFS(i, edl, visited);
            ss << '\n';
        }
    }
    cout << answ << '\n'; // вывели посчитанный ответ
    string s;
    while (getline(ss, s)) {
        cout << count(s.begin(), s.end(), ' ') << '\n'; // вывели размер компаненты
        cout << s << '\n'; // и саму компаненту
    }
    return 0;
}
