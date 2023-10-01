/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   executor.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/28 16:56:14 by marvin			#+#	#+#			 */
/*   Updated: 2023/10/01 14:20:13 by marvin		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	int	 cmd_count;

	tmp = mini->cmd;
	cmd_count = 0;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	return (cmd_count);
}

void	print_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	char	**tmp_args;

	tmp = mini->cmd;
	while (tmp)
	{
		tmp_args = tmp->args;
		while (*tmp_args)
		{
			ft_putstr_fd(*tmp_args, 2);
			ft_putstr_fd("\n", 2);
			tmp_args++; 
		}
		ft_putstr_fd("----\n", 2);
		tmp = tmp->next;
	}
}

void	*execute_commands(t_minishell *mini)
{
	int		command_count;
	int		status;
	int		i;
	pid_t	pid;
	int		*pipe_fds;

	//print_commands(mini);
	command_count = count_commands(mini);
	pipe_fds = (int *) ft_calloc(2 * command_count + 1, sizeof(pipe_fds));

	i = 0;
	for(i = 0; i < command_count; i++){
		if(pipe(pipe_fds + i*2) < 0) {
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
	}


	int j = 0;
	while(mini->cmd)
	{
		pid = fork();
		if(pid == 0)
		{
			//if not last command
			if(mini->cmd->next){
				if(dup2(pipe_fds[j + 1], 1) < 0){
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			//if not first command&& j!= 2*numPipes
			if(j != 0 ){
				if(dup2(pipe_fds[j-2], 0) < 0){
					perror(" dup2");///j-2 0 j+1 1
					exit(EXIT_FAILURE);

				}
			}
			for(i = 0; i < 2 * command_count; i++){
					close(pipe_fds[i]);
			}
			if( execvp(*mini->cmd->args, mini->cmd->args) < 0 ){
					perror(*mini->cmd->args);
					exit(EXIT_FAILURE);
			}
		} else if(pid < 0){
			perror("error");
			exit(EXIT_FAILURE);
		}

		mini->cmd = mini->cmd->next;
		j+=2;
	}
	for(i = 0; i < 2 * command_count; i++){
		close(pipe_fds[i]);
	}
	for(i = 0; i < command_count + 1; i++){
		wait(&status);
	}
	return (mini);
}
