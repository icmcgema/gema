#include <bits/stdc++.h>
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define For(a,b) for(int (i)=0; (i)<(b); (i++))
#define Fo(a,b,c) for(int (i)=(b); (i)<=(c); (i++))

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
const int INF=0x3f3f3f3f;
const int N=212345;

int n, m;

vector<ii> adj[N];
priority_queue<ii, vector<ii>, greater<ii>> pq;
bool vis[N];

int main(void) {
	cin >> n >> m;

	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].pb(mk(w,v));
		adj[v].pb(mk(w,u));
	}


	// algoritmo Prim

	int u = 1;

	int ans = 0;

	For(i,n-1) { // cada iteracao adiciona uma aresta

		vis[u]=true;

		for (auto e : adj[u])
			if (!vis[e.se])
				pq.push(e);

		while (vis[pq.top().se])
			pq.pop();

		u = pq.top().se;
		ans += pq.top().fi;
	}

	cout << ans << endl;

	return 0;
}
