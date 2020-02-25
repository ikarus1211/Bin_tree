#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
    int height;
} NODE;


NODE* Right(NODE *ptr)
{
    NODE *temp = ptr->left;
    ptr->left = ptr->left->right;
    temp->right =ptr;
    ptr = temp;
    return ptr;
}
NODE *LeftRight(NODE *ptr)
{
    NODE *temp = ptr->left;
    ptr->left = temp->right;
    temp->right = ptr->left->right;
    ptr->left->left = temp;
    return Right(ptr);
}
NODE* Left(NODE *ptr)
{
    NODE *temp = ptr->right;
    ptr->right = ptr->right->left;
    temp->left = ptr;
    ptr = temp;
    return ptr;
}
NODE* RightLeft(NODE *ptr)
{
    NODE *temp = ptr->right;
    ptr->right = temp->left;
    temp->left = ptr->right->right;
    ptr->right->right =temp;
    return Left(ptr);
}
NODE *InitLeft(NODE *ptr)
{
    if (ptr->left->right == NULL || ptr->left->right->height < ptr->left->left->height)
       return Right(ptr);
    else
       return LeftRight(ptr);
}
NODE* InitRight(NODE *ptr)
{
    if (ptr->right->left == NULL || ptr->right->left->height < ptr->right->right->height)
        return Left(ptr);
    else
        return RightLeft(ptr);

}

int checkDepth(NODE *ptr)
{
    int leftD;
    int rightD;

    if (ptr == NULL)
        return 0;
    leftD = checkDepth(ptr->left);
    rightD = checkDepth(ptr->right);

    if (leftD == rightD) {
        ptr->height = leftD;
        return rightD + 1;
    }
    if (leftD > rightD) {
        ptr->height = leftD;
        return leftD + 1;
    }
    if (leftD < rightD) {
        ptr->height = rightD;
        return rightD + 1;
    }


}
int search(NODE *ptr, int value)
{
    if (ptr == NULL)
        return 0;
    if (ptr->data == value) {
        printf("%d| ", ptr->height);
        return 1;
    }
    if (value > ptr->data)
        return  search(ptr->right, value);
    if (value < ptr->data)
        return search(ptr->left, value);

}

NODE *addF(NODE *ptr, int value)
{

    if (ptr == NULL)
    {
        NODE *new_n= (NODE*)malloc (sizeof(NODE));
        new_n->left = NULL;
        new_n->right = NULL;
        new_n->data =  value;
        new_n->height = 1;
        printf("Hodnota pridana\n");
        return  new_n;
    }
    if (value == ptr->data) {
        printf("hodnot uz existuje");
        return ptr;
    }
    if (value < ptr->data)
    {
        ptr->left = addF(ptr->left, value);
    }
    if (value > ptr->data)
    {
        ptr->right = addF(ptr->right, value);
    }
    printf("tusom");
    checkDepth(ptr);
    int leftH, rightH;
    if (ptr->left == NULL)
        leftH = 0;
    else
        leftH = ptr->left->height + 1;

    if (ptr->right == NULL)
        rightH = 0;
    else
        rightH = ptr->right->height + 1;

    if ((ptr->height - leftH) > 1)
        return InitRight(ptr);
    if ((ptr->height - rightH) > 1)
        return  InitLeft(ptr);

    return ptr;

}
int main()
{

    NODE *my_t = NULL;
    int value;
    char flag = 0 ;
    while (flag != 'q')
    {
        scanf("%c",&flag);
        if (flag == 'a')
        {

            scanf("%d",&value);
            my_t = addF(my_t, value);

        }
       if (flag == 's')
       {
           checkDepth(my_t);
           scanf("%d",&value);
           if (search(my_t, value))
               printf("Found it\n");
           else
               printf("Not here\n");
       }

    }

}