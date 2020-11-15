// https://hihocoder.com/problemset/problem/1035
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> Pair;
const ll max_n = 1000000 + 10;
struct Data {
    int u, c0, c1;
    Data(int u_, int c0_, int c1_) { u = u_, c0 = c0_, c1 = c1_; }
};
vector<Data> a[max_n];
int kp[max_n], n, m;
void getcount(int p, int fa) {
    for (int i = 0; i < a[p].size(); ++i) {
        if (a[p][i].u != fa) {
            getcount(a[p][i].u, p);
            kp[p] += kp[a[p][i].u];
        }
    }
}

ll dp[max_n][5];
void dfs(int p, int fa) {
    for (int i = 0; i < a[p].size(); ++i) {
        if (a[p][i].u != fa && kp[a[p][i].u]) {
            dfs(a[p][i].u, p);
        }
    }
    ll minval1 = 0, minval4 = 0, minval5 = 0;
    Pair minval2[2], minval3[2];
    minval2[0] = minval2[1] = minval3[0] = minval3[1] = Pair(0, 0);

    for (int i = 0; i < a[p].size(); ++i)
        if (a[p][i].u != fa && kp[a[p][i].u]) {
            int q = a[p][i].u;
            ll cost0 = dp[q][0] + a[p][i].c0 * 2;  //无车来回
            ll cost1 = dp[q][1] + a[p][i].c1 * 2;  //有车来回
            ll cost2 = min(dp[q][2], dp[q][1]) + a[p][i].c0 +
                       a[p][i].c1;             // 有车来无车回
            ll cost3 = dp[q][3] + a[p][i].c0;  //无车一去不回
            ll cost4 = min(dp[q][3] + a[p][i].c0,
                           dp[q][4] + a[p][i].c1);  //有车一去不回

            minval1 = min(minval1, cost2 - min(cost0, cost1));
            minval4 = min(minval4, cost3 - cost0);
            minval5 = min(minval5, cost4 - min(cost0, cost1));
            ll tmp;
            tmp = cost3 - min(cost0, cost1);
            if (tmp < minval3[0].second) {
                minval3[1] = minval3[0];
                minval3[0] = Pair(i, tmp);
            } else {
                if (tmp < minval3[1].second) minval3[1] = Pair(i, tmp);
            }
            tmp = cost2 - min(cost0, cost1);
            if (tmp < minval2[0].second) {
                minval2[1] = minval2[0];
                minval2[0] = Pair(i, tmp);
            } else {
                if (tmp < minval2[1].second) minval2[1] = Pair(i, tmp);
            }

            dp[p][0] += cost0;              //无车来回
            dp[p][1] += min(cost0, cost1);  //有车来回
        }
    dp[p][2] = dp[p][1] + minval1;  // 有车来无车回
    dp[p][3] = dp[p][0] + minval4;  // 无车一去不回

    if (minval2[0].first != minval3[0].first)
        dp[p][4] = dp[p][1] + minval2[0].second + minval3[0].second;
    else
        dp[p][4] = dp[p][1] + min(minval2[0].second + minval3[1].second,
                                  minval2[1].second + minval3[0].second);
    dp[p][4] = min(dp[p][4], dp[p][1] + minval5);
}
int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin >> n;
    for (int i = 1, u, v, c0, c1; i < n; ++i) {
        cin >> u >> v >> c0 >> c1;
        a[u].push_back(Data(v, c0, c1));
        a[v].push_back(Data(u, c0, c1));
    }
    cin >> m;
    for (int i = 0, j; i < m; ++i) {
        cin >> j;
        kp[j] = 1;
    }
    getcount(1, -1);
    dfs(1, -1);
    cout << dp[1][4] << endl;
    return 0;
}
