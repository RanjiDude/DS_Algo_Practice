#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>

// Basic vertex structure in the graph (attributes: vertex/node name, visited status)
struct vertex
{
    char name;
    bool visited = 0;
    vertex(char n);
};

vertex::vertex(char n)
{
    vertex::name = n;
}

// Basic edge structure in the graph (attributes: from vertex's pointer, to vertex's pointer,
// distance between the two vertices)
struct edge
{
    vertex* from;
    vertex* to;
    int distance;
    edge(vertex &f, vertex &t, int d)
    {
        from = &f;
        to = &t;
        distance = d;
    }
};

// Basic graph structure (attributes: vector of all vertices, vector of all edges)
struct graph
{
    std::vector<vertex*> vertices;
    std::vector<edge*> edges;
    void graph_init()
    {
        for (auto x: vertices)
        {
            x->visited = 0;
        }
    }
};

// Basic structure of elements getting stored in the priority queue
// Makes it easier to compare two elements during sorting
struct pq_elem
{   
    vertex* v;
    int dist;
    
    pq_elem()
    {
        v = NULL;
        dist = 0;
    }

    pq_elem(vertex &vert, int d)
    {
        v = &vert;
        dist = d;
    }
};

// Comparision function for priority queue
struct compare
{
    bool operator()(const pq_elem &a, const pq_elem &b)
    {
        return a.dist > b.dist;
    }
};

// Custom 1D vector print function
template <class T>
void print_vect(std::vector<T> vec)
{
    while(!vec.empty())
    {
        T el = vec.back();
        vec.pop_back();
        std::cout << el;
        if (!vec.empty())
        {
            std::cout << "->";
        }
    }
    std::cout << std::endl;
}

// Custom print function for priority queue
void print_pq(std::priority_queue<pq_elem, std::vector<pq_elem>, compare> pq)
{
    while(!pq.empty())
    {
        pq_elem temp = pq.top();
        std::cout << "[" << temp.v->name << ", " << temp.dist << "]";
        pq.pop();
        if (!pq.empty())
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

// Custom print function for tuples
void print_tuple(std::tuple<vertex*, int> t)
{
    auto x = t;
    std::cout << "{" << std::get<0>(x)->name << ", " << std::get<1>(x) << "}";
}

// Custom print functions for maps
void print_map(const std::map<vertex*, std::tuple<vertex*, int>> &m)
{
    for(auto x : m)
    {
        std::cout << "[" <<  x.first->name << " : ";
        auto y = x.second;
        if (std::get<0>(y))
        {
            std::cout << "{" << std::get<0>(y)->name << ", " << std::get<1>(y)<< "}";
        }
        else
        {
            std::cout << "{" << "NULL" << ", " << std::get<1>(y)<< "}";
        }
        
        std::cout << "]";
    }
    std::cout << std::endl;
}

// MAIN DIJKSTRA'S ALGORTIHM FUNCTION
std::vector<char> dijkstra(graph g, vertex &start, vertex &goal)
{
    std::vector<char> result;
    std::priority_queue<pq_elem, std::vector<pq_elem>, compare> pq;
    
    std::map<vertex*, std::tuple<vertex*, int>> m;
    m.insert(std::pair<vertex*, std::tuple<vertex*, int>>(&start, {NULL, 0}));

    pq_elem next(start, 0);
    pq.push(next);
    
    while (!pq.empty())
    {
        // print_pq(pq);
        // print_map(m);
        
        pq_elem node = pq.top();
        node.v->visited = 1;
        pq.pop();

        if (node.v->name == goal.name)
        {
            vertex* current = &goal;
            while(current)
            {
                auto y = m[current];
                {
                    result.push_back(current->name);
                    current = std::get<0>(y);
                }
            }
            break;
        }

        // std::cout << "Nodes discovered from " << node.v->name << " " << node.dist << ":" << std::endl;

        for (auto x : g.edges)
        {
            if (x->from->name == node.v->name and x->to->visited == 0)
            {
                next.v = x->to;
                next.dist = x->distance + node.dist;
                // std::cout << next.v->name << std::endl;
                pq.push(next);
                if (m.find(next.v) == m.end())
                {
                    m.insert(std::pair<vertex*, std::tuple<vertex*, int>>(next.v, {node.v, next.dist}));
                }
                else if (m.find(next.v) != m.end())
                {
                    auto i = m[next.v];
                    if (std::get<1>(i) > next.dist)
                    {
                        m[next.v] = {node.v, next.dist};
                    }
                }
            }
        }
    }
    if (!result.empty())
    {
        return result;
    }
    else
    {
        std::cout << "No path found" << std:: endl;
        return {};
    }
}

int main()
{
    
    // Creating all vertices in the graph
    vertex* a = new vertex('a');
    vertex* b = new vertex('b');
    vertex* c = new vertex('c');
    vertex* d = new vertex('d');
    vertex* e = new vertex('e');
    vertex* f = new vertex('f');
    vertex* h = new vertex('h');

    // Creating all edges in the graph and connecting different vertices
    // Edges in this graph are bi-directional i.e. we can move from a to b and b to a as well
    // This need not be the case for all vertices. Feel free to change as you see fit.
    edge* ab = new edge(*a, *b, 4);
    edge* ba = new edge(*b, *a, 4);
    
    edge* ac = new edge(*a, *c, 2);
    edge* ca = new edge(*c, *a, 2);

    edge* bc = new edge(*b, *c, 1);
    edge* cb = new edge(*c, *b, 1);

    edge* bd = new edge(*b, *d, 5);
    edge* db = new edge(*d, *b, 5);

    edge* cd = new edge(*c, *d, 8);
    edge* dc = new edge(*d, *c, 8);

    edge* ce = new edge(*c, *e, 10);
    edge* ec = new edge(*e, *c, 10);

    edge* de = new edge(*d, *e, 2);
    edge* ed = new edge(*e, *d, 2);

    edge* df = new edge(*d, *f, 6);
    edge* fd = new edge(*f, *d, 6);

    edge* ef = new edge(*e, *f, 5);
    edge* fe = new edge(*f, *e, 5);
    
    // Initializing the graph
    graph g;
    
    // Adding all created vertices to the vertices vector in the graph
    g.vertices.push_back(a);
    g.vertices.push_back(b);
    g.vertices.push_back(c);
    g.vertices.push_back(d);
    g.vertices.push_back(e);
    g.vertices.push_back(f);
    g.vertices.push_back(h);
    
    // Adding all created edges to the edges vector in the graph
    g.edges.push_back(ab);
    g.edges.push_back(ac);
    g.edges.push_back(bc);
    g.edges.push_back(bd);
    g.edges.push_back(cd);
    g.edges.push_back(ce);
    g.edges.push_back(de);
    g.edges.push_back(df);
    g.edges.push_back(ef);

    g.edges.push_back(ba);
    g.edges.push_back(ca);
    g.edges.push_back(cb);
    g.edges.push_back(db);
    g.edges.push_back(dc);
    g.edges.push_back(ec);
    g.edges.push_back(ed);
    g.edges.push_back(fd);
    g.edges.push_back(fe);

    g.graph_init();

    // dijkstra(g, *a, *f);
    print_vect(dijkstra(g, *a, *f));
    
    return 0;
}
