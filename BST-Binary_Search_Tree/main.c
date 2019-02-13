#include <stdio.h>

#define MAX_SEQ_LEN 300000

typedef struct	s_tree_node
{
	int key;
	struct s_tree_node *parent;
	struct s_tree_node *left;
	struct s_tree_node *right;
} 				t_tree_node;


void	tree_insert(t_tree_node **root, t_tree_node *node, long *count)
{
	t_tree_node *parent = NULL;
	t_tree_node *trav = *root;

	while (trav)
	{
		(*count)++;
		parent = trav;
		if (node->key < trav->key)
			trav = trav->left;
		else
			trav = trav->right;
	}
	node->parent = parent;
	if (!parent)
		*root = node;
	else if (node->key < parent->key)
		parent->left = node;
	else
		parent->right = node;
}

void	recursive_tree_insert(t_tree_node *root, t_tree_node *node, long long *count)
{
	(*count)++;
	if (node->key < root->key)
	{
		if (!root->left)
			root->left = node;
		else
			recursive_tree_insert(root->left, node, count);
	}
	else
	{
		if (!root->right)
			root->right = node;
		else
			recursive_tree_insert(root->right, node, count);
	}
}

int		main()
{
	int seq_len, key;
	long long count = 0;
	static t_tree_node seq[MAX_SEQ_LEN];
	t_tree_node *root = NULL;

	freopen("input.txt", "r", stdin);

	scanf("%d", &seq_len);
	for (int i = 0; i < seq_len; i++)
	{
		scanf("%d", &key);
		seq[i].key = key;
		seq[i].parent = NULL;
		seq[i].left = NULL;
		seq[i].right = NULL;

		if (!root)
			root = &(seq[i]);
		else
			recursive_tree_insert(root, &(seq[i]), &count);

		printf("%lld\n", count);
	}
	return (0);
}