#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node * next;
} ll_node;

void print_list(ll_node * head);
void push(ll_node * head, int value);
void add_first(ll_node ** head, int value);
int pop_first(ll_node ** head);
int pop(ll_node * head);
int pop_index(ll_node ** head, int n);
int pop_by_value(ll_node ** head, int search_value);

int main (void) {
    ll_node * head = NULL;
    head = malloc(sizeof(ll_node));
    if (head == NULL) {
        return 1;
    }

    head->value = 1;
    head->next = malloc(sizeof(ll_node));
    head->next->value = 2;
    head->next->next = NULL;

    print_list(head);
;
    push(head, 3);
    printf("Updated list: \n");
    print_list(head);

    printf("Adding to start: \n");
    add_first(&head, 0);
    print_list(head);

    printf("Popping first element: \n");
    pop_first(&head);
    print_list(head);

    printf("Popping item: \n");
    int popped_value = pop(head);
    printf("Popped value: %d\n", popped_value);
    print_list(head);

    printf("Popping item by index: \n");
    popped_value = pop_index(&head, 1);
    printf("Popped value: %d\n", popped_value);
    print_list(head);

    printf("Popping item by value: \n");
    pop_by_value(&head, 1);
    print_list(head);
    return 0;
}

void print_list(ll_node * head) {
    ll_node * current = head;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void push(ll_node * head, int value) {
    ll_node * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(ll_node));
    current->next->value = value;
    current->next->next = NULL;
}

void add_first(ll_node ** head, int value) {
    ll_node * new_head = malloc(sizeof(ll_node));

    new_head->value = value;
    new_head->next = *head;
    *head = new_head;
}

int pop_first(ll_node ** head) {
    ll_node * second_node = NULL;
    int return_value = -1;

    if (*head != NULL) {
        return_value = (*head)->value;
        second_node = (*head)->next;
        free(*head);
        *head = second_node;
    }
    return return_value;
}

int pop(ll_node * head) {
    ll_node * current = head;
    int return_value = -1;


    if (head == NULL) {
        return return_value;
    }

    /* If only one item in the list exists, remove it. */
    if (head->next == NULL) {
        return_value = head->value;
        free(head);
        return return_value;
    }

    /* Find second to the last node. */
    while (current->next->next != NULL) {
        current = current->next;
    }
    /* Reached second to the last item. */
    return_value = current->next->value;
    free(current->next);
    current->next = NULL;
    return return_value;
}

int pop_index(ll_node ** head, int n) {
    int i;
    int return_value = -1;

    ll_node * current = *head;
    ll_node * temp_node = NULL;

    if (n == 0) {
        return pop_first(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    return_value = temp_node->value;
    current->next = temp_node->next;
    free(temp_node);

    return return_value;
}

int pop_by_value(ll_node ** head, int search_value) {
    int return_value = -1;
    
    ll_node * current = *head;
    ll_node * temp_node = NULL;

    /* If head contains the search value, pop it. */
    if ((*head)->value == search_value) {
        return pop_first(head);
    }

    while (current->next->value != search_value) {
        if (current->next == NULL) {
            return return_value;
        }
        current = current->next;
    }

    temp_node = current->next;
    return_value = temp_node->value;
    current->next = temp_node->next;
    free(temp_node);

    return return_value; 
}