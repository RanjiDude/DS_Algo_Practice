#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Template function to print 2D vectors of any type
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

// Map class
class Map
{
    public:
        int mapHeight;
        int mapWidth;
        vector<vector<int>> grid;

        Map()
        {
            mapHeight = 5;
            mapWidth = 6;
            grid = {{0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0}};
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
    vector<vector<int>> open = {{0, planner.start[0], planner.start[1]}};
    vector<vector<int>> closed;

    int g = 0, x = 0, y = 0;

    bool done = false;
    bool giveup = false;
    int exp = 0;

    while (!done && !giveup)
    {
        exp += 1;
        if(open.empty())
        {
            giveup = true;
            cout << "No path found" << endl;
            return mapstr;
        }
        else
        {
            vector<int> node = open[0];
            open.erase(open.begin());

            closed.push_back({node[0], node[1], node[2]});
            // map.grid[node[1]][node[2]] = exp;

            if (node[1] == planner.goal[0] && node[2] == planner.goal[1])
            {
                map.grid[node[1]][node[2]] = exp-1;   
                print2DVector(map.grid);
                done = true;
                g = node[0];

                std::reverse(closed.begin(), closed.end());

                // print2DVector(closed);

                vector<vector<int>> path;
                vector<int> next_node = {0,0,0};

                for (int p=0; p<g; p++)
                {
                    for (int i=0; i<planner.movements.size(); i++)
                    {
                        next_node[0] = node[0] - 1;
                        next_node[1] = node[1] + planner.movements[i][0];
                        next_node[2] = node[2] + planner.movements[i][1];

                        for (int j=0; j<closed.size(); j++)
                        {
                            if (closed[j] == next_node)
                            {
                                path.push_back({node[1], node[2]});
                                mapstr[next_node[1]][next_node[2]] = planner.movements_arrows_reversed[i];
                                node[0] = next_node[0];
                                node[1] = next_node[1];
                                node[2] = next_node[2];
                            }
                        }
                    }
                }

                // print2DVector(path);
                mapstr[planner.start[0]][planner.start[1]] = "0";
                mapstr[planner.goal[0]][planner.goal[1]] = "*";
                return mapstr;
            }
            else
            {
                // print2DVector(map.grid);

                for (int i=0; i<planner.movements.size(); i++)
                {
                    g = node[0] + 1;
                    x = node[1] + planner.movements[i][0];
                    y = node[2] + planner.movements[i][1];
                    
                    vector<int> temp = {g, x, y};
                    bool found = 0;

                    if (x >= 0 && x < map.mapHeight && y >= 0 && y < map.mapWidth && map.grid[x][y] == 0 && x+y !=0)
                    {
                        for (int j = 0; j<open.size(); j++)
                        {
                            if (open[j] == temp)
                            {
                                found = 1;
                                break;
                            }
                        }
                        if (found == 0)
                        {
                            open.push_back({g, x, y});
                        }
                    }
                }
                map.grid[node[1]][node[2]] = exp-1;
            }
        }
    }
}

int main(int argc, char ** argv)
{
    // std::cout << "Have " << argc << " arguments:" << std::endl;
    // for (int i = 0; i < argc; ++i) 
    // {
    //     std::cout << argv[i] << std::endl;
    // }
    
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
