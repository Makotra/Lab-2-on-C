#include "converter.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		puts("Error: Program expects exactly two arguments: format and number.");
		return 1;
	}

	char out_buf[256] = { 0 };
	print(out_buf, argv[1], argv[2]);
	puts(out_buf);

	return 0;
}