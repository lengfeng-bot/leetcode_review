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

void dfs2(vector<vector<char>> &grid, vector<vector<bool>> &visited, int x, int y)
{

    if (visited[x][y] || grid[x][y] == 0)
        return 0;
    visited[x][y] = true;
    int num_closed = 0;
    if (x - 1 >= 0 && grid[x - 1][y] == '1')
    {

        dfs(grid, visited, x - 1, y);
    }
    if (x + 1 < grid.size() && grid[x + 1][y] == '1')
        dfs(grid, visited, x + 1, y);
    if (y - 1 >= 0 && grid[x][y - 1] == '1')
        dfs(grid, visited, x, y - 1);
    if (y + 1 < grid[0].size() && grid[x][y + 1] == '1')
        dfs(grid, visited, x, y + 1);
}
// 找出封闭岛屿的数量
int closedIsland(vector<vector<int>> &grid)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    int num = 0;
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                int colsed = 0;
                dfs(grid, visited, i, j);
                if (colsed == 4)
                    num++;
            }
        }

    return num;
}