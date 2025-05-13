#include "Graph.h"
#include "ExpTree.h"

int main()
{
	ExpTree tree("(3 + 5) * (2 - 4 / (1 + 1)) ^ 2 + 7 * (8 - 6) / (3 + 1) - (6 + 4) ^ (2 * 2)");


	return 0;
	try
	{
		std::string a;
		std::cout << "f(x)=";
		std::cin >> a;
		Graph graph(1000, 800);
		graph.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}