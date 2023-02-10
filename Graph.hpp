#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace Structures
{
	class Edge
	{
	private:
		int src;
		int dest;
		int weight;

	public:
		Edge() = delete;
		Edge(int aSrc, int aDest, int aWeight)
		{
			this->src = aSrc;
			this->dest = aDest;
			this->weight = aWeight;
		}
		~Edge() {}

		const int Source() { return this->src; };
		const int Destination() { return this->dest; };
		const int Weight() { return this->weight; };

		friend bool operator <(const Edge& lhs, const Edge& rhs)
		{
			return lhs.weight < rhs.weight;
		}

		friend bool operator >(const Edge& lhs, const Edge& rhs)
		{
			return lhs.weight > rhs.weight;
		}

		friend std::ostream& operator <<(std::ostream& os, const Edge& edge)
		{
			os << "[" << edge.src << "-" << edge.dest << " : " << edge.weight << "]";
			return os;
		}
	};

	class Graph
	{
	private:
		int E, V;
		std::vector<std::vector<Edge>> adjList;
		std::vector<Edge> edgeList;

		void sanity(int x, int y = 0)
		{
			try
			{
				assert(x >= 0 && x < V);
				assert(y >= 0 && y < V);
			}
			catch (std::exception& e)
			{
				throw e;
			}
		}

	public:
		Graph() = delete;
		Graph(int n)
		{
			adjList.resize(n);
			E = 0;
			V = n;
		}
		~Graph() {}

		int Size()
		{
			return V;
		}

		void DirectedEdge(int x, int y, int w = 1)
		{
			sanity(x, y);
			adjList[x].push_back(Edge(x, y, w));
			E++;
		}

		void ParallelEdge(int x, int y, int w = 1)
		{
			sanity(x, y);
			adjList[x].push_back(Edge(x, y, w));
			adjList[y].push_back(Edge(y, x, w));
			edgeList.push_back(Edge(x, y, w));
			E++;
		}

		std::vector<int> Dijkstra(int x)
		{
			std::vector<int> distance(V, INT_MAX);
			std::vector<int> parent(V, -1);
			std::vector<bool> visited(V, false);

			distance[x] = 0, parent[x] = x;

			for (int v = 0; v < V; v++)
			{
				int select = 0, min = INT_MAX;
				for (int i = 0; i < V; i++)
				{
					if (distance[i] < min && !visited[i])
					{
						select = i, min = distance[i];
					}
				}
				visited[select] = true;

				for (Edge& edge : adjList[select])
				{
					int dest = edge.Destination(), weight = edge.Weight();
					if (distance[select] + weight < distance[dest] && !visited[dest])
					{
						distance[dest] = distance[select] + weight;
						parent[dest] = select;
					}
				}
			}

			std::stringstream ss;

			std::cout << "|Vertex|Dijkstra|Parent|\n";
			for (int i = 0; i < V; i++)
			{
				if (distance[i] == INT_MAX)
					std::cout << "|" << std::setw(6) << i << "|" << std::setw(8) << "INF" << "|" << std::setw(6) << parent[i] << "|" << std::endl;
				else
					std::cout << "|" << std::setw(6) << i << "|" << std::setw(8) << distance[i] << "|" << std::setw(6) << parent[i] << "|" << std::endl;
			}

			return distance;
		}
	};
}

#endif // !GRAPH_HPP
