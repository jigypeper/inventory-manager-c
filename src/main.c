#include <stdio.h>
#include <stdbool.h>
#include "item-fns/item_fns.h"
#include "commands/commands.h"

int main(void) {
  printf("Welcome to your parts database\n");
  int command;
  item *root = NULL;

  item* (*commands[5])(item *root) = {
    *insert_item,
    *update_item,
    *delete_item,
    *print_item,
    *print_items
  };

  // TODO: Abstract switch case to an array of function pointers
  // user chooses a number and this indexes to array and runs functions,
  // might make the update options later on more ergonomic.
  // NOTE: all command functions will need same signature and return

  while (true) {
    printf("Choose an option\n0: insert a part\n1: update a part\n2: delete a part\n3: print a part\n4: list all parts\n5: quit\n");
    scanf("%d", &command);
    if (command < 0 || command > 5) {
      printf("\'%d\' is not a valid option\n", command);
    }
    
    if (command == 5) {
      return 0;
    }
    
    root = commands[command](root);
  }

  return 0;
}
