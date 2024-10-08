/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:28:13 by lde-sous          #+#    #+#             */
/*   Updated: 2023/06/29 14:20:30 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZE_H
# define SANITIZE_H

# include "minishell.h"

// free_one.c
void	free_arr(char **arr);
void	free_tokens(char **tokens, t_attr *att);
void	free_g_env(t_attr *att);
void	free_d_env(t_attr *att);
void	free_exp_env(t_attr *att);

// free_two.c
void	free_d_exp_env(t_attr *att);
void	exit_free(t_attr *att);
void	ft_delete_matrix(void *matrix);
void	free_start_args(t_exec *args, t_attr *att);
void	free_child(t_attr *att, t_exec *args);

#endif