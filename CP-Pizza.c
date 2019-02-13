#include <stdio.h>

const int MAX_PIECES = 50;
const int MAX_PEOPLE = 25;
const int MAXINT = 10000000;

#define MIN(a,b) ((a<b)?(a):(b))
#define MAX(a,b) ((a>b)?(a):(b))


int		dp(int N, int M, int cur_max, const int arr[MAX_PIECES],
			int cache[MAX_PEOPLE][MAX_PIECES])
{
	if (cache[N][M] != -1)
		return cache[N][M];

	if (N == 1)
	{
		int min = 0;
		for (int i = 0; i < M; ++i)
			min += arr[i];

		if (min > cur_max)
			min = -MAXINT;
		cache[N][M] = min;
		return (min);
	}
	if (M == N)
	{
		int min = MAXINT;
		for (int i = 0; i < M; ++i)
		{
			if (arr[i] > cur_max)
			{
				cache[N][M] = -MAXINT;
				return -MAXINT;
			}
			else
				min = MIN(min, arr[i]);
		}
		cache[N][M] = min;
		return (min);
	}
	int min = -MAXINT;
	for (int i = M - 1; i >= N - 1; --i)
	{
		int cur_left_slice = 0;

		for (int j = 0; j < M - i; ++j)
			cur_left_slice += arr[M - 1 - j];
		if (cur_left_slice > cur_max)
			break;
		int min_other = dp(N - 1, i, cur_max, arr, cache);
		min = MAX(min, MIN(cur_left_slice, min_other));
	}
	cache[N][M] = min;
	return (min);
}

int		main()
{
	int T;

	freopen("input.txt", "r", stdin);

	scanf("%d", &T);
	for (int test = 1; test <= T; ++test)
	{
		int N, M;
		int res = MAXINT;
		// number of sausage pieces on every pizza slice
		int sausage_init[MAX_PIECES];
		int cache[MAX_PEOPLE][MAX_PIECES];

		scanf("%d %d", &N, &M);

		float sum = 0;
		for (int i = 0; i < M; ++i)
		{
			scanf("%d", &sausage_init[i]);
			sum += sausage_init[i];
		}
		// average amount of sausage for every person
		float average = sum / N;

		for (int i = 0; i < M; ++i)
		{
			int sum = 0;
			for (int j = 0; j < M - N + 1; ++j)
				sum += sausage_init[(j + i) % M];

			for (int j = M - N; j >= 0 && sum >= average; --j)
			{
				int temp_array[MAX_PIECES];
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						cache[i][j] = -1;

				for (int k = 0; k < M - j - 1; ++k)
					temp_array[k] = sausage_init[(i + j + k + 1) % M];

				int min_size = dp(N - 1, M - (j + 1), sum, temp_array, cache);
				if (sum >= min_size && (sum - min_size) < res)
					res = sum - min_size;
				sum -= sausage_init[(j + i) % M];
			}
		}
		printf("%d\n", res);
	}
	return (0);
}