/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 12:48:09 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minitrees.h"

void	execute(t_data *data, t_cmd *cmd, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;
	int		count;

	i = -1;
	data->status = 0;
	tab = ft_split(cmd->flags, ' ');
	while (tab[++i])
		tab[i] = invert(tab[i]);
	i = -1;
	cmd->cmd = invert(cmd->cmd);
	while (boolean && data->path && data->path[++i])
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

int	matching(char *match)
{
	int	i;

	if (!match)
		return (0);
	static const char *matchs[7] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"};
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(matchs[i++], match))
			return (1);
	}
	return (0);
}

void	forking(t_data *data, int index, int max, t_cmd *cmd)
{
	if (index != max - 1) // 0 1 2 3
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0) // 1 2 3 4
		dupnclose(data->prev_pipes, STDIN_FILENO);
	openfiles(cmd->redi, data, cmd, index);
	close(data->fd[1]);
	close(data->fd[0]);
	if (matching(cmd->cmd))
	{
		ft_builtin(cmd, data);
		exit(1);
	}
	else if (cmd->cmd)
		execute(data, cmd, !(ft_strchr(cmd->cmd, '/')));
}

void	flags_wild(t_cmd *cmd, char *tab)
{
	char	*wild;

	wild = 0;
	cmd->flags = ft_realloc(cmd->flags, " ");
	if (ft_strchr(tab, '*'))
	{
		wild = ft_wildcard(tab);
		cmd->flags = ft_realloc(cmd->flags, wild);
		ft_free((void **)&wild);
	}
	else
		cmd->flags = ft_realloc(cmd->flags, tab);
}

char	*checkstring(t_cmd *cmd, char *str)
{
	int		i;
	int		count;
	char	**tab;

	tab = ft_split(str, ' ');
	cmd->flags = 0;
	cmd->redi = 0;
	count = 0;
	i = -1;
	while (tab[++i])
	{
		if (!isaredirection(tab[i]) && !count)
		{
			count++;
			cmd->cmd = ft_strdup(tab[i]);
			cmd->flags = ft_realloc(cmd->flags, tab[i]);
		}
		else if (!isaredirection(tab[i]))
			flags_wild(cmd, tab[i]);
		else
			i += ft_lstadd_back_rr(&cmd->redi, ft_lstnewrr(ft_strdup(tab[i
							+ 1]), isaredirection(tab[i])));
	}
	ft_freetab(tab);
	return (NULL);
}

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	int	copyfd;

	if (!matching(cmd->cmd))
		return (0);
	copyfd = dup(STDOUT_FILENO);
	if (openfiles_bt(cmd->redi, data, cmd, 0))
	{
		dup2(copyfd, STDOUT_FILENO);
		close(copyfd);
		return (1);
	}
	ft_builtin(cmd, data);
	dup2(copyfd, STDOUT_FILENO);
	free_all(2, 1, &cmd->flags, &cmd->cmd, data->split);
	ft_freerr(cmd->redi);
	close(data->fd[0]);
	close(data->fd[1]);
	close(copyfd);
	return (1);
}

void	printstruct(t_cmd *cmd, void *str, t_data *data, int index)
{
	ft_printf("\t %rnode%0 : [%s] (%g%i%0 cmds)\n", str, data->nbcmd);
	ft_printf("\t\t %bstruct of part%0 : [%s]\n", data->split[index]);
	ft_printf("COMMAND NAME={%m%s%0}\n", cmd->cmd);
	ft_printf("COMMAND FLAGS={%m%s%0}\n", cmd->flags);
	ft_printf("COMMAND REDI\n");
	ft_printlist(cmd->redi);
	// ft_printf("COMMAND HD_DELIM\n");
	// ft_printtab(data->here->here_docs);
	// ft_printf("COMMAND HD_FILENAME\n");
	// ft_printtab(data->here->filename);
}

int	exec_command(t_btree *tree, t_btree *head)
{
	int			i;
	char		**tab;
	t_cmd		cmd;
	char		*temp;
	int			status;

	temp = ft_expand(tree->node, tree->data->env);
	ft_bzero(&cmd, sizeof(t_cmd));
	tree->data->split = ft_split(temp, '|');
	tree->data->nbcmd = ft_countdelim(temp, '|');
	free(temp);
	i = -1;
	while (++i < tree->data->nbcmd) // < tree->data->nbcmd)
	{
		tree->data->split[i] = ft_spacestr(tree->data->split[i]);
		checkstring(&cmd, tree->data->split[i]);
		printstruct(& cmd, tree->node, tree->data, i);
		pipe(tree->data->fd);
		if (tree->data->nbcmd == 1 && exec_builtin(&cmd, tree->data))
			return (0);
		signal(SIGINT, SIG_IGN);
		tree->data->pid[i] = fork();
		if (tree->data->pid[i] == 0)
		{
			signal(SIGINT, &ctrlc);
			signal(SIGQUIT, &antislash);
			forking(tree->data, i, tree->data->nbcmd, &cmd);
			ft_errorcmd(tree->data, &cmd, cmd.redi, "");
			freestruct(tree->data);
			status = tree->data->status;
			free_tree(head);
			exit(status);
		}
		else
		{
			close(tree->data->fd[1]);
			if (tree->data->prev_pipes != -1)
				close(tree->data->prev_pipes);
			tree->data->prev_pipes = tree->data->fd[0];
			free_all(2, 0, &cmd.cmd, &cmd.flags);
			ft_freerr(cmd.redi);
			signal(SIGQUIT, SIG_IGN);
		}
	}
	free_all(1, 1, &cmd.flags, tree->data->split);
	close(tree->data->fd[0]);
	exec_waitpid(tree->data);
	signal(SIGINT, &ctrlc);
	return (0);
}

int	exec_tree(t_btree *tree, t_btree *head)
{
	tree->data->prev_pipes = -1;
	if (!ft_strcmp((char *)tree->node, "||"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, head);
		if (tree->data->status)
			return (exec_tree(tree->r, head));
		return (0);
	}
	else if (!ft_strcmp((char *)tree->node, "&&"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, head);
		if (!tree->data->status)
			return (exec_tree(tree->r, head));
		return (1);
	}
	return (exec_command(tree, head));
}
