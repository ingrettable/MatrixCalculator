# Matrix Operations Library ReadMe

## Overview

The Matrix Operations Library (`hw6.h`) provides a set of functions for performing various operations on matrices in a C environment. These operations include matrix creation, addition, multiplication, transposition, evaluation of expressions, and more. The library is designed to facilitate matrix manipulation and computation within C programs.

## Functions

### 1. `full_copy_matrix(const matrix_sf *a)`

- **Description:** Fully copies a matrix into another matrix using dynamic memory allocation.
- **Parameters:**
  - `a`: Pointer to the matrix that needs to be copied.
- **Returns:** Pointer to the copied matrix.

### 2. `insert_bst_sf(matrix_sf *mat, bst_sf *root)`

- **Description:** Inserts a matrix into a Binary Search Tree (BST) based on the matrix name.
- **Parameters:**
  - `mat`: Pointer to the matrix to be added to the BST.
  - `root`: Pointer to the root of the BST.
- **Returns:** Pointer to the root of the updated BST.

### 3. `find_bst_sf(char name, bst_sf *root)`

- **Description:** Finds a matrix by name in a Binary Search Tree (BST).
- **Parameters:**
  - `name`: The name of the matrix being searched for.
  - `root`: Pointer to the root of the BST.
- **Returns:** Pointer to the matrix found, or NULL if not found.

### 4. `free_bst_sf(bst_sf *root)`

- **Description:** Frees memory allocated for all matrices in a BST.
- **Parameters:**
  - `root`: Pointer to the root of the BST.
- **Returns:** Void.

### 5. `add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)`

- **Description:** Adds the contents of two matrices together.
- **Parameters:**
  - `mat1`: Pointer to the first matrix.
  - `mat2`: Pointer to the second matrix.
- **Returns:** Pointer to the resulting matrix.

### 6. `mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)`

- **Description:** Multiplies two matrices.
- **Parameters:**
  - `mat1`: Pointer to the first matrix.
  - `mat2`: Pointer to the second matrix.
- **Returns:** Pointer to the resulting matrix.

### 7. `transpose_mat_sf(const matrix_sf *mat)`

- **Description:** Transposes a matrix.
- **Parameters:**
  - `mat`: Pointer to the matrix to be transposed.
- **Returns:** Pointer to the transposed matrix.

### 8. `infix2postfix_sf(char *infix)`

- **Description:** Converts an infix expression to a postfix expression.
- **Parameters:**
  - `infix`: Pointer to the infix expression string.
- **Returns:** Pointer to the postfix expression string.

### 9. `evaluate_expr_sf(char name, char *expr, bst_sf *root)`

- **Description:** Evaluates matrix operations expressed in an infix string.
- **Parameters:**
  - `name`: Name of the final result matrix.
  - `expr`: Pointer to the infix string containing operations.
  - `root`: Pointer to the root of the BST containing matrices.
- **Returns:** Pointer to the final result matrix.

### 10. `execute_script_sf(char *filename)`

- **Description:** Executes matrix operations specified in a script file.
- **Parameters:**
  - `filename`: Pointer to the script file containing matrix operations.
- **Returns:** Pointer to the final result matrix.

## Usage

- Include the `hw6.h` header file in your C program.
- Compile your program with the Matrix Operations Library.
- Utilize the provided functions for matrix manipulation and computation within your program.

## Dependencies

- Standard C libraries are used for memory allocation, string manipulation, file I/O, and other basic operations.
