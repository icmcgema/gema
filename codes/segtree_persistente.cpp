// solucao de https://cses.fi/problemset/task/1737/
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
#define mid ((l+r)>>1)
 
struct node {
    ll val;
    node * l, * r;
    
    node() {
        l = r = NULL;
    }
};
 
node * update(node * cur, int l, int r, int j, ll x) {
    if(l > j or r < j) return cur;
    node * u = cur? new node(*cur) : new node();
    
    if(l == r) {
        u->val = x;
    } else {
        u->l = update(u->l, l, mid, j, x);
        u->r = update(u->r, mid+1, r, j, x);
        u->val = (u->l? u->l->val : 0) + (u->r? u->r->val : 0);
    }
    return u;
}
 
ll query(node * cur, int l, int r, int a, int b) {
    if(!cur or r < a or l > b) return 0;
    
    if(l >= a and r <= b) return cur->val;
    return query(cur->l, l, mid, a, b) + query(cur->r, mid+1, r, a, b);
}
 
const int N = 2e5 + 7;
node * ver[N];
 
int main() {
    int n, q; cin >> n >> q;
    
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        ver[1] = update(ver[1], 1, n, i, x);
    }
    
    int cur = 1;
    while(q--) {
        int op; cin >> op;
        
        if(op == 1) { // atualiza ver[k] pra arr[ver[k]][i] = x
            int k, i, x; cin >> k >> i >> x;
            
            ver[k] = update(ver[k], 1, n, i, x);
        } else if(op == 2) { // consulta soma arr[ver[k]][a..b]
            int k, a, b; cin >> k >> a >> b;
            
            cout << query(ver[k], 1, n, a, b) << '\n';
        } else { // fazer uma copia da ver[k]
            int k; cin >> k;
            
            ver[++cur] = ver[k];
        }
    }
}
