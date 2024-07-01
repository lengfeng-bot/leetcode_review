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

/// @brief 太平洋大西洋水流问题
/// @param heights
/// @return
vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
{
}