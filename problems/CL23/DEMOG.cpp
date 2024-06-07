#include<bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    int count, exist;

    TrieNode() {
        for(int i = 0; i < 26; i++) children[i] = nullptr;
        count = 0;
        exist = 0;
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void add(string s) {
        TrieNode* cur = root;
        for(char c : s) {
            if(cur->children[c - 'a'] == nullptr) 
                cur->children[c-'a'] = new TrieNode();
            cur = cur->children[c - 'a'];
            cur->count++;
        }
        cur->exist++;
    }

    bool delete_recursive(TrieNode* cur, string s, int idx) {
        if(idx != s.size()) {
            if(cur->children[s[idx] - 'a'] == nullptr) 
                return false;
            if(delete_recursive(cur->children[s[idx] - 'a'], s, idx + 1)) {
                cur->children[s[idx] - 'a'] = nullptr;
            }
        } else {
            cur->exist--;
        }

        if(cur != root) {
            cur->count--;
            if(cur->count == 0 && cur->exist == 0) {
                delete cur;
                return true;
            }
        }
        return false;
    }

    void delete_(string s) {
        if(!find(s))
            return;
        delete_recursive(root, s, 0);
    }

    int find(string s) {
        TrieNode* cur = root;
        for(char c : s) {
            if(cur->children[c - 'a'] == nullptr) 
                return false;
            cur = cur->children[c - 'a'];
        }
        return cur->exist;
    }

    int find_prefix(string s) {
        TrieNode* cur = root;
        for(char c : s) {
            if(cur->children[c - 'a'] == nullptr) 
                return 0;
            cur = cur->children[c - 'a'];
        }
        return cur->count;
    }

    int query(string s, int pos) {
        TrieNode* cur = root;
        int ret = -1;
        for(int i = pos; i < s.size(); i++) {
            if(cur->children[s[i] - 'a'] == nullptr) 
                return ret;
            cur = cur->children[s[i] - 'a'];
            if(cur->exist > 0) {
                ret = max(ret, i);
            }
        }
        return ret;
    }
};

Trie trie;

int n;
string target;
vector<string> s;

string lower(string s) {
    for(char &c : s) {
        if(c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return s;
}

int main() {
    cin >> n;
    cin >> target;
    target = lower(target);

    for(int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        tmp = lower(tmp);
        s.push_back(tmp);
    }

    for(string str : s) {
        trie.add(str);
    }

    int last_pos = -1;
    int pos = 0;

    for(int res = 1; res <= target.size(); res++) {
        int new_pos = -1;
        int iter = pos;

        while (iter > last_pos) {
            if(iter + 20 < new_pos)
                break;
            int ret = trie.query(target, iter);
            if(ret != -1) {
                new_pos = max(new_pos, ret);
            }

            iter--;
        }

        last_pos = pos;
        pos = new_pos;

        if(pos == target.size() - 1) {
            cout << res << endl;
            return 0;
        }
    }
}