#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int inf = 401; // не уверен, что здесь максимальный ответ N*N, но с inf = 401 ответ даётся правильный

struct coords {// структурка для хранения координат
    int x, y;
};

coords x_y(int x, int y) { // make_pair, но для моей структурки
    coords answ;
    answ.x = x; answ.y = y;
    return answ;
}

struct dot { // состояние точки
    bool vis;
    int dist;
    coords pr;
};

void rec(coords u, vector <vector <dot> > &a) { // вывод ответа по той же схеме, что и в задаче A
    if (a[u.x][u.y].pr.x != u.x || a[u.x][u.y].pr.y != u.y) {
        rec(x_y(a[u.x][u.y].pr.x, a[u.x][u.y].pr.y), a);
        cout << u.x + 1 << ' ' << u.y + 1 << '\n';
    }
    else {
        cout << u.x + 1 << ' ' << u.y + 1 << '\n';
    }
}


int main()
{
    int n;
    int x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;
    vector <vector <dot> > a(n); // матрица состояний точек
    queue < coords > q;
    vector < coords > w = {x_y(-2, -1), x_y(-2, 1), // все возможные ходы коня(так удобнее)
                           x_y(-1, -2), x_y(-1, 2),
                           x_y(1, -2), x_y(1, 2),
                           x_y(2, -1), x_y(2, 1)};
    dot def; def.vis = false; def.dist = inf; def.pr = x_y(-1, -1); // опять всё делаю калечно..
    for(int i = 0; i < n; i++) {
        a[i].resize(n, def);
    }
    a[x1][y1].vis = true; a[x1][y1].dist = 0; a[x1][y1].pr = x_y(x1, y1); // вершина начала посещена, расстояние до неё 0 и её предок - она сама(в этой задаче можно было поставить и -1, т.к. -1 больше не используется
    q.push(x_y(x1, y1));
    while (!q.empty()) {
        coords curr = q.front();
        q.pop();
        for(int i = 0; i < w.size(); i++) {
            int new_x = curr.x + w[i].x, // x после шага коня
                new_y = curr.y + w[i].y; // y после шага коня
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) { // если x и y не выходят за рамки поля
                if (!a[new_x][new_y].vis) { // если клетка ещё не была посещена
                    a[new_x][new_y].dist = a[curr.x][curr.y].dist + 1; // бфсик
                    a[new_x][new_y].pr = x_y(curr.x, curr.y);
                    a[new_x][new_y].vis = true;
                    q.push(x_y(new_x, curr.y + w[i].y));
                }
            }
        }
    }
    cout << a[x2][y2].dist << '\n'; // кол-во ходов
    rec(x_y(x2, y2), a); // сами ходы
    return 0;
}
