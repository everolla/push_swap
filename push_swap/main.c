#include "push_swap.h"

void    ft_exit(t_general *general)
{
    free(general);
    exit(0);
}

    // PUSH FIRST IN STACK_A TO FIRST IN STACK_B
void    pa(t_list *stack_a, t_list *stack_b)
{
    int i;

    i = 0;
    stack_a.next->preview = stack_a.preview;
    stack_a.preview->next = stack_a.next;
    stack_a->preview = stack_b->preview;
    stack_a->next = stack_b;
    stack_b.prev->next = stack_a;
    stack_b->prev = stack_a;
    while(i <= stack_a->total)
    {
        stack_a->total -= 1;
        stack_a->pos -= 1;
        stack_a = stack_a.next;
        i++;
    }
    i = 0;
    while(i <= stack_b->total)
    {
        stack_b->total += 1;
        stack_b->pos += 1;
        stack_b = stack_b.next;
        i++;
    }
}

    // LAST ELEMENT BECOMES THE FIRST ONE
void    rra(t_list *list)
{
    int i;

    i = 0;
    list.preview->pos = 0;
    while (i <= list->total -1)
    {
        list->pos += 1;
        i++;
        list = list.next;
    }
}

    // FIRST ELEMENT BECOMES THE LAST ONE
void    ra(t_list *list)
{
    int i;

    i = 1;
    list->pos = list->total;
    while(i <= list->total)
    {
        list.next->pos -= 1;
        list = list.next;
        i++;
    }
}

    // SWAP FIRST TWO ELEMENTS IN STACK
void    sa(t_list *list)
{
    list->pos = 1;
    list->next->pos = 0;
    list->next = list->next->next;
    list->next->preview = list->preview;
    list->preview = list->next;
    list->next->next = list;

}

    // RANK STRUCT FROM SMALLEST TO BIGGEST
void    ranking(t_general *general)
{
    t_list  *temp;
    t_list  *buffer;
    int     ranking;

    ranking = 0;
    buffer = general->stack_a;
    temp = buffer;
    while(ranking <= general->total)
    {
        while(buffer->next != general->stack_a)
        {
            if (temp->num > buffer->next->num && buffer->next->rank == -3)
                temp = buffer->next;
            buffer = buffer->next;
        }    
        temp->rank = ranking;
        ranking++;
        buffer = general->stack_a;
    }
}

void    ft_all(t_general *general, t_list *new, t_list *prev, int i)
{
    new = malloc(sizeof(t_list));
    new->pos = i - 1;
    new->num = ft_atoi(general->argv[i]);
    new->next = NULL;
    new->rank = -3;
    prev->next = new;
    new->preview = prev;
    prev = new;
    i++;
}
// CREATE STACK_A CIRCULAR LIST
void    create_list(t_general *general)
{
    t_list  *stlist;
    t_list  *prev;
    t_list  *new;
    int     i;

    i = 2;
    stlist = malloc(sizeof(t_list));
    stlist->pos = 0;
    stlist->num = ft_atoi(general->argv[i]);
    stlist->next = NULL;
    stlist->rank = -3;
    stlist->preview = NULL;
    prev = stlist;
    while(general->argv[i])
        ft_all(general, new, prev, &i);
    general->total = i - 1;
    prev->next = stlist;
    stlist->preview = prev;
    general->stack_a = stlist;    //   CREATING STACK_A  
    free(stlist);
    free(new);
}

    // CHECK INPUT ONLY CONTAINS NUMBERS
void    num_check(char *pot_num, t_general *general)
{
    int i;

    i = 0;
    while (pot_num[i])
    {
        if (pot_num[i] >= '0' && pot_num[i] <= '9')
            i++;
        else
            ft_exit(general);
    }
}

    // CHECK VALID INPUT
void    input_handler(t_general *general)
{
    int     i;
    int     c;
    char    **v;

    i = 1;
    if (general->argc < 2)
        ft_exit(general);
    if (general->argc == 2)
        general->argv = ft_split(general->argv[1], " ");
    while(general->argv[i])
        num_check(general->argv[i++], &general);
}

t_general *ft_start(int argc, char **argv)
{
    t_general *general;

    general = (t_general*)malloc(sizeof(t_general));
    general->argv = argv;
    general->argc = argc;
    general->stack_a = malloc(sizeof(t_list));
    general->stack_b = malloc(sizeof(t_list));
    general->sort = malloc(sizeof(t_sort));
    return(general);
}

int main(int argc,char **argv)
{
    t_general *general;

    general = ft_start(argc, argv);
    input_handler(general);
    create_list(general);
    ranking(general);
    chunkz_sort(general);
}

void    sort_first(t_general *general, int start, int finish)
{
    t_list  *buff;
    int     r;

    buff = general->stack_a;
    while(buff->next != general->stack_a)
    {
        if(buff->rank >= start && buff->rank <= finish)
        {
            general->sort->hold_first = buff->pos;
            break;
        }
        buff++;
    }
}

void    sort_second(t_general *general, int start, int finish)
{
    t_list  *buff;
    int     r;

    buff = general->stack_a;
    while(buff->preview != general->stack_a)
    {
        if(buff->rank >= start && buff->rank <= finish)
        {
            general->sort->hold_second = buff->pos;
            break;
        }
        buff--;
    }
}

void    moves_counter(t_general *general)
{
    int x;

    
    // CONTA QUALE NUMERO È MEGLIO TRA HOLD FIRST E HOLD SECOND E LO MANDA
}

void    ft_fredric(t_general *general, int z, int j)
{
    int x;

    x = 0;
    while(x < j)
    {
        sort_first(general, z, j);
        sort_second(general,z, j);
        moves_counter(general);
        x++;
    }
}

void    chunkz_sort(t_general *general)
{
    int j;
    int z;

    j = 10;
    z = 0;
    while(j < general->total && z < j)
    {
        ft_fredric(general, z, j);
        z = j;
        j += j;
        if (j >= general->total)
            j = general->total - 1;
    }
}