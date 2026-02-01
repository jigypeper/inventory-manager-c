#include <stdio.h>
#include <stdbool.h>
#include "item-fns/item_fns.h"
#include "commands/commands.h"

int main(void) {
  printf("Welcome to your parts database\n");
  int command;
  item *root = NULL;

  item *(*commands[7])(item *root) = {
    *insert_item,
    *update_item,
    *delete_item,
    *print_item,
    *print_items,
    *import_items,
    *export_items,
  };

  while (true) {
    printf("Choose an option\n0: insert a part\n1: update a part\n2: delete a part\n3: print a part\n4: list all parts\n5: Import CSV\n6:Export parts to CSV\n7: quit\n");
    scanf("%d", &command);
    if (command < 0 || command > 7) {
      printf("\'%d\' is not a valid option\n", command);
    }
    
    if (command == 7) {
      return 0;
    }
    
    root = commands[command](root);
  }

  return 0;
}
