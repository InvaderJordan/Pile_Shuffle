/*
You are given a deck containing N cards.  While holding the deck facedown:

1. Deal all the cards facedown onto a table into Y piles (i.e. P1, P2, ..., PY).
2. Combine all the piles into a deck by placing P1 onto P2, then P1+P2 onto P3, and so on. This is a round.
3. Pick up the deck from the table and repeat steps 1-2 until the deck is in the original order.
4. For each round, vary the pile count according to a repeating pattern. Start with 3 piles, then 4, then 5, then loop back to 3, then 4 and so on.
	
Write a program to determine how many rounds it will take to put a deck back into the original order.  This will involve creating a data structure to represent the order of the cards. Do not use an array.
This program should be written in C only. It should take a number of cards in the deck as a command line argument and write the result to stdout.  Please ensure the program compiles and runs correctly (no pseudo-code).  
This isn't a trick question; it should be fairly straightforward.

Bonus: Output how many rounds should be completed before the deck is adequately shuffled from the original deck for a person who is casually playing a game with cards. Provide your methodology in a comment block.
*/

// Jordan Wagner
// 5/18/2020

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Structure of a card in the linked list deck
typedef struct card {
  // Value of the card, used for determining if the deck is back to original order
  uint32_t card_num;
  struct card *next;
} card_t;

// Checks if the deck is sorted (lowest card_num first)
bool is_sorted(card_t *deck) {
  if (deck == NULL) {
    printf("%s: deck is NULL!\r\n", __FUNCTION__);
    return false;
  }
  
  while (deck->next != NULL) {
    card_t *next = deck->next;
    if (deck->card_num >= next->card_num) {
      return false;
    }
    deck = deck->next;
  }
  
  return true;
}

// Prints out the deck in the current order
void print_deck(card_t *deck) {
  if (deck == NULL) {
    printf("%s: deck is NULL!\r\n", __FUNCTION__);
    return;
  }
  
  while (deck != NULL) {
    printf("%4u", deck->card_num);
    deck = deck->next;
  }
  printf("\r\n");
}

// Function for dealing cards into three piles
// Uses three stacks to push cards into, then just links all the stacks together and returns
card_t * three_piles(card_t *deck) {
  if (deck == NULL) {
    printf("%s: deck is NULL!\r\n", __FUNCTION__);
    return NULL;
  }
  // Pile stack pointers
  card_t *p1_stack = NULL, *p2_stack = NULL, *p3_stack = NULL;
  // Keep track of the bottom of piles 1 and 2 for rebuilding the deck
  card_t *p1_end = NULL, *p2_end = NULL;
  // Counter to keep track of which pile to add a card to
  uint32_t pile_count = 0;
  
  while (deck != NULL) {
    card_t * temp = deck->next;
    if (pile_count % 3 == 0) {
      if (p1_stack == NULL) {
        p1_stack = deck;
        p1_end = deck;
        p1_stack->next = NULL;
      } else {
        deck->next = p1_stack;
        p1_stack = deck;
      }
    } else if (pile_count % 3 == 1) {
      if (p2_stack == NULL) {
        p2_stack = deck;
        p2_end = deck;
        p2_stack->next = NULL;
      } else {
        deck->next = p2_stack;
        p2_stack = deck;
      }
    } else if (pile_count % 3 == 2) {
      if (p3_stack == NULL) {
        p3_stack = deck;
        p3_stack->next = NULL;
      } else {
        deck->next = p3_stack;
        p3_stack = deck;
      }
    }
    pile_count++;
    deck = temp;
  }
  
  // Rebuild the deck by simply pointing the bottom of p1 to the top of p2 and the bottom of p2 to the top of p3
  p1_end->next = p2_stack;
  p2_end->next = p3_stack;
  return p1_stack;
}

// Function for dealing cards into four piles
// Uses four stacks to push cards into, then just links all the stacks together and returns
card_t * four_piles(card_t *deck) {
  if (deck == NULL) {
    printf("%s: deck is NULL!\r\n", __FUNCTION__);
    return NULL;
  }
  // Pile stack pointers
  card_t *p1_stack = NULL, *p2_stack = NULL, *p3_stack = NULL, *p4_stack = NULL;
  // Keep track of the bottom of piles 1, 2, and 3 for rebuilding the deck
  card_t *p1_end = NULL, *p2_end = NULL, *p3_end = NULL;
  // Counter to keep track of which pile to add a card to
  uint32_t pile_count = 0;
  
  while (deck != NULL) {
    card_t * temp = deck->next;
    if (pile_count % 4 == 0) {
      if (p1_stack == NULL) {
        p1_stack = deck;
        p1_end = deck;
        p1_stack->next = NULL;
      } else {
        deck->next = p1_stack;
        p1_stack = deck;
      }
    } else if (pile_count % 4 == 1) {
      if (p2_stack == NULL) {
        p2_stack = deck;
        p2_end = deck;
        p2_stack->next = NULL;
      } else {
        deck->next = p2_stack;
        p2_stack = deck;
      }
    } else if (pile_count % 4 == 2) {
      if (p3_stack == NULL) {
        p3_stack = deck;
        p3_end = deck;
        p3_stack->next = NULL;
      } else {
        deck->next = p3_stack;
        p3_stack = deck;
      }
    } else if (pile_count % 4 == 3) {
      if (p4_stack == NULL) {
        p4_stack = deck;
        p4_stack->next = NULL;
      } else {
        deck->next = p4_stack;
        p4_stack = deck;
      }
    }
    pile_count++;
    deck = temp;
  }
  
  // Rebuild the deck by simply modifying the bottom of the stack pointers
  p1_end->next = p2_stack;
  p2_end->next = p3_stack;
  p3_end->next = p4_stack;
  return p1_stack;
}

// Function for dealing cards into five piles
// Uses five stacks to push cards into, then just links all the stacks together and returns
card_t * five_piles(card_t *deck) {
  if (deck == NULL) {
    printf("%s: deck is NULL!\r\n", __FUNCTION__);
    return NULL;
  }
  // Pile stack pointers
  card_t *p1_stack = NULL, *p2_stack = NULL, *p3_stack = NULL, *p4_stack = NULL, *p5_stack = NULL;
  // Keep track of the bottom of piles 1, 2, 3, and 4 for rebuilding the deck
  card_t *p1_end = NULL, *p2_end = NULL, *p3_end = NULL, *p4_end = NULL;
  // Counter to keep track of which pile to add a card to
  uint32_t pile_count = 0;
  
  while (deck != NULL) {
    card_t * temp = deck->next;
    if (pile_count % 5 == 0) {
      if (p1_stack == NULL) {
        p1_stack = deck;
        p1_end = deck;
        p1_stack->next = NULL;
      } else {
        deck->next = p1_stack;
        p1_stack = deck;
      }
    } else if (pile_count % 5 == 1) {
      if (p2_stack == NULL) {
        p2_stack = deck;
        p2_end = deck;
        p2_stack->next = NULL;
      } else {
        deck->next = p2_stack;
        p2_stack = deck;
      }
    } else if (pile_count % 5 == 2) {
      if (p3_stack == NULL) {
        p3_stack = deck;
        p3_end = deck;
        p3_stack->next = NULL;
      } else {
        deck->next = p3_stack;
        p3_stack = deck;
      }
    } else if (pile_count % 5 == 3) {
      if (p4_stack == NULL) {
        p4_stack = deck;
        p4_end = deck;
        p4_stack->next = NULL;
      } else {
        deck->next = p4_stack;
        p4_stack = deck;
      }
    } else if (pile_count % 5 == 4) {
      if (p5_stack == NULL) {
        p5_stack = deck;
        p5_stack->next = NULL;
      } else {
        deck->next = p5_stack;
        p5_stack = deck;
      }
    }
    pile_count++;
    deck = temp;
  }
  
  // Rebuild the deck by simply modifying the bottom of the stack pointers
  p1_end->next = p2_stack;
  p2_end->next = p3_stack;
  p3_end->next = p4_stack;
  p4_end->next = p5_stack;
  return p1_stack;
}

void main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <Deck Size>\r\n", argv[0]);
    return;
  }
  uint32_t deck_size = atoi(argv[1]);
  
  card_t *deck = NULL, *prev = NULL;
  for (uint32_t i = 0; i < deck_size; i++) {
    card_t *node = malloc(sizeof(card_t));
    if (node == NULL) {
      printf("Error allocating card #%u\r\n", i);
      return;
    }
    node->card_num = i;
    node->next = NULL;
    if (deck == NULL) {
      // Point the deck pointer to the first card
      deck = node;
    } else if (prev == NULL) {
      // Initialize prev to the first card in the deck
      prev = node;
      deck->next = node;
    } else {
      prev->next = node;
      prev = node;
    }
  }
  
  uint32_t shuffle_times = 0;
  //print_deck(deck);
  while (true) {
    deck = three_piles(deck);
    shuffle_times++;
    //print_deck(deck);
    if (is_sorted(deck)) {
      break;
    }
    deck = four_piles(deck);
    shuffle_times++;
    //print_deck(deck);
    if (is_sorted(deck)) {
      break;
    }
    deck = five_piles(deck);
    shuffle_times++;
    //print_deck(deck);
    if (is_sorted(deck)) {
      break;
    }
  }
  
  printf("Number of shuffles: %u\r\n", shuffle_times);
  
  while (deck != NULL) {
    card_t *next = deck->next;
    free(deck);
    deck = next;
  }
}
