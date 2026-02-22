#include "commands/commands.h"
#include "item-fns/item_fns.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  printf("Welcome to your parts database\n");
  int command;
  item_t *root = NULL;

  item_t *(*commands[7])(item_t *root) = {
      *insert_item, *update_item,  *delete_item,  *print_item,
      *print_items, *import_items, *export_items,
  };

  while (true) {
    printf("Choose an option\n"
           "0: insert a part\n"
           "1: update a part\n"
           "2: delete a part\n"
           "3: print a part\n"
           "4: list all parts\n"
           "5: Import CSV\n"
           "6: Export parts to CSV\n"
           "7: quit\n");
   
    while (scanf("%d", &command) != 1) {
      while (getchar() != '\n')
        ;
      printf("Invalid input, please enter a number:\n");
    }
    
    if (command < 0 || command > 7) {
      printf("'%d' is not a valid option\n", command);
    }

    if (command == 7) {
      return 0;
    }

    root = commands[command](root);
  }

  return 0;
}
