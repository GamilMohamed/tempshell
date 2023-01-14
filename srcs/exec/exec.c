/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/14 14:41:56 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minitrees.h"

void	execute(t_data *data, t_cmd *cmd, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	data->status = 0;
	tab = ft_split(cmd->flags, ' ');
	if (!data->env[0])
		ft_printf("%s: command not found\n", cmd->cmd);
	while (boolean && data->path[++i])
	{
		temp = ft_slash(data->path[i], cmd->cmd);
		if (access(temp, F_OK | X_OK) != -1)
			execve(temp, tab, data->env);
		free(temp);
	}
	if (!boolean)
		if (access(cmd->cmd, F_OK | X_OK) == 0)
			execve(cmd->cmd, tab, data->env);
	if (boolean)
		ft_printf("%s: command not found\n", cmd->cmd);
	else if (errno == 13)
		ft_printf("bash: %s: Permission denied\n", cmd->cmd);
	else
		ft_printf("bash: %s: No such file or directory\n", cmd->cmd);
	data->status = 127;
	ft_freetab(tab);
}

void	openfiles(t_rr *node)
{
	int	fd;

	while (node)
	{
		if (node->type == 1) // >
			fd = open(node->content, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		if (node->type == 2) // >>
			fd = open(node->content, O_APPEND | O_WRONLY | O_CREAT, 0666);
		if (node->type == 3) // <
		{
			fd = open(node->content, O_RDONLY);
			dupnclose(fd, STDIN_FILENO);
		}
		else
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
	}
}

void	forking(t_data *data, int index, int max, t_cmd *cmd)
{
	// openfiles(cmd->redi);
	if (index != max - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0)
		dupnclose(data->prev_pipes, STDIN_FILENO);
	close(data->fd[1]);
	close(data->fd[0]);
}

char	*checkstring(t_cmd *cmd, char *str)
{
	int		i;
	int		count;
	char	*flags;
	char	**tab;
	t_rr	*tmp;

	tab = ft_splitex(str);
	tmp = cmd->redi;
	cmd->flags = ft_calloc(1, 1);
	count = 0;
	i = -1;
	while (tab[++i])
	{
		if (!isaredirection(tab[i]) && !count)
		{
			ft_printf("%g%s%0 ", tab[i], count++); // COMMAND
			cmd->cmd = ft_strdup(tab[i]);
			cmd->flags = ft_strjoin_gnl(cmd->flags, tab[i]);
		}
		else if (!isaredirection(tab[i]))
		{
			ft_printf("%y%s%0 ", tab[i]); // FLAG
			cmd->flags = ft_strjoin_gnl(cmd->flags, " ");
			if (ft_strchr(tab[i], '*'))
				cmd->flags = ft_strjoin_gnl(cmd->flags, ft_wildcard(tab[i]));
			else
				cmd->flags = ft_strjoin_gnl(cmd->flags, tab[i]);
		}
		else
		{
			ft_printf("%b%s%0 %b%s%0 ", tab[i], tab[i + 1]); // REDIRECTION
			ft_lstadd_back_rr(&cmd->redi, ft_lstnewrr(ft_strdup(tab[i + 1]),
						isaredirection(tab[i])));
			i++;
		}
	}
	ft_freetab(tab);
	ft_printf("\n");
	// ft_printf("{%s}\n", cmd->flags);
	// ft_printlist(cmd->redi);
	return (NULL);
}

int	exec_command(t_btree *tree, int infile, int outfile, char **ev)
{
	int		i;
	char	**tab;
	int		nbcmd;
	t_cmd	*cmd;
	int		status;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	// printf("[%s]\n", (char *)tree->node);
	tab = ft_split(tree->node, '|');
	nbcmd = ft_countdelim(tree->node, '|');
	i = -1;
	while (++i < nbcmd) // < nbcmd)
	{
		checkstring(cmd, tab[i]);
		pipe(tree->data->fd);
		tree->data->pid[i] = fork();
		if (tree->data->pid[i] == 0)
		{
			forking(tree->data, i, nbcmd, cmd);
			execute(tree->data, cmd, !(ft_strchr(cmd->flags, '/')));
			// ft_free((void **)& cmd->flags);
			ft_free((void **)& cmd->cmd);
			ft_free((void **)& cmd);
			ft_freetab(tree->data->path);
			ft_freetab(tab);
			exit(tree->data->status);
		}
		else
		{
			// printf("%i|%i|%i\n", tree->data->fd[0], tree->data->fd[1], tree->data->prev_pipes);
			close(tree->data->fd[1]);
			if (tree->data->prev_pipes != -1)
				close(tree->data->prev_pipes);
			tree->data->prev_pipes = tree->data->fd[0];
		}
		// free(cmd->flags);
		// free(cmd->cmd);
	}
	// free(cmd);
	i = -1;
	while (++i < nbcmd)
		waitpid(tree->data->pid[i], &status, 0);
	if (WIFEXITED(status))
		tree->data->status = WIFEXITED(status);
	ft_freetab(tab);
	return (0);
}

int	exec_tree(t_btree *tree, int infile, int outfile, char **ev)
{
	if (!ft_strcmp((char *)tree->node, "||"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, infile, outfile, NULL);
		// ft_printf("status=%i\n", tree->data->status);
			if (!tree->data->status)
				return (exec_tree(tree->r, infile, outfile, NULL));
		return (0);
	}
	else if (!ft_strcmp((char *)tree->node, "&&"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, infile, outfile, NULL);
		// ft_printf("status=%i\n", tree->data->status);
			if (tree->data->status)
				return (exec_tree(tree->r, infile, outfile, NULL));
		return (1);
	}
	return (exec_command(tree, infile, outfile, NULL));
}
