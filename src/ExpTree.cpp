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
	freeTree(root);
}

void ExpTree::print(Node *root)
{
	if (!root)
		return;

	print(root->left);
	std::cout << root->value << "\n";
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
		{
			if (i - 1 >= 0 && (isdigit(form[i - 1]) || isalpha(form[i - 1])))
				res.push_back('|');
			continue;
		}

		if (!isOperator(form[i]))
		{
			res.push_back(form[i]);

			if (i + 1 >= form.size() || isOperator(form[i + 1]))
				res.push_back('|');
		}
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

float ExpTree::getResult(Node *root, float value)
{

	if (!root)
		return 0;

	if (!root->left && !root->right)
	{	
		if (root->value == "x")
			return value;
		return std::stod(root->value);
	}


	double leftVal = getResult(root->left, value);
	double rightVal = getResult(root->right, value);

	if (root->value == "+") return leftVal + rightVal;
	if (root->value == "-") return leftVal - rightVal;
	if (root->value == "*") return leftVal * rightVal;
	if (root->value == "/") return leftVal / rightVal;
	if (root->value == "^") return std::pow(leftVal,rightVal);

	throw std::runtime_error("Unknown operator: " + root->value);
}

void ExpTree::constructTree()
{
	std::stack<Node*> stack;
	std::string res = infixToPostfix();
	std::string value;

	for (int i = 0; i < res.size(); i++)
	{
		if (res[i] == '|')
		{
			Node *temp = new Node(value);
			stack.push(temp);
			value.clear();
		}
		else if (!isOperator(res[i]))
			value.push_back(res[i]);
		else
		{
			value.push_back(res[i]);
			Node* temp = new Node(value);

			if (!stack.empty())
			{
				temp->right = stack.top();
				stack.pop();
			}
			if (!stack.empty())
			{
				temp->left = stack.top();
				stack.pop();
			}
			
			stack.push(temp);
			value.clear();
		}
	}
	if (!stack.empty())
		root = stack.top();
}

void ExpTree::freeTree(Node *root)
{
	if (!root)
		return;

	freeTree(root->left);
	free(root->left);
	freeTree(root->right);
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
