#include "Graph.h"

int main()
{
	try
	{	
		Graph graph(800, 600);
		graph.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}