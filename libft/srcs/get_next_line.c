/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:47:05 by rrichard          #+#    #+#             */
/*   Updated: 2024/06/18 14:50:29 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_isfull(char **static_storage)
{
	char	*newline_position;
	char	*line;
	char	*new_storage;
	char	*tmp;

	if (!*static_storage)
		return (NULL);
	line = NULL;
	newline_position = ft_strchr(*static_storage, '\n');
	if (newline_position != NULL)
	{
		*newline_position = '\0';
		tmp = ft_strdup(*static_storage);
		if (!tmp)
			return (NULL);
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		new_storage = ft_strdup(newline_position + 1);
		free(*static_storage);
		*static_storage = new_storage;
	}
	return (line);
}

char	*process_line(char *buffer, char **static_storage,
						char *newline_position)
{
	char	*line;
	char	*tmp;

	line = NULL;
	*newline_position = '\0';
	tmp = ft_strdup(newline_position + 1);
	if (!tmp)
		return (NULL);
	line = create_line(line, static_storage, buffer);
	if (*tmp != '\0')
		*static_storage = tmp;
	else
	{
		free(tmp);
		*static_storage = NULL;
	}
	return (line);
}

char	*process_buffer(char *buffer, char **static_storage)
{
	char	*newline_position;
	char	*line;
	char	*tmp;

	newline_position = ft_strchr(buffer, '\n');
	line = NULL;
	if (newline_position != NULL)
		line = process_line(buffer, static_storage, newline_position);
	else if (newline_position == NULL && *static_storage == NULL)
		*static_storage = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(*static_storage, buffer);
		free(*static_storage);
		*static_storage = tmp;
	}
	return (line);
}

char	*clear_storage(char **static_storage, char *line, ssize_t bytes_read)
{
	if (bytes_read == 0 && *static_storage)
	{
		if (**static_storage == '\0')
		{
			free(*static_storage);
			*static_storage = NULL;
			return (NULL);
		}
		else
		{
			line = ft_strdup(*static_storage);
			free(*static_storage);
			*static_storage = NULL;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;
	static char	*static_storage = NULL;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_isfull(&static_storage);
	if (line)
	{
		free(buffer);
		return (line);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		line = process_buffer(buffer, &static_storage);
		if (line)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (clear_storage(&static_storage, line, bytes_read));
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	size_t	i = 1;

// 	if (argc == 2)
// 	{
// 		fd = STDIN_FILENO;
// 		line = get_next_line(fd);
// 		while (line)
// 		{
// 			if (ft_strncmp(argv[1], line, ft_strlen(argv[1])) == 0)
// 			{
// 				free(line);
// 				return (0);
// 			}
// 			printf("line [%02zu]: %s", i++, line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		free(line);
// 		close(fd);
// 	}
// 	return (0);
// }
