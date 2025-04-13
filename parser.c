#include "parser.h"

static int is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static int is_hex_digit(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

static char to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + ('a' - 'A');
	}
	return c;
}

long long parse_number(const char *number)
{
	int is_negative = 0;
	if (number[0] == '-')
	{
		is_negative = 1;
		number++;
	}

	long long value = 0;
	int base = 10;

	if (number[0] == '0')
	{
		if (number[1] == 'x' || number[1] == 'X')
		{
			base = 16;
			number += 2;
		}
		else if (number[1] == 'b' || number[1] == 'B')
		{
			base = 2;
			number += 2;
		}
		else if (is_digit(number[1]))
		{
			base = 8;
			number++;
		}
	}

	while (*number)
	{
		char c = to_lower(*number);
		int digit;
		if (is_digit(c))
		{
			digit = c - '0';
		}
		else if (is_hex_digit(c))
		{
			digit = c - 'a' + 10;
		}
		else
		{
			break;
		}

		if (digit >= base)
		{
			puts("Error: Invalid digit for the given base.");
			return 0;
		}

		value = value * base + digit;
		number++;
	}

	if (is_negative)
	{
		value = ~value + 1;	   // Two's complement for negative values
	}

	return value;
}
