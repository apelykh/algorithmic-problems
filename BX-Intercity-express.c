#include <stdio.h>

#define MAX_CITIES 2000

typedef struct	s_node
{
	int price;
	int dest;
}				t_node;

int visited[MAX_CITIES], city_inds[MAX_CITIES];
int blocked_from;
int blocked_dest;
int glob_max;
int v_t;

void	dfs(t_node gr[MAX_CITIES][MAX_CITIES], t_node *t, int diam)
{
	visited[t->dest] = 1;

	for (int i = 0; i < city_inds[t->dest]; i++)
	{
		if (!visited[gr[t->dest][i].dest] &&
			(((blocked_from != t->dest) || (blocked_dest != gr[t->dest][i].dest)) &&
			 ((blocked_dest != t->dest) || (blocked_from != gr[t->dest][i].dest))))
		{
			dfs(gr, &gr[t->dest][i], diam + gr[t->dest][i].price);
		}
	}
	if (diam > glob_max)
	{
		v_t = t->dest;
		glob_max = diam;
	}
}


int		solve()
{
	int num_cities;
	int visited_cpy[MAX_CITIES];
	t_node graph[MAX_CITIES][MAX_CITIES];

	scanf("%d\n", &num_cities);
	for (int i = 0; i < num_cities; i++)
	{
		city_inds[i] = 0;
		visited[i] = 0;
	}

	for (int i = 0; i < num_cities - 1; i++)
	{
		int price, from, dest;

		scanf("%d %d %d\n", &price, &from, &dest);
		from--;
		dest--;
		graph[from][(city_inds[from])].price = price;
		graph[from][(city_inds[from])++].dest = dest;

		graph[dest][(city_inds[dest])].price = price;
		graph[dest][(city_inds[dest])++].dest = from;
	}

	int max_diam = 0;
	// for every edge
	for (int i = 0; i < num_cities - 1; i++)
	{
		for (int j = 0; j < city_inds[i]; j++)
		{
			int diam = 0;
			t_node t;
			t.price = 0;

			// edge [i][j] is deleted
			blocked_from = i;
			blocked_dest = graph[i][j].dest;

			// counting first connected area diameter
			t.dest = blocked_from;
			v_t = 0;
			glob_max = 0;
			dfs(graph, &t, 0);

			// reset the state to the one before dfs call
			for (int i = 0; i < num_cities; i++)
				visited[i] = 0;

			t.dest = v_t;
			glob_max = 0;
			dfs(graph, &t, 0);
			diam += glob_max;

			// save visited state
			for (int i = 0; i < num_cities; i++)
				visited_cpy[i] = visited[i];

			// counting second connected area diameter
			t.dest = blocked_dest;
			v_t = 0;
			glob_max = 0;
			dfs(graph, &t, 0);

			// reset the state to the one before dfs call
			for (int i = 0; i < num_cities; i++)
				visited[i] = visited_cpy[i];

			t.dest = v_t;
			glob_max = 0;
			dfs(graph, &t, 0);
			diam += glob_max;

			// diameter + price for the deleted edge
			diam += graph[i][j].price;

			if (diam > max_diam)
				max_diam = diam;

			for (int i = 0; i < num_cities; i++)
				visited[i] = 0;
		}
	}
	return (max_diam);
}

int		main()
{
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d\n", &T);
	for (int test = 1; test <= T; test++)
		printf("%d %d\n", test, solve());

	return (0);
}