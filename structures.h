/* MARGARIT Andrei - 315CD */

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// implementare heap cu arbori

typedef struct {
	int prior; // Item priority
	char *name; // Item d
}NodeData;

typedef struct node {
    NodeData value;
    struct node *left, *right;
} TreeNode, *Tree;

typedef struct heap {
	Tree *vector;
	int size;
	int capacity;
	int (*compare_func)(const void*, const void*);
} *Heap;

Heap initHeap(int capacity, int (*compare_func) (const void*, const void*)) {
	Heap h = (Heap)malloc(sizeof(struct heap));
	h->size = 0;
	h->capacity = capacity;
	h->vector = malloc(capacity * sizeof(Tree));
	h->compare_func = compare_func;
	return h;
}

Heap siftDown(Heap h, int index) {
	int minIndex = index;
	int l = index * 2 + 1;
	if (l < h->size && h->compare_func(&h->vector[l], &h->vector[minIndex]) > 0) {
		minIndex = l;
	}
	int r = index * 2 + 2;
	if (r < h->size && h->compare_func(&h->vector[r], &h->vector[minIndex]) > 0) {
		minIndex = r;
	}
	if (index != minIndex) {
		Tree aux = h->vector[index];
		h->vector[index] = h->vector[minIndex];
		h->vector[minIndex] = aux;
		h = siftDown(h, minIndex);
	}
	return h;
}

Heap siftUp(Heap h, int index) {
	while (index >= 0 && h->compare_func(&h->vector[(index - 1) / 2], &h->vector[index]) < 0) {
	Tree aux = h->vector[(index - 1) / 2];
	h->vector[(index - 1) / 2] = h->vector[index];
	h->vector[index] = aux;
	index = (index - 1) / 2;
	}
	return h;
}

Heap insertHeap(Heap h, Tree element) {
	if (h->size == h->capacity) {
		h->capacity *= 2;
		h->vector = realloc(h->vector, h->capacity * sizeof(Tree));
	}
	h->vector[h->size] = element;
	h = siftUp(h, h->size);
	h->size++;
	return h;
}

Tree extractMin(Heap h) {
	Tree min;
	if (h && h->size > 0) {
		min = h->vector[0];
		h->vector[0] = h->vector[h->size - 1];
		h->size--;
		h = siftDown(h, 0);
		return min;
	}
	return NULL;
}

int compare(const void *a, const void *b) {
	Tree *pa, *pb;
	pa = (Tree*) a;
	pb = (Tree*) b;
	Tree x, y;
	x = *pa;
	y = *pb;
	if (x->value.prior < y->value.prior || (strcmp(x->value.name, y->value.name) < 0 &&
		x->value.prior == y->value.prior)) {
		return 1;
	} else if (x->value.prior > y->value.prior || (strcmp(x->value.name, y->value.name) > 0 &&
		x->value.prior == y->value.prior)) {
		return -1;
	}
	return 0;
}

Tree createTree(NodeData value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value.prior = value.prior;
	root->value.name = malloc(sizeof(char) * (strlen(value.name) + 1));
	strcpy(root->value.name, value.name);
	root->left = NULL;
	root->right = NULL;
	return root;
}

int height(Tree root) {
	if (root == NULL || (root->left == NULL && root->right == NULL)) {
		return 0;
	}
	int left, right;
	left = height(root->left);
	right = height(root->right);
	if (left < right) {
		return right + 1;
	}
	return left + 1;
}

// functii de eliberare a memoriei pentru heap si arbore

void freeTree(Tree root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root->value.name);
		free(root);
	}
}

void freeHeap(Heap h) {
    if (h == NULL) {
        return;
    }
    for (int i = 0; i < h->size; i++) {
        freeTree(h->vector[i]);
    }
    free(h->vector);
    free(h);
}

// coada

typedef struct QueueNode {
	Tree treeNode;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue {
	QueueNode *front, *rear;
} Queue;

Queue* createQueue() {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

void enqueue(Queue *q, Tree treeNode) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	temp->treeNode = treeNode;
	temp->next = NULL;
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}
	q->rear->next = temp;
	q->rear = temp;
}

Tree dequeue(Queue *q) {
	if (q->front == NULL) {
		return NULL;
	}
	QueueNode *temp = q->front;
	Tree treeNode = temp->treeNode;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
	return treeNode;
}

int isQueueEmpty(Queue *q) {
	return q->front == NULL;
}

void freeQueue(Queue *q) {
    QueueNode *current = q->front;
    while (current != NULL) {
        QueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}

void bfs(Tree root, FILE *g) {
	if (root == NULL) {
		return;
	}
	int currentLevel = 0;
	Queue *q = createQueue();
	enqueue(q, root);
	enqueue(q, NULL);
	int firstInLevel = 1;
	while (!isQueueEmpty(q)) {
		Tree current = dequeue(q);
		if (current == NULL) {
			fprintf(g, "\n");
			currentLevel++;
			firstInLevel = 1;
			if (!isQueueEmpty(q)) {
				enqueue(q, NULL);
			}
		} else {
			if (!firstInLevel) {
				fprintf(g, " ");
			}
			fprintf(g, "%d-%s", current->value.prior, current->value.name);
			firstInLevel = 0;
			if (current->left != NULL) {
				enqueue(q, current->left);
			}
			if (current->right != NULL) {
				enqueue(q, current->right);
			}
		}
	}
	freeQueue(q);
}

#endif

