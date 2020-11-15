// https://hihocoder.com/problemset/problem/1033
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Data;  // nums, sum
const ll Mod = 1000000007;
const int delt = 300;
int s[20];
ll fact[20];
Data f[20][2][3][400];
bool visited[20][2][3][delt * 2];
Data dp(int pos, bool ismax, char iszero, int res) {  //数位dp
    if (pos == -1) {
        return res == 0 ? Data(1, 0) : Data(0, 0);
    }
    if (visited[pos][ismax][iszero][res + delt])
        return f[pos][ismax][iszero][res + delt];
    visited[pos][ismax][iszero][res + delt] = true;
    int maxval = ismax ? s[pos] : 9;
    Data ans = Data(0, 0);
    for (int i = 0; i <= maxval; ++i) {
        Data tmp = dp(pos - 1, ismax & (i == maxval),
                      iszero == 2 ? (i == 0 ? 2 : 0) : (iszero ^ 1),
                      res - (iszero == 0 ? -1 : 1) * i);
        ans.first += tmp.first;
        ans.second += (tmp.second + tmp.first * i * fact[pos]);
        ans.first %= Mod;
        ans.second %= Mod;
    }
    return f[pos][ismax][iszero][res + delt] = ans;
}
ll sol(ll t, int k) {
    memset(s, 0, sizeof(s));
    memset(visited, 0, sizeof(visited));
    for (int i = 0; t != 0; ++i) {
        s[i] = t % 10;
        t /= 10;
    }
    return dp(18, true, 2, k).second;
}
int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    fact[0] = 1;
    for (int i = 1; i < 20; ++i) fact[i] = (fact[i - 1] * 10) % Mod;
    ll l, r;
    int k;
    cin >> l >> r >> k;
    cout << (sol(r, k) - sol(l - 1, k) + Mod) % Mod << endl;
    return 0;
}
