#include <bits/stdc++.h>
using namespace std;

struct FenwickTree {
    int n;
    vector<int> bit;
    FenwickTree(int n) : n(n + 1), bit(n + 1) {}
    int query(int r) {
        int ret = 0;
        while(r > 0) {
            ret += bit[r];
            r -= (r & -r);
        }

        return ret;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }

    void update(int idx, int delta) {
        while(idx < n) {
            bit[idx] += delta;
            idx += (idx & -idx);
        }
    }
};
