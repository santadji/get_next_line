#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s != NULL && s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*select_line(char *str)
{
	int	i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc((sizeof(char)) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*stock_line(char *str)
{
	int	i;
	int	j;
	char	*stock;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	stock = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!stock)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		stock[j++] = str[i++];
	stock[j] = '\0';
	free(str);
	return (stock);
}

char	*get_line(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes != 0 && !ft_strchr(str, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = get_line(fd, str);
	if (!str)
		return (NULL);
	line = select_line(str);
	str = stock_line(str);
	if (line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/*
char    *get_next_line(int fd)
{
	char *line = NULL;
    static char *str = NULL;
    int		read_bytes;
    char	buffer[BUFFER_SIZE + 1];
//    char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    read_bytes = 1;
	//line = NULL;
//	str = "";
//    if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
  //      return (NULL);
    while (read_bytes > 0 && !ft_strchr(str, '\n'))
    {
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		buffer[read_bytes] = 0;
		//tmp = str;
		str = ft_strjoin(str, buffer);
		//free(tmp);
		if (ft_strchr(str, '\n'))
			break;
    }
	if (!str)
		return (NULL);
//	printf("str %s\n", str);
    line = select_line(str);
 //   tmp = str;
	printf("line = %s\n", line);
    str = stock_line(str);
//    free(tmp);
//    if (line[0] == '\0')
//        return (NULL);
    return (line);   
}

int main()
{
    int fd = open("test.txt", O_RDONLY);


    char *s;
    // s = get_next_line(fd);
    // printf("[%s]", s);
    // s = get_next_line(fd);
    // printf("[%s]", s);
    // s = get_next_line(fd);
    // printf("[%s]", s);

    s = get_next_line(fd);
    printf("[%s]\n", s);
    free(s);
    while (s)
    {
        s = get_next_line(fd);
        printf("[%s]\n", s);    
        free(s);
    }
	printf("gnl ok\n");
    close(fd);
}

int	main()
{
	char	*line;
	int		fd;

	printf("avant open fichier\n");
	fd = open("test.txt", O_RDONLY);
	printf("fichier open %d\n", BUFFER_SIZE);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
	return (fd);
}*/
