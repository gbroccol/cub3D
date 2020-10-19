/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_notify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:31:42 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:31:44 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		errors_notify2(int code)
{
	if (code == 12)
		write(1, "Error\nThere is no map\n", 22);
	else if (code == 13)
		write(1, "Error\nThere is no ceiling's color\n", 34);
	else if (code == 14)
		write(1, "Error\nThere is no floor's color\n", 32);
	return (-1);
}

int		errors_notify(int code)
{
	if (code == 0)
		write(1, "Error\nWrong symb on the map\n", 28);
	else if (code == 1)
		write(1, "Error\nNo such file or directory\n", 32);
	else if (code == 2)
		write(1, "Error\nWrong legend\n", 19);
	else if (code == 3)
		write(1, "Error\nIncorrect giving of data\n", 31);
	else if (code == 4)
		write(1, "Error\nExtra wall or sprite\n", 27);
	else if (code == 5)
		write(1, "Error\nThere is no necessary wall or sprite\n", 43);
	else if (code == 6)
		write(1, "Error\nExtra data after map\n", 27);
	else if (code == 7)
		write(1, "Error\nNo such texture\n", 22);
	else if (code == 8)
		write(1, "Error\nStart position error\n", 27);
	else if (code == 9)
		write(1, "Error\nWrong map\n", 16);
	else if (code == 10)
		write(1, "Error\nWrong size of window\n", 27);
	else if (code == 11)
		write(1, "Error\nUnnecessary smbol(-s)\n", 28);
	return (-1);
}
