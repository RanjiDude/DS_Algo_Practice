#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
#include "math.h"

class compare
{
    public:
        bool operator()(const std::vector<int> &a, const std::vector<int> &b)
        {
            return a[0] > b[0];
        }
};

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

void printpq(std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, compare> q)
{
    while(!q.empty())
    {
        std::vector<int> temp = q.top();
        std::cout << "[" << temp[0] << "," << temp[1] << "," << temp[2] << "] ";
        q.pop();
    }
    std::cout << std::endl;
}

void printvector(const std::vector<int> &v)
{
    for (auto i:v)
    {
        std::cout << i << " ";
    }
    // std::cout << std::endl;
}

std::vector<std::vector<int>> getNeighbors(const std::vector<std::vector<int>> &graph, const std::vector<int> &node)
{
    std::vector<std::vector<int>> neighbors;
    std::vector<std::vector<int>> directions = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};
    int x = 0, y = 0;
    for (int i=0; i<directions.size(); ++i)
    {
        x = node[0] + directions[i][0];
        y = node[1] + directions[i][1];
        if (0 <= x and x < graph.size() and 0 <= y and y < graph[0].size())
        {
            neighbors.push_back({x, y});
        }
    }
    return neighbors;
}

std::vector<std::vector<int>> getHeuristic(std::vector<std::vector<int>> graph, const std::vector<int> &goal, char distance)
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

    std::queue<std::vector<int>> q;
    q.push({0, goal[0], goal[1]});
    while (!q.empty())
    {
        std::vector<int> node = q.front();
        q.pop();
        graph[node[1]][node[2]] = -1;
        h[node[1]][node[2]] = node[0];
        std::vector<std::vector<int>> nebs = getNeighbors(graph, {node[1], node[2]});
        for (auto n : nebs)
        {
            int heur;
            if (distance == 'c')
            {
                heur = std::max(std::abs(goal[0]-n[0]), std::abs(goal[1]-n[1]));
            }
            else if (distance == 'm')
            {
                heur = std::abs(goal[0]-n[0]) + std::abs(goal[1]-n[1]);
            }
            // else if (distance == 'e')
            // {
            //     heur = std::pow(std::pow(goal[0]-n[0], 2) + std::pow(goal[1]-n[1], 2), 0.5);
            // }
            // q.push({heur, n[0], n[1]});

            if (graph[n[0]][n[1]] != -1)
            {
                q.push({heur, n[0], n[1]});
            }
        }
    }

    return h;
}



std::map<std::vector<int>, std::vector<int>> astar(std::vector<std::vector<int>> graph, const std::vector<int> &start, const std::vector<int> &goal, char distance)
{
    std::vector<std::vector<int>> h = getHeuristic(graph, goal, distance);
    print(h);
    std::map<std::vector<int>, std::vector<int>> m;
    m.insert(std::pair<std::vector<int>, std::vector<int>>(start, {}));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, compare> q;
    q.push({0 + h[start[0]][start[1]], start[0], start[1]});
    int s=0;
    while(!q.empty())
    {
        // std::cout << "Iteration " << s++ << std::endl;
        // print(graph);
        // printpq(q);
        std::vector<int> node = q.top();
        // std::cout << "Chosen Node: " << "[" << node[1] << "," << node[2] << "] " << std::endl;
        q.pop();
        graph[node[1]][node[2]] = node[0];
        if (node[1] == goal[0] and node[2] == goal[1])
        {
            break;
        }
        std::vector<std::vector<int>> nebs = getNeighbors(graph, {node[1], node[2]});
        for (auto n: nebs)
        {
            if (graph[n[0]][n[1]] == 0)
            {
                m.insert(std::pair<std::vector<int>, std::vector<int>>(n, {node[1], node[2]}));
                
                int g = 0;
                if (distance == 'c')
                {
                    g = std::max(std::abs(start[0]-n[0]), std::abs(start[1]-n[1]));
                }
                else if (distance == 'm')
                {
                    g = std::abs(start[0]-n[0]) + std::abs(start[1]-n[1]);
                }
                int f = 0;
                f = g + h[n[0]][n[1]];
                graph[n[0]][n[1]] = f;
                // std::cout << "[" << f << "," << n[0] << "," << n[1] << "] " << std::endl;
                q.push({f, n[0], n[1]});
            }
        }
    }
    if (q.empty())
    {
        std::cout << "No path found" << std::endl;
        std::map<std::vector<int>, std::vector<int>> nm;
        return nm;
    }
    print(graph);
    return m;
}

void getPath(std::map<std::vector<int>, std::vector<int>> m,const std::vector<int> &goal)
{
    std::vector<std::vector<int>> path;
    std::vector<int> current = goal;
    while(!current.empty())
    {
        path.insert(path.begin(), current);
        current = m[current];
    }
    for (int i=0; i<path.size(); ++i)
    {
        std::cout << "[" << path[i][0] << "," << path[i][1] << "]";
        if (i != path.size()-1)
        {
            std::cout << "->";
        }
    }
    std::cout << std::endl;
    
}


int main()
{
    std::vector<std::vector<int>> graph = {{1, 0, 0, 0, 0},
                                           {0, 1, 1, 1, 0},
                                           {0, 0, 0, 1, 0},
                                           {0, 0, 0, 1, 0},
                                           {0, 0, 0, 1, 0}};

    print(graph);
    std::vector<int> start = {0, 0}, goal = {4, 4};
    if (graph[start[0]][start[1]] == 1 or graph[goal[0]][goal[1]] == 1)
    {
        std::cout << "There cannot be an obstacle at the start position or the goal position" << std::endl;
        return 0;
    }
    // std::vector<std::vector<int>> h = getHeuristic(graph, goal, 'c');
    // print(h);
    std::map<std::vector<int>, std::vector<int>> pathnodes = astar(graph, start, goal, 'c');
    // for (auto it=pathnodes.begin(); it!=pathnodes.end(); ++it)
    // {
    //     printvector(it->first);
    //     std::cout << "=> ";
    //     printvector(it->second);
    //     std::cout << std::endl;
    // }
    if (!pathnodes.empty())
    {
        getPath(pathnodes, goal);
    }

    return 0;
}