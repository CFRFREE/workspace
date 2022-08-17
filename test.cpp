#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define LL long long
#define endl '\n'
#define N 200005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
int n, flag;
vector<int> a, b;
inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}
void cal()
{
    stack<int> s;
    for (auto y : b)
    {
        if (!s.size())
            s.push(y);
        else
        {
            int x = s.top();
            if (x == y || x == 0 && y == 1 || x == 1 && y == 2 ||
                x == 2 && y == 0)
                s.pop();
            if (s.size() && s.top() == y)
                continue;
            s.push(y);
        }
    }
    int cnt[3] = {0, 0, 0};
    while (s.size())
    {
        cnt[s.top()] = 1;
        s.pop();
    }
    if (cnt[0] + cnt[1] + cnt[2] == 1)
        flag = 1;
}
void work()
{
    srand(time(NULL));
    n = read();
    flag = 0;
    a.resize(n);
    vector<int> vis(n + 1);
    for (auto &x : a)
        x = read();
    int cnt = min(100, n) * 2;
    while (cnt--)
    {
        int pos = rand() % n;
        if (vis[pos])
            continue;
        vis[pos] = 1;
        b.clear();
        for (int i = pos; i < n; i++)
            b.push_back(a[i]);
        for (int i = 0; i < pos; i++)
            b.push_back(a[i]);
        cal();
        if (flag)
        {
            puts("Yes");
            return;
        }
    }
    puts("No");
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif
    int T = 1;
    T = read();
    while (T--)
        work();
    return 0;
}