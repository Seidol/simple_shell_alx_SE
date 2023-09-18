#include "shell.h"

/**
 * main - The main entry point of the shell program.
 * @count: The ergument count
 * @vector: The argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int count, char **vector)
{
	info_t info[] = { INFO_INIT };
	int error_fd = STDERR_FILENO, fd;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (error_fd)
		: "r" (error_fd));
	if (count == 2)
		fd = open(vector[1], O_RDONLY);

		if (fd == -1)
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
				_puts(vector[0]);
				_puts(": 0: Can't open ");
				_puts(vector[1]);
				_putchar('\n');
				_putchar(BUF_FLUSH);
				exit(127);
			return (EXIT_FAILURE);
		info->readfd = fd;
	populate_env_list(info);
	read_history(info);
	hsh(info, vector);
	return (EXIT_SUCCESS);
}
