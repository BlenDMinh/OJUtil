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
};

int main() {
    Trie trie;
    trie.root = new TrieNode();
    trie.add("hello");
    trie.add("world");
    trie.add("helo");

    cout << trie.find("hello") << endl;
}