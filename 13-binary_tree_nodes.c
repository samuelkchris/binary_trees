#include "binary_trees.h"

/**
 * binary_tree_nodes - counts the nodes with atleast one child
 * @tree: pointer to the root node of a tree to count
 *
 * Return: if tree is NULL, return 0, otherwise - node count
 */
size_t binary_tree_nodes(const binary_tree_t *tree)
{
	size_t nodes = 0;

	if (tree)
	{
		nodes += (tree->left || tree->right) ? 1 : 0;
		nodes += binary_tree_nodes(tree->left);
		nodes += binary_tree_nodes(tree->right);
	}
	return (nodes);
}
