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
	void print(Node *root);
	Node *getRoot() const;
	std::string infixToPostfix();

private:
	Node *root;
	std::string form;
private:
	
	void constructTree();
	void freeTree(Node *root);

	bool isOperator(char opr);
	int getPriority(char opr);

};