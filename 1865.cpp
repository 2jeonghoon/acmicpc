#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int inf = 10001;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
    int tc;
    
    cin >> tc;
    
    for (int _tc = 0; _tc < tc; _tc++) {
        int n, m, w, s, e, t;
        cin >> n >> m >> w;
        
        int weight[501][501];
        vector<vector<int>> edge(501);
        int distance[n+1];
        
        memset(weight, inf, sizeof(weight));
        
        for (int _m = 0; _m < m; _m++) {
            cin >> s >> e >> t;

            if(weight[s][e] > inf) {
                edge[s].push_back(e);
                edge[e].push_back(s);
                weight[s][e] = t;
                weight[e][s] = t;
                
                //cout << "init vertex " << s << " and " << e << " weight " << t << " " << edge[s].size() << endl;
            } else if(weight[s][e] > t) {
                weight[s][e] = t;
                weight[e][s] = t;
                
                //cout << "update vertex " << s << " and " << e << " weight " << t << endl;
            }
        }
        
        for (int _w = 0; _w < w; _w++) {
            cin >> s >> e >> t;

            if(weight[s][e] > inf) {
                edge[s].push_back(e);
                weight[s][e] = -t;
                
                //cout << "init vertex " << s << " to " << e << " weight " << -t << endl;
            } else if(weight[s][e] > -t) {
                weight[s][e] = -t;
                
                //cout << "update vertex " << s << " to " << e << " weight " << -t << endl;
            }
        }
        
        bool res = false;

            memset(distance, 0, sizeof(distance));
            for (int v = 1; v <= n; v++) {
                for (int cur_v = 1; cur_v <= n; cur_v++) {
                    for(auto dest : edge[cur_v]) {
                        //cout << "cur_v : " << cur_v << " dest : " << dest << endl;
                        if(distance[dest] > distance[cur_v] + weight[cur_v][dest]) {
                            //cout << "distance[" << dest << "] update to " << distance[cur_v]+weight[cur_v][dest] << endl;
                            distance[dest] = distance[cur_v] + weight[cur_v][dest];
                            
                            if (v == n) {
                                res = true;
                                break;
                            }
                        }
                    }
                    
                }
            }
        
        if (res) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}