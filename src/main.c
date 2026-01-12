#include <stdio.h>
#include <stdbool.h>
#include "item-fns/item_fns.h"
#include "commands/commands.h"

int main(void) {
  printf("Welcome to your parts database\n");
  char command;
  item *root = NULL;

  // TODO: Abstract switch case to an array of function pointers
  // user chooses a number and this indexes to array and runs functions,
  // might make the update options later on more ergonomic.
  // NOTE: all command functions will need same signature and return

  while (true) {
    printf("Choose an option\ni: insert a part\nu: update a part\nd: delete a part\np: print a part\nl: list all parts\nq: quit\n");
    scanf(" %c", &command);
    switch (command) {
      case 'i':
      case 'I':
        root = insert_item(root);
        break;
      case 'u':
      case 'U':
        root = update_item(root);
        break;
      case 'd':
      case 'D':
        root = delete_item(root);
        break;
      case 'p':
      case 'P':
        print_item(root);
        break;
      case 'l':
      case 'L':
        print_items(root);
		break;
      case 'q':
      case 'Q':
        return 0;
        break;
      default:
        printf("\'%c\' is not a valid option\n", command);
        break;
    }
  }

  return 0;
}
