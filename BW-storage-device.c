#include <stdio.h>

#define MAX_RESULT 1000000000
#define MAX_N 1000
#define S_MASK 1	//001
#define N_MASK 2	//010
#define M_MASK 4	//100
#define ALL_MASK 7	//111
#define NULL_MASK 0	//000

/*
 * filling the SNM table based on the input sequence
 */
void	prepare(int table[][MAX_N + 1], char *data, int N)
{
	// write 0 to the first column
	for (int i = 0; i < 3; i++)
		table[i][0] = 0;

	for (int j = 1; j <= N; j++)
	{
		// write the value from previous column
		for (int row = 0; row < 3; row++)
			table[row][j] = table[row][j - 1];
		if (data[j - 1] == 'S')
			table[0][j]++;
		else if (data[j - 1] == 'N')
			table[1][j]++;
		else if (data[j - 1] == 'M')
			table[2][j]++;
	}
}

/*
 * calculation of the total device production cost
 */
int		calc_cost(int wd_len, int wd_cost, int w_cost, int w_num)
{
	return (wd_len * wd_cost + w_cost * w_num);
}

int		is_identical(int table[][MAX_N + 1], int i, int L, int *mask)
{
	*mask = NULL_MASK;

	if ((table[0][i] - table[0][i - L] == 0) && (table[1][i] - table[1][i - L] == 0))
		*mask = M_MASK;
	if ((table[0][i] - table[0][i - L] == 0) && (table[2][i] - table[2][i - L] == 0))
		*mask = N_MASK;
	if ((table[1][i] - table[1][i - L] == 0) && (table[2][i] - table[2][i - L] == 0))
		*mask = S_MASK;
	if ((table[0][i] - table[0][i - L] == 0) &&
		(table[1][i] - table[1][i - L] == 0) &&
		(table[2][i] - table[2][i - L] == 0))
	{
		*mask = ALL_MASK;
	}
	return (*mask > NULL_MASK ? 1 : 0);
}

int		main()
{
	int N, wd_cost, w_cost, w_num, result;
	int snm_table[3][MAX_N + 1];

	char data[MAX_N + 1];
	for (int i = 0; i <= MAX_N; i++)
		data[i] = '0';

	freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &N, &wd_cost, &w_cost);
	scanf("%s", data);

	prepare(snm_table, data, N);
	// device cost for the writing device of length 1
	result = calc_cost(1, wd_cost, w_cost, N);

	// start with the device of length 2 and 
	// increase the length until writing is impossible
	for (int len = 2; len <= N; len++)
	{
		int arr_1[MAX_N + 1], masks[MAX_N + 1];

		arr_1[0] = 0;
		masks[0] = NULL_MASK;
		for (int i = 1; i < len; i++)
		{
			arr_1[i] = MAX_RESULT;
			masks[i] = NULL_MASK;
		}

		for (int i = len; i <= N; i++)
		{
			int var_1 = MAX_RESULT;
			int var_2 = NULL_MASK;
			int mask = 0;

			if (is_identical(snm_table, i, len, &mask))
			{
				if (arr_1[i - len] != MAX_RESULT)
				{
					var_1 = arr_1[i - len] + 1;
					var_2 = mask;
				}
				for (int j = i - len + 1; j < i; j++)
				{
					if (((mask & masks[j]) != 0) && (arr_1[j] + 1 < var_1))
					{
						var_1 = arr_1[j] + 1;
						var_2 = mask & masks[j];
					}
				}
			}
			// here arr_1[i] == MAX_RESULT or the smallest number of records
			arr_1[i] = var_1;
			masks[i] = var_2;
		}
		w_num = arr_1[N];
		if (w_num >= MAX_RESULT)
			break;

		int res = calc_cost(len, wd_cost, w_cost, w_num);
		if (res < result)
			result = res;
	}
	printf("%d\n", result);
	return (0);
}