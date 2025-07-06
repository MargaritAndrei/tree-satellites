/* MARGARIT Andrei - 315CD */

#include "structures.h"
#include <stdio.h>
#define MAX_LENGTH 17

Heap make_tree(FILE *f) {
    int n, i;
    fscanf(f, "%d\n", &n);
    Heap h = initHeap(n, compare);
    NodeData x;
    x.name = malloc(MAX_LENGTH * sizeof(char));
    for (i = 0; i < n; i++) {
        fscanf(f, "%d %s\n", &x.prior, x.name);
        Tree copacel = createTree(x);
        insertHeap(h, copacel);
    }
    free(x.name);
    for (i = 0; i < n - 1; i++) {
        Tree copacel1 = extractMin(h);
        Tree copacel2 = extractMin(h);
        x.prior = copacel1->value.prior + copacel2->value.prior;
        x.name = malloc((strlen(copacel1->value.name) + strlen(copacel2->value.name) + 1) * sizeof(char));
        strcpy(x.name, copacel1->value.name);
        strcat(x.name, copacel2->value.name);
        Tree new_root = createTree(x);
        free(x.name);
        new_root->left = copacel1;
        new_root->right = copacel2;
        insertHeap(h, new_root);
    }
    return h;
}

void first_task(Tree root, FILE *g) {
    bfs(root, g);
}

void second_task(Tree root, FILE *f, FILE *g) {
    int n, i, j, m;
    fscanf(f, "%d\n", &n);
    char x[1002];
    Tree current = root;
    for (i = 0; i < n; i++) {
        fscanf(f, "%s\n", x);
        m = strlen(x);
        current = root;
        for (j = 0; j < m; j++) {
            if (current->left == NULL && current->right == NULL) {
                fprintf(g, "%s ", current->value.name);
                current = root;
            }
            if (x[j] == '0') {
                current = current->left;
            } else if (x[j] == '1') {
                current = current->right;
            }
        }
        if (current->left == NULL && current->right == NULL) {
            fprintf(g, "%s", current->value.name);
        }
        fprintf(g, "\n");
    }
}

void dfs(Tree root, char x[], char *y, FILE *g) {
    if (strcmp(root->value.name, x) == 0) {
        fprintf(g, "%s", y);
        return;
    }
    if (root->left != NULL) {
        char *left;
        left = malloc(1002 * sizeof(char));
        strcpy(left, y);
        strcat(left, "0");
        dfs(root->left, x, left, g);
        free(left);
    }
    if (root->right != NULL) {
        char *right;
        right = malloc(1002 * sizeof(char));
        strcpy(right, y);
        strcat(right, "1");
        dfs(root->right, x, right, g);
        free(right);
    }
}

void third_task(Tree root, FILE *f, FILE *g) {
    int n, i;
    fscanf(f, "%d\n", &n);
    char x[1002];
    for (i = 0; i < n; i++) {
        fscanf(f, "%s\n", x);
        dfs(root, x, "", g);
    }
}

int find(Tree root, char *target) {
	if (root == NULL) {
        return 0;
    }
	if (strcmp(root->value.name, target) == 0) {
        return 1;
    }
	return find(root->left, target) || find(root->right, target);
}

int count_matches(Tree root, char **names, int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (find(root, names[i])) {
			count++;
		}
	}
	return count;
}

Tree find_lca(Tree root, char **names, int n) {
	if (root == NULL) {
        return NULL;
    }
	if (count_matches(root, names, n) < n) {
        return NULL;
    }
	Tree left = find_lca(root->left, names, n);
	Tree right = find_lca(root->right, names, n);
	if (left && count_matches(left, names, n) == n) {
        return left;
    }
	if (right && count_matches(right, names, n) == n) {
        return right;
    }
	return root;
}

void fourth_task(Tree root, FILE *f, FILE *g) {
	int n;
	fscanf(f, "%d\n", &n);
	char **names = malloc(n * sizeof(char *));
	for (int i = 0; i < n; i++) {
		names[i] = malloc(MAX_LENGTH * sizeof(char));
		fscanf(f, "%s\n", names[i]);
	}
	Tree result = find_lca(root, names, n);
	fprintf(g, "%s\n", result->value.name);
	for (int i = 0; i < n; i++) {
		free(names[i]);
	}
	free(names);
}

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[2], "r");
    FILE *g = fopen(argv[3], "w");
    int task = argv[1][2] - '0';
    Heap h = make_tree(f);
    Tree root = h->vector[0]; 
    if (task == 1) {
        first_task(root, g);
    } else if (task == 2) {
        second_task(root, f, g);
    } else if (task == 3) {
        third_task(root, f, g);
    } else if (task == 4) {
        fourth_task(root, f, g);
    }
    fclose(f);
    fclose(g);
    freeHeap(h);
    return 0;
}
