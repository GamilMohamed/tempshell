/*

fou ca dans ton main, appelle ft_infix avec ton arbre en argument
test avec des a | b | c && d tout ca
tu verras bien l'ordre d'execution et si il execute ou non les choses apres les && ou ||



*/
void	ft_infix(t_btree *tree)
{
	static int ordre;
	if (tree)
	{
		if (tree && isoperator(tree->node) == 1)
		{
			printf("[%i]AND:%s\n", ordre++, (char *)tree->node);
			ft_infix(tree->l);
			ft_printf("status of (leftnode)[%s]: %i\n", tree->l->node, tree->l->status);
			if (tree->l && tree->l->status > 1)
				ft_infix(tree->r);
			tree->status = tree->l->status + tree->r->status;
		}
		else if (tree && isoperator(tree->node) == 2)
		{
			printf("[%i]OR:%s\n", ordre++, (char *)tree->node);
			ft_infix(tree->l);
			ft_printf("status of (leftnode)[%s]: %i\n", tree->l->node, tree->l->status);
			if (tree->l && tree->l->status == 0)
				ft_infix(tree->r);
			tree->status = tree->l->status + tree->r->status;
		}
		else if (tree && isoperator(tree->node) == 3)
		{
			printf("[%i]PIPE:%s\n", ordre++, (char *)tree->node);
			ft_infix(tree->l);
			ft_infix(tree->r);
			tree->status = tree->l->status + tree->r->status;
		}
		else
		{
			printf("[%i]CMD:%s\n", ordre++, (char *)tree->node);
			tree->status = 100;
		}
	}
}
