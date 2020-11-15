// https://hihocoder.com/problemset/problem/1053
#include <bits/stdc++.h>
using namespace std;
const int max_n = 1e5 + 10;
typedef long long ll;
struct Data {
    ll pos, num;
    friend bool operator<(const Data &aa, const Data &bb) {
        return aa.pos < bb.pos;
    }
} a[max_n];
ll n, R, c[max_n];
bool isOk(int t) {
    for (int i = 0; i < n; ++i) c[i] = a[i].num;
    queue<int> inp, outp;  // inp:当前可以吸收的人口  oup:当前待吸收的人口
    for (int i = 0; i < n; ++i) {
        while ((!inp.empty()) && c[i] != 0) {
            int top = inp.front();
            if (a[i].pos - a[top].pos > R) {
                inp.pop();
                continue;
            }
            int rest = min(t - c[top], c[i]);
            c[top] += rest;
            c[i] -= rest;
            if (c[top] == t) inp.pop();
        }
        int delt = c[i];
        while ((!outp.empty()) && c[i] < t + delt) {
            int top = outp.front();
            if (a[i].pos - a[top].pos > R) return false;
            int rest = min(t + delt - c[i], c[top] - t);
            c[i] += rest;
            c[top] -= rest;
            if (c[top] == t) outp.pop();
        }
        if (c[i] > t)
            outp.push(i);
        else if (c[i] < t)
            inp.push(i);
    }
    return outp.empty() ? true : false;
}
void solve() {
    cin >> n >> R;
    ll l = 0, r = 0, ans;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].pos >> a[i].num;
        r = max(r, a[i].num);
    }
    sort(a, a + n, less<Data>());
    ans = r;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (isOk(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    cout << ans << endl;
}
int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
