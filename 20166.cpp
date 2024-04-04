#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;

struct pos {
    int x;
    int y;
};

int N, M, K;
char world[11][11];

stack<pair<struct pos, string>> dfs;
map<string, int> _case;

int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

int main() {
    /*
    row N, col M, 격자 세상 - 왼쪽 위:(1,1) 오른쪽 아래:(N,M)
    아무 곳에서 시작해서 상하좌우, 대각선 방향의 칸으로 한 칸씩 이동 가능
    이미 지나왔던 칸들을 다시 방문하는 것도 허용
    신이 문자열 K를 알려줄 것이고, 각 문자열마다 너가 만들 수 있는 경우의 수를 대답해야 한다.
    경우의 수를 셀 때, 방문 순사가 다르면 다른 경우다.
    즉 (1,1) > (1,2)와 (1,2) > (1,1)는 다른 경우다.

    1행에서 위로 가면 N행으로 가게되며 반대도 가능하다
    1열에서 왼쪽으로 가면 M열로 가게되며 반대도 가능하다
    대각선 방향에서도 동일한 규칙이 적용된다

    입력 : 격자크기 N, M, 신이 좋아하는 문자열 개수 K
    */
   ios::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> world[i][j];

            string s;
            s += world[i][j];
            dfs.push(make_pair(pos{i,j}, s));
        }
    }

    while(!dfs.empty()) {
        pair<struct pos, string> item = dfs.top();
        dfs.pop();

        auto case_it = _case.find(item.second);

        if(case_it != _case.end()) {
            case_it->second++;
        } else {
            _case.insert({item.second, 1});
        }

        if(item.second.size() == 5) {
            continue;
        }

        for(int i = 0; i < 8; i++) {
            int next_x = item.first.x + dx[i];
            int next_y = item.first.y + dy[i];

            if(next_x == 0) {
                next_x = N;
            } else if(next_x > N) {
                next_x = 1;
            }

            if(next_y == 0) {
                next_y = M;
            } else if(next_y > M) {
                next_y = 1;
            }

            char next_char = world[next_x][next_y];

            string next_str = item.second + next_char;

            dfs.push(make_pair(pos{next_x, next_y}, next_str));
        }
    }
    
    for (int i = 0; i < K; i++) {
        string sacred_string;
        cin >> sacred_string;

        auto res = _case.find(sacred_string);

        if (res != _case.end()) {
            cout << res->second << "\n";
        } else {
            cout << "0\n";
        }
    }

}