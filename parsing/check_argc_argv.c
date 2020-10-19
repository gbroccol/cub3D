/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:31:27 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:31:28 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			check_extention(char *str)
{
	int		len;

	len = ft_strlen(str);
	len--;
	if (str[len--] == 'b')
		if (str[len--] == 'u')
			if (str[len--] == 'c')
				if (str[len--] == '.')
					return (1);
	return (-1);
}

int			check_argc_argv(int argc, char **argv)
{
	if (argc < 2)
		write(1, "Error\nToo few arguments\n", 24);
	else if (argc > 3)
		write(1, "Error\nToo many arguments\n", 25);
	else if (check_extention(argv[1]) == -1)
		write(1, "Error\nWrong extention, not \".cub\"\n", 34);
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
			write(1, "Error\nWrong flag, not \"--save\"\n", 31);
		else
			return (0);
	}
	else
		return (0);
	exit(0);
	return (-1);
}
