/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftataje- <ftataje-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:46:41 by ftataje-          #+#    #+#             */
/*   Updated: 2022/05/24 13:36:33 by ftataje-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_cut_line(char *save)
{
	int		x;
	char	*str;

	x = 0;
	if (!save[x])
		return (0);
	while (save[x] && save[x] != '\n')
		x++;
	str = (char *)malloc(sizeof (char) * (x + 2));
	if (!str)
		return (0);
	x = 0;
	while (save[x] && save[x] != '\n')
	{
		str[x] = save[x];
		x++;
	}
	if (save[x] == '\n')
	{
		str[x] = save [x];
		x++;
	}
	str[x] = '\0';
	return (str);
}

char	*ft_cut_save(char *save)
{
	int		y;
	int		n;
	char	*str;

	y = 0;
	while (save[y] && save[y] != '\n')
		y++;
	if (!save[y])
	{
		free(save);
		return (0);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(save) - y + 1));
	if (!str)
		return (0);
	y++;
	n = 0;
	while (save[y])
		str[n++] = save[y++];
	str[n] = '\0';
	free(save);
	return (str);
}

char	*ft_read(int fd, char *save)
{
	char	*buffer;
	int		z;

	buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	z = 1;
	while (z != 0 && (!ft_strchr(save, '\n')))
	{
		z = read(fd, buffer, BUFFER_SIZE);
		if (z == -1)
		{
			free (buffer);
			return (0);
		}
		buffer[z] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*save[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX -1)
	{
		return (0);
	}
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
	{
		return (0);
	}
	line = ft_cut_line(save[fd]);
	save[fd] = ft_cut_save(save[fd]);
	return (line);
}

/*int	main(void)
{
	int	file;
	int	file2;

	file = open("test.txt", O_RDWR);
	file2 = open("test2.txt", O_RDWR);
	printf("file: %s\n", get_next_line(file));
	printf("file: %s\n", get_next_line(file2));
	printf("file: %s\n", get_next_line(file));
	printf("file: %s\n", get_next_line(file2));
	printf("file: %s\n", get_next_line(file));
	printf("file: %s\n", get_next_line(file2));
}*/
