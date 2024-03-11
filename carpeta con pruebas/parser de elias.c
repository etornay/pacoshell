
static int	parser_cmd3(t_paco *p, t_parser *node, int *i)
{
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
	{
		if (flag_pipe(p, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	pass_tokens(p, i);
	if (p->lex2[*i] && p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i] != NULL)
		get_cmd(p, node, i);
	if (node->full_cmd)
		path_cmd(p, node);
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		(*i)++;
	while (p->lex2[*i] && p->lex2[*i][0] == '>' && p->lex2[*i][0] == '<')
		p_utils(p, node, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
	return (EXIT_SUCCESS);
}

static int	parser_cmd2(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>' && p->lex2[*i] && (*i) <= p->count)
		get_cmd(p, node, i);
	if (node->full_cmd && check_builtin(p) == EXIT_FAILURE)
		path_cmd(p, node);
	else if (check_builtin(p) == EXIT_SUCCESS)
		node->full_path = NULL;
	while (p->lex2[*i] && p->lex2[*i][0] != '|'
		&& p->lex2[*i][0] != '<' && p->lex2[*i][0] != '>')
		(*i)++;
	p_utils(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
	{
		if (flag_pipe(p, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] != '|')
		pass_tokens(p, i);
	ft_lstadd_back(&p->lst_cmd, ft_lstnew(node));
	return (EXIT_SUCCESS);
}

static void	parser_cmd_special(t_paco *p, t_parser *node, int *i)
{
	if (token_errors(p, i))
		return ;
	else if (p->lex2[*i] && p->lex2[0][0] == '>'
		&& p->lex2[1] && p->lex2[1][0] == '>' && p->lex2[2])
		exec_append(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '>' && p->lex2[1]
		&& p->lex2[1][0] != '>')
		exec_trunc(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '<'
		&& p->lex2[1] && p->lex2[1][0] == '<' && p->lex2[2])
		exec_heredoc(p, node, i);
	else if (p->lex2[*i] && p->lex2[0][0] == '<' && p->lex2[1]
		&& p->lex2[1][0] != '<')
		read_only(p, node, i);
	return ;
}

static int	parser_cmd_continue(t_paco *p, t_parser *node, int *i)
{
	if (p->lex2[*i] && ((p->lex2[0][0] == '>' && !p->lex2[1])
		|| (p->lex2[0][0] == '<' && !p->lex2[1])
		|| (p->lex2[0][0] == '<' && p->lex2[1][0] == '<' && p->lex2[2])
		|| (p->lex2[0][0] == '<' && p->lex2[1])
		|| (p->lex2[0][0] == '>' && p->lex2[1][0] == '>' && p->lex2[2])
		|| (p->lex2[0][0] == '>' && p->lex2[1])))
		parser_cmd_special(p, node, i);
	if (p->lex2[*i] && p->lex2[*i][0] != '|' && p->lex2[*i][0] != '<'
		&& p->lex2[*i][0] != '>')
	{
		if (parser_cmd2(p, node, i) == EXIT_FAILURE)
		{
			free(node);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	parser_cmd(t_paco *p, int i)
{
	t_parser	*node;

	while (p->lex2[i])
	{
		node = ft_calloc(1, sizeof(t_parser));
		node->outfile = 1;
		node->infile = 0;
		if (parser_cmd_continue(p, node, &i) == EXIT_FAILURE)
			break ;
		if (p->lex2[i] && p->lex2[i][0] == '|')
			if (flag_pipe(p, &i) == EXIT_FAILURE)
				return ;
		if (p->lex2[i] && (p->lex2[i][0] == '<' || p->lex2[i][0] == '>'))
		{
			pass_tokens(p, &i);
			while (p->lex2[i] && (p->lex2[i][0] == '<' || p->lex2[i][0] == '>'))
				i++;
			continue ;
		}
		if (p->lex2[i] && p->lex2[i][0] != '<'
			&& p->lex2[i][0] != '>' && p->lex2[i][0] != '|')
		{
			if (parser_cmd3(p, node, &i) == EXIT_FAILURE)
			{
				free(node);
				break ;
			}
		}
		if (i >= p->count)
			break ;
	}
}

/*t_list	*aux;
	aux = p->lst_cmd;
	int	j;
	while (aux != NULL)
	{
		j = 0;
		printf("Nodo \n");
		printf("path: %s\n", ((t_parser *)(aux->content))->full_path);
		if (((t_parser *)(aux->content))->full_cmd != NULL)
		{
			while (((t_parser *)(aux->content))->full_cmd[j] != NULL)
			{
				printf("cmd: %s\n", ((t_parser *)(aux->content))->full_cmd[j]);
				j++;
			}
		}
		printf("infile: %d\n", ((t_parser *)(aux->content))->infile);
		printf("outfile: %d\n", ((t_parser *)(aux->content))->outfile);
		aux = aux->next;
	}*/


	/*else if (p->lex2[*i] && (p->lex2[*i][0] == '<'
		|| p->lex2[*i][0] == '>') && (p->lex2[*i + 2]
		|| (p->lex2[*i + 2] && p->lex2[*i + 2][0] == '|')))
	{
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return (EXIT_FAILURE);
	}*/
	