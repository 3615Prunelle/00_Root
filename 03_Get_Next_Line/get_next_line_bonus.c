/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:21:43 by schappuy          #+#    #+#             */
/*   Updated: 2025/09/17 23:00:56 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer_array[1024];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer_array[fd], 0) < 0)
		return (free_null_three(&buffer_array[fd], NULL, NULL));
	if (!buffer_array[fd])
	{
		buffer_array[fd] = ft_calloc_copy(BUFFER_SIZE + 1, 1);
		if (!buffer_array[fd] || read(fd, buffer_array[fd], BUFFER_SIZE) <= 0)
			return (free_null_three(&buffer_array[fd], NULL, NULL));
	}
	temp = ft_calloc_copy(BUFFER_SIZE + 1, 1);
	if (!temp)
		return (free_null_three(&buffer_array[fd], NULL, NULL));
	line = ft_calloc_copy(BUFFER_SIZE + 1, 1);
	if (!line)
		return (free_null_three(&buffer_array[fd], NULL, &temp));
	read_line(fd, &buffer_array[fd], &line, &temp);
	if (!line)
		return (free_null_three(&buffer_array[fd], NULL, &temp));
	free(temp);
	return (line);
}

void	read_line(int fd, char **buffer, char **line, char **temp)
{
	int	len;

	while (*buffer)
	{
		if (ft_strchr_mod(*buffer, '\n'))
		{
			len = (ft_strchr_mod(*buffer, '\n') - *buffer);
			*temp = ft_strlcpy_copy(*temp, *buffer, len + 1);
			len = ft_strlen_copy(*buffer) - len;
			*buffer = ft_strlcpy_copy(*buffer, ft_strchr_mod(*buffer, '\n'), len + 1);
			*line = ft_strjoin_mod(*line, *temp);
			return ;
		}
		*line = ft_strjoin_mod(*line, *buffer);
		if (!*line)
			return ;
		ft_memset_copy(*buffer, 0, BUFFER_SIZE);
		if (read(fd, *buffer, BUFFER_SIZE) <= 0)
		{
			if (*line && *line[0] == '\0')
				free_null_three(buffer, line, temp);
			return ;
		}
	}
}

char	*free_null_three(char **buff, char **line, char **temp)
{
	if (buff && *buff)
	{
		free(*buff);
		*buff = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (temp && *temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (NULL);
}

void	*ft_memset_copy(void *str, int constante, size_t taille)
{
	unsigned char	*ptr_s;
	size_t			i;

	ptr_s = (unsigned char *)str;
	i = 0;
	while (i < taille)
	{
		ptr_s[i] = (unsigned char)constante;
		i++;
	}
	return (str);
}

#define ROUQUINETTE_DEBUG //pour lancer tester : comment out uniquement cette ligne au lieu de tout le reste en dessous
#ifdef ROUQUINETTE_DEBUG

void freedom_yolo(void **mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

int	main(void)
{
	int			amount_of_fd = 3;
	int			file_descriptor1;
	int			file_descriptor2;
	int			file_descriptor3;
	int			fd_array[amount_of_fd];
	int			fd_number;
	int			line_number;
	char		*grand_final[amount_of_fd];
	int			fd_finished[amount_of_fd];

	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_nl", O_RDONLY);
	 file_descriptor1 = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_42_char_no_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_42_char_with_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_multiple_line_no_nl", O_RDONLY);
	 file_descriptor2 = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_multiple_line_with_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_multiple_nlx5", O_RDONLY);
	 file_descriptor3 = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_alternate_line_nl_no_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_alternate_line_nl_with_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_big_line_no_nl", O_RDONLY);
	// file_descriptor = open ("/home/schappuy/00_Root/3_Get_Next_Line/TestFile_big_line_with_nl", O_RDONLY);
	// file_descriptor = open ("", O_RDONLY);

	fd_array[0] = file_descriptor1;
	fd_array[1] = file_descriptor2;
	fd_array[2] = file_descriptor3;

	for (int i = 0; i < amount_of_fd; i++)
	{
		grand_final[i] = NULL;
		fd_finished[i] = 0;
	}

	line_number = 1;
	int active_fds = amount_of_fd;

	while (active_fds > 0)
	{
		active_fds = 0;
		for (fd_number = 0; fd_number < amount_of_fd; fd_number++)
		{
			if (fd_finished[fd_number])
				continue;
			if (grand_final[fd_number])
				freedom_yolo((void **)&grand_final[fd_number]);
			grand_final[fd_number] = get_next_line(fd_array[fd_number]);
			if (grand_final[fd_number])
			{
				printf("\n| File : [%i] - Line : [%i] |	%s", fd_number + 1, line_number, grand_final[fd_number]);
				active_fds++;
			}
			else
			{
				fd_finished[fd_number] = 1;
			}
		}
		line_number++;
		printf("\n*****************");
	}
	for (int i = 0; i < amount_of_fd; i++)
	{
		if (grand_final[i])
			freedom_yolo((void **)&grand_final[i]);
		close(fd_array[i]);
	}
	return (0);
}

#endif
