#include <iostream>
#include <vector>
#include <queue> // �������� ��� ������

using namespace std;
const int inf = 101; // ����� ������ ����� ���� 100 => ����� ����, ������ 101 - �����������

struct vertex { // ��������� �������
    bool vis;
    int pr, dist;
};


void rec(int u, vector <vertex> &a) { // ������� ��� ������ ������ (���������� �� �������, ������� � ������ �������, �.�. � v1 � ���������� �� v2)
    if (a[u].pr != u) {
        rec(a[u].pr, a); // ���� ��� ����� ����������, ����������
        cout << u + 1 << ' '; // ����� �������
    }
    else {
        cout << u + 1 << ' '; // ���� ��� ������ ����������, ������ �������
    }
}

vector <vector <int> > matrix_to_edl(vector <vector <int> > &matrix) { // ������������ ������� � ������ ���������
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
    vector <vector <int> > matrix(n); // �������, � ��� � ���� ��������
    for(int i = 0; i < n; i++) {
        matrix[i].resize(n);
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    auto edl = matrix_to_edl(matrix);
    int v1, v2;
    cin >> v1 >> v2;
    v1--; v2--; // ����� �� �������� �������
    queue <int> q;
    q.push(v1);
    vertex def; def.vis = false; def.pr = -1; def.dist = inf; // �� ��� ��������� ��������� ������ ����� ����������, ������� ����� ��� ��� ��� �������
    vector <vertex> a(n, def); // ������ ��������� ������ ��������, ��������� � ���������, ����� ������ ��������� ��������� ��������, ���� ��� ����� ����� � ������ ��������� ����� �� ������
    a[v1].pr = v1; a[v1].dist = 0; a[v1].vis = true; // ������ �������������� ������� - ���� ��� �������(��� ��� �����, ��� ������ -1 ����� � -2 � ������ ���������� ����_
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for(int i = 0; i < edl[curr].size(); i++) {
            if (!a[edl[curr][i]].vis) { // ���� ������� �� ��������
                a[edl[curr][i]].dist = a[curr].dist + 1; // �����
                a[edl[curr][i]].vis = true;
                a[edl[curr][i]].pr = curr;
                q.push(edl[curr][i]);
            }
        }
    }
    if (a[v2].pr != -1) { // ������� ��� ������ ��������� (���� ���� ����)
        if (v1 == v2) { // ���� ����� ���� ����� 0 (18-�� ���� :) )
            cout << 0;
            return 0;
        }
        cout << a[v2].dist << '\n';
        rec(v2, a);
    }
    else { // ���� ���� ���
        cout << -1;
    }
    return 0;
}
