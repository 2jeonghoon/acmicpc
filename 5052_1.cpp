#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct node {
    bool is_leaf;
    struct node* link[10];

    node() { 
        is_leaf = false;
        for (int i = 0; i < 10; i++) {
            link[i] = NULL;
        }
    }
    ~node() { 
        for(int i = 0; i < 10; i++) {
            if(link[i]) {
                delete link[i];
            }
        }
    }
};

int res;

bool check_consistency(struct node* root, char *_value) {
    struct node* cur_node = root;

    bool is_create_node = false;

    for(int i = 0; _value[i] != 0; i++) {
        auto target_node_it = cur_node->link[_value[i]-'0'];
        if(target_node_it != NULL) {
            cur_node = target_node_it;
        } else {
            if(cur_node->is_leaf) {
                return false;
            }
            //cout << _value[i] << "isn't find, so create new link\n";
            is_create_node = true;
            cur_node->link[_value[i]-'0'] = new node;
            cur_node = cur_node->link[_value[i]-'0'];
        }
    }

    //cout << "finish check consistency\n";

    cur_node->is_leaf = true;

    if(!is_create_node) {
        return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    scanf("%d", &t);

    for(int _t = 1; _t <= t; _t++) {
        int n;
        scanf("%d", &n);

        bool res = true;

        struct node *root = new node;

        for(int _n = 1; _n <= n; _n++) {
            char input[10];

            scanf("%s", input);
            
            if(res) {
                if (!check_consistency(root, input)) {
                    res = false;
                }
            }
        }

        delete root;
        
        if(res) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}