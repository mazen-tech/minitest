/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:52:47 by joaoalme          #+#    #+#             */
/*   Updated: 2023/06/28 22:16:50 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*process_token_two(char *s, t_attr *att)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	if (!token)
		return (NULL);
	token[0] = s[att->tai];
	token[1] = '\0';
	return (token);
}

char	*process_token_three(char *s, t_attr *att)
{
	char	*token;

	token = malloc(sizeof(char) * 3);
	if (!token)
		return (NULL);
	token[0] = s[att->tai];
	token[1] = s[att->tai + 1];
	token[2] = '\0';
	return (token);
}

char	*process_default(char *s, t_attr *att)
{
	char	*token;
	int		i;

	i = 0;
	token = malloc(sizeof(char) * (att->tai + 1));
	if (!token)
		return (NULL);
	token[att->tai] = '\0';
	while (i < att->tai)
	{
		token[i] = s[i];
		i++;
	}
	return (token);
}

void	reinit_toki(t_toki *tok)
{
	tok->j = 0;
	tok->i = 0;
	tok->pos = 0;
	tok->token = NULL;
	tok->flag = 0;
}

char	*process_special_char(char *s, t_attr *att)
{
	if (s[att->tai] == '|' && s[att->tai + 1] != '|'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_two(s, att));
	else if (s[att->tai] == '|' && s[att->tai + 1] == '|'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_three(s, att));
	else if (s[att->tai] == '>' && s[att->tai + 1] != '>'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_two(s, att));
	else if (s[att->tai] == '>' && s[att->tai + 1] == '>'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_three(s, att));
	else if (s[att->tai] == '<' && s[att->tai + 1] != '<'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_two(s, att));
	else if (s[att->tai] == '<' && s[att->tai + 1] == '<'
		&& att->oq % 2 == 0 && att->odq % 2 == 0)
		return (process_token_three(s, att));
	return (NULL);
}
