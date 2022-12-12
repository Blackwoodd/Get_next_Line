/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:02:57 by nbechon           #+#    #+#             */
/*   Updated: 2022/12/12 10:48:02 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readline(char *str, int *found, int fd);
static char	*ft_newline(char *str, int *found);

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;
	char		*s1;
	char		*s2;
	int			i;

	i = 0;
	if (BUFFER_SIZE > 0)
	{
		save[BUFFER_SIZE] = '\0';
		line = ft_newline(save, &i);
		while (i == 0)
		{
			s1 = ft_readline(save, &i, fd);
			s2 = ft_strjoin(line, s1);
			free(line);
			line = ft_strdup(s2, 1);
			free(s1);
		}
		if (line && !line[0])
			return (free(line), NULL);
		return (line);
	}
	return (NULL);
}

static char	*ft_readline(char *save, int *found, int fd)
{
	char	*bu;
	int		i;

	bu = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bu)
		return (NULL);
	i = read(fd, bu, BUFFER_SIZE);
	if (i > -1)
	{
		bu[i] = '\0';
		i = 0;
		while (bu[i] && bu[i] != '\n')
			i++;
		*found = ((!bu[0]) || (!bu[i] && i < BUFFER_SIZE) || (bu[i] == '\n'));
		if (bu[i] == '\n')
		{
			ft_strlcpy(save, bu, BUFFER_SIZE + 1);
			bu[i + 1] = '\0';
		}
		ft_str_clean(save);
		return (bu);
	}
	free(bu);
	*found = 1;
	return (NULL);
}

static char	*ft_newline(char *save, int *found)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		*found = 1;
	i += *found;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = save[i];
	ft_str_clean(save);
	return (line);
}
