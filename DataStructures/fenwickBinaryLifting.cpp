#include <bits/stdc++.h>

using namespace std;

template <class T> struct BIT {
  int n;
  vector<T> bit;
  BIT(int _n) {
    n = _n;
    bit.assign(n + 1, 0);
  }

  void add(int i, T val) {
    for (; i <= n; i += (i & -i))
      bit[i] += val;
  }

  int findKth(int k) {
    int idx = 0;

    int bitMask = 1 << 20;
    while (bitMask != 0) {
      int tIdx = idx + bitMask;
      bitMask >>= 1;
      if (tIdx > n)
        continue;
      if (k > bit[tIdx]) {
        idx = tIdx;
        k -=bit[tIdx];
      }
    }
    return idx+1;
  }
};
