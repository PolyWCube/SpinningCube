#pragma GCC optimize("O3") 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

float A, B, C;
float x, y, z;
float ooz;
int xp, yp;

float cube_width = 20;
float k1 = 40;
int distance_from_viewport = 60;
int width = 180, height = 50;
float z_buffer[180 * 50];
char buffer[180 * 50];
char output_buffer[180 * 50 + 1];
int background_ascii_code = ' ';

float increment_space = 0.6;
int i;

float calculate_x(int a, int b, int c) {
	return b * sin(A) * sin(B) * cos(C) - c * cos(A) * sin(B) * cos(C) + b * cos(A) * sin(C) + c * sin(A) * sin(C) + a * cos(B) * cos(C);
}
float calculate_y(int a, int b, int c)
{
	return b * cos(A) * cos(C) + c * sin(A) * cos(C) - b * sin(A) * sin(B) * sin(C) + c * cos(A) * sin(B) * sin(C) - a * cos(B) * sin(C);
}
float calculate_z(int a, int b, int c)
{
	return c * cos(A) * cos(B) - b * sin(A) * cos(B) + a * sin(B);
}
void calculate_surface(float cube_x, float cube_y, float cube_z, int ch)
{
	x = calculate_x(cube_x, cube_y, cube_z);
	y = calculate_y(cube_x, cube_y, cube_z);
	z = calculate_z(cube_x, cube_y, cube_z) + distance_from_viewport;
	
	ooz = 1/z;
	xp = (int)(width / 2 + k1 * ooz * x * 2);
	yp = (int)(height / 2 + k1 * ooz * y);
	
	i = xp + yp * width;
	if (i >= 0 && i < width * height)
	{
		if (ooz > z_buffer[i])
		{
			z_buffer[i] = ooz;
			buffer[i] = ch;
		}
	}
}
void initial()
{
	
}

int main() 
{ 
	system("cls");
	while (true)
	{
		memset(buffer, background_ascii_code, width * height);
		memset(z_buffer, 0, width * height * 4);
		for (float cube_x = -cube_width; cube_x < cube_width; cube_x += increment_space)
		{
			for (float cube_y = -cube_width; cube_y < cube_width; cube_y += increment_space)
			{
				calculate_surface(cube_x, cube_y, -cube_width, '.');
				calculate_surface(cube_width, cube_y, cube_x, '$');
				calculate_surface(-cube_width, cube_y, -cube_x, ';');
				calculate_surface(-cube_x, cube_y, cube_width, '>');
				calculate_surface(cube_x, -cube_width, -cube_y, '%');
				calculate_surface(cube_x, cube_width, cube_y, '&');
			}
		}
		system("cls");
		int buffer_index = 0;
		for (int k = 0; k < width * height; k++) {
			output_buffer[buffer_index++] = (k % width ? buffer[k] : '\n');
		}
		output_buffer[buffer_index] = '\0';
		
		A += 0.05;
		B += 0.05;
		
		printf("%s", output_buffer);
	}
	return 0; 
}