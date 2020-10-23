#include <stdio.h>
#include <stdlib.h>

/* structure of a binary tree */
struct bitree
{
    float value;
    struct bitree *left;  /* pointer to the left node */
    struct bitree *right; /* pointer to the right node */
};

int add_node(float, struct bitree *);
int read_node(struct bitree *);

/* sample input data : {8, 5, 7, 3, 10, 9, 6, 1, 20} */

int main(void)
{
    float data[256];
    int i, j;
    struct bitree root, *node;

    /*  Use setbuf to avoid this 
        practice_program/second-term # ./a.out 
        8
        5
        7
        Input a number(End:ctrl-d) >Input a number(End:ctrl-d) >Input a number(End:ctrl-d) >Input a number(End:ctrl-d) >
     */
    setbuf(stdout, NULL);

    /* Input numbers into array data[i] */
    i = 0;
    do
    {
        if (i > 255)
            return -1;
        printf("Input a number(End:ctrl-d) >");
    } while (scanf("%f", &(data[i++])) != EOF); /* ctrl-d means End Of File */
    i--;                                        /* 1 step back */
    printf("\n");

    /* Test */
    // float numbers[256] ={8, 5, 7, 3, 10, 9, 6, 1, 20};
    // for ( i = 0; i < 9; i++) 
    // {
    //     data[i]=numbers[i];
    // }
    // i--;

    /* Set the root */
    if (i > 0)
    {
        root.value = data[0];
        root.left = (struct bitree *)NULL; //cast
        root.right = (struct bitree *)NULL;
    }

    /* Create a binary tree */
    for (j = 1; j < i; j++)
    {
        add_node(data[j], &root);
    }

    /* Print sorted sequence */
    read_node(&root);
    return 0;
}

int add_node(float val, struct bitree *node)
{
    if (val < node->value)
    {
        if (node->left != (struct bitree *)NULL)
        {
            return add_node(val, node->left);
        }
        else
        {
            struct bitree *newnode = (struct bitree *)malloc(sizeof(struct bitree));
            newnode->left = (struct bitree *)NULL;
            newnode->right = (struct bitree *)NULL;
            node->left = newnode;
            return add_node(val,newnode);
        }
    }
    else
    {
        if (node->right != (struct bitree *)NULL)
        {
            return add_node(val, node->right);
        }
        else
        {
            struct bitree *newnode = (struct bitree *)malloc(sizeof(struct bitree));
            newnode->left = (struct bitree *)NULL;
            newnode->right = (struct bitree *)NULL;
            node->right = newnode;
            return add_node(val,newnode);
        }
    }
}

int read_node(struct bitree *node)
{
    if (node != (struct bitree *)NULL)
    {
        read_node(node->left);
        printf("%f ",node->value);
        read_node(node->right);
    }
}
// int read_node2(struct bitree *node)
// {
//     struct bitree *parentnode = (struct bitree *)NULL;
//     if (node->left == (struct bitree *)NULL)
//     {
//         // while (node->right == (struct bitree *)NULL)
//         // {
//         //     printf("%d ", node->value);
//         //     node = parentnode;
//         // }
//         do
//         {
//             printf("%d ", node->value);
//             node = parentnode;
//         } while (node->right == (struct bitree *)NULL);
//         printf("%d ", node->value);

//         return read_node2(node->right);
//     }
//     else
//     {
//         parentnode = node;
//         return read_node2(node->left);
//     }
// }