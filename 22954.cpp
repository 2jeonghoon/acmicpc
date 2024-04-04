#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct s_edge {
    int edge_num;
    int source;
    int dest;
};

int N, M;

int union_find[100001];

map<int, vector<struct s_edge>> spanning_tree_list;
vector<struct s_edge> edge_list;

int find_parent(int node) {
    if(union_find[node] == node) return node;
    return union_find[node] = find_parent(union_find[node]);
}

void print_spanning_tree(vector<struct s_edge> &spanning_tree) {
        map<int, int> res1;
        vector<int> res2;

        for(auto it = spanning_tree.begin(); it != spanning_tree.end(); it++) {
            //cout << "source: " << it->source << "dest : " << it->dest << "\n";
            if(res1.find(it->source) == res1.end()) {
                res1.insert({it->source, 0});
            }
            if(res1.find(it->dest) == res1.end()) {
                res1.insert({it->dest, 0});
            }
            res2.push_back(it->edge_num);
        }

        sort(res2.begin(), res2.end());

        for(auto res : res1) {
            cout << res.first << " ";
        }
        cout << "\n";
        for(auto res : res2) {
            cout << res << " ";
        }
        cout << "\n";
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);
    //cout.tie(NULL);

    cin >> N >> M;

    for(int i = 1; i <= N; i++) {
        union_find[i] = i;
    }

    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        edge_list.push_back({i, u, v});
    }

   if(N == 2) {
        cout << -1;
        return 0;
    }

    for(auto edge : edge_list) {
        int source_parent = find_parent(edge.source);
        int dest_parent = find_parent(edge.dest);

        //cout << "source parent : " << source_parent << " dest parent : " << dest_parent << "\n";

        if (source_parent == dest_parent) {
            continue;
        }

        if(source_parent > dest_parent) {
            union_find[source_parent] = dest_parent;
            spanning_tree_list[dest_parent].push_back(edge);
        } else {
            union_find[dest_parent] = source_parent;
            spanning_tree_list[source_parent].push_back(edge);
        }
    }

    for (int i = 1; i <= N; i++) {
        //cout << union_find[i] << endl;
    }

    //cout << "spanning tree count : " << spanning_tree_list.size() << endl;

    for(auto spanning_tree : spanning_tree_list) {
        //cout << spanning_tree.first << endl;

        for(auto edge : spanning_tree.second) {
            //cout << edge.source << "to" << edge.dest << endl;
        }
    }

    if(spanning_tree_list.size() == 1) {
        //cout << "size == 1\n";
        cout << "1 " << N-1 << "\n";
        map<int, vector<struct s_edge>> edge_cnt;

        auto spanning_tree = spanning_tree_list.begin()->second;

        for(struct s_edge edge : spanning_tree) {
            //cout << "edge info : " << edge.source << " " << edge.dest << "\n";
            auto source_vertex_it = edge_cnt.find(edge.source);
            auto dest_vertex_it = edge_cnt.find(edge.dest);

            if(source_vertex_it != edge_cnt.end()) {
                source_vertex_it->second.push_back(edge);
                //cout << "edge pushback " << edge.source << " " << edge_cnt[edge.source].size() << "\n";
            } else {
                edge_cnt.insert({edge.source, vector<struct s_edge>{edge}});
                //cout << "insert " << edge.source << edge_cnt[edge.source].size() << "\n";
            }

            if(dest_vertex_it != edge_cnt.end()) {
                dest_vertex_it->second.push_back(edge);
                //cout << "edge pushback " << edge.dest << " " << edge_cnt[edge.dest].size() << "\n";
            } else {
                edge_cnt.insert({edge.dest, vector<struct s_edge>{edge}});
                //cout << "insert " << edge.dest << edge_cnt[edge.dest].size() <<"\n";
            }
        }

        int remove_vertex;
        struct s_edge remove_edge;

        for(auto edge : edge_cnt) {
            if(edge.second.size() == 1) {
                
                remove_vertex = edge.first;
                //cout << "remove " << remove_vertex << "\n";
                for(auto it = spanning_tree.begin(); it != spanning_tree.end(); it++) {
                    if(it->source == edge.second.front().source && it->dest == edge.second.front().dest) {
                        //cout << "erase" << "source : " << it->source << "dest : "<< it->dest << "\n";
                        spanning_tree.erase(it);
                    }
                }
                break;
            }
        }

        cout << remove_vertex << "\n";
        cout << "\n";
        print_spanning_tree(spanning_tree);
        
        return 0;
    }

    if(spanning_tree_list.size() > 2 || spanning_tree_list.size() == 0) {
        //cout << "else";
        cout << -1;

        return 0;
    }

    if(spanning_tree_list.size() == 2) {
        //cout << "size == 2\n";
        if(spanning_tree_list.begin()->second.size()+1 == (++spanning_tree_list.begin())->second.size()+1) {
            cout << -1;

            return 0;
        }
        cout << spanning_tree_list.begin()->second.size()+1 << " " << (++spanning_tree_list.begin())->second.size()+1 << "\n";

        print_spanning_tree(spanning_tree_list.begin()->second);
        print_spanning_tree((++spanning_tree_list.begin())->second);

        return 0;
    }
}