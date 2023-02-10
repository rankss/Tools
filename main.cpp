#include <thread>
#include <string>
#include <iostream>

#include "Logger.hpp"
#include "Graph.hpp"

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
    Tools::Logger logger(Tools::Logger::Level::TRACE, "logfile.log");
    std::thread threads[10];
    for (int i = 0; i < 10; i++)
        threads[i] = std::thread(threadLog, i);

    for (int i = 0; i < 10; i++)
        threads[i].join();
}

void TestDijkstra()
{
	// Digraph Test Driver
	Structures::Graph g(9);
	g.DirectedEdge(0, 1, 4);
	g.DirectedEdge(0, 7, 8);
	g.DirectedEdge(1, 2, 8);
	g.DirectedEdge(1, 7, 11);
	g.DirectedEdge(2, 3, 7);
	g.DirectedEdge(2, 8, 2);
	g.DirectedEdge(2, 5, 4);
	g.DirectedEdge(3, 4, 9);
	g.DirectedEdge(3, 5, 14);
	g.DirectedEdge(4, 5, 10);
	g.DirectedEdge(5, 6, 2);
	g.DirectedEdge(6, 7, 1);
	g.DirectedEdge(6, 8, 6);
	g.DirectedEdge(7, 8, 7);


}

int main()
{

    return 0;
}