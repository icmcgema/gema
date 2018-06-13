#include <bits/stdc++.h>
#define mk make_pair
#define pb push_back
#define For(a,b) for(int (i)=0; (i)<(b); (i++))
#define Fo(a,b,c) for(int (i)=(b); (i)<=(c); (i++))

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

const int INF=0x3f3f3f3f;

const int N=100000;

int uf[N];

int fin(int x) {
	return uf[x]==x ? x : (uf[x]=fin(uf[x]));
}

void uni(int x, int y) {
	x = fin(x);
	y = fin(y);
	if (x != y)
		uf[x]=y;
}

int main(void) {

	for (int i = 0;i<N; i++)
		uf[i]=i;

	return 0;
}
