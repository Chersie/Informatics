#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct coords {// структурка для хранения координат
    char x, y;
};

coords x_y(char x, char y) { // make_pair, но для моей структурки
    coords answ;
    answ.x = x; answ.y = y;
    return answ;
}

struct dot { // состояние точки
    bool vis;
    int dist;
};

int main()
{
    const int inf = 10001;
    int n, m;
    cin >> n >> m;
    vector <vector <int> > matrix(n + 2);
    vector <vector <dot> > a(n);
    dot def; def.dist = inf; def.vis = false;
    for(int i = 0; i < n; i++) {
        a[i].resize(m, def);
    }
    queue <coords> q;
    q.push(x_y(0, 0));
    a[0][0].dist = 0; a[0][0].vis = true;
    for(int i = 0; i < n + 2; i++) {
        matrix[i].resize(m + 2, 1);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> matrix[i + 1][j + 1];
        }
    }
    while (!q.empty()) {
        coords curr = q.front();
        q.pop();
        coords new_coords; // в new_coords будут записаны координаты точки, стоящей рядом со стенкой в каждом из направлений
        for(int i = curr.x; matrix[i + 1][curr.y + 1] != 1; i++) { // направление вниз
            if (matrix[i + 1][curr.y + 1] == 2) { // если мы прошли по лунке, то вывели ответ
                cout << a[curr.x][curr.y].dist + 1 << '\n';
                return 0;
            }
            new_coords = x_y(i, curr.y); // в new_coords будут записаны координаты точки, стоящей рядом со стенкой

        }
        if (!a[new_coords.x][new_coords.y].vis) { // если точка с координатами new_coords ещё не была обработана, то применим на ней что?
            a[new_coords.x][new_coords.y].dist = a[curr.x][curr.y].dist + 1; // правильно, бфсик
            a[new_coords.x][new_coords.y].vis = true;
            q.push(new_coords);
        }
        for(char i = curr.x; matrix[i + 1][curr.y + 1] != 1; i--) { // направление вверх
            if (matrix[i + 1][curr.y + 1] == 2) { // если мы прошли по лунке, то вывели ответ
                cout << a[curr.x][curr.y].dist + 1 << '\n';
                return 0;
            }
            new_coords = x_y(i, curr.y); // в new_coords будут записаны координаты точки, стоящей рядом со стенкой

        }
        if (!a[new_coords.x][new_coords.y].vis) { // бфсик
            a[new_coords.x][new_coords.y].dist = a[curr.x][curr.y].dist + 1;
            a[new_coords.x][new_coords.y].vis = true;
            q.push(new_coords);
        }
        for(int j = curr.y; matrix[curr.x + 1][j + 1] != 1; j++) { // направление вправо
            if (matrix[curr.x + 1][j + 1] == 2) { // если мы прошли по лунке, то вывели ответ
                cout << a[curr.x][curr.y].dist + 1 << '\n';
                return 0;
            }
            new_coords = x_y(curr.x, j); // в new_coords будут записаны координаты точки, стоящей рядом со стенкой

        }
        if (!a[new_coords.x][new_coords.y].vis) { // бфсик
            a[new_coords.x][new_coords.y].dist = a[curr.x][curr.y].dist + 1;
            a[new_coords.x][new_coords.y].vis = true;
            q.push(new_coords);
        }
        for(int j = curr.y; matrix[curr.x + 1][j + 1] != 1; j--) { // направление влево
            if (matrix[curr.x + 1][j + 1] == 2) { // если мы прошли по лунке, то вывели ответ
                cout << a[curr.x][curr.y].dist + 1 << '\n';
                return 0;
            }
            new_coords = x_y(curr.x, j); // в new_coords будут записаны координаты точки, стоящей рядом со стенкой

        }
        if (!a[new_coords.x][new_coords.y].vis) { // бфсик
            a[new_coords.x][new_coords.y].dist = a[curr.x][curr.y].dist + 1;
            a[new_coords.x][new_coords.y].vis = true;
            q.push(new_coords);
        }
    }
    // в задаче дано, что ответ всегда будет, так что выполнение программы всегда прервётся до завершения циклов
    return 0;
}
