/* 2551102 ×¿03 ÍõÑ¦ğ© */
#include <iostream>
#include <ctime>
using namespace std;

void generate_minefield(int minefield[10][26])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			minefield[i][j] = 0;
		}
	}

	int placed = 0;
	while (placed < 50)
	{
		int r = rand() % 10;
		int c = rand() % 26;
		if (minefield[r][c] == -1)
		{
			continue;
		}
		minefield[r][c] = -1;
		placed++;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (minefield[i][j] == -1)
			{
				continue;
			}
			int cnt = 0;
			for (int dr = -1; dr <= 1; dr++)
			{
				for (int dc = -1; dc <= 1; dc++)
				{
					if (dr == 0 && dc == 0)
					{
						continue;
					}
					int nr = i + dr;
					int nc = j + dc;
					if (nr >= 0 && nr < 10 && nc >= 0 && nc < 26)
					{
						if (minefield[nr][nc] == -1)
						{
							cnt++;
						}
					}
				}
			}
			minefield[i][j] = cnt;
		}

	}

}

void print_minefield(const int minefield[10][26])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (minefield[i][j] == -1)
			{
				cout << "*" << " ";
			}
			else
			{
				cout << minefield[i][j] << " ";
			}
		}
		cout << endl;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int a[10][26];
	generate_minefield(a);
	print_minefield(a);
	return 0;
}