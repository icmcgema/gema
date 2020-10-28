#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mp make_pair
#define fi first
#define se second

int N, M, t;
int v[5][5] = {{0, 0, 0, 0, 0},
               {0, 0, 7, 1, 1},
               {0, 2, 1, 5, 3},
               {0, 3, 4, 0, 4},
               {0, 1, 0, 0, 8}};

struct NodeY{
    ll s;
    NodeY *L, *R;

    NodeY(){
        s = 0LL;
        L = NULL;
        R = NULL;
    }

    void update(int l, int r, int y, ll v){
        if(l == r){
            s = v;
        }else{
            int m = (l+r)/2;

            if(y <= m){
                if(L == NULL) L = new NodeY;

                L->update(l, m, y, v);
            }else if(m < y){
                if(R == NULL) R = new NodeY;

                R->update(m+1, r, y, v);
            }

            s = (L == NULL ? 0:L->s) + (R == NULL ? 0:R->s);
        }
    }

    void update2(NodeY *Left, NodeY *Right, int y, int l, int r){
        if(Left == NULL && Right == NULL) return;

        s = (Left == NULL ? 0:Left->s) + (Right == NULL ? 0:Right->s);

        if(l == r) return ;

        int m = (l+r)/2;

        if(y <= m){
            if(L == NULL) L = new NodeY;

            L->update2((Left == NULL ? NULL:Left->L), (Right == NULL ? NULL:Right->L), y, l, m);
        }else{
            if(R == NULL) R = new NodeY;

            R->update2((Left == NULL ? NULL:Left->R), (Right == NULL ? NULL:Right->R), y, m+1, r);
        }
    } 

    ll query(int l, int r, int a, int b){
        if(a <= l && r <= b){
            return s;
        }

        ll ans = 0;

        if(l != r){
            int m = (l+r)/2;

            if(b <= m && L != NULL){
                ans += L->query(l, m, a, b);
            }else if(m < a && R != NULL){
                ans += R->query(m+1, r, a, b);
            }else{
                if(L!= NULL) ans += L->query(l, m, a, b);
                if(R!= NULL) ans += R->query(m+1, r, a, b);
            }
        }

        return ans;
    }
};

struct NodeX{
    NodeY *segY;
    NodeX *L, *R;

    NodeX(){
        segY = new NodeY;
        L = NULL;
        R = NULL;
    }

    void update(int l, int r, int x, int y, ll v){
        if(l == r){
            segY->update(1, M, y, v);
        }else{
            int m = (l+r)/2;

            if(x <= m){
                if(L == NULL) L = new NodeX;

                L->update(l, m, x, y, v);
            }else if(m < x){
                if(R == NULL) R = new NodeX;

                R->update(m+1, r, x, y, v);
            }
        }

        segY->update2((L == NULL ? NULL:L->segY), (R == NULL ? NULL:R->segY), y, 1, M);
    } 

    ll query(int l, int r, int a, int b, int aY, int bY){
        if(a <= l && r <= b){
            return segY->query(1, M, aY, bY);
        }

        ll ans = 0;

        if(l != r){
            int m = (l+r)/2;

            if(b <= m && L != NULL){
                ans += L->query(l, m, a, b, aY, bY);
            }else if(m < a && R != NULL){
                ans += R->query(m+1, r, a, b, aY, bY);
            }else{
                if(L!= NULL) ans += L->query(l, m, a, b, aY, bY);
                if(R!= NULL) ans += R->query(m+1, r, a, b, aY, bY);
            }
        }

        return ans;
    }
};

int main(){
    N = 4;
    M = 4; 

    NodeX *segX = new NodeX;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            segX->update(1, N, i, j, v[i][j]);
        }
    }

    cout << segX->query(1, N, 1, 2, 2, 4) << "\n";
    cout << segX->query(1, N, 2, 4, 1, 3) << "\n";

    return 0;
}