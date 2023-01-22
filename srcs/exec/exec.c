/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 01:53:23 by mgamil           ###   ########.fr       */
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

void	ft_errorcmd_bt(t_data *data, t_cmd *cmd, t_rr *node, char *str)
{
	// ft_freepostexec(cmd, data);
	ft_free((void **)&cmd->flags);
	ft_free((void **)&cmd->cmd);
	// ft_freetab(data->path);
	// ft_freetab(data->here_docs);
	// ft_freetab(data->filename);
	ft_freetab(data->split);
	ft_freerr(node);
	close(data->fd[0]);
	close(data->fd[1]);
	// ft_free((void **)&cmd);

}

int	error_fd_bt(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	if (errno == 13 && node->type != 4)
		ft_printf("bash: %s: Permission denied\n", node->content);
	else if (errno == 13 && node->type == 4)
		ft_printf("bash: %s: Permission denied\n", data->filename[index]);
	else if (node->type != 4)
		ft_printf("bash: %s: No such file or directory\n", node->content);
	else
		ft_printf("bash: %s: No such file or directory\n",
				data->filename[index]);
	ft_errorcmd_bt(data, cmd, cmd->redi, "");
	return (1);
	// close(data->fd[1]);
	// close(data->fd[0]);
}


int	openfiles_bt(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	int		fd;
	t_rr	*head;

	head = node;
	while (node)
	{
		if (node->type == 1) // >
			fd = open(node->content, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 2) // >>
			fd = open(node->content, O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 3) // <
			fd = open(node->content, O_RDONLY);
		else if (node->type == 4) // <<
			fd = open(data->filename[index], O_RDONLY);
		if (fd == -1)
			if (error_fd_bt(node, data, cmd, index))
				return (1);
		if (node->type > 2)
			dupnclose(fd, STDIN_FILENO);
		else if (node->type < 3)	
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
		ft_printf("fd=%i\n", fd);
	}
	return (0);
}


void	openfiles(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	int		fd;
	t_rr	*head;

	head = node;
	while (node)
	{
		if (node->type == 1) // >
			fd = open(node->content, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 2) // >>
			fd = open(node->content, O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 3) // <
			fd = open(node->content, O_RDONLY);
		else if (node->type == 4) // <<
			fd = open(data->filename[index], O_RDONLY);
		if (fd == -1)
			error_fd(node, data, cmd, index);
		if (node->type > 2)
			dupnclose(fd, STDIN_FILENO);
		else if (node->type < 3)	
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
		ft_printf("fd=%i\n", fd);
	}
}

void	forking(t_data *data, int index, int max, t_cmd *cmd)
{
	// if (index == 0 && max == 1)
	// {
	// 	if (!ft_strncmp(cmd->cmd, "echo", 4))
	// 		;
	// 	else
	// 		ft_builtin(cmd->cmd, data->path, &data->path);
	// }
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

char	*checkstring(t_cmd *cmd, char *str)
{
	int		i;
	int		count;
	char	**tab;
	char	*wild;
	tab = ft_split(str, ' ');
	// ft_printtab(tab);
	cmd->redi = 0;
	cmd->flags = 0;
	count = 0;
	wild = 0;
	i = -1;
	while (tab[++i])
	{
		if (!isaredirection(tab[i]) && !count)
		{
			// ft_printf("%g%s%0 ", tab[i], count++); // COMMAND
			count++;
			cmd->cmd = ft_strdup(tab[i]);
			cmd->flags = ft_realloc(cmd->flags, tab[i]);
		} 
		else if (!isaredirection(tab[i]))
		{
			// ft_printf("%y%s%0 ", tab[i]); // FLAG
			cmd->flags = ft_realloc(cmd->flags, " ");
			if (ft_strchr(tab[i], '*'))
			{
				wild = ft_wildcard(tab[i]);
				cmd->flags = ft_realloc(cmd->flags, wild);
				ft_free((void **)& wild);
			}
			else
				cmd->flags = ft_realloc(cmd->flags, tab[i]);
		}
		else
			i += ft_lstadd_back_rr(&cmd->redi, ft_lstnewrr(ft_strdup(tab[i + 1]), isaredirection(tab[i])));
	}
	ft_printlist(cmd->redi);
	ft_freetab(tab);
	// ft_printf("{%s}\n", cmd->flags);
	return (NULL);
}

int    matching(char *match)
{
    static const char    *matchs[7] = {
        "cd", "echo", "exit", "export", "pwd", "unset", "env"
    };
    int                    i;

    i = 0;
	ft_printf("match=%s\n", match);
    while (i < 7)
    {
        if (!ft_strcmp(matchs[i++], match))
            return (1);
    }
    return (0);
}

int exec_builtin(t_cmd *cmd, t_data *data)
{
	int copyfd;
	if (!cmd->cmd || !matching(cmd->cmd))
		return (0);
	copyfd = dup(STDOUT_FILENO);
	// openfiles_bt(cmd->redi, data, cmd, 0);
	if (openfiles_bt(cmd->redi, data, cmd, 0))
	{
		dup2(copyfd, STDOUT_FILENO);
		close(copyfd);
		return (1);
	}
	ft_builtin(cmd, data);
	dup2(copyfd, STDOUT_FILENO);
	ft_free((void **)& cmd->flags);
	ft_free((void **)& cmd->cmd);
	ft_freetab(data->split);
	ft_freerr(cmd->redi);
	close(data->fd[0]);
	close(data->fd[1]);
	close(copyfd);
	return (1);
}

int	exec_command(t_btree *tree, int infile, int outfile)
{
	int		i;
	char	**tab;
	int		nbcmd;
	t_cmd	cmd;
	char	*temp;
	int		status;
	static int var = 0;

	ft_bzero(& cmd, sizeof(t_cmd));
	// printf("[%s]\n", (char *)tree->node);
	tree->data->split = ft_split(tree->node, '|');
	nbcmd = ft_countdelim(tree->node, '|');
	i = -1;
	while (++i < nbcmd) // < nbcmd)
	{
		tree->data->split[i] = ft_spacestr(tree->data->split[i]);
		checkstring(& cmd, tree->data->split[i]);
		pipe(tree->data->fd);
		if (nbcmd == 1 && exec_builtin(&cmd, tree->data))
				return 0;
		signal(SIGINT, SIG_IGN);
		tree->data->pid[i] = fork();
		if (tree->data->pid[i] == 0)
		{
			signal(SIGINT, & ctrlc);
			signal(SIGQUIT, & antislash);
			forking(tree->data, i, nbcmd, & cmd);
			ft_errorcmd(tree->data, & cmd, cmd.redi, "");
			exit(tree->data->status);
		}
		else
		{
			close(tree->data->fd[1]);
			if (tree->data->prev_pipes != -1)
				close(tree->data->prev_pipes);
			tree->data->prev_pipes = tree->data->fd[0];
			ft_free((void **)&cmd.cmd);
			ft_free((void **)&cmd.flags);
			ft_freerr(cmd.redi);
			signal(SIGQUIT, SIG_IGN);
		}
	}
	ft_freetab(tree->data->split);
	ft_free((void **)& cmd.flags);
	// ft_freerr(cmd.redi);
	// ft_freetab(tree->data->here_docs);
	// ft_freetab(tree->data->filename);
	// tree->data->filename = 0;
	// tree->data->here_docs = 0;
	// ft_free((void **)&cmd.cmd);
	// ft_free((void **)&cmd);
	close(tree->data->fd[0]);
	i = -1;
	while (++i < nbcmd)
	{
		ft_printf("tonpere\n");
		waitpid(tree->data->pid[i], &tree->data->status, 0);
		if (WIFEXITED(tree->data->status))
		{
			ft_printf("tamere\n");
			tree->data->status = WEXITSTATUS(tree->data->status);
		}
		if (tree->data->status == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
	var = 0;
	signal(SIGINT, & ctrlc);
	return (0);
}

int	exec_tree(t_btree *tree, int infile, int outfile)
{
	tree->data->prev_pipes = -1;
	if (!ft_strcmp((char *)tree->node, "||"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, infile, outfile);
		// ft_printf("status=%i\n", tree->data->status);
		if (tree->data->status)
			return (exec_tree(tree->r, infile, outfile));
		return (0);
	}
	else if (!ft_strcmp((char *)tree->node, "&&"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, infile, outfile);
		// ft_printf("status=%i\n", tree->data->status);
		if (!tree->data->status)
			return (exec_tree(tree->r, infile, outfile));
		return (1);
	}
	return (exec_command(tree, infile, outfile));
}
