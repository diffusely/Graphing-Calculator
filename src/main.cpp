#include "Graph.h"
#include "ExpTree.h"

int main()
{
	try
	{
		// std::string input;
		// std::cout << "f(x)=";
		// std::getline(std::cin, input);
		Graph graph(1000, 800, "x");
		graph.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}