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

// Checks if the deck is sorted by comparing each value to it's index in the deck
bool is_sorted(uint32_t * deck, uint32_t deck_size) {
  for (uint32_t i = 0; i < deck_size; i++) {
    if (deck[i] != i) {
      return false;
    }
  }
  
  return true;
}

// Prints out the deck in the current order
void print_deck(uint32_t * deck, uint32_t deck_size) {
  for (uint32_t i = 0; i < deck_size; i++) {
    printf("%4u", deck[i]);
  }
  printf("\r\n");
}

// Function for dealing cards into three piles
void three_piles(uint32_t * deck, uint32_t * pile1, uint32_t * pile2, uint32_t * pile3, uint32_t deck_size) {
  // Pile indexes
  uint32_t p1 = 0, p2 = 0, p3 = 0;
  for(uint32_t i = 0; i < deck_size; i++) {
    if ((i % 3) == 0) {
      pile1[p1++] = deck[i];
    } else if ((i % 3) == 1) {
      pile2[p2++] = deck[i];
    } else if ((i % 3) == 2) {
      pile3[p3++] = deck[i];
    }
  }
  
  // Copy each pile back to the deck in "reverse" order
  // Each pile is essentially a stack, so this preserves the LIFO ordering
  uint32_t deck_ptr = 0;
  for(uint32_t i = p1; i > 0; i--) {
    deck[deck_ptr++] = pile1[i - 1];
  }
  for(uint32_t i = p2; i > 0; i--) {
    deck[deck_ptr++] = pile2[i - 1];
  }
  for(uint32_t i = p3; i > 0; i--) {
    deck[deck_ptr++] = pile3[i - 1];
  }
}

// Function for dealing cards into four piles
void four_piles(uint32_t * deck, uint32_t * pile1, uint32_t * pile2, uint32_t * pile3, uint32_t * pile4, uint32_t deck_size) {
  // Pile indexes
  uint32_t p1 = 0, p2 = 0, p3 = 0, p4 = 0;
  for(uint32_t i = 0; i < deck_size; i++) {
    if ((i % 4) == 0) {
      pile1[p1++] = deck[i];
    } else if ((i % 4) == 1) {
      pile2[p2++] = deck[i];
    } else if ((i % 4) == 2) {
      pile3[p3++] = deck[i];
    } else if ((i % 4) == 3) {
      pile4[p4++] = deck[i];
    }
  }
  
  // Copy each pile back to the deck in "reverse" order
  // Each pile is essentially a stack, so this preserves the LIFO ordering
  uint32_t deck_ptr = 0;
  for(uint32_t i = p1; i > 0; i--) {
    deck[deck_ptr++] = pile1[i - 1];
  }
  for(uint32_t i = p2; i > 0; i--) {
    deck[deck_ptr++] = pile2[i - 1];
  }
  for(uint32_t i = p3; i > 0; i--) {
    deck[deck_ptr++] = pile3[i - 1];
  }
  for(uint32_t i = p4; i > 0; i--) {
    deck[deck_ptr++] = pile4[i - 1];
  }
}

// Function for dealing cards into five piles
void five_piles(uint32_t * deck, uint32_t * pile1, uint32_t * pile2, uint32_t * pile3, uint32_t * pile4, uint32_t * pile5, uint32_t deck_size) {
  // Pile indexes
  uint32_t p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
  for(uint32_t i = 0; i < deck_size; i++) {
    if ((i % 5) == 0) {
      pile1[p1++] = deck[i];
    } else if ((i % 5) == 1) {
      pile2[p2++] = deck[i];
    } else if ((i % 5) == 2) {
      pile3[p3++] = deck[i];
    } else if ((i % 5) == 3) {
      pile4[p4++] = deck[i];
    } else if ((i % 5) == 4) {
      pile5[p5++] = deck[i];
    }
  }
  
  // Copy each pile back to the deck in "reverse" order
  // Each pile is essentially a stack, so this preserves the LIFO ordering
  uint32_t deck_ptr = 0;
  for(uint32_t i = p1; i > 0; i--) {
    deck[deck_ptr++] = pile1[i - 1];
  }
  for(uint32_t i = p2; i > 0; i--) {
    deck[deck_ptr++] = pile2[i - 1];
  }
  for(uint32_t i = p3; i > 0; i--) {
    deck[deck_ptr++] = pile3[i - 1];
  }
  for(uint32_t i = p4; i > 0; i--) {
    deck[deck_ptr++] = pile4[i - 1];
  }
  for(uint32_t i = p5; i > 0; i--) {
    deck[deck_ptr++] = pile5[i - 1];
  }
}

void main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <Deck Size>\r\n", argv[0]);
    return;
  }
  uint32_t deck_size = atoi(argv[1]);
  
  uint32_t * deck = (uint32_t *)malloc(deck_size * sizeof(uint32_t));
  // Each of the first three piles will hold at most a third of the deck (rounded up)
  uint32_t * pile1 = (uint32_t *)malloc(((deck_size / 3) + 1) * sizeof(uint32_t));
  uint32_t * pile2 = (uint32_t *)malloc(((deck_size / 3) + 1) * sizeof(uint32_t));
  uint32_t * pile3 = (uint32_t *)malloc(((deck_size / 3) + 1) * sizeof(uint32_t));
  // The fourth pile will need to hold 1/4th of the deck at most (rounded up)
  uint32_t * pile4 = (uint32_t *)malloc(((deck_size / 4) + 1) * sizeof(uint32_t));
  // The fifth pile will only need to hold 1/5th of the deck (rounded up)
  uint32_t * pile5 = (uint32_t *)malloc(((deck_size / 5) + 1) * sizeof(uint32_t));
  if (deck == NULL || pile1 == NULL || pile2 == NULL || pile3 == NULL || pile4 == NULL || pile5 == NULL) {
    free(deck);
    free(pile1);
    free(pile2);
    free(pile3);
    free(pile4);
    free(pile5);
    printf("Error allocating memory!\r\n");
    return;
  }
  
  for (uint32_t i = 0; i < deck_size; i++) {
    // Set each card value to be the same as it's index
    deck[i] = i;
  }
  
  uint32_t shuffle_times = 0;
  //print_deck(deck, deck_size);
  
  while(true) {
    three_piles(deck, pile1, pile2, pile3, deck_size);
    shuffle_times++;
    //print_deck(deck, deck_size);
    if (is_sorted(deck, deck_size)) {
      break;
    }
    four_piles(deck, pile1, pile2, pile3, pile4, deck_size);
    shuffle_times++;
    //print_deck(deck, deck_size);
    if (is_sorted(deck, deck_size)) {
      break;
    }
    five_piles(deck, pile1, pile2, pile3, pile4, pile5, deck_size);
    shuffle_times++;
    //print_deck(deck, deck_size);
    if (is_sorted(deck, deck_size)) {
      break;
    }
  }
  
  printf("Number of shuffles: %u\r\n", shuffle_times);
  
  free(deck);
  free(pile1);
  free(pile2);
  free(pile3);
  free(pile4);
  free(pile5);
}
