#include <bits/stdc++.h>



using namespace std;

typedef pair<int, int> ii;



const int N = 1e5 + 7;

vector<ii> e[N];

int pai[N][25], f[N][25];

int tim[N], lev[N];



int tt;

void dfs(int u, int par = -1, int w = -1, int l = 0) {

    tim[u] = ++tt;

    lev[u] = l;

    // calcular binary lifting

    pai[u][0] = par == -1? u : par;

    

    f[u][0] = w;

    for(int i = 1; i < 25; ++i) {

        pai[u][i] = pai[pai[u][i-1]][i-1];

        f[u][i] = max(f[u][i-1], f[pai[u][i-1]][i-1]);

    }

    

    for(auto & [v, w] : e[u]) {

        if(v == par) continue;

        dfs(v, u, w, l + 1);

    }

}



int lca(int u, int v) {

    if(u == v) return u;

    

    if(tim[u] > tim[v]) {

        swap(u, v);

    }

    

    for(int i = 24; i >= 0; --i) {

        int w = pai[v][i];

        if(tim[w] > tim[u]) v = w;

    }

    return pai[v][0];

}



int query(int u, int v) {

    int uv = lca(u, v);
    int d1 = lev[u] - lev[uv];
    int d2 = lev[v] - lev[uv];
    int ans1 = 0;

    for(int i = 24; i >= 0; --i) {
        if((d1 >> i)&1) {
            ans1 = max(ans1, f[u][i]);
            u = pai[u][i];
        }
    }

    int ans2 = 0;

    for(int i = 24; i >= 0; --i) {

        if((d2 >> i)&1) {
            ans2 = max(ans2, f[v][i]);
            v = pai[v][i];

        }

    }

    

    return max(ans1, ans2);
}



int main() {
    int n; cin >> n;

    for(int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;

        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    
    dfs(1);
    
    int q; cin >> q;
    
    while(q--) {
        int a, b; cin >> a >> b;
        cout << query(a, b) << endl;
    }

    return 0;

}
