#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fi first
#define se second

const int MAXN = 1025;

int N, M;
int seg[2*MAXN][2*MAXN];
int v[5][5] = {{0, 0, 0, 0, 0},
               {0, 0, 7, 1, 1},
               {0, 2, 1, 5, 3},
               {0, 3, 4, 0, 4},
               {0, 1, 0, 0, 8}};

void buildY(int noX, int lX, int rX, int noY, int lY, int rY){
    if(lY == rY){
        if(lX == rX){
            seg[noX][noY] = v[rX][rY];
        }else{
            seg[noX][noY] = seg[2*noX][noY] + seg[2*noX+1][noY];
        }
    }else{
        int m = (lY+rY)/2;

        buildY(noX, lX, rX, 2*noY, lY, m);
        buildY(noX, lX, rX, 2*noY+1, m+1, rY);

        seg[noX][noY] = seg[noX][2*noY] + seg[noX][2*noY+1];
    }
}

void buildX(int noX, int lX, int  rX){
    if(lX != rX){
        int m = (lX+rX)/2;

        buildX(2*noX, lX, m);
        buildX(2*noX+1, m+1, rX);
    }

    buildY(noX, lX, rX, 1, 1, M);
}

void updateY(int noX, int lX, int rX, int noY, int lY, int rY, int y, int v){
    if(lY == rY){
        if(lX == rX){
            seg[noX][noY] = v;
        }else{
            seg[noX][noY] = seg[2*noX][noY] + seg[2*noX+1][noY];
        }
    }else{
        int m = (lY+rY)/2;

        if(y <= m){
            updateY(noX, lX, rX, 2*noY,lY, m, y, v);
        }else if(m < y){
            updateY(noX, lX, rX, 2*noY+1, m+1, rY, y, v);
        }

        seg[noX][noY] = seg[noX][2*noY] + seg[noX][2*noY+1];
    }
}

void updateX(int noX, int lX, int rX, int x, int y, int v){
    int m = (lX+rX)/2;

    if(lX != rX){
        if(x <= m){
            updateX(2*noX, lX, m, x, y, v);
        }else if(m < x){
            updateX(2*noX+1, m+1, rX, x, y, v);
        }
    }

    updateY(noX, lX, rX, 1, 1, M, y, v);
} 

int queryY(int noX, int noY, int lY, int rY, int aY, int bY){
    if(aY <= lY && rY <= bY) return seg[noX][noY];

    int m = (lY+rY)/2;

    if(bY <= m) return queryY(noX, 2*noY, lY, m, aY, bY);
    if(m < aY) return queryY(noX, 2*noY+1, m+1, rY, aY, bY);

    return queryY(noX, 2*noY, lY, m, aY, bY) + queryY(noX, 2*noY+1, m+1, rY, aY, bY);
}

int queryX(int noX, int lX, int rX, int aX, int bX, int aY, int bY){
    if(aX <= lX && rX <= bX) return queryY(noX, 1, 1, M, aY, bY);

    int m = (lX+rX)/2;

    if(bX <= m) return queryX(2*noX, lX, m, aX, bX, aY, bY);
    if(m < aX) return queryX(2*noX+1, m+1, rX, aX, bX, aY, bY);

    return queryX(2*noX, lX, m, aX, bX, aY, bY) + queryX(2*noX+1, m+1, rX, aX, bX, aY, bY);
}

int main(){
    N = 4;
    M = 4; 

    buildX(1, 1, N);

    cout << queryX(1, 1, 4, 1, 2, 2, 4) << "\n";
    cout << queryX(1, 1, 4, 2, 4, 1, 3) << "\n";

    return 0;
}