#include "hw6.h"

/**
 * Fully copies matrix.
 * @param a: The const matrix pointer to the matrix that needs to be memory copied into another matrix, using malloc
 * @return m: the copied matrix into a allocated memory
 */
matrix_sf *full_copy_matrix(const matrix_sf *a)
{
    matrix_sf *m = malloc(sizeof(matrix_sf) + a->num_rows * a->num_cols * sizeof(int));
    m->name = a->name;
    m->num_rows = a->num_rows;
    m->num_cols = a->num_cols;
    memcpy(m->values, a->values, a->num_rows * a->num_cols * sizeof(int));
    return m;
}

/**
 * Inserts a matrix into a BST using the root of the tree. If the root is null, the matrix is inserted as the root.
 * Otherwise, the function checks both the left and the right child of the BST to place the new node accordingly.
 * @param mat: the matrix_sf pointer that points to the matrix that will be added to the BST
 * @param root: the bst_sf pointer to the root of the BST we want to add matrix too
 * @return newNode: the node added to the BST
 */
bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{
    if (root == NULL)
    {
        bst_sf *newNode = (bst_sf *)calloc(1, sizeof(bst_sf));
        newNode->mat = mat;
        newNode->left_child = NULL;
        newNode->right_child = NULL;
        return newNode;
    }
    else
    {
        if (mat->name < root->mat->name)
        {
            root->left_child = insert_bst_sf(mat, root->left_child);
        }
        else if (mat->name > root->mat->name)
        {
            root->right_child = insert_bst_sf(mat, root->right_child);
        }
    }
    return root;
}

/**
 * It finds a node by name in a BST. This functions checks if the root is null. Otherwise, it searches left and right until the name is found.
 * @param name: the character that holds the name of the matrix we are searching for
 * @param root: the pointer to the root of the BST we are searching through
 * @return mat: the matrix that matches the name inputted in the function
 */
matrix_sf *find_bst_sf(char name, bst_sf *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (name < root->mat->name)
        {
            return find_bst_sf(name, root->left_child);
        }
        else if (name > root->mat->name)
        {
            return find_bst_sf(name, root->right_child);
        }
        else if (name == root->mat->name)
        {
            return root->mat;
        }
    }
    return NULL;
}

/**
 * This function frees all the matrices in a BST that is identified by a given root.
 * @param root: a pointer to the root of the BST we are clearing from
 * The return type is void.
 */
void free_bst_sf(bst_sf *root)
{
    if (root != NULL)
    {
        free_bst_sf(root->left_child);
        free_bst_sf(root->right_child);
        free(root->mat);
        free(root);
    }
}

/**
 * This function addes the contents of two matrices together.
 * @param mat1: the pointer to the first matrix in our addition
 * @param mat2: the pointer to the second matrix in our addition
 * @return result: the resulting matrix after adding mat1 to mat2
 * Caller is responsible for memory returned
 */
matrix_sf *add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    matrix_sf *result = (matrix_sf *)calloc(1, sizeof(matrix_sf) + mat1->num_rows * mat1->num_cols * sizeof(int));
    result->name = ' ';
    result->num_rows = mat1->num_rows;
    result->num_cols = mat1->num_cols;
    for (unsigned int i = 0; i < mat1->num_rows; i++)
    {
        for (unsigned int j = 0; j < mat1->num_cols; j++)
        {
            unsigned int index = i * mat1->num_cols + j;
            result->values[index] = mat1->values[index] + mat2->values[index];
        }
    }
    return result;
}

/**
 * This function multiples two matrices.
 * @param mat1: the pointer to the first matrix we are multiplying
 * @param mat2: the pointer to the second matrix we are multiplying
 * @return result: the resulting matrix after multiplying mat1 and mat2
 * Caller is responsible for memory returned
 */
matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{
    matrix_sf *result = (matrix_sf *)calloc(1, sizeof(matrix_sf) + mat1->num_rows * mat2->num_cols * sizeof(int));
    result->name = ' ';
    result->num_rows = mat1->num_rows;
    result->num_cols = mat2->num_cols;
    for (unsigned int i = 0; i < mat1->num_rows; i++)
    {
        for (unsigned int j = 0; j < mat2->num_cols; j++)
        {
            int sum = 0;
            for (unsigned int k = 0; k < mat1->num_cols; k++)
            {
                sum += mat1->values[i * mat1->num_cols + k] * mat2->values[k * mat2->num_cols + j];
            }
            result->values[i * mat2->num_cols + j] = sum;
        }
    }
    return result;
}

/**
 * This function tranposes a matrix.
 * @param mat1: the pointer to the first matrix we are transposing
 * @return result: the resulting matrix after transposing
 * Caller is responsible for memory returned
 */
matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{
    matrix_sf *transposed = (matrix_sf *)calloc(1, sizeof(matrix_sf) + mat->num_cols * mat->num_rows * sizeof(int));
    transposed->num_rows = mat->num_cols;
    transposed->num_cols = mat->num_rows;
    for (unsigned int i = 0; i < mat->num_rows; i++)
    {
        for (unsigned int j = 0; j < mat->num_cols; j++)
        {
            transposed->values[j * transposed->num_cols + i] = mat->values[i * mat->num_cols + j];
        }
    }
    return transposed;
}

/**
 * This function skips all whitespaces in a constant string.
 * @param str: the pointer to the constant string we are skipping whitespaces in
 * @return str: the moved pointer to the next non-whitespace character
 */
const char *skip_whitespace(const char *str)
{
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
    {
        str++;
    }
    return str;
}

/**
 * This function creates a matrix using an expression that includes rows, columns and values seperated by semicolons
 * @param name: the name of the matrix we are creating
 * @param expr: the const pointer to the expression we are using to create a matrix
 * @return matrix: the resulting matrix created by using expr
 * Caller is responsible for memory returned
 */
matrix_sf *create_matrix_sf(char name, const char *expr)
{
    unsigned int num_rows, num_cols;
    expr = skip_whitespace(expr);
    sscanf(expr, "%u %u", &num_rows, &num_cols);
    matrix_sf *matrix = calloc(1, sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    matrix->name = name;
    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;
    int *values = matrix->values;
    while (*expr != '[')
    {
        expr++;
    }
    expr++;
    int counter = 0;
    int current_row = 0;
    while (*expr != '\0' && *expr != ']')
    {
        expr = skip_whitespace(expr);
        int value;
        sscanf(expr, "%d", &value);
        values[counter] = value;
        counter++;
        while (*expr != '\0' && ((*expr >= '0' && *expr <= '9') || *expr == '-'))
        {
            expr++;
        }
        expr = skip_whitespace(expr);
        if (*expr == ';' || *expr == ',')
        {
            expr++;
            current_row++;
            counter = current_row * num_cols;
        }
        expr = skip_whitespace(expr);
    }

    return matrix;
}

/**
 * This function determines whether or not a character is an operator.
 * @param ch: the character we are testing for operator
 * @return: a true or false integer based on whether or not ch is equal to +, *, and \
 */
int isOperator(char ch)
{
    return (ch == '+' || ch == '*' || ch == '\'');
}

/**
 * This function returns the precedence of a character.
 * @param ch: the character we are testing for precedence
 * @return: integer based on the precedence of the character
 */
int getPrecedence(char ch)
{
    if (ch == '\'')
        return 2;
    if (ch == '*' || ch == '/')
        return 1;
    if (ch == '+' || ch == '-')
        return 0;
    return -1;
}

/**
 * This function converts an infix function to a postfix function using a stack, alongside the isOperator() and getPrecedence() functions.
 * @param infix: a pointer to the infix string
 * @return postfix: the pointer to the new postfix string
 * Caller is responsible for memory returned
 */
char *infix2postfix_sf(char *infix)
{
    int len = strlen(infix);
    char *postfix = (char *)calloc((len), sizeof(char));
    int postfixIndex = 0;
    char stack[len];
    int stackIndex = -1;
    for (int i = 0; i < len; i++)
    {
        char currentChar = infix[i];
        if ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
        {
            postfix[postfixIndex] = currentChar;
            postfixIndex = postfixIndex + 1;
        }
        else if (currentChar == '(')
        {
            stackIndex = stackIndex + 1;
            stack[stackIndex] = currentChar;
        }
        else if (currentChar == ')')
        {
            while (stackIndex >= 0 && stack[stackIndex] != '(')
            {
                postfix[postfixIndex] = stack[stackIndex];
                postfixIndex = postfixIndex + 1;
                stackIndex = stackIndex - 1;
            }
            if (stack != NULL)
            {
                stackIndex = stackIndex - 1;
            }
        }
        else if (isOperator(currentChar))
        {
            while (stackIndex >= 0 && (getPrecedence(currentChar) <= getPrecedence(stack[stackIndex])))
            {
                postfix[postfixIndex] = stack[stackIndex];
                postfixIndex = postfixIndex + 1;
                stackIndex = stackIndex - 1;
            }
            stackIndex = stackIndex + 1;
            stack[stackIndex] = currentChar;
        }
    }
    while (stackIndex >= 0)
    {
        postfix[postfixIndex] = stack[stackIndex];
        postfixIndex = postfixIndex + 1;
        stackIndex = stackIndex - 1;
    }
    postfix[postfixIndex] = '\0';
    return postfix;
}

/**
 * This function evaluates the operations in a given infix string, using the infix2postfix, addition, multiplication and transpose functions.
 * @param name: the name of the final result
 * @param expr: the infix string that contains all the functions to be evaluated
 * @param root: the root of the BST we will search for matrices in.
 * @return finalResult: the final matrix after completing all operations
 */
matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{
    char *postfix = infix2postfix_sf(expr);
    int len = strlen(postfix);
    matrix_sf *stack[len];
    for (int i = 0; i < len; i++)
    {
        stack[i] = NULL;
    }
    int stackIndex = -1;
    int i = 0;
    matrix_sf *free_list[len];
    int listLen = 0;

    while (postfix[i] != '\0')
    {
        if ((postfix[i] >= 'A' && postfix[i] <= 'Z') || (postfix[i] >= 'a' && postfix[i] <= 'z'))
        {
            matrix_sf *mat = find_bst_sf(postfix[i], root);
            stack[++stackIndex] = mat;
        }
        else if (postfix[i] == '+')
        {
            matrix_sf *popped2 = stack[stackIndex--];
            matrix_sf *popped1 = stack[stackIndex--];
            matrix_sf *result = add_mats_sf(popped1, popped2);
            free_list[listLen++] = result;
            stack[++stackIndex] = result;
        }
        else if (postfix[i] == '*')
        {
            matrix_sf *popped2 = stack[stackIndex--];
            matrix_sf *popped1 = stack[stackIndex--];
            matrix_sf *result = mult_mats_sf(popped1, popped2);
            free_list[listLen++] = result;
            stack[++stackIndex] = result;
        }
        else if (postfix[i] == '\'')
        {
            matrix_sf *popped = stack[stackIndex--];
            matrix_sf *result = transpose_mat_sf(popped);
            free_list[listLen++] = result;
            stack[++stackIndex] = result;
        }
        i++;
    }
    free(postfix);
    matrix_sf *finalResult = stack[stackIndex];
    finalResult->name = name;
    finalResult = full_copy_matrix(finalResult);
    for (int j = 0; j < listLen; j++)
    {
        free(free_list[j]);
    }
    return finalResult;
}

/**
 * This functions checks if a character is a Digit.
 * @param c: the character we are checking
 * @return: integer based on whether or not c is a digit
 */
int isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

/**
 * This functions skips all whitespace in a non-constant pointer.
 * @param str: the pointer in which we need to skip whitespaces in.
 * @return str: the pointer will now point to the next non-whitespace character
 */
char *skip_whitespace_pointer(char *str)
{
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
    {
        str++;
    }
    return str;
}

/**
 * This function executes matrix operations on matrices, as instructed by a script.
 * @param filename: a pointer to the file we are going to perform matrix operations on.
 * @return result: the final matrix after completing all operations
 * Caller is responsible for memory returned
 */
matrix_sf *execute_script_sf(char *filename)
{
    char *str = NULL;
    FILE *file = fopen(filename, "r");
    size_t max_line_size = MAX_LINE_LEN;
    ssize_t strSize = 0;
    matrix_sf *lastMatrix = NULL;
    bst_sf *root = NULL;

    while ((strSize = getline(&str, &max_line_size, file)) != -1)
    {
        char *cStr = str;
        cStr = skip_whitespace_pointer(cStr);
        char *name = malloc(sizeof(char));
        *name = str[0];
        cStr++;
        cStr = skip_whitespace_pointer(cStr);
        cStr++;
        cStr = skip_whitespace_pointer(cStr);
        if (isDigit(*cStr))
        {
            matrix_sf *mat = create_matrix_sf(*name, cStr);
            root = insert_bst_sf(mat, root);
            lastMatrix = mat;
        }
        else
        {
            matrix_sf *mat = evaluate_expr_sf(*name, cStr, root);
            root = insert_bst_sf(mat, root);
            lastMatrix = mat;
        }
        free(name);
    }
    fclose(file);
    matrix_sf *result = full_copy_matrix(lastMatrix);
    free_bst_sf(root);
    free(str);
    return result;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[])
{
    matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows * num_cols * sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat)
{
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++)
    {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows * mat->num_cols - 1)
            printf(" ");
    }
    printf("\n");
}
