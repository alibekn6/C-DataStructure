#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


typedef struct {
    Node* head;
    Node* tail;   
    size_t size;          
} LinkedList;


LinkedList* list_create(void) {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL; // failed
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}


Node* node_create(int data) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL; // falied
    }
    
    node->data = data;
    node->next = NULL;
    
    return node;
}

bool is_empty(const LinkedList* list) {
    if (list == NULL) {
        return true;
    }
    return list->size == 0;
}


size_t size(const LinkedList* list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}



 // adding to the start (true false)
bool prepend(LinkedList* list, int data) {
    if (list == NULL) {
        return false;
    }
    
    Node* node = node_create(data);
    if (node == NULL) {
        return false;
    }
    
    if (list->head == NULL) {
        // list is empty
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    
    list->size++;
    return true;
}

// adding to the end (true false)
bool append(LinkedList* list, int data) {
    if (list == NULL) {
        return false;
    }
    
    Node* node = node_create(data);
    if (node == NULL) {
        return false;
    }
    
    if (list->head == NULL) {
        // list is empty
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    
    list->size++;
    return true;
}




bool insert(LinkedList* list, int data, size_t position) {
    if (list == NULL || position > list->size) {
        return false;
    }
    
    // handle special cases
    if (position == 0) {
        return prepend(list, data);
    } else if (position == list->size) {
        return append(list, data);
    }
    
    Node* node = node_create(data);
    if (node == NULL) {
        return false;
    }
    
    // Find the node before the insertion point
    Node* current = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    node->next = current->next;
    current->next = node;
    list->size++;
    
    return true;
}

bool list_remove_first(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return false;
    }
    
    Node* removed_node = list->head;
    list->head = list->head->next;
    
    // If the list becomes empty, update the tail
    if (list->head == NULL) {
        list->tail = NULL;
    }
    
    free(removed_node);
    list->size--;
    
    return true;
}




bool removeAt(LinkedList* list, size_t position) {
    if (list == NULL || list->head == NULL || position >= list->size) {
        return false;
    }


    if (position == 0) {
        return list_remove_first(list);
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* to_remove = current->next;

    if (to_remove == list->tail) {
        list->tail = current;
        current->next = NULL;
    } else {
        current->next = to_remove->next;
    }
    
    free(to_remove);
    list->size--;
    
    return true;
}



//  Get the value at a specific position 
bool list_get_at(const LinkedList* list, size_t position, int* out) {
    if (list == NULL || position >= list->size || out == NULL) {
        return false;
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < position; i++) {
        current = current->next;
    }
    
    *out = current->data;
    return true;
}


int get(const LinkedList* list, size_t position) {
    Node* current = list->head;
    for (size_t i = 0; i < position; i++) {
        current = current->next;
    }
    
    return current->data;
}


void destroy(LinkedList* list) {
    if (list == NULL) {
        return;
    }
    
   
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}


void print(const LinkedList* list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }
    
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node* current = list->head;
    printf("List [%zu]: ", list->size);
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}


int main() {

    LinkedList* list = list_create();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }
    
    // add elements
    append(list, 10);
    append(list, 20);
    append(list, 5);
    insert(list, 15, 2);
    

    print(list);  // expected: 5 -> 10 -> 15 -> 20
    
    // get element at position 2
    int value;
    if (list_get_at(list, 2, &value)) {
        printf("Value at position 2: %d\n", value);  // Expected: 15
    }
    
    // remove elements (index)

    removeAt(list, 1);

    
    // Print the updated list
    print(list);  // Expected: List [2]: 10 -> 15
    
    // Clean up
    destroy(list);
    
    return EXIT_SUCCESS;
}