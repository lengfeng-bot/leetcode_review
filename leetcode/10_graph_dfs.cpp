#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

void dfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    if (visited[x][y] || grid[x][y] == 0)
        return;
    visited[x][y] = true;

    if (x - 1 >= 0 && grid[x - 1][y] == '1')
        dfs(grid, visited, x - 1, y);
    if (x + 1 < grid.size() && grid[x + 1][y] == '1')
        dfs(grid, visited, x + 1, y);
    if (y - 1 >= 0 && grid[x][y - 1] == '1')
        dfs(grid, visited, x, y - 1);
    if (y + 1 < grid[0].size() && grid[x][y + 1] == '1')
        dfs(grid, visited, x, y + 1);
}

void bfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    queue<pair<int, int>> que; // 定义队列
    que.push({x, y});
    visited[x][y] = true;
    while (!que.empty())
    {
        pair<int, int> cur = que.front();
        que.pop();
        int cur_x = cur.first;
        int cur_y = cur.second;

        if (cur_x - 1 >= 0 && grid[cur_x - 1][cur_y] == '1' && !visited[cur_x - 1][cur_y])
        {
            que.push({cur_x - 1, cur_y});
            visited[cur_x - 1][cur_y] = true;
        }
        if (cur_x + 1 < grid.size() && grid[cur_x + 1][cur_y] == '1' && !visited[cur_x + 1][cur_y])
        {
            que.push({cur_x + 1, cur_y});
            visited[cur_x + 1][cur_y] = true;
        }
        if (cur_y - 1 >= 0 && grid[cur_x][cur_y - 1] == '1' && !visited[cur_x][cur_y - 1])
        {
            que.push({cur_x, cur_y - 1});
            visited[cur_x][cur_y - 1] = true;
        }
        if (cur_y + 1 < grid[0].size() && grid[cur_x][cur_y + 1] == '1' && !visited[cur_x][cur_y + 1])
        {
            que.push({cur_x, cur_y + 1});
            visited[cur_x][cur_y + 1] = true;
        }
    }
}

// 岛屿数量(dfs&&bfs)
int numIslands(vector<vector<char>> &grid)
{

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    int result = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '1' && !visited[i][j])
            {
                result++;
                // dfs(grid, visited, i, j);
                bfs(grid, visited, i, j);
            }
        }

    return result;
}

// int main()
// {
//     vector<vector<char>> grid = {{'1', '1', '0', '0', '0', '0'},
//                                  {'1', '1', '0', '0', '0', '0'},
//                                  {'0', '0', '1', '0', '0', '0'},
//                                  {'0', '0', '0', '0', '1', '1'}};
//     cout << numIslands(grid) << endl;
//     system("pause");
//     return 0;
// }
int dfs1(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    if (visited[x][y] || grid[x][y] == 0)
        return 0;
    visited[x][y] = true;
    int area = 1;

    if (x - 1 >= 0 && grid[x - 1][y] == 1)
    {
        area += dfs1(grid, visited, x - 1, y);
    }
    if (x + 1 < grid.size() && grid[x + 1][y] == 1)
    {
        area += dfs1(grid, visited, x + 1, y);
    }
    if (y - 1 >= 0 && grid[x][y - 1] == 1)
    {
        area += dfs1(grid, visited, x, y - 1);
    }
    if (y + 1 < grid[0].size() && grid[x][y + 1] == 1)
    {
        area += dfs1(grid, visited, x, y + 1);
    }
    return area;
}
/// @brief 岛屿的最大面积
/// @param grid
/// @return
int maxAreaOfIsland(vector<vector<int>> &grid)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    int max_area = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                max_area = max(max_area, dfs1(grid, visited, i, j));
            }
        }

    return max_area;
}

// int main()
// {
//     vector<vector<int>> grid = {{1, 1, 0, 0, 0, 0},
//                                 {1, 1, 0, 0, 0, 0},
//                                 {0, 0, 1, 0, 0, 0},
//                                 {0, 0, 0, 1, 1, 1}};
//     cout << maxAreaOfIsland(grid) << endl;
//     system("pause");
//     return 0;
// }

void dfs2(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    if (visited[x][y] || grid[x][y] == 1)
        return;
    grid[x][y] = 1;
    visited[x][y] = true;

    if (x - 1 >= 0 && grid[x - 1][y] == 0)
        dfs2(grid, visited, x - 1, y);
    if (x + 1 < grid.size() && grid[x + 1][y] == 0)
        dfs2(grid, visited, x + 1, y);
    if (y - 1 >= 0 && grid[x][y - 1] == 0)
        dfs2(grid, visited, x, y - 1);
    if (y + 1 < grid[0].size() && grid[x][y + 1] == 0)
        dfs2(grid, visited, x, y + 1);
}
// 找出封闭岛屿的数量
// 找出不是孤岛的岛屿，然后把它们都置0，之后在遍历一次，岛屿数量就是孤岛的数量。不是孤岛的岛屿可以从边界条件开始遍历得出
// 需要注意的是，这道题目倒反天罡，0是陆地，1是水，有点反直觉了。
int closedIsland(vector<vector<int>> &grid)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i][0] == 0)
            dfs2(grid, visited, i, 0);
        if (grid[i][grid[0].size() - 1] == 0)
            dfs2(grid, visited, i, grid[0].size() - 1);
    }

    for (int i = 0; i < grid[0].size(); i++)
    {
        if (grid[0][i] == 0)
            dfs2(grid, visited, 0, i);
        if (grid[grid.size() - 1][i] == 0)
            dfs2(grid, visited, grid.size() - 1, i);
    }

    int num = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 0 && !visited[i][j])
            {
                num++;
                dfs2(grid, visited, i, j);
            }
        }

    return num;
}

// int main()
// {
//     vector<vector<int>> grid = {{0, 0, 1, 0, 0},
//                                 {0, 1, 0, 1, 0},
//                                 {0, 1, 1, 1, 0}};
//     cout << closedIsland(grid) << endl;
//     system("pause");
//     return 0;
// }

int dfs3(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    if (visited[x][y] || grid[x][y] == 0)
        return 0;

    int per = 4;
    visited[x][y] = true;

    if (x - 1 >= 0 && grid[x - 1][y] == 1)
    {
        per--;
        per += dfs3(grid, visited, x - 1, y);
    }
    if (x + 1 < grid.size() && grid[x + 1][y] == 1)
    {
        per--;
        per += dfs3(grid, visited, x + 1, y);
    }
    if (y - 1 >= 0 && grid[x][y - 1] == 1)
    {
        per--;
        per += dfs3(grid, visited, x, y - 1);
    }
    if (y + 1 < grid[0].size() && grid[x][y + 1] == 1)
    {
        per--;
        per += dfs3(grid, visited, x, y + 1);
    }
    return per;
}
/// @brief 岛屿的周长
/// @param grid
/// @return
// 这道题目并不麻烦，我们只需要设置最初每个小方格的周长为4，然后对其上下左右四个方向进行寻找，当有一个方向有邻接岛屿，那么周长数量减一，这样遍历即可。
int islandPerimeter(vector<vector<int>> &grid)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    int zhou = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                zhou = dfs3(grid, visited, i, j);
            }
        }
    return zhou;
}

// int main()
// {
//     vector<vector<int>> grid = {{0, 1, 0, 0},
//                                 {1, 1, 1, 0},
//                                 {0, 1, 0, 0},
//                                 {1, 1, 0, 0}};
//     cout << islandPerimeter(grid) << endl;
//     system("pause");
//     return 0;
// }

void dfs4(vector<vector<int>> &grid, int x, int y)
{

    if (grid[x][y] != 1)
        return;
    grid[x][y] = 2;

    if (x - 1 >= 0 && grid[x - 1][y] == 1)
        dfs4(grid, x - 1, y);
    if (x + 1 < grid.size() && grid[x + 1][y] == 1)
        dfs4(grid, x + 1, y);
    if (y - 1 >= 0 && grid[x][y - 1] == 1)
        dfs4(grid, x, y - 1);
    if (y + 1 < grid[0].size() && grid[x][y + 1] == 1)
        dfs4(grid, x, y + 1);
}

/// @brief 飞地的数量
/// @param grid
/// @return
// 这道题目跟找出封闭岛屿的数量简直一模一样，不同之处在于，一个岛屿可能会由好几个飞地组成
int numEnclaves(vector<vector<int>> &grid)
{

    int num_one = 0;
    int num_two = 0;

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                num_one++;
            }
        }

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i][0] == 1)
            dfs4(grid, i, 0);
        if (grid[i][grid[0].size() - 1] == 1)
            dfs4(grid, i, grid[0].size() - 1);
    }

    for (int i = 0; i < grid[0].size(); i++)
    {
        if (grid[0][i] == 1)
            dfs4(grid, 0, i);
        if (grid[grid.size() - 1][i] == 1)
            dfs4(grid, grid.size() - 1, i);
    }

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 2)
            {
                num_two++;
            }
        }

    return num_one - num_two;
}

// int main()
// {
//     vector<vector<int>> grid = {{0, 0, 0, 0},
//                                 {1, 0, 1, 0},
//                                 {0, 1, 1, 0},
//                                 {0, 0, 0, 0}};
//     cout << numEnclaves(grid) << endl;
//     system("pause");
//     return 0;
// }

void dfs5(vector<vector<int>> &grid, int x, int y, vector<vector<bool>> &reach)
{

    if (reach[x][y])
        return;
    reach[x][y] = 1;
    if (x - 1 >= 0 && grid[x - 1][y] >= grid[x][y])
        dfs5(grid, x - 1, y, reach);
    if (x + 1 < grid.size() && grid[x + 1][y] >= grid[x][y])
        dfs5(grid, x + 1, y, reach);
    if (y - 1 >= 0 && grid[x][y - 1] >= grid[x][y])
        dfs5(grid, x, y - 1, reach);
    if (y + 1 < grid[0].size() && grid[x][y + 1] >= grid[x][y])
        dfs5(grid, x, y + 1, reach);
}

/// @brief 太平洋大西洋水流问题
/// @param heights
/// @return
// 水流逆流而上，先分别统计能到达太平洋，能到达大西洋的网格，之后取交集即可。
vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
{
    int m = heights.size();
    int n = heights[0].size();
    vector<vector<bool>> reachPO(m, vector<bool>(n, 0));
    vector<vector<bool>> reachAO(m, vector<bool>(n, 0));
    for (int i = 0; i < m; i++)
    {
        dfs5(heights, i, 0, reachPO);
        dfs5(heights, i, n - 1, reachAO);
    }

    for (int i = 0; i < n; i++)
    {
        dfs5(heights, 0, i, reachPO);
        dfs5(heights, m - 1, i, reachAO);
    }
    vector<vector<int>> ans;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (reachAO[i][j] && reachPO[i][j])
                ans.push_back({i, j});
        }
    return ans;
}

// int main()
// {
//     vector<vector<int>> grid = {{0, 0, 0, 0},
//                                 {1, 2, 3, 0},
//                                 {0, 1, 2, 0},
//                                 {0, 0, 1, 0}};
//     pacificAtlantic(grid);
//     system("pause");
//     return 0;
// }

/// 上面都是网格问题，它更好理解一些，下面开始，真正接触到复杂的图了！

/// @brief 找到最终的安全状态
/// @param graph
/// @return
// 三色法，很实用！
bool isSafe(vector<vector<int>> &graph, vector<int> &color, int x)
{

    if (color[x] > 0)
        return color[x] == 2;
    color[x] = 1;
    for (int y : graph[x])
    {
        if (!isSafe(graph, color, y))
            return false;
    }
    color[x] = 2;
    return true;
}

vector<int> eventualSafeNodes(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> ans;
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (isSafe(graph, color, i))
            ans.push_back(i);
    }
    return ans;
}

// int main()
// {
//     vector<vector<int>> graph = {{1, 2},
//                                  {2, 3},
//                                  {5},
//                                  {0},
//                                  {5},
//                                  {},
//                                  {}};
//     vector<int> ans = eventualSafeNodes(graph);
//     system("pause");
//     return 0;
// }

// 上面一题其实可以用到拓扑排序解决，在此之前，需要了解拓扑排序，出度和入度的相关概念。之后再说吧！

// 寻找图中是否存在路径
// 这道题要先进行转化，通过题意新建一个数组，获得每个节点相邻的对应关系。之后再去dfs,标记是否走过的节点即可。
// 本来我想的是dfs不返回值，最后判断destination节点是否被访问过即可，但是下面的方法更好。
bool dfs_path(vector<vector<int>> &path, int begin, int end, vector<bool> &isReach)
{
    isReach[begin] = true;
    if (begin == end)
        return true;

    for (int i = 0; i < path[begin].size(); ++i)
    {
        if (isReach[path[begin][i]] == false && dfs_path(path, path[begin][i], end, isReach))
            return true;
    }
    return false;
}

bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
{
    vector<vector<int>> path(n);
    vector<bool> isReach(n, 0);

    for (int i = 0; i < edges.size(); ++i)
    {
        path[edges[i][0]].push_back(edges[i][1]);
        path[edges[i][1]].push_back(edges[i][0]);
    }
    bool res = dfs_path(path, source, destination, isReach);
    cout << res << endl;
    return res;
}

// int main()
// {

//     vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};
//     int n = 3;
//     int source = 0, destination = 2;
//     validPath(n, edges, source, destination);
//     system("pause");
//     return 0;
// }
vector<vector<int>> paths;
vector<int> path;

void dfs_path2(vector<vector<int>> &graph, int begin, int end)
{
    if (path.back() == end)
    {
        paths.push_back(path);
        return;
    }
    for (int i = 0; i < graph[begin].size(); i++)
    {

        path.push_back(graph[begin][i]);
        dfs_path2(graph, graph[begin][i], end);
        path.pop_back();
    }
}

/// @brief 所有可能的路径
/// @param graph
/// @return
// 这道题怎么感觉，跟之前做的回溯非常的像,果然，轻松拿下了！
vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
{
    path.push_back(0);
    dfs_path2(graph, 0, graph.size() - 1);
    return paths;
}

// int main()
// {

//     vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
//     allPathsSourceTarget(graph);
//     return 0;
// }

/// @brief 钥匙和房间
/// @param rooms
/// @return
// 这道题也不难，因为已经规定了，只能从第0号房间进入。设置一个visited数组，对房间进行一个遍历，如果所有房间都被访问到了，返回true
bool canVisitAllRooms(vector<vector<int>> &rooms)
{
    bool ans;

    return ans;
}