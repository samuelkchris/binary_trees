#include "binary_trees.h"

/**
 * binary_tree_size - Measures the size of a binary tree.
 *
 * @tree: Pointer to the root node of the tree to measure the size of.
 *
 * Return: Size of the binary tree.
 */
size_t binary_tree_size(const heap_t *tree)
{
    if (!tree)
        return (0);
    return (binary_tree_size(tree->left) + 1 + binary_tree_size(tree->right));
}

/**
 * sift_down - Repairs a max binary heap by sifting down a node.
 *
 * @heap: Pointer to the root node of the heap to repair.
 */
void sift_down(heap_t *heap)
{
    heap_t *max_node, *temp;

    while (1)
    {
        max_node = heap;
        if (heap->left && heap->left->n > max_node->n)
            max_node = heap->left;
        if (heap->right && heap->right->n > max_node->n)
            max_node = heap->right;
        if (max_node == heap)
            break;
        temp = heap->n;
        heap->n = max_node->n;
        max_node->n = temp;
        heap = max_node;
    }
}

/**
 * get_last_node - Gets the last node in the level-order traversal of a tree.
 *
 * @root: Pointer to the root node of the tree.
 *
 * Return: Pointer to the last node, or NULL if the tree is empty.
 */
heap_t *get_last_node(heap_t *root)
{
    int size, mask;
    heap_t *node;

    size = binary_tree_size(root);
    if (size == 0)
        return (NULL);

    mask = size >> 1;
    node = root;

    while (mask > 0)
    {
        if (size & mask)
            node = node->right;
        else
            node = node->left;
        mask >>= 1;
    }

    return (node);
}

/**
 * heap_extract - Extracts the root node of a max binary heap.
 *
 * @root: Double pointer to the root node of the heap.
 *
 * Return: Value stored in the root node, or 0 on failure.
 */
int heap_extract(heap_t **root)
{
    int value;
    heap_t *last_node;

    if (!root || !*root)
        return (0);

    value = (*root)->n;
    last_node = get_last_node(*root);

    if (*root == last_node)
    {
        free(*root);
        *root = NULL;
        return (value);
    }

    (*root)->n = last_node->n;

    if (last_node->parent->right == last_node)
        last_node->parent->right = NULL;
    else
        last_node->parent->left = NULL;

    free(last_node);
    sift_down(*root);
    return (value);
}
