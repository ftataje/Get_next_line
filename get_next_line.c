/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftataje- <ftataje-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:35:41 by ftataje-          #+#    #+#             */
/*   Updated: 2022/05/24 13:23:46 by ftataje-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*save;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (0);
	}
	save = ft_read(fd, save);
	if (!save)
	{
		return (0);
	}
	line = ft_cut_line(save);
	save = ft_cut_save(save);
	return (line);
}

/*int	main(void)
{
	int	file;

	file = open("test.txt", O_RDWR);
	printf("file: %d\n", get_next_line(file));
	printf("file: %d\n", get_next_line(file));
	printf("file: %d\n", get_next_line(file));
}*/
