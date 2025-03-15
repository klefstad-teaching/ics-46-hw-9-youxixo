#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);

    using pii = pair <int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto [curr_dist, u] = pq.top();
        pq.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for(auto &edge : G[u])
        {
            int v = edge.dst;
            int w = edge.weight;
            if(!visited[v] && curr_dist + w < dist[v])
            {
                dist[v] = curr_dist + w;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, 
                                 const vector<int>& previous, 
                                 int destination)
{
    vector<int> path;
    for(int v = destination; v != -1; v = previous[v])
    {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}