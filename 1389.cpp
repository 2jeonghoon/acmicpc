#include <iostream>
#include <queue>
#include <vector>

using namespace std;


queue<pair<int, int>> bfs;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int main() {
    int n, m;

    cin >> m >> n;

    int map[1001][1001];
    int result[1001][1001];
    int visited[1001][1001];
    
    pair<int, int> target_pos;
    
    memset(map, 0, sizeof(map));
    memset(result, 0, sizeof(result));
    memset(visited, 0, sizeof(visited));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
            
            if(map[i][j] == 2) {
                target_pos.first = j;
                target_pos.second = i;
            }
        }
    }
    
    bfs.push(target_pos);

    while(!bfs.empty()) {
        pair<int, int> target = bfs.front();
        bfs.pop();

        for(int i = 0; i < 4; i++) {
            int next_x = target.first + dx[i];
            int next_y = target.second + dy[i];

            if(map[next_y][next_x] == 1 && !(next_x > m || next_x < 1 || next_y > n || next_y < 1)) {
                visited[next_y][next_x] = true;
                result[next_y][next_x] = result[target.second][target.first] + 1;
                bfs.push(make_pair(next_x, next_y));
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}