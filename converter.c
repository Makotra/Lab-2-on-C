// converter.c
#include "converter.h"	  //птатта

#include "parser.h"

static void reverse_str(char *str, size_t len)
{
	for (size_t i = 0; i < len / 2; i++)
	{
		char temp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = temp;
	}
}

static size_t convert_to_base(long long number, char *buffer, int base, int uppercase)
{
	const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	size_t index = 0;

	int is_negative = 0;
	if (number < 0)
	{
		is_negative = 1;
		number = -number;
	}

	do
	{
		buffer[index++] = digits[number % base];
		number /= base;
	} while (number > 0);

	if (is_negative)
	{
		buffer[index++] = '-';
	}

	reverse_str(buffer, index);
	buffer[index] = '\0';
	return index;
}

void print(char *out_buf, const char *format, const char *number)
{
	// Проверка на неправильные форматы:
	if (format == NULL || *format != '%' || !(*format == 'd' || *format == 'x' || *format == 'X' || *format == 'o' || *format == 'b'))
	{
		puts("Error: Invalid format specifier.");
		return;
	}

	long long parsed_number = parse_number(number);

	char specifier = 0;
	int field_width = 0;
	int left_align = 0;
	int show_plus = 0;
	int space_prefix = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '-')
			{
				left_align = 1;
				format++;
			}
			if (*format == '+')
			{
				show_plus = 1;
				format++;
			}
			if (*format == ' ')
			{
				space_prefix = 1;
				format++;
			}
			while (*format >= '0' && *format <= '9')
			{
				field_width = field_width * 10 + (*format - '0');
				format++;
			}
			if (*format == 'd' || *format == 'x' || *format == 'X' || *format == 'o' || *format == 'b')
			{
				specifier = *format;
				break;
			}
		}
		format++;
	}

	char temp_buf[256] = { 0 };
	size_t len = 0;

	switch (specifier)
	{
	case 'd':	 // Decimal
		len = convert_to_base(parsed_number, temp_buf, 10, 0);
		break;
	case 'x':	 // Hexadecimal (lowercase)
		len = convert_to_base(parsed_number, temp_buf, 16, 0);
		break;
	case 'X':	 // Hexadecimal (uppercase)
		len = convert_to_base(parsed_number, temp_buf, 16, 1);
		break;
	case 'o':	 // Octal
		len = convert_to_base(parsed_number, temp_buf, 8, 0);
		break;
	case 'b':	 // Binary
		len = convert_to_base(parsed_number, temp_buf, 2, 0);
		break;
	default:
		puts("Error: Unknown format specifier.");
		return;
	}

	if (show_plus && parsed_number >= 0)
	{
		temp_buf[len++] = '+';
		reverse_str(temp_buf, len);
	}
	else if (space_prefix && parsed_number >= 0)
	{
		temp_buf[len++] = ' ';
		reverse_str(temp_buf, len);
	}

	if (field_width > 0 && field_width > len)
	{
		char padding = left_align ? ' ' : ' ';
		size_t padding_len = field_width - len;

		if (left_align)
		{
			for (size_t i = 0; i < len; i++)
			{
				out_buf[i] = temp_buf[i];
			}
			for (size_t i = 0; i < padding_len; i++)
			{
				out_buf[len + i] = padding;
			}
			out_buf[field_width] = '\0';
		}
		else
		{
			for (size_t i = 0; i < padding_len; i++)
			{
				out_buf[i] = padding;
			}
			for (size_t i = 0; i < len; i++)
			{
				out_buf[padding_len + i] = temp_buf[i];
			}
			out_buf[field_width] = '\0';
		}
	}
	else
	{
		for (size_t i = 0; i < len; i++)
		{
			out_buf[i] = temp_buf[i];
		}
		out_buf[len] = '\0';
	}
}
