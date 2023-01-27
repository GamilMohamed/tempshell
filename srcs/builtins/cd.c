/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/26 16:43:31 by mgamil           ###   ########.fr       */
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
	char	*home;

	home = ft_ev_getvar("HOME", ev);
	if (home == NULL)
		return (ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO), NULL);
	new_pwd = ft_strchr(home, '=') + 1;
	if (new_pwd == NULL)
		return (ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO), NULL);
	else if (av && av[0] && !ft_strncmp(av[0], "~/", 2))
			new_pwd = ft_strjoin(new_pwd, av[0] + 1);
	else
		new_pwd = ft_strdup(new_pwd);
	return (new_pwd);
}

char	*get_oldpath(char **av, char **ev)
{
	char	*new_pwd;
	char	*oldpwd;

	oldpwd = ft_ev_getvar("OLDPWD", ev);
	if (oldpwd == NULL)
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO), NULL);
	new_pwd = ft_strchr(oldpwd, '=') + 1;
	if (new_pwd == NULL)
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO), NULL);
	printf("%s\n", new_pwd);
	oldpwd = ft_strdup(new_pwd);
	if (!oldpwd)
		ft_puterror(FAILED_MALLOC, (char *)__func__);
	return (oldpwd);
	ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
	return (NULL);
}

char	*ft_getpath(char **av, char **ev)
{
	if (av == NULL || av[0] == NULL || !ft_strncmp(av[0], "~/", 2)
		|| !ft_strcmp(av[0], "~") || !ft_strcmp(av[0], "--"))
		return (get_homepath(av, ev));
	else if (!ft_strcmp(av[0], "-"))
		return (get_oldpath(av, ev));
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
		return (ft_puterror(FAILED_MALLOC, (char *)__func__), 0);
	if (!chdir(new_pwd))
	{
		ft_ev_setvar("OLDPWD", pwd, addr_ev);
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (ft_puterror(FAILED_MALLOC, (char *)__func__), 0);
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
		ft_free((void **) & new_pwd);
		return (ft_puterror(ERROR_CD_BUILTIN, av[0]), 1);
	}
	if (new_pwd)
		free(new_pwd);
	return (0);
}
