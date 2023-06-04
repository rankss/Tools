#include <thread>
#include <string>
#include <iostream>
#include <vector>

#include "Logger.hpp"
#include "Graph.hpp"
#include "Unionset.hpp"

void TestLogger()
{
    Tools::Logger::Instance().Log(Tools::Logger::Level::INFO, "Test.");
}

void threadLog(int n)
{
    for (int i = 0; i < 6; i++)
        Tools::Logger::Instance().Log((Tools::Logger::Level)i, std::to_string(i));
}

void TestLoggerThread()
{
    std::thread threads[10];
    for (int i = 0; i < 10; i++)
        threads[i] = std::thread(threadLog, i);

    for (int i = 0; i < 10; i++)
        threads[i].join();
}

void TestUnionSet()
{
	Structures::UnionSet set(5);
	std::vector<int> cmp1 = { 0, 1, 2, 3, 4 };
	assert(set.Set() == cmp1);
	set.Union(1, 2);
	cmp1 = { 0, 1, 1, 3, 4 };
	assert(set.Set() == cmp1);
	set.Union(0, 3);
	cmp1 = { 0, 1, 1, 0, 4 };
	assert(set.Set() == cmp1);
	set.Union(4, 3);
	cmp1 = { 0, 1, 1, 0, 0 };
	assert(set.Set() == cmp1);
}

void TestKruskal()
{
	// Digraph Test Driver
	Structures::Graph g(9);
	g.ParallelEdge(0, 1, 4);
	g.ParallelEdge(0, 7, 8);
	g.ParallelEdge(1, 2, 8);
	g.ParallelEdge(1, 7, 11);
	g.ParallelEdge(2, 3, 7);
	g.ParallelEdge(2, 8, 2);
	g.ParallelEdge(2, 5, 4);
	g.ParallelEdge(3, 4, 9);
	g.ParallelEdge(3, 5, 14);
	g.ParallelEdge(4, 5, 10);
	g.ParallelEdge(5, 6, 2);
	g.ParallelEdge(6, 7, 1);
	g.ParallelEdge(6, 8, 6);
	g.ParallelEdge(7, 8, 7);
	
	g.Kruskal();
}

void TestDijkstra()
{
	// Digraph Test Driver
	Structures::Graph g(9);
	g.DirectedEdge(0, 1, 4);
	g.DirectedEdge(0, 4, 2);
	g.DirectedEdge(1, 2, 8);
	g.DirectedEdge(2, 8, 2);
	g.DirectedEdge(2, 3, 7);
	g.DirectedEdge(3, 7, 9);
	g.DirectedEdge(3, 6, 8);
	g.DirectedEdge(4, 5, 1);
	g.DirectedEdge(4, 8, 8);
	g.DirectedEdge(5, 8, 6);
	g.DirectedEdge(6, 7, 0);

	std::vector<int> result = g.Dijkstra(0);
}

int main()
{
	TestLogger();
	TestLoggerThread();
	TestUnionSet();
	TestKruskal();
	TestDijkstra();
    return 0;
}