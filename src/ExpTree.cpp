#include "ExpTree.h"

ExpTree::ExpTree(const std::string &form)
	: form(form)
	, root(nullptr)
{
	std::cout << infixToPostfix() << "\n";
	constructTree();
}

ExpTree::~ExpTree()
{

}

void ExpTree::insert(const std::string& val)
{
	if (!root)
		root = new Node(val);
	else
	{

	}
}

void ExpTree::print(Node *root)
{
	if (!root)
		return;

	print(root->left);
	std::cout << root->ch << "\n";
	print(root->right);
}

ExpTree::Node *ExpTree::getRoot() const
{
	return root;
}

std::string ExpTree::infixToPostfix()
{
	std::stack<char> stack;
	std::string res;

	for (int i = 0; i < form.size(); i++)
	{
		if (isspace(form[i]))
			continue;

		if (!isOperator(form[i]))
			res.push_back(form[i]);
		else if (form[i] == ')')
		{
			while (!stack.empty() && stack.top() != '(')
			{
				res.push_back(stack.top());
				stack.pop();
			}

			stack.pop();
		}
		else
		{
			while (!stack.empty() && stack.top() != '(' &&
				getPriority(stack.top()) >= getPriority(form[i]))
			{
				res.push_back(stack.top());
				stack.pop();
			}

			stack.push(form[i]);
		}
	}

	while (!stack.empty())
	{
		res.push_back(stack.top());
		stack.pop();
	}

	return res;
}

void ExpTree::constructTree()
{
	std::stack<Node*> stack;
	std::string res = infixToPostfix();

	for (int i = 0; i < res.size(); i++)
	{
		if (!isOperator(res[i]))
		{
			Node *temp = new Node(res[i]);
			stack.push(temp);
		}
		else
		{
			Node* temp = new Node(res[i]);

			temp->left = stack.top();
			stack.pop();
			temp->right = stack.top();
			stack.pop();
			stack.push(temp);
		}
	}
	if (!stack.empty())
		root = stack.top();
}

bool ExpTree::isOperator(char opr)
{
	return (opr == '+' || opr == '/' || 
			opr == '-' || opr == '*' || 
			opr == '^' || opr == '(' || 
			opr == ')');
}

int ExpTree::getPriority(char opr)
{
	if (opr == '-' || opr == '+')
		return 1;
	if (opr == '/' || opr == '*')
		return 2;
	if (opr == '^')
		return 3;
	if (opr == '(')
		return 4;
	return 0;
}
