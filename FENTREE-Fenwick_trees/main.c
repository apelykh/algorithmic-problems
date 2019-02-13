#include <stdio.h>

#define MAX_SIZE 1000000

long long	read_sum(long long fentree[], int i)
{
	long long sum = 0;

	while (i > 0)
	{
		sum += fentree[i];
		i -= (i & -i);
	}
	return (sum);
}

void		update(long long fentree[], int N, int i, int val)
{
	while (i <= N)
	{
		fentree[i] += val;
		i += (i & -i);
	}
}

int			main()
{
	char op;
	int ai, num_q, N, l, r;
	long long fentree[MAX_SIZE + 1];

	freopen("input.txt", "r", stdin);
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &ai);
		update(fentree, N, i, ai);
	}
	scanf("%d\n", &num_q);
	while (num_q--)
	{
		scanf("%c %d %d\n", &op, &l, &r);
		if (op == 'q')
			printf("%lld\n", read_sum(fentree, r) - read_sum(fentree, l - 1));
		else if (op == 'u')
			update(fentree, N, l, r);
	}
	return (0);
}