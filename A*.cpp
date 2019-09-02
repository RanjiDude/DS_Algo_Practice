#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class compare
{
    public:
        bool operator()(std::vector<int> const& a, std::vector<int> const& b)
        {
            return a[0] > b[0];
        }
};

// Template functions to print 2D vectors and queues of any type
template <typename T>
void print1DVector(vector<T> v)
{
    for (int i=0; i<v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void print2DVector(vector<vector<T>> g)
{
    for (int i=0; i<g.size(); i++)
    {
        for (int j=0; j<g[0].size(); j++)
        {
            std::cout << g[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void print2Dqueue(priority_queue<vector<T>, vector<vector<T>>, compare> q)
{
    while(!q.empty())
    {
        vector<int> temp = q.top();
        cout << temp[0] << " " << temp[1] << " " << temp[2] << " " << temp[3] <<  endl;
        q.pop();
    }
    std::cout << std::endl;
}

// Map class
class Map
{
    public:
        int mapHeight;
        int mapWidth;
        vector<vector<int>> grid;
        vector<vector<int>> h;

        Map()
        {
            mapHeight = 5;
            mapWidth = 6;
            grid = {{0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0}};
                    
            h =    {{9, 8, 7, 6, 5, 4},
                    {8, 7, 6, 5, 4, 3},
                    {7, 6, 5, 4, 3, 2},
                    {6, 5, 4, 3, 2, 1},
                    {5, 4, 3, 2, 1, 0}};
        }
};

// Planner class
class Planner
{
    public:
        vector<vector<int>> movements = {{-1,0},{0,-1},{1,0},{0,1}};
        vector<string> movements_arrows = {"^", "<", "v", ">"};
        vector<string> movements_arrows_reversed = {"v", ">", "^", "<"};
        vector<int> start = {0,0};
        vector<int> goal = {4,5};
        int cost = 1;
};




// The search function which will generate the expansion list
vector<vector<string>> search(Map map, Planner planner, vector<vector<string>> mapstr)
{
    priority_queue<vector<int>, vector<vector<int>>, compare> open;
    open.push({map.h[planner.start[0]][planner.start[1]] + 0, 0, planner.start[0], planner.start[1]});
    
    vector<vector<int>> closed;

    int g = 0, f = map.h[planner.start[0]][planner.start[1]] + g, x = 0, y = 0;

    bool done = false;
    bool giveup = false;
    int exp = 0;

    while (!done && !giveup)
    {
        exp += 1;
        if (open.empty())
        {
            giveup = true;
            cout << "No path found" << endl;
            return mapstr;
        }
        else
        {
            vector<int> node = open.top();
            // print1DVector(node);
            // print2Dqueue(open);

            open.pop();

            closed.push_back(node);
            // print2DVector(closed);

            if (node[2] == planner.goal[0] && node[3] == planner.goal[1])
            {
                map.grid[node[2]][node[3]] = exp-1;
                done = 1;
                // g = node[1];

                // print2DVector(closed);
                vector<vector<int>> path;

                for (int p=0; p<closed.size()-1; p++)
                {
                    vector<int> next_node = closed[p+1];
                    for (int i=0; i<planner.movements.size(); i++)
                    {
                        if (closed[p][2] + planner.movements[i][0] == next_node[2] && closed[p][3] + planner.movements[i][1] == next_node[3])
                            {
                                path.push_back({closed[p][2], closed[p][3]});
                                mapstr[closed[p][2]][closed[p][3]] = planner.movements_arrows[i];
                            }
                    }
                }
                print2DVector(path);
                mapstr[planner.start[0]][planner.start[1]] = "0";
                mapstr[planner.goal[0]][planner.goal[1]] = "*";
                return mapstr;
            }
            else
            {
                for (int i=0; i<planner.movements.size(); i++)
                {
                    g = node[1] + 1;
                    x = node[2] + planner.movements[i][0];
                    y = node[3] + planner.movements[i][1];

                    if (x >= 0 && x < map.mapHeight && y >= 0 && y < map.mapWidth && map.grid[x][y] == 0 && x+y != 0)
                    {
                        f = map.h[x][y]+g;
                        open.push({f, g, x, y});
                    }
                }
            }
            map.grid[node[2]][node[3]] = exp-1;
        }
    }
}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;
    vector<vector<int>> pth;

    vector<vector<string>> mapstr;
    for (int i=0; i<map.mapHeight; i++)
    {
        mapstr.push_back({});
        for (int j=0; j<map.mapWidth; j++)
        {
            mapstr[i].push_back(std::to_string(map.grid[i][j]));
        }
    }
    
    // Search for the expansions
    mapstr = search(map, planner, mapstr);
    
    print2DVector(mapstr);

    return 0;
}
