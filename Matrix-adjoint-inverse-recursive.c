#include <stdio.h>

void permuteB(int *A, int *B, int l, int r, int **matrix);
void permuteA(int *A, int *B, int l, int r, int **matrix);
void creatematrix(int choice);
void createadjoint(int val, int *B, int count);
void inversematrix(int **matrix, int choice);

int count = 0;
int x, y;
int Adj[3][3];

void creatematrix(int choice)
{
	int **matrix1;

	matrix1 = malloc(3 * sizeof(int*));
	for (int i = 0; i < 3; i++)
		matrix1[i] = malloc(3 * sizeof(int));

	printf("\nPlease enter co-ordinates for 3x3 matrix : \n\n");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("[%d][%d] = ", i, j);
			scanf("%d", &matrix1[i][j]);
		}
	}

	int A[] = { 0, 1, 2 };
	int B[] = { 0, 1, 2 };

	permuteA(A, B, 0, 2, matrix1, Adj);

	if (choice == 5)
	{
		printf("\nAdjoint of matrix is :\n\n");

		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
				printf("%4d", Adj[j][k]);
			printf("\n");
		}
		printf("\n");
		displaymenu();
	}
	else if ((choice == 6) || (choice == 7))
		inversematrix(matrix1, choice);
}

void permuteA(int *A, int *B, int l, int r, int **matrix)
{
	int i;
	if (l != r)
	{
		for (i = l; i <= r; i++)
		{
			swap((A + l), (A + i));
			if (l == 0)
			{
				B[0] = 0; B[1] = 1; B[2] = 2;
			}
			permuteB(A, B, 0, 2, matrix);
			permuteA(A, B, (l + 1), 2, matrix);
			swap((A + l), (A + i));
		}
	}
}

void permuteB(int *A, int *B, int l, int r, int **matrix)
{
	int i;
	if (l == r)
	{
		int val = matrix[B[1]][A[1]] * matrix[B[2]][A[2]];;
		int coordinates[] = { A[0], B[0] };
		count++;
		createadjoint(val, coordinates, count);
	}
	else
	{
		for (i = l; i <= r; i++)
		{
			if ((l == 0) && (i == 1))
				break;
			else if (((A[0] == 0) && (A[1] == 2) && (l == 0)) ||
				((A[0] == 1) && (A[1] == 2) && (l == 0)) ||
				((A[0] == 2) && (A[1] == 0) && (l == 0)))
				i = 2;
			swap((B + l), (B + i));
			permuteB(A, B, (l + 1), 2, matrix);
			swap((B + 1), (B + i));
		}
	}
}

void createadjoint(int val, int *B, int count)
{
	int a;
	if (count % 2)
		x = val;
	else
	{
		y = val;
		int r = 2 + B[0] + B[1];
		if (B[0] == 2)
		{
			if (r % 2)
				a = 1;
			else
				a = -1;
		}
		else
		{
			if (r % 2)
				a = -1;
			else
				a = 1;
		}
		Adj[B[0]][B[1]] = a * (x - y);
	}
}

void inversematrix(int **matrix, int choice)
{
	double det = 0; double inv[3][3];
	for (int i = 0; i < 3; i++)
	{
		det = det + (Adj[i][0] * matrix[0][i]);
	}

	if (choice == 6)
		printf("\ndet = %.2f\n\n", det);
	else if (choice == 7)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				inv[i][j] = Adj[i][j] / det;
			}
		}

		printf("\nInverse of matrix is :\n\n");

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%7.2f", inv[i][j]);
			printf("\n");
		}
		printf("\n");
	}

	displaymenu();
}
