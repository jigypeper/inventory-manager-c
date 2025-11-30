#include <stdio.h>
#include <stdbool.h>
#include "item-fns/item_fns.h"

int main(void) {
  printf("Welcome to your parts database\n");
  char command;
  item *root = NULL;
  int part_number;

  while (true) {
    printf("Choose an option\ni: insert a part\np: print a part\nq: quit\n");
    scanf(" %c", &command);
    switch (command) {
      case 'i':
      case 'I':
        root = insert_item(root);
        break;
      case 'p':
      case 'P':
        printf("part number: ");
        scanf("%d", &part_number);
        print_item(root, part_number);
        break;
      case 'q':
      case 'Q':
        return 0;
        break;
    }
  }

  return 0;
}
