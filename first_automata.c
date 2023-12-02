/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first-automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:43:14 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/01 19:43:18 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//------------------------------------

/*
* set (array) of all states
* 1st -> initial state
* all error states at the beginning, so we can set that 
*		error < #finalstate
* final(s) state at the end of the array
* 
* this automata will only accept strings that:
* 	have leading/trailing spaces
* 	have sequence of numbers with '0' & '1'
*	those sequences always start/end with '1'
*/
size_t	t_states[][4] =
{
	//\s 1 0  ^	// dict {' ', '1', '0'}
	{0, 3, 2, 1},	// 0 INIT
	{1, 1, 1, 1},	// 1 ERROR
	{0, 3, 2, 1},	// 2 '0' found
	{0, 3, 2, 1}	// 3 '1' found
}; //transition states array

size_t f_states[] = {0, 3}; //final states array

//-----------------------------------------

int		check_fstates(size_t state)
{
	//hardcoded '2', we know there are only 2 final states {0,3}
	for (int i = 0; i < 2; i++)
	{
		if (f_states[i] == state)
			return (1);
	}
	return (0);
}
//initialize automata
char	*automata(char *c)
{
	char 		*dict = " 10"; //input symbols: {' ', '1', '0'}
	size_t 		len = strlen(c);
	size_t		state = 0; //INIT state

	for (int i = 0; i < len; i++)
	{
		if (strchr(dict, c[i]) != NULL)
		{
			//update state with actual state and char found
			if (c[i] == dict[0])
				state =  t_states[state][0];
			if (c[i] == dict[1])
				state = t_states[state][1];
			if (c[i] == dict[2])
				state = t_states[state][2];
		}
		else
		{
			state = t_states[state][3];
		}
	}
	return (check_fstates(state) == 1 ? "OK" : "BAD INPUT");
}

int	main(int argc, char **argv)
{
	char	*aut;

	if (argc == 2)
	{
		aut = automata(argv[1]);
		printf("%s\n", aut);
	}
	return (0);
}
