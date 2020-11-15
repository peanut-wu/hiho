// https://hihocoder.com/problemset/problem/1014
#include <bits/stdc++.h>
using namespace std;
const int max_n = 100000 + 10, max_s = 10 + 10;
int n, m;
char s[max_s];

struct Node {
    int cnt;
    int ch[26];  // a-z
    Node() {
        cnt = 0;
        memset(ch, 0, sizeof(ch));
    }
};

class Trie {
    vector<Node> mp;  // memorypool;
   public:
    Trie() {
        mp.reserve(max_n * 5);
        mp.push_back(Node());  // root
    }
    void add(char *str) {
        int len = strlen(str);
        int next = 0;
        for (int i = 0; i < len; ++i) {
            if (mp[next].ch[str[i] - 'a'] == 0) {
                mp.push_back(Node());
                mp[next].ch[str[i] - 'a'] = mp.size() - 1;
            }
            next = mp[next].ch[str[i] - 'a'];
            mp[next].cnt++;
        }  //此处用指针更为清晰(如query)，但vector动态分配内存后指针可能失效
    }
    int query(char *str) {
        int len = strlen(str);
        Node *next = &mp[0];
        for (int i = 0; i < len; ++i) {
            if (next->ch[str[i] - 'a'] == 0) {
                return 0;
            } else {
                next = &mp[next->ch[str[i] - 'a']];
            }
        }
        return next->cnt;
    }
};

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin >> n;
    Trie trie;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        trie.add(s);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        cout << trie.query(s) << endl;
    }
    return 0;
}
