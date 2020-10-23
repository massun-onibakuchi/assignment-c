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
        /practice_program/second-term #
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
    //valがノードのvalueより小さい時
    if (val < node->value)
    {
        //ブランチがleftにある場合
        if (node->left != (struct bitree *)NULL)
        {
            //一つ深いところに進む．再帰呼び出し
            return add_node(val, node->left);
        }
        else
        {
            //リーフノードを作る
            struct bitree *newnode = (struct bitree *)malloc(sizeof(struct bitree));
            newnode->left = (struct bitree *)NULL;
            newnode->right = (struct bitree *)NULL;
            newnode->value=val;
            node->left = newnode;
        }
    }
    else
    {
        if (node->right != (struct bitree *)NULL)
        { 
            //一つ深いところに進む．再帰呼び出し
            return add_node(val, node->right);
        }
        else
        {
            //リーフノードを作る
            struct bitree *newnode = (struct bitree *)malloc(sizeof(struct bitree));
            newnode->left = (struct bitree *)NULL;
            newnode->right = (struct bitree *)NULL;
            newnode->value=val;
            node->right = newnode;
        }
    }
}

int read_node(struct bitree *node)
{
    if (node != (struct bitree *)NULL)
    {
        //現在のノードから左側を読んでから現在のノードの値を出力して，それから右側を読む
        read_node(node->left);
        printf("%f ",node->value);
        read_node(node->right);
    }
}