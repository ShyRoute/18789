// v1 : change neighbor's number to random number


#include <bits/stdc++.h>
#define Fio freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#pragma GCC optimize("Ofast")

using namespace std;
using ll = long long;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 9);

struct e {
	int x, y, cnt;
};

class Matrix {
	public:
	int arr[8][14];
	int dx[8]={-1, 0, 1,-1, 1,-1, 0, 1};
	int dy[8]={-1,-1,-1, 0, 0, 1, 1, 1};
	bitset<10000> chk;
	
	Matrix() {
		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 14; ++j) {
				arr[i][j] = dis(gen);
			}
		}
	}
	
	const int checkScore() {
		chk.reset();
		for(int k = 0; k < 10000; ++k) {
			if(chk[k]) continue;
			queue<e> q;
			string s = to_string(k);
			int sz = s.size();

			for(int i = 0; i < 8; ++i) {
				for(int j = 0; j < 14; ++j) {
					if(s[0] - '0' == arr[i][j]) {
						q.push({i, j, 1});
					}
				}
			}

			while(!q.empty()) {
				int x = q.front().x;
				int y = q.front().y;
				int now = q.front().cnt;
				q.pop();
				if(now == sz) {
					chk[k] = true;
					reverse(s.begin(), s.end());
					chk[stoi(s)] = true;
					break;
				}

				for(int i = 0; i < 8; ++i) {
					int nx = x + dx[i];
					int ny = y + dy[i];
					if(nx<0 || nx>=8 || ny<0 || ny>=14) continue;
					if(arr[nx][ny] == s[now] - '0') {
						q.push({nx, ny, now + 1});
					}
				}
			}
		}
		
		for(int i = 1;; ++i) if(!chk[i]) return i - 1;
	}
};



int main() {
    Fio;
		
	Matrix mx;
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 14; ++j) {
			scanf("%1d", &mx.arr[i][j]);
		}
	}	
		
	int ans = 1698;
	int epoch = 10;
	while(epoch--) {
    for(int x = 0; x < 8; ++x) {
      for(int y = 0; y < 14; ++y) {
        int tmp = mx.arr[x][y];
        mx.arr[x][y] = dis(gen);

        int xx = mx.checkScore();
        if(ans < xx) {
          cout << "Score : " << xx << '\n';
          for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 14; ++j) {
              cout << mx.arr[i][j];
            }
            cout << '\n';
          }	
          ans = xx;
          cout << '\n';
        }

        else mx.arr[x][y] = tmp;
      }
    }
	}
	
	cout << "Done";
	
    return 0;
}
