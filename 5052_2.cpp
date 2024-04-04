#include <iostream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

struct node {
    bool is_leaf;
    map<char, struct node> link;
};

int res;
char input[10];

bool check_consistency(struct node* root, char *_value) {
    struct node* cur_node = root;

    bool is_create_node = false;

    for(int i = 0; _value[i] != 0; i++) {
        auto target_node_it = cur_node->link.find(_value[i]);
        if(target_node_it != cur_node->link.end()) {
            //cout << _value[i] << "find\n";
            cur_node = &target_node_it->second;
        } else {
            if(cur_node->is_leaf) {
                return false;
            }
            //cout << _value[i] << "isn't find, so create new link\n";
            is_create_node = true;
            cur_node->link[_value[i]] = {false, {}};
            cur_node = &cur_node->link[_value[i]];
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
    int t;
    scanf("%d", &t);

    for(int _t = 1; _t <= t; _t++) {
        int n;
        scanf("%d", &n);

        bool res = true;

        struct node root = {false, {}};

        for(int _n = 1; _n <= n; _n++) {
            memset(input, 0, sizeof(input));

            scanf("%s", input);
            
            if(res) {
                if (!check_consistency(&root, input)) {
                    res = false;
                }
            }
        }

        if(res) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}