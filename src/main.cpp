#include "Graph.h"
#include "ExpTree.h"

int main()
{
	try
	{
		std::string a;
		std::cout << "f(x)=";
		std::cin >> a;
		ExpTree tree(a);
		tree.print(tree.getRoot());
		// Graph graph(1000, 800);
		// graph.Run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}