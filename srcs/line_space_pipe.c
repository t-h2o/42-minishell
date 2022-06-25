#include "minishell.h"
#include <string.h>

char	*trim_space(char *line)
{
	int	i;
	int	pos;
	char	*str;

	pos = strchr(line, '|') - line;
	if (pos < 0)
		return line;
	str = malloc(strlen(line) + 3);
	for (i = 0; i != pos; ++i)
		str[i] = line[i];
	str[i++] = ' ';
	str[i++] = '|';
	str[i] = ' ';
	++pos;
	for ( ; line[pos]; ++pos)
		str[++i] = line[pos];
	str[i + 1] = 0;
	line = str;
	return (line);
}
