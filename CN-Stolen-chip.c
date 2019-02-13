#include <stdio.h>

#define MAX_SIDE 500
#define M 300


int		overlaps_any(int overlaps[M + 1][M + 1], int *used, short col)
{
	for (short i = 1; i <= M; i++)
	{
		if (used[i] && overlaps[i][col])
			return (1);
	}
	return (0);
}

int		find_next(int overlaps[M + 1][M + 1], int *used)
{
	// looking for the color that does not overlap any of already used colors
	for (short col = 1; col <= M; col++)
	{
		if (used[col] && !overlaps_any(overlaps, used, col))
		{
			used[col] = 0;
			return (col);
		}
	}
	return (-1);
}

int		find_order(int *order, int *used, int num_used,
			int overlaps[M + 1][M + 1])
{
	for (short step = 1; step <= num_used; step++)
	{
		int next = find_next(overlaps, used);
		if (next == -1)
			return (0);
		order[next] = step;
	}
	return (1);
}

int		main()
{
	int T, side_len, tgt_color, result;
	int chip[MAX_SIDE][MAX_SIDE];
	int Xmin[M + 1], Xmax[M + 1];
	int Ymin[M + 1], Ymax[M + 1];
	int overlaps[M + 1][M + 1];
	int used[M + 1], order[M + 1];
	int num_used;

	freopen("input.txt", "r", stdin);

	scanf("%d", &T);
	for (int test = 1; test <= T; test++)
	{
		num_used = 0;
		result = -1;
		
		// arrays initialization
		for (short i = 1; i <= M; i++)
		{
			Xmin[i] = MAX_SIDE;
			Xmax[i] = 0;
			Ymin[i] = MAX_SIDE;
			Ymax[i] = 0;
			used[i] = 0;

			for (short j = 1; j <= M; j++)
				overlaps[i][j] = 0;
		}
		scanf("%d %d", &side_len, &tgt_color);
		for (short i = 0; i < side_len; i++)
			for (short j = 0; j < side_len; j++)
				scanf("%d ", &chip[i][j]);

		// reading the boders of different colors areas 
		for (short y = 0; y < side_len; y++)
		{
			for (short x = 0; x < side_len; x++)
			{
				short color = chip[y][x];
				if (x < Xmin[color])
					Xmin[color] = x;
				if (x > Xmax[color])
					Xmax[color] = x;
				if (y < Ymin[color])
					Ymin[color] = y;
				if (y > Ymax[color])
					Ymax[color] = y;
				used[color] = 1;
			}
		}

		// overlaps[i][j] = 1 means j overlaps i
		for (short i = 1; i <= M; i++)
		{
			if (used[i])
			{
				num_used++;
				for (short y = Ymin[i]; y <= Ymax[i]; y++)
				{
					for (short x = Xmin[i]; x <= Xmax[i]; x++)
					{
						short color = chip[y][x];
						if (color != i)
							overlaps[i][color] = 1;
					}
				}
			}
		}
		if (find_order(order, used, num_used, overlaps))
			result = order[tgt_color];
		printf("#%d %d\n", test, result);
	}
	return (0);
}