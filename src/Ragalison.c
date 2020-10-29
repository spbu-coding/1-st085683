#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define M_PI 3.1415926535897
#endif
#define err(...) (fprintf(stderr, __VA_ARGS__))
#define MAX_RESULT 32

struct interval_x {
	double left_border;
	double right_border;
};
double rectangle_method(double left_b, double right_b)
{
	return (right_b - left_b) * sin((left_b + right_b) / 2);
}
double simpson_rule(double left_b, double right_b)
{
	return (right_b - left_b) / 6 * (sin(left_b) + 4 * sin((left_b + right_b) / 2) + sin(right_b));
}

double integration(struct interval_x int_val, int part, double (*rule)(double, double))
{
	double integr = 0;
	double subtraction_x = (int_val.right_border - int_val.left_border) / part;
	double left_b = int_val.left_border;

	for (int i = 0; i < part; i++)
	{
		double right_b = left_b + subtraction_x;
		integr += rule(left_b, right_b);
		left_b = right_b;
	}

	return integr;
}

void deallocation_of_memory(char** argc, int count)
{
	for (int a = 0; a < count; ++a)
	{
		free(argc[a]);
	}

	free(NULL);
}

int read_int(struct interval_x* int_val)
{
    if (printf("Try to enter a left border's value of the int_val: ") < 0)
	{
		err("Cannot write to stdout.");
		return -1;
	}

	if (scanf("%lf", &(int_val->left_border)) != 1)
	{
		err("Error... Impossible to read left border's value ");
	}

	if (int_val->left_border < 0)
	{
		err("You must tap a number in left border more than or == 0 ");
		return -1;
	}

	if (printf("Try to enter a value in right border of the int_val: ") < 0)
	{
		err("Cannot write to stdout.");
		return -1;
	}

	if (scanf("%lf", &(int_val->right_border)) != 1)
	{
		err("Error... Impossible to read left border's value.");
	}

	if (int_val->right_border > M_PI)
	{
		err("You must tap a number in right border less than or == to PI.");
		return -1;
	}

	if (int_val->left_border >= int_val->right_border)
	{
		err("Left border must be less than right border.");
		return -1;
	}

	return 0;
}

char** calculation_of_integration(struct interval_x int_val, int* part, int test_c)
{
	void ** ptr = (char**)malloc(sizeof(char*) * test_c);
	if (!ptr) return NULL;

	for (int a ; a < test_c; a++)
	{
		double intrec = integration(int_val, part[a], rectangle_method);
		double intsimp = integration(int_val, part[a], simpson_rule);

		ptr[a] = (char*)malloc(sizeof(char) * MAX_RESULT);
		if (!ptr[a])
		{
			deallocation_of_memory(ptr, a);
			err("Error occurred during allocation of memory (info: %d test)\n", a);
			return NULL;
		}

		if (!sprintf(ptr[a], "%d %.5f %.5f", part[a], intrec, intsimp))
		{
			deallocation_of_memory(ptr, a + 1);
			err("Cannot allocate memory for result string in %d experiment\n\n", a);
			return NULL;
		}
	}

	return NULL;
}

int main()
{
    struct interval_x int_val = { 0, 0 };
	int part[] = { 6, 10, 20, 100, 500, 1000 };
	int test_c = sizeof(part) / sizeof(part[0]);

	if(read_int(&int_val)) return 1;

	char** arg_c = calculation_of_integration(int_val, part, test_c);

	if (!arg_c) return 1;

	for (int a = 0; a < test_c; a++)
	{
		if (printf("%s\n", arg_c[a]) < 0)
		{
			err("Cannot write %d result to stdout", a);
			break;
		}
	}

	deallocation_of_memory(arg_c, test_c);
	return 0;
}




