#include<bits/stdc++.h>
using namespace std;

template<typename T>
class SegmentTreeNode {
public:
    T value;
    T lazy;
    int start, end;
    SegmentTreeNode<T> *left, *right;

    SegmentTreeNode(T value, int start, int end) {
        this->value = value;
        this->left = this->right = nullptr;
        this->start = start;
        this->end = end;
    }

    SegmentTreeNode(T value, T lazy, int start, int end) {
        this->value = value;
        this->lazy = lazy;
        this->left = this->right = nullptr;
        this->start = start;
        this->end = end;
    }
};

template<typename T>
class SegmentTree {
private:
    SegmentTreeNode<T> *root;
    virtual T merge(T a, T b) = 0;
    virtual T create() = 0;

    void lazy_down(SegmentTreeNode<T>* node) {
        if(node->lazy != create()) {
            if(node->left != nullptr) {
                node->left->value = merge(node->left->value, node->lazy);
                node->left->lazy = merge(node->left->lazy, node->lazy);
            }
            if(node->right != nullptr) {
                node->right->value = merge(node->right->value, node->lazy);
                node->right->lazy = merge(node->right->lazy, node->lazy);
            }
            node->lazy = create();
        }
    }
public:
    SegmentTree() {
        root = nullptr;
    }

    SegmentTreeNode<T>* build(vector<T>& arr, int start, int end) {
        if(start > end) {
            return nullptr;
        }
        if(start == end) {
            return new SegmentTreeNode<T>(arr[start], start, end);
        }
        SegmentTreeNode<T>* node = new SegmentTreeNode<T>(create(), start, end);
        int mid = start + (end - start) / 2;
        node->left = build(arr, start, mid);
        node->right = build(arr, mid + 1, end);
        node->value = merge(node->left->value, node->right->value);
        return node;
    }

    void build(vector<T>& arr) {
        root = build(arr, 0, arr.size() - 1);
    }

    T query(SegmentTreeNode<T>* node, int start, int end) {
        // if(node != nullptr) {
            // cout << node->start << " " << node->end << " " << node->value << endl;
        // }
        if(node == nullptr || start > node->end || end < node->start) {
            return create();
        }
        lazy_down(node);
        if(start <= node->start && end >= node->end) {
            return node->value;
        }
        return merge(query(node->left, start, end), query(node->right, start, end));
    }

    T query(int start, int end) {
        return query(root, start, end);
    }

    void update(SegmentTreeNode<T>* node, int start, int end, T value) {
        if(node == nullptr || start > node->end || end < node->start) {
            return;
        }
        if(start <= node->start && end >= node->end) {
            node->value = merge(node->value, value);
            node->lazy = merge(node->lazy, value);
            return;
        }
        lazy_down(node);
        update(node->left, start, end, value);
        update(node->right, start, end, value);
        node->value = merge(node->left->value , node->right->value);
    }

    void update(int start, int end, T value) {
        update(root, start, end, value);
    }
};

struct MinMaxData {
    int min, max;
    MinMaxData(int min = INT_MAX, int max = INT_MIN) {
        this->min = min;
        this->max = max;
    }

    bool operator!=(const MinMaxData& other) const {
        return min != other.min || max != other.max;
    }
};

class MinMaxTree : public SegmentTree<MinMaxData> {
public:
    MinMaxData merge(MinMaxData a, MinMaxData b) {
        return MinMaxData(min(a.min, b.min), max(a.max, b.max));
    }

    MinMaxData create() {
        return MinMaxData(INT_MAX, INT_MIN);
    }
};

MinMaxTree tree;
int n, q;
int h[55000];

int main() {
    scanf("%d %d", &n, &q);
    for(int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }
    vector<MinMaxData> arr;
    for(int i = 0; i < n; i++) {
        arr.push_back(MinMaxData(h[i], h[i]));
    }
    tree.build(arr);

    for(int i = 0; i < q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;
        MinMaxData data = tree.query(l, r);
        printf("%d\n", data.max - data.min);
    }
}