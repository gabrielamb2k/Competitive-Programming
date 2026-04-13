#include <bits/stdc++.h>

using namespace std;

// problem CSES: Sliding Window Minimum

class MonotonickQueue {
private:
  deque<int> dq;

public:
  void push(int val) {
    while (!dq.empty() and dq.back() > val)
      dq.pop_back();
    dq.push_back(val);
  }

  void pop(int val) {
    if (!dq.empty() and dq.front() == val)
      dq.pop_front();
  }

  int getMin() { return dq.front(); }
};

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  vector<int> arr(n + 1);
  int x, a, b, c;
  cin >> x >> a >> b >> c;

  arr[1] = x;
  for (int i = 2; i <= n; i++) {
    arr[i] = (a * arr[i - 1] + b) % c;
  }

  MonotonickQueue mq;
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    mq.push(arr[i]);
    if (i >= k) {
      ans.push_back(mq.getMin());
      int elem = arr[i - k + 1];
      mq.pop(elem);
    }
  }

  int resp = 0;
  for (auto i : ans) {
    resp ^= i;
  }
  cout << resp << endl;

  return 0;
}
