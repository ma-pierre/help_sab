#include "../minishell.h"

char    *expand_env_var(t_minishell *ms, char *input_slice)
{
    int i;
    char    *var_expanded;
    char    *expanded_slice;

    i = 0;
    var_expanded = NULL;
    expanded_slice = NULL;
    while(input_slice[i] && input_slice[i] != '$')
        i++;
    
    var_expanded = get_var_value()
    
}