/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:42:11 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/11 14:58:52 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_the_line(char *str)
{
	size_t	strt;
	size_t	end;
	char	*s;

	strt = 0;
	end = 0;
	while (str[strt] != '\0' && str[strt] != '\n')
		strt++;
	strt++;
	while (str[end] != '\0')
		end++;
	if (strt >= end)
	{
		free(str);
		return (NULL);
	}
	s = malloc(((end - strt) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str + strt, (end - strt) + 1);
	free(str);
	return (s);
}

char	*draw_the_line(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (1)
	{
		if (str[i] == '\0')
			break ;
		else if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	s = malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[i] = '\0';
	while (i-- > 0)
		s[i] = str[i];
	return (s);
}

char	*set_the_buff(int fd, char *u_buff)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(u_buff, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		u_buff = ft_strjoin(u_buff, buff);
	}
	free(buff);
	return (u_buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*u_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	u_buff = set_the_buff(fd, u_buff);
	if (!u_buff)
		return (NULL);
	line = draw_the_line(u_buff);
	u_buff = extract_the_line(u_buff);
	if (!line)
		return (NULL);
	return (line);
}
