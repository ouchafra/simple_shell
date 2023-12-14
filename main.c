/**
 * main - Entry point for the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on general error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;  // Defaulting to stderr

	// Adjusting file descriptor using inline assembly
	asm (
			"mov %1, %0\n\t"
			"add $FD_OFFSET, %0"  // Use a named constant or explain the purpose
			: "=r" (fd)
			: "r" (fd)
	    );

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);  // Permission issue
			if (errno == ENOENT)
			{
				// File not found error message
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				perror("");  // Print specific error message
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);  // File not found
			}
			return (EXIT_FAILURE);  // General error
		}
		info->readfd = fd;
	}

	// Populate environment list and read history
	populate_env_list(info);
	read_history(info);

	// Call your shell function (replace hsh with the actual function name)
	hsh(info, av);

	return (EXIT_SUCCESS);
}
