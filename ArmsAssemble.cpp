/**
 * 有n * m的地图，地图上'0'表示陆地，可站，'1'表示沼泽，不可站
 * 有k支部队要集合到一个地点，每个部队可以往上下左右四个方向移动，求所有部队集合所花的时间（取最终到达集合地点的时间）的最小值
 * 输出最小值，无法集合输出-1
 */
#include <bits/stdc++.h>
using namespace std;

int path;
int oneWaymn;
vector<vector<int>> directions = {{1,0}, {-1,0}, {0,1}, {0, -1}};
void oneWay(vector<string>& matrix, int si, int sj, int ti, int tj, vector<vector<bool>>& visited) {
    if (si == ti && sj == tj) {
        oneWaymn = min(oneWaymn, path);
        return;
    }
    for (auto& k : directions) {
        int ni = si + k[0], nj = sj + k[1];
        if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[0].size() && matrix[ni][nj] == '0' && !visited[ni][nj]) {
            visited[ni][nj] = true;
            path++;
            oneWay(matrix, ni, nj, ti, tj, visited);
            path--;
            visited[ni][nj] = false;
        }
    }
}

int dfs(vector<string>& matrix, vector<vector<int>>& arms, int ti, int tj) {
    int res = 0;
    for (int i = 0; i < arms.size(); ++i) {
        path = 0;
        oneWaymn = INT_MAX;
        vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
        int si = arms[i][0] - 1, sj = arms[i][1] - 1;
        oneWay(matrix, si, sj, ti, tj, visited);
        // cout << "Arms " << i + 1 << " : " << oneWaymn << endl;
        if (oneWaymn == INT_MAX) return -1;
        res = max(res, oneWaymn);
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> matrix(n);
    for (int i = 0; i < n; ++i) {
        cin >> matrix[i];
        // cout << matrix[i] << endl;
    }
    int k;
    cin >> k;
    vector<vector<int>> arms(k, vector<int>(2, 0));
    for (int i = 0; i < k; ++i) {
        cin >> arms[i][0] >> arms[i][1];
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == '0') {
                int curTime = dfs(matrix, arms, i, j);
                if (curTime == -1) continue;
                ans = min(ans, curTime);
            }
        }
    }
    if (ans == INT_MAX) ans = -1;
    cout << ans << endl;

}