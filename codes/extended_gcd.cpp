#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

void xgcd(int a, int b, int & x1, int & y1, int & x2, int & y2) {
	if(b == 0) return;
	int x3, y3;
	int q = a / b;
	x3 = x1 - q * x2;
	y3 = y1 - q * y2;
	x1 = x2; y1 = y2;
	x2 = x3; y2 = y3;
	xgcd(b, a%b, x1, y1, x2, y2);
}

pair<int, int> xgcd(int a, int b) {
	int g = gcd(a, b);
	int x1, y1, x2, y2; 
	x1 = 1, y1 = 0;
	x2 = 0, y2 = 1;
	xgcd(a, b, x1, y1, x2, y2);
	return make_pair(x1, y1);
}

pair<int, int> small_xgcd(int a, int b) {
	if(b == 0) return make_pair(1, 0);
	int x, y;
	tie(x, y) = small_xgcd(b, a%b);
	return make_pair(y, x - (a/b) * y);
}

int main() {
	int a, b, c; cin >> a >> b >> c;

	// ve se tem solucao
	if(c%gcd(a, b)) {
		cout << "Nao tem solucao" << endl;
	} else {
		int g = gcd(a, b);
		int k = c / g;

		// x * a + y * b = g


		int x, y;
		tie(x, y) = small_xgcd(a, b); 
		x *= k;
		y *= k;

		assert(x * a + y * b == c);
		cout << x << ' ' << y << endl;
	}
}