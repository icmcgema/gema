#include <bits/stdc++.h>
using namespace std;

#define BEG 0
#define END 1

struct Event{
	int x, tipo;

	bool operator<(const Event& b) const{
		if(x == b.x) return tipo < b.tipo;
		return x < b.x;
	}
};


int sweep_line(vector<Event> v){
	int cnt = 0, ans = 0;
	for(int i = 0; i < v.size(); i++){
		if(v[i].tipo == BEG){
			cnt++;
			ans = max(ans, cnt);
		}
		else{ // END
			cnt--;
		}
	}

	return ans;
}
