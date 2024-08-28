/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:15:45 by lde-sous          #+#    #+#             */
/*   Updated: 2023/06/29 14:35:58 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
int check_quotes_and_space(char *s, t_attr *att, int quotes, int quote_type)
{
    
    if (quote_type == 1 && att->oq == quotes && s[att->tai + 1] == ' ')
    {
        return 0; 
    }
    else if (quote_type == 2 && att->odq == quotes && s[att->tai + 1] == ' ')
    {
        return 0;
    }
    return 0; 
}
*/


void check_qouts_slash(char *s, t_attr *att, int *quotes, int *flag)
{
	if (s[att->tai] == '"' && (*flag == 0 || *flag == 2))
	{
		att->inside_single_quotes = 0;
		*flag = 2;
		(*quotes)++;	
	}
	else if (s[att->tai] == '\'' && (*flag == 0 || *flag == 1))
	{
		att->inside_single_quotes = 1;
		*flag = 1;
		(*quotes)++;
	}
}


char *minimize(char *s, t_attr *att, int *quotes, int *flag)
{
	while (s[att->tai])
	{
		check_qouts_slash(s, att, quotes, flag);	
		if (s[att->tai] == ' ' && *quotes % 2 == 0)
			break ;
		else if ( (s[att->tai] == '|' && s[att->tai + 1] != '|' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '>' && s[att->tai + 1] != '>' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '<' && s[att->tai + 1] != '<' && att->oq % 2 == 0 && att->odq % 2 == 0))
			return (process_token_two(s, att));//two
		else if ((s[att->tai] == '|' && s[att->tai + 1] == '|' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '>' && s[att->tai + 1] == '>' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '<' && s[att->tai + 1] == '<' && att->oq % 2 == 0 && att->odq % 2 == 0))
			return (process_token_three(s, att));
		att->tai++;
	}
	return (NULL);
}

char	*get_token(char *s, t_attr *att, t_toki tok)
{
	int	flag;
	int	quotes;

	flag = 0;
	quotes = 0;
	att->tai = 0;
	minimize(s, att, &quotes, &flag);
	/*while (s[att->tai])
	{
		check_qouts_slash(s, att, &quotes, &flag);	
		if (s[att->tai] == ' ' && quotes % 2 == 0)
			break ;
		else if ( (s[att->tai] == '|' && s[att->tai + 1] != '|' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '>' && s[att->tai + 1] != '>' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '<' && s[att->tai + 1] != '<' && att->oq % 2 == 0 && att->odq % 2 == 0))
			return (process_token_two(s, att));//two
		else if ((s[att->tai] == '|' && s[att->tai + 1] == '|' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '>' && s[att->tai + 1] == '>' && att->oq % 2 == 0 && att->odq % 2 == 0)
		|| (s[att->tai] == '<' && s[att->tai + 1] == '<' && att->oq % 2 == 0 && att->odq % 2 == 0))
			return (process_token_three(s, att));
		att->tai++;
	}*/
	if (quotes >= 2)
		return (process_multi_quote(s, att, &tok));
	else
		return (process_default(s, att));
}

char	*quotentoken(char *s, t_attr *att, t_toki *tok)
{
	tok->token = malloc(sizeof(char) * (tok->pos + 1));
	tok->token[tok->pos] = 0;
	tok->i = 0;
	tok->j = 0;
	while (tok->j < tok->pos && s[tok->i] != '\0')
	{
		if (tok->flag == 1)
			tok->token = process_single_quotes(s, att, tok);
		else if (tok->flag == 2)
			tok->token = process_double_quotes(s, att, tok);
		tok->i++;
	}
	return (tok->token);
}
