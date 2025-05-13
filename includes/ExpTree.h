#pragma once

#include <stack>
#include <string>
#include <iostream>

class ExpTree
{
private:
	struct Node
	{
		Node(const std::string &value)
			: left(nullptr)
			, right(nullptr)
			, value(value)
		{}

		Node *left;
		Node *right;
		std::string value;
	};
public:
	ExpTree(const std::string &form);
	~ExpTree();

	void insert(const std::string& val);

private:
	Node *root;
	std::string form;
private:
	std::string infixToPostfix();
	void constructTree();

	bool isOperator(char opr);
	int getPriority(char opr);

};