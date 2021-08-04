#ifndef LIST_CARD_H
#define LIST_CARD_H

typedef struct Node Node;
struct Node // The card
{
    int suit;
    int rank;
    int value;

    Node *next;
};

Node *list_init_deck(void);
Node *list_pop_deck(Node **root);
void list_set_hand(Node **root, Node *node);
void list_return_deck(Node **deck, Node **hand);
int list_value_cards(Node *root);
void list_free(Node **root);
void list_print_card(Node *node);
void list_print_all_cards(Node *root);

#endif