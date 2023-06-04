#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "Logger.hpp"
#include "Unionset.hpp"

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
		std::vector<int> parent;

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
			this->adjList.resize(n);
			this->E = 0;
			this->V = n;
		}
		~Graph() {}

		int Size()
		{
			return this->V;
		}

		void DirectedEdge(int x, int y, int w = 1)
		{
			this->sanity(x, y);
			this->adjList[x].push_back(Edge(x, y, w));
			this->E++;
		}

		void ParallelEdge(int x, int y, int w = 1)
		{
			this->sanity(x, y);
			this->adjList[x].push_back(Edge(x, y, w));
			this->adjList[y].push_back(Edge(y, x, w));
			this->edgeList.push_back(Edge(x, y, w));
			this->E++;
		}

		std::vector<int> Dijkstra(int x)
		{
			std::vector<int> distance(V, INT_MAX);
			this->parent.resize(V, -1);
			std::vector<bool> visited(V, false);

			distance[x] = 0, this->parent[x] = x;

			for (int v = 0; v < V; v++)
			{
				int select = 0, min = INT_MAX;
				for (int i = 0; i < V; i++)
					if (distance[i] < min && !visited[i])
						select = i, min = distance[i];
				visited[select] = true;

				for (Edge& edge : adjList[select])
				{
					int dest = edge.Destination(), weight = edge.Weight();
					if (distance[select] + weight < distance[dest] && !visited[dest])
					{
						distance[dest] = distance[select] + weight;
						this->parent[dest] = select;
					}
				}
			}

			std::stringstream ss;

			ss << "\n|Vertex|Dijkstra|Parent|\n";
			for (int i = 0; i < V; i++)
			{
				if (distance[i] == INT_MAX)
					ss << "|" << std::setw(6) << i << "|" << std::setw(8) << "INF" << "|" << std::setw(6) << this->parent[i] << "|" << std::endl;
				else
					ss << "|" << std::setw(6) << i << "|" << std::setw(8) << distance[i] << "|" << std::setw(6) << this->parent[i] << "|" << std::endl;
			}
			Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, ss.str());
			return distance;
		}
		
		Graph Kruskal()
		{
			std::vector<Edge> mstEdgeList;
			std::sort(this->edgeList.begin(), this->edgeList.end());
			Structures::UnionSet set(V);

			int count = 0;
			for (int i = 0; count < this->V - 1 && i < this->E; i++)
			{
				Edge edge = edgeList[i];
				if (set.Union(edge.Source(), edge.Destination()))
				{
					mstEdgeList.push_back(edge);
					count++;
				}
			}
			
			Graph mst(V);
			if (set.SetCount() > 1)
			{
				Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, "Graph is disjoint.");
				return mst;
			}

			for (Edge& edge : mstEdgeList)
				mst.ParallelEdge(edge.Source(), edge.Destination(), edge.Weight());

			Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, "Returned Kruskal's resulting graph.");
			return mst;
		}

		std::vector<int> BellmanFord(int x)
		{
			std::vector<int> distance(V, INT_MAX);
			this->parent.resize(V, -1);

			distance[x] = 0, this->parent[x] = x;
			
			for (int count = 0; count < V - 1; count++)
			{
				for (int src = 0; src < V; src++)
				{
					for (Edge& edge : this->adjList[src])
					{
						int dest = edge.Destination(), weight = edge.Weight();
						if (distance[src] != INT_MAX && distance[src] + weight < distance[dest])
						{
							distance[dest] = distance[src] + weight;
							this->parent[dest] = src;
						}
					}
				}
			}

			for (int src = 0; src < V; src++)
			{
				for (Edge& edge : this->adjList[src])
				{
					int dest = edge.Destination(), weight = edge.Weight();
					if (distance[src] != INT_MAX && distance[src] + weight < distance[dest])
					{
						Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, "There exists a negative cycle.");
						distance.clear();
						return distance;
					}
				}
			}

			std::stringstream ss;

			ss << "\n|Vertex|Bellman-Ford|Parent|\n";
			for (int i = 0; i < V; i++)
			{
				if (distance[i] == INT_MAX)
					ss << "|" << std::setw(6) << i << "|" << std::setw(12) << "INF" << "|" << std::setw(6) << this->parent[i] << "|" << std::endl;
				else
					ss << "|" << std::setw(6) << i << "|" << std::setw(12) << distance[i] << "|" << std::setw(6) << this->parent[i] << "|" << std::endl;
			}
			Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, ss.str());
			return distance;
		}
	};
}

#endif // !GRAPH_HPP