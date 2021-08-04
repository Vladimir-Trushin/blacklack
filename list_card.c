#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list_card.h"

static char *suit[] = {"Hearts", "Dimonds", "Clubs", "Spades"};
static char *rank[] = {
    "",
    "Ace",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King"};

static size_t list_len; // count of cards in the deck

////-------------------------------------------------
// Builds a list of deck cards
Node *list_init_deck(void)
{
    srand(time(NULL));

    Node *root = malloc(sizeof(Node));
    if (!root)
    {
        puts("allocation error");
        exit(1);
    }
    root->suit = 0;
    root->rank = 1;
    root->value = 1;

    Node *node = root;
    for (size_t i = 1; i < 52; i++)
    {
        node->next = malloc(sizeof(Node));
        node = node->next;
        if (!node)
        {
            puts("allocation error");
            exit(1);
        }

        node->suit = i % 4;      // suit
        node->rank = i % 13 + 1; // rank

        if (i % 13 + 1 < 10) // value
            node->value = i % 13 + 1;
        else
            node->value = 10;
    }

    node->next = NULL;
    list_len = 52;

    return root;
}

////-------------------------------------------------
// Get a card from the deck in the index position
static Node *list_get(Node **root, int num)
{
    Node *node_index = NULL;
    Node *node_before = NULL;

    if (num == 0)
    {
        node_index = *root;
        *root = (*root)->next;
        node_index->next = NULL;
        list_len--;

        return node_index;
    }

    node_index = *root;

    for (size_t i = 0; i < num; i++)
    {
        node_before = node_index;
        node_index = node_index->next;
    }

    node_before->next = node_index->next;
    node_index->next = NULL;
    list_len--;

    return node_index;
}

////-------------------------------------------------
// Set a card to the deck in the index position
static void list_set(Node **root, Node *node, int num)
{
    Node *node_index = NULL;
    Node *node_before = NULL;

    if (num == 0)
    {
        node->next = *root;
        *root = node;
        list_len++;

        return;
    }

    node_index = *root;

    for (size_t i = 0; i < num; i++)
    {
        node_before = node_index;
        node_index = node_index->next;
    }

    node_before->next = node;
    node->next = node_index;
    list_len++;
}

////-------------------------------------------------
// Get a random card from the deck
Node *list_pop_deck(Node **root)
{
    return list_get(root, rand() % list_len);
}

////-------------------------------------------------
// Set a card to the deck in random position
static void list_push_deck(Node **root, Node *node)
{
    list_set(root, node, rand() % list_len);
}

////-------------------------------------------------
// Add a card to the hand
void list_set_hand(Node **root, Node *node)
{
    if (!*root)
    {
        *root = node;
        (*root)->next = NULL;
        return;
    }

    node->next = *root;
    *root = node;
}

////-------------------------------------------------
//  Return cards fro a hand to the deck
void list_return_deck(Node **deck, Node **hand)
{
    Node *curent = *hand;
    Node *next = NULL;

    while (curent)
    {
        next = curent->next;
        list_push_deck(deck, curent);
        curent = next;
    }

    *hand = NULL;
}

////-------------------------------------------------
// Calculate the value of the cards
int list_value_cards(Node *root)
{
    int counter = 0;
    int rank = 0;

    Node *node = root;

    while (node)
    {
        if (node->value == 1)
        {
            rank += 11;
            counter++;
        }
        else
        {
            rank += node->value;
        }

        node = node->next;
    }

    while (rank > 21 && counter > 0)
    {
        rank -= 10;
        counter--;
    }

    return rank;
}

////-------------------------------------------------
// Delete the list
void list_free(Node **root)
{
    Node *curent = *root;
    Node *next = NULL;

    while (curent)
    {
        next = curent->next;
        free(curent);
        curent = next;
    }

    *root = NULL;
}

////-------------------------------------------------
// Print a card
void list_print_card(Node *node)
{
    printf("suit: %s rank: %s value: %d\n", suit[node->suit], rank[node->rank],
           (node->value == 1) ? 11 : node->value);
}

////-------------------------------------------------
// Print all cards in the hand
void list_print_all_cards(Node *root)
{
    while (root->next)
    {
        list_print_card(root);
        root = root->next;
    }

    list_print_card(root);
}