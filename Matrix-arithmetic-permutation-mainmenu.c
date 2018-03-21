#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void displaymenu();

void creatematrices(int); //choice 1, 2 or 3
void addmatrices(int **Myarray, int **Myarray2, int row, int col); //choice 1
void submatrices(int **Myarray, int **Myarray2, int row, int col); //choice 2
void prodmatrices(int **Myarray, int **Myarray2, int row, int col); //choice 3

void genpermutaions(); //choice 4
void swap(char *x, char *y); 
void permute(char *a, int l, int r);

main()
{
	displaymenu();
}

void displaymenu()
{
	int choice = 0;
	int i = 0;
	do
	{
		printf("What would you like to do?\n\n");
		printf("1. Add two matrices\n");
		printf("2. Subtract two matrices\n");
		printf("3. Multiply two matrices\n");
		printf("4. Generate all possible permutations of a set of characters (max 6)\n");
		printf("5. Adjoint of a matrix (size 3x3)\n");
		printf("6. Determinant of a matrix (size 3x3)\n");
		printf("7. Inverse of a matrix (size 3x3)\n");
		printf("8. Apply rotation matrix onto 2d geometric structure\n");
		printf("9. Apply rotation matrix onto 3d geometric structure\n");
		printf("10. Exit program\n\n");

		printf("Please enter your choice : ");
		scanf(" %i", &choice);

		if ((choice == 1) || (choice == 2) || (choice == 3))
		{
			creatematrices(choice);
		}
		else if (choice == 4)
		{
			genpermutaions();
		}
		else if ((choice == 5) || (choice == 6) || (choice == 7))
		{
			creatematrix(choice);
		}
		else if ((choice == 8) || (choice == 9))
		{
			rotationtype(choice);
		}
		else if (choice == 10)
		{
			printf("\nThank you for using this program.\n\n");
		}
		else
		{
			printf("\nPlease make a valid choice\n\n");
		}
		i++;
	} while (((choice > 10) || (choice <= 0)) && (i < 3));

	if (i >= 3)
	{
		printf("Too many invalid choices. Goodbye !\n\n");
	}
}

void creatematrices(int choice)
{	
	int row, col, count1, count2;	
	printf("\nPlease enter the dimensions for your matrix/matrices\n");
	printf("\nDimension 1 : ");
	scanf("%i", &row);
	printf("\nDimension 2 : ");
	scanf("%i", &col);
	printf("\n");
	
	int **Myarray, **Myarray2;

	Myarray = malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
	{
		Myarray[i] = malloc(col * sizeof(int));
	}
	
	Myarray2 = malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
	{
		Myarray2[i] = malloc(col * sizeof(int));
	}

	printf("\nPlease enter the values for your first matrix\n");
	for (count1 = 0; count1 < row; count1++)
	{
		for (count2 = 0; count2 < col; count2++)
		{
			printf("[%i][%i] = ", count1, count2);
			scanf("%i", &Myarray[count1][count2]);
		}
	}

	count1 = 0; count2 = 0;
	printf("\n\nPlease enter the values for your second matrix\n");
	for (count1 = 0; count1 < row; count1++)
	{
		for (count2 = 0; count2 < col; count2++)
		{
			printf("[%i][%i] = ", count1, count2);
			scanf("%i", &Myarray2[count1][count2]);
		}
	}

	switch (choice)
	{
	case 1: addmatrices(Myarray, Myarray2, row, col); break;
	case 2: submatrices(Myarray, Myarray2, row, col); break;
	case 3: prodmatrices(Myarray, Myarray2, row, col); break;
	}	
}

void addmatrices(int **Myarray, int **Myarray2)
{
	int i, j;
	int **Newarray;

	Newarray = malloc(2*sizeof(int*));
	for (i = 0; i < 2; i++)
	{
		Newarray[i] = malloc(2*sizeof(int));
	}
	
	printf("\nMatrix 1 :  \n");

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			printf("%4d", Myarray[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 2 :  \n");

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			printf("%4d", Myarray2[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 1 + Matrix 2 : \n");
	
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			Newarray[i][j] = Myarray[i][j] + Myarray2[i][j];
			printf("%4d", Newarray[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	displaymenu();
}

void submatrices(int **Myarray, int **Myarray2, int row, int col)
{
	int i, j;
	int **Newarray;

	Newarray = malloc(row*sizeof(int*));
	for (i = 0; i < row; i++)
	{
		Newarray[i] = malloc(col*sizeof(int));
	}

	printf("\nMatrix 1 :  \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%4d", Myarray[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 2 :  \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%4d", Myarray2[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 1 - Matrix 2 : \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			Newarray[i][j] = Myarray[i][j] - Myarray2[i][j];
			printf("%4d", Newarray[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	displaymenu();
}


void prodmatrices(int **Myarray, int **Myarray2, int row, int col)
{
	int i, j;
	int **Newarray;

	Newarray = malloc(row*sizeof(int*));
	for (i = 0; i < row; i++)
	{
		Newarray[i] = malloc(col*sizeof(int));
	}

	printf("\nMatrix 1 :  \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%4d", Myarray[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 2 :  \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%4d", Myarray2[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix 1 x Matrix 2 : \n");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			Newarray[i][j] = Myarray[i][j] * Myarray2[i][j];
			printf("%4d", Newarray[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	displaymenu();
}

void swap(char *x, char *y)
{
	char temp; //creates new character
	temp = *x; //stores value for x in temp
	*x = *y; //puts old value of y in storage space for x
	*y = temp; //puts old value of x in the storage space for y
}

void permute(char *a, int l, int r)
{
	//recursive function, swaps all characters in string;
	int i;
	if (l == r)
	{
		printf("%s \n", a);
	}
	else
	{
		for (i = l; i <= r; i++)
		{
			swap((a + l), (a + i));
			permute(a, (l + 1), r);
			swap((a + l), (a + i));
		}
	}
}

void genpermutaions()
{
	char *str;
	int answer;
	int i = 0;
	do{
		i++; //i < 2 condition breaks program if a character other than an integer is input
		printf("\nHow many characters would you like to enter : ");
		scanf("%d", &answer);

		if (answer > 6)
		{
			printf("\nPlease enter a number less than 6 and greater than 0.\n");
		}
		else if (answer <= 0)
		{
			printf("\nPlease enter a positive number less than 6.\n");
		}
	} while (((answer <= 0) || (answer > 6)) && (i < 3));

	str = malloc(sizeof(char) * (answer -1));
	printf("\nPlease enter your string : ");
	scanf("%s", str);
	printf("\nGenerating permutations...\n\n");
	permute(str, 0, (answer -1));
	printf("\n");
	displaymenu();
}
