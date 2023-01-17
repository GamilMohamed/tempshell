/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 23:20:44 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// on doit gerer cd - et retourner au previous directory, comment faire ?
// cd --- donne en message d'erreur: "bash: cd: --: invalid option"
// il faut que j'expand les $ de str ou non ?

// $> unset HOME
// $> cd $HOME
// doit renvoyer
// bash: cd: HOME not set
// $>

char	*get_homepath(char **av, char **ev)
{
	char	*new_pwd;

	new_pwd = ft_strchr(ft_ev_getvar("HOME", ev), '=') + 1;
	if (new_pwd == NULL)
		ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
	else if (av && av[0] && !ft_strncmp(av[0], "~/", 2))
			new_pwd = ft_strjoin(new_pwd, av[0] + 1);
	else
		new_pwd = ft_strdup(new_pwd);
	return (new_pwd);
}

char	*ft_getpath(char **av, char **ev)
{
	char	*new_pwd;

	if (av == NULL || av[0] == NULL || !ft_strncmp(av[0], "~/", 2)
		|| !ft_strcmp(av[0], "--"))
		return (get_homepath(av, ev));
	else if (!ft_strcmp(av[0], "-"))
	{
		new_pwd = ft_strchr(ft_ev_getvar("OLDPWD", ev), '=') + 1;
		if (new_pwd)
		{
			printf("%s\n", new_pwd);
			return (ft_strdup(new_pwd));
		}
		ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
	}
	else if (!ft_strncmp(av[0], "--", 2))
		ft_putstr_fd("bash: cd: --: invalid option\n", STDERR_FILENO);
	else if (av[0][0] == '/')
		return (ft_strdup(av[0]));
	else
		return (ft_strjoin("./", av[0]));
	return (NULL);
}

int	change_directory(char *new_pwd, char ***addr_ev)
{
	char	*pwd;

	if (!new_pwd)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_puterror(FAILED_MALLOC), 0);
	if (!chdir(new_pwd))
	{
		ft_ev_setvar("OLDPWD", pwd, addr_ev);
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (ft_puterror(FAILED_MALLOC), 0);
		ft_ev_setvar("PWD", pwd, addr_ev);
		free(pwd);
		return (0);
	}
	else
		return (free(pwd), -1);
}

int	ft_cd(char **av, char ***addr_ev)
{
	char	*new_pwd;

	new_pwd = ft_getpath(av, *addr_ev);
	errno = 0;
	if (change_directory(new_pwd, addr_ev) || errno)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		if (errno == EACCES || errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Error changing directory\n", STDERR_FILENO);
		if (new_pwd)
			free(new_pwd);
		return (-1);
	}
	if (new_pwd)
		free(new_pwd);
	return (0);
}
