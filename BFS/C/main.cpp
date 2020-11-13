#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int inf = 1001;

struct coords {
    int x, y;
};

coords x_y(int x, int y) { // make_pair, но для моей структурки
    coords answ;
    answ.x = x; answ.y = y;
    return answ;
}

struct dot {
    bool vis;
    int dist;
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector <vector <int> > matrix(n);
    queue <coords> q;

    vector <vector <dot> > a(n);
    dot def; def.dist = inf; def.vis = false;
    vector < coords > w = {x_y(-1, 0), x_y(1, 0), // все возможные ходы в табличке(так удобнее)
                           x_y(0, -1), x_y(0, 1)};
    for(int i = 0; i < n; i++) {
        a[i].resize(m, def);
    }

    for(int i = 0; i < n; i++) {
        matrix[i].resize(m);
        for(int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j]) { // если клетка таблички равна 1, то записываем её в очередь для БФСа
                q.push(x_y(i, j));
                a[i][j].dist = 0;
                a[i][j].vis = true;
            }
        }
    }

    while (!q.empty()) {
        coords curr = q.front();
        q.pop();
        for(int i = 0; i < w.size(); i++) {
            coords nw; // коорды нашей точки в таблице
            nw.x = curr.x + w[i].x;
            nw.y = curr.y + w[i].y;
            if (nw.x >= 0 && nw.x < n && nw.y >= 0 && nw.y < m) { // проверка координат на корректность
                if (!a[nw.x][nw.y].vis) { // если вершина не посещена

                    a[nw.x][nw.y].dist = a[curr.x][curr.y].dist + 1; // бфсик без предков
                    a[nw.x][nw.y].vis = true;
                    q.push(x_y(nw.x, nw.y));
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j].dist << ' '; // ответ - таблица дистанций
        }
        cout << '\n';
    }
    return 0;
}
