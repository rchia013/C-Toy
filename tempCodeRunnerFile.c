
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        } else {
            if (strcmp(employee->name, root->employee->name) > 0)
                root->left = insertBSTNode(root->left, employee, sortBySalary,order);
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        }
    }

    return root;
}

void inOrderPrint(BSTNode *root) {
    if (root == NULL)
        return;
    inOrderPrint(root->left);
    printf("ID: %d, Name: %s, Department: %s, Position: %s, Salary: %.2f\n",