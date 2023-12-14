#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return 0;

	return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
}

/**
 * dup_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to new buffer (caller responsible for freeing).
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf = malloc(stop - start + 1);
	if (buf)
	{
		int i, k = 0;
		for (i = start; i < stop; i++)
		{
			if (pathstr[i] != ':')
				buf[k++] = pathstr[i];
		}
		buf[k] = '\0';
	}
	return buf;
}

/**
 * find_path - Finds this cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL (caller responsible for freeing).
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path = NULL;

	if (!pathstr)
		return NULL;

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return _strdup(cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			char *dir = dup_chars(pathstr, curr_pos, i);
			if (dir)
			{
				path = malloc(_strlen(dir) + _strlen(cmd) + 2);
				if (path)
				{
					_strcpy(path, dir);
					_strcat(path, "/");
					_strcat(path, cmd);
					if (is_cmd(info, path))
					{
						free(dir);
						return path;
					}
					free(path);
				}
				free(dir);
			}

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}

	return NULL;
}
