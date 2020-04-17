/*
	Heavy-Light Decomposition

	Implementacao do problema: https://acm.timus.ru/problem.aspx?space=1&num=1553

	Encontrar o maximo valor de um vertice no caminho entre dois vertices, com
	queries de update de incremento no valor de um vertice.
*/


#include<bits/stdc++.h>
 
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define INF 0x3f3f3f3f
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
	x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

struct segtree {
	vector <int> seg;
	int n, k, a, b;
	segtree () { }
	segtree (int n) : n(n) {
		seg.resize(4*n+10, 0);
	}
	int query (int r, int i, int j) {
		if (i > b or j < a) return 0;
		if (i >= a and j <= b) return seg[r] += k;
		int mid = (i + j) / 2;
		int le = query(r*2, i, mid);
		int ri = query(r*2+1, mid+1, j);
		seg[r] = max(seg[r*2], seg[r*2+1]);
		return max(le, ri);
	}
	int query (int l, int r) {
		a = l; b = r; k = 0;
		return query(1, 0, n-1);
	}
	void update (int p, int val) {
		a = b = p; k = val;
		query(1, 0, n-1);
	}
} st;
 
const int N = 101234;
int pai[N][20], cost[N], prof[N], size[N];
int heavy[N];
vector <int> g[N];
int query_lca (int u, int v) {
	if (prof[u] > prof[v]) swap (u, v);
	int diff = prof[v] - prof[u];
	for (int j = 0; j < 20; j++) {
		if (diff & (1<<j)) 
			v = pai[v][j];
	}
	if (u == v) return u;
	for (int j = 19; j >= 0; j--) {
		if (pai[u][j] != pai[v][j]) {
			u = pai[u][j];
			v = pai[v][j];
		}
	}
	return pai[u][0];
}
void dfs (int u, int pu, int p = 0) {
	size[u] = 1;
	prof[u] = p;
	for (int v : g[u]) {
		if (v == pu) continue;
		dfs(v, u, p+1);
		pai[v][0] = u;
		size[u] += size[v];
		if (size[heavy[u]] < size[v]) 
			heavy[u] = v;
	}
}

int cnt_chain, chainId[N];
vector < int > chains[N];
int posChain[N], ent[N], sai[N], dfscnt;
void hld (int u, int pu, int chain) {
	
	chains[chain].pb(u);
	chainId[u] = chain;
	posChain[u] = chains[chain].size() - 1;
	ent[u] = dfscnt++;

	if (heavy[u] != 0) 
		hld(heavy[u], u, chain);
	
	//novas chains
	for (auto v : g[u]) {
		if (v == pu or v == heavy[u]) continue; 
		cnt_chain++;
		hld(v, u, cnt_chain);
	}
 
	sai[u] = dfscnt-1;
}
 
int query (int u, int lca) {
	int ans = 0;
	while (true) {
		if (chainId[u] != chainId[lca]) {
			int head = chains[chainId[u]][0];
			ans = max(ans, st.query(ent[head], ent[u]));
			u = pai[head][0];
		} else {
			ans = max(ans, st.query(ent[lca], ent[u]));
			return ans;
		}
	}
}

int main (void) {
	int n; rd(n);
	st = segtree(n);

	for (int i = 0 ; i+1 < n; i++) {
		int u, v;
		rd(u); rd(v);
		g[u].pb(v);
		g[v].pb(u);
	}

	memset (pai, -1, sizeof pai);
	dfs(1, 0);
	hld(1, 0, 0);
	
	//build LCA
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			if (pai[i][j-1] != -1)
				pai[i][j] = pai[pai[i][j-1]][j-1];
		}
	}

	int q; rd(q);
	while (q--) {
		char c; scanf("%c", &c);
		if (c == 'I') {
			int u, val;
			rd(u); rd(val);
			st.update(ent[u], val);
		} else {
			int u, v;
			rd(u); rd(v); 
			int lca = query_lca(u, v);
			printf("%d\n", max(query(u, lca), query(v, lca)));
		}
	}
	return 0;
}
