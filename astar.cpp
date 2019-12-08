#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>

void print(std::vector<std::vector<int>> &graph)
{
    for (auto i: graph)
    {
        for (auto j: i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> getneighbors(const std::vector<std::vector<int>> &graph, std::vector<int> node)
{
    std::vector<std::vector<int>> neighbors;
    std::vector<std::vector<int>> directions = {{0, 1}, {1, 1}, {1, 0}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    int x = 0, y = 0;
    for (int i=0; i<directions.size(); ++i)
    {
        x = node[0] + directions[i][0];
        y = node[1] + directions[i][1];
        if (0 <= x and x < graph.size() and 0 <= y and y < graph[0].size() and graph[x][y] != -1)
        {
            neighbors.push_back({x, y});
        }
    }
    return neighbors;
}

std::vector<std::vector<int>> getheuristic(std::vector<std::vector<int>> graph, const std::vector<int> &goal, char distance)
{
    std::vector<std::vector<int>> h;
    for (int i=0; i<graph.size(); ++i)
    {
        h.push_back({});
        for (int j=0; j<graph[i].size(); ++j)
        {
            h[i].push_back(std::numeric_limits<int>::max());
        }
    }

    if (distance=='c')
    {
        std::queue<std::vector<int>> q;
        q.push({0, goal[0], goal[1]});
        while (!q.empty())
        {
            std::vector<int> node = q.front();
            q.pop();
            graph[node[1]][node[2]] = -1;
            h[node[1]][node[2]] = node[0];
            std::vector<std::vector<int>> nebs = getneighbors(graph, {node[1], node[2]});
            for (auto n : nebs)
            {
                int heur = std::max(std::abs(goal[0]-n[0]), std::abs(goal[1]-n[1]));
                q.push({heur, n[0], n[1]});
            }
        }

    }
            
    return h;
}



int main()
{
    std::vector<std::vector<int>> graph = {{0, 0, 0, 0, 0},
                                           {0, 1, 1, 1, 0},
                                           {0, 0, 0, 1, 0},
                                           {0, 0, 0, 1, 0},
                                           {0, 0, 0, 0, 0}};

    print(graph);
    std::vector<std::vector<int>> h = getheuristic(graph, {0, 4}, 'c');
    print(h);

}