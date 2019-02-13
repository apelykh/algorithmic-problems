#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 100

int		is_valid_comb(int comb, int mask)
{
	return ((comb & mask) == mask);
}

int		calculate_squares(int prev, int cur, int N)
{
	int res = 0;

	for (int i = 0; i < N; i++)
	{
		if (((prev & (3 << i)) == 0) && ((cur & (3 << i)) == (3 << i)))
		{
			res++;
			i++;
		}
	}
	return (res);
}

void	calculate(int res[][MAX_COLS], int i, int j, int N,
			int num_comb, int *masks)
{
	int result = 0;

	res[i][j] = 0;
	for (int prev = 0; prev < num_comb; prev++)
	{
		if (is_valid_comb(prev, masks[j - 1]))
		{
			result = calculate_squares(prev, i ^ masks[j], N) + res[prev][j - 1];
			if (result > res[i][j])
				res[i][j] = result;
		}
	}
}

int		main()
{
	int N, M, masks[MAX_COLS], num_comb;
	int res[1 << MAX_ROWS][MAX_COLS];
	char dot;

	freopen("input.txt", "r", stdin);

    scanf("%d %d\n", &N, &M);
    for (int i = 0; i < M; i++)
    	masks[i] = 0;

    for (int i = 0; i < N; i++)
    {
    	for (int j = 0; j < M; j++)
    	{
    		scanf("%c", &dot);
    		if (dot == '#')
    			masks[j] = masks[j] | (1 << i);
    	}
    	scanf("%c", &dot);
    }
    num_comb = (1 << N);

    for (int j = 1; j < M; j++)
    {
    	for (int i = 0; i < num_comb; i++)
    	{
    		if (is_valid_comb(i, masks[j]))
    			calculate(res, i, j, N, num_comb, masks);
    	}
    }
    printf("%d\n", res[num_comb - 1][M - 1]);
	return (0);
}