#include <bits/stdc++.h>

#define pb push_back
using namespace std;
typedef long long ll;

const int N = 1000007;
int red[N];
vector<int> e[N];

bool morto[N];

int sz[N];

void calc_sz(int u, int par = -1) {
	sz[u] = 1;
	for(int v : e[u]) {
		if(v == par or morto[v]) continue;
		calc_sz(v, u);
		sz[u] += sz[v];
	}
}

int centroid(int u, int tot) {
	for(int v : e[u]) {
		if(sz[v] > sz[u] or morto[v]) continue;
		if(2 * sz[v] > tot) return centroid(v, tot);
	}
	return u;
}

int freq[N + N]; // frequencia dos saldos

void dfs(int u, vector<int> & saldos, int par = -1, int s = 0) {
	// x + s + (red[centroid]? 1 : -1) == 0
	// x = - s - (red[centroid]? 1 : -1)
	s += red[u]? 1 : -1;
	saldos.push_back(s);

	for(int v : e[u]) {
		if(v == par or morto[v]) continue;
		dfs(v, saldos, u, s);
	}
}

ll centroid_decomp(int u) {
	// calcular tamanhos das subarvores
	calc_sz(u);

	u = centroid(u, sz[u]); // u virou centroide

	morto[u] = true;
	// processar os caminhos que passam pelo centroide (u)

		int * freq = ::freq + N;

		
		// processa os caminhos passando por u
		ll ans = 0;

		vector<int> vec;
		for(int v : e[u]) {
			if(morto[v]) continue;
			vector<int> saldos;
			dfs(v, saldos);

			for(int s : saldos) {
				ans += freq[-s - (red[u]? 1 : -1)];
				ans += (s + (red[u]? 1 : -1)) == 0;
			}

			for(int s : saldos) {
				vec.pb(s);
				freq[s]++;
			}

		}

		for(int x : vec) freq[x] = 0;

	for(int v : e[u]) {
		if(morto[v] == false) ans += centroid_decomp(v);
	}

	// morto[u] = false;
	return ans;
}

int main() {
	int n; cin >> n;

	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		e[u].pb(v);
		e[v].pb(u);
	}

	for(int i = 1; i <= n; ++i) {
		cin >> red[i];
	}

	ll ans = centroid_decomp(1);

	cout << ans << endl;
}