#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1003;
int mx[MAXN],my[MAXN];
bool vy[MAXN];
vector<int> edge[MAXN];

int n, m;
int greedy_matching()
{
    int c = 0;
    for (int x=1; x<=n; ++x) {
        if (mx[x] == -1) {
            for (auto y : edge[x]) {
                if (my[y] == -1) {
                        mx[x] = y; my[y] = x;
                        c++;
                        break;
                }
            }
        }
    }
    return c;
}
 
bool DFS(int x)
{
    for (auto y : edge[x]) {
        if (!vy[y]) {
            vy[y] = true;
            if (my[y] == -1 || DFS(my[y]))
            {
                mx[x] = y; my[y] = x;
                return true;
            }
        }
    }
    return false;
}

int bipartite_matching()
{
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
 
    int c = greedy_matching();
 
    for (int x=1; x<=n; ++x)
        if (mx[x] == -1)  
        {
            memset(vy, false, sizeof(vy));
            if (DFS(x)) c++;
        }
    return c;
}


int main () {
    cin >> n >> m;
    int ecnt;
    cin >> ecnt;
    while (ecnt--) {
        int f,t;
        cin >> f >> t;
        edge[f].emplace_back(t);
    }    

    cout << bipartite_matching() << endl;
}