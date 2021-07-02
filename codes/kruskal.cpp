#include <bits/stdc++.h>

using namespace std;

// union - find
struct unionfind {

	vector<int> par;
	vector<int> sz;

	// par[u] = v // u eh descendente direto de v
	// sz[u] = tamanho da componente em que u eh a raiz

	unionfind(int n) {
		par.resize(n + 1);
		sz.resize(n + 1);
		for(int i = 1; i <= n; ++i) {
			par[i] = i;
			sz[i] = 1;
		}
	}

	int find(int u) {
		return par[u] == u? u : par[u] = find(par[u]);
	}

	void unite(int u, int v) {
		u = find(u);
		v = find(v);

		if(sz[u] > sz[v]) swap(u, v);

		par[u] = v; // u -> v
		sz[v] += sz[u];
	}

	// u e v estao na mesma componente? find(u) == find(v)
	// cc. juntar u e v -> unite(u, v)
};

int cmp(tuple<int, int, int> a, tuple<int, int, int> b) {
	return get<2>(a) < get<2>(b);
}

int kruskal(vector<tuple<int, int, int>> edges, int n) {
	int m = edges.size();

	sort(edges.begin(), edges.end(), cmp);

	unionfind uf(n);
	int tot = 0;
	for(auto & [u, v, c] : edges) {
		if(uf.find(u) != uf.find(v)) {
			uf.unite(u, v);
			tot += c;
		}
	}

	return tot;
}

int main() {

	int n, m; cin >> n >> m;

	vector<tuple<int, int, int> > edges;
	for(int i = 0; i < m; ++i) {
		int u, v, c; cin >> u >> v >> c;
		edges.emplace_back(u, v, c);
	}

	cout << kruskal(edges, n) << '\n';

	return 0;
}