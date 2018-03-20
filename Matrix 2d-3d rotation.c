#include <stdio.h>
#include <math.h>

void rot3dmatrix(float x, float y, float z, int choice, float theta, int c2);
void rotationtype(int c2);

void rotationtype(int c2)
{
	float x, y, z, theta;
	int choice, choice1;
	
	if (c2 == 9)
	{
		do
		{
			printf("\nSelect the axis about which you would like to carry out your rotation : ");
			printf("\n\n1: Rotate about x-axis\n2: Rotate about y-axis\n3: Rotate about z-axis");
			printf("\n\nPlease enter your choice (1, 2 or 3) : ");
			scanf("%d", &choice);
			if ((choice < 1) || (choice > 3))
				printf("\nInvalid choice. Please choose option 1, 2 or 3\n");
		} while ((choice < 1) || (choice > 3));
	}
	else
		choice = 3;

	printf("\nPlease enter the x co-ordinate : ");
	scanf("%f", &x);
	printf("\nPlease enter the y co-ordinate : ");
	scanf("%f", &y);
	if (c2 == 9)
	{
		printf("\nPlease enter the z co-ordinate : ");
		scanf("%f", &z);
	}
	else
		z = 0;
	do
	{
		printf("\nWould you like to rotate clockwise or anti-clockwise : ");
		printf("\n\n1: Clockwise\n2: Anti-clockwise");
		printf("\n\nPlease enter your choice (1 or 2) : ");
		scanf("%d", &choice1);
		if ((choice1 < 1) || (choice1 > 2))
			printf("\nInvalid choice. Please choose option 1 or 2\n\n");
	} while ((choice1 < 1) || (choice1 > 2));

	printf("\nPlease enter the angle you would like to rotate by (in degrees) : ");
	scanf("%f", &theta);
	if (choice1 == 1)
		theta = 360 - theta;
	theta = theta / (180 / 3.14159);
	rot3dmatrix(x, y, z, choice, theta, c2);
}

void rot3dmatrix(float x, float y, float z, int choice, float theta, int c2)
{
	float A = sin(theta), B = cos(theta);

	printf("\nCalculating new co-ordinates...\n");
	if (choice == 1)
	{
		float matrix3d[3][3] = { 1, 0, 0, 0, B, -A, 0, A, B };
		float x1 = x * matrix3d[0][0] + y * matrix3d[0][1] + z * matrix3d[0][2];
		float y1 = x * matrix3d[1][0] + y * matrix3d[1][1] + z * matrix3d[1][2];
		float z1 = x * matrix3d[2][0] + y * matrix3d[2][1] + z * matrix3d[2][2];
		printf("\nx' = %2.2f\ny' = %2.2f\nz' = %2.2f\n\n", x1, y1, z1);
	}
	else if (choice == 2)
	{
		float matrix3d[3][3] = { B, 0, A, 0, 1, 0, -A, 0, B };
		float x1 = x * matrix3d[0][0] + y * matrix3d[0][1] + z * matrix3d[0][2];
		float y1 = x * matrix3d[1][0] + y * matrix3d[1][1] + z * matrix3d[1][2];
		float z1 = x * matrix3d[2][0] + y * matrix3d[2][1] + z * matrix3d[2][2];
		printf("\nx' = %2.2f\ny' = %2.2f\nz' = %2.2f\n\n", x1, y1, z1);
	}
	else if (choice == 3)
	{
		float matrix3d[3][3] = { B, -A, 0, A, B, 0, 0, 0, 1 };
		float x1 = x * matrix3d[0][0] + y * matrix3d[0][1] + z * matrix3d[0][2];
		float y1 = x * matrix3d[1][0] + y * matrix3d[1][1] + z * matrix3d[1][2];
		float z1 = x * matrix3d[2][0] + y * matrix3d[2][1] + z * matrix3d[2][2];
		if (c2 == 9)
			printf("\nx' = %2.2f\ny' = %2.2f\nz' = %2.2f\n\n", x1, y1, z1);
		else
			printf("\nx' = %2.2f\ny' = %2.2f\n\n", x1, y1);

	}
	displaymenu();
}