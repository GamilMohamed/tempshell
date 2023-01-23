/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/23 01:17:13 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minitrees.h"

static char	*ft_whichchar(char *tab, int r, char quote)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (r + 1)); // check malloc
	j = -1;
	i = 0;
	while (tab[++j])
	{
		if (tab[j] != quote)
			new[i++] = tab[j];
	}
	new[i] = 0;
	return (new);
}

static char	**ft_stripchar(char **tab, int count)
{
	char	**new;
	char	quote;
	int		i;
	int		j;
	int		r;

	new = malloc(sizeof(char *) * (count + 1)); // check malloc
	i = -1;
	while (tab[++i])
	{
		r = 0;
		j = -1;
		quote = 0;
		while (tab[i][++j])
		{
			if (ft_checkchars(tab[i][j], SPACE, SQUOTE, DQUOTE) > 1 && !quote)
				quote = tab[i][j];
			if (tab[i][j] != quote)
				r++;
		}
		new[i] = ft_whichchar(tab[i], r, quote); // check malloc
	}
	ft_freetab(tab);
	new[i] = 0;
	return (new);
}

void	execute(t_data *data, t_cmd *cmd, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;
	int		count;

	i = -1;
	data->status = 0;
	tab = ft_split(cmd->flags, ' ');
	count = ft_countdelim(cmd->flags, ' ');
	tab = ft_stripchar(tab, count);
	while (tab[++i])
		tab[i] = invert(tab[i]);
	i = -1;
	cmd->cmd = invert(cmd->cmd);
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

void	forking(t_data *data, int index, int max, t_cmd *cmd)
{
	if (index != max - 1) // 0 1 2 3
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0) // 1 2 3 4
		dupnclose(data->prev_pipes, STDIN_FILENO);
	openfiles(cmd->redi, data, cmd, index);
	close(data->fd[1]);
	close(data->fd[0]);
	if (cmd->cmd)
		execute(data, cmd, !(ft_strchr(cmd->cmd, '/')));
}

void	flags_wild(t_cmd *cmd, char *tab)
{
	char	*wild;

	wild = 0;
	cmd -> flags = ft_realloc(cmd->flags, " ");
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
			i += ft_lstadd_back_rr(&cmd->redi, ft_lstnewrr(ft_strdup(tab[i + 1]), isaredirection(tab[i])));
	}
	// ft_printlist(cmd->redi);
	ft_freetab(tab);
	return (NULL);
}

int	matching(char *match)
{
	int	i;

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

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	int	copyfd;

	if (!cmd->cmd || !matching(cmd->cmd))
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
	free_all(2, 1, & cmd->flags, & cmd->cmd, data->split);
	ft_freerr(cmd->redi);
	close(data->fd[0]);
	close(data->fd[1]);
	close(copyfd);
	return (1);
}

int	exec_command(t_btree *tree)
{
	int			i;
	char		**tab;
	t_cmd		cmd;
	char		*temp;
	int			status;
	static int	var;

	var = 0;
	ft_bzero(&cmd, sizeof(t_cmd));
	tree->data->split = ft_split(tree->node, '|');
	tree->data->nbcmd = ft_countdelim(tree->node, '|');
	i = -1;
	while (++i < tree->data->nbcmd) // < tree->data->nbcmd)
	{
		tree->data->split[i] = ft_spacestr(tree->data->split[i]);
		checkstring(&cmd, tree->data->split[i]);
		printf("[%s]\n", cmd.cmd);
		ft_printtab(tree->data->filename);
		ft_printf("stop\n");
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
			exit(tree->data->status);
		}
		else
		{
			close(tree->data->fd[1]);
			if (tree->data->prev_pipes != -1)
				close(tree->data->prev_pipes);
			tree->data->prev_pipes = tree->data->fd[0];
			free_all(2, 0, & cmd.cmd, & cmd.flags);
			ft_freerr(cmd.redi);
			signal(SIGQUIT, SIG_IGN);
		}
	}
	free_all(1, 1, & cmd.flags, tree->data->split);
	close(tree->data->fd[0]);
	exec_waitpid(tree->data);
	signal(SIGINT, &ctrlc);
	return (0);
}

int	exec_tree(t_btree *tree)
{
	tree->data->prev_pipes = -1;
	if (!ft_strcmp((char *)tree->node, "||"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l);
		if (tree->data->status)
			return (exec_tree(tree->r));
		return (0);
	}
	else if (!ft_strcmp((char *)tree->node, "&&"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l);
		if (!tree->data->status)
			return (exec_tree(tree->r));
		return (1);
	}
	return (exec_command(tree));
}
