#include "commands.h"
#include <stdio.h>
#include "../item-fns/read_line.h"
#include <stdlib.h>
#include <string.h>

item* insert_item(item *root) {
  item *part = malloc(sizeof(item));

  printf("Part no.: ");
  scanf("%d", &part->part_number);

  printf("Part name: ");
  read_line(part->part_name, NAME_LEN);

  printf("Quantity: ");
  scanf("%d", &part->qty);

if (search_item_node(root, part->part_number) == NULL){
    // Update root, not part
    root = insert_item_node(root, part);
  } else {
    printf("Part [%d] already exists\n", part->part_number);
    // Free the allocated memory since we're not using it
    free(part);
  }
  // Always return the root
  return root;
}

//TODO: need to think of the best way to handle updates, should the user be able to choose what they want to update before giving the options? Or do we check for which items have been populated?
item* update_item(item *root) {
  item* existing_part = NULL;
  int part_number, new_part_number, new_qty;
  char new_part_name[NAME_LEN];

  printf("Which part do you want to update? [part no.]: ");
  scanf("%d", &part_number);
  existing_part = search_item_node(root, part_number);

  if (existing_part != NULL) {

    printf("Part no.: ");
    scanf("%d", &new_part_number);

    printf("New Part name: ");
    read_line(new_part_name, NAME_LEN);

    printf("Quantity: ");
    scanf("%d", &new_qty);

    strcpy(existing_part->part_name, new_part_name);
    existing_part->part_number = new_part_number;
    existing_part->qty = new_qty;

    return root;
  }

  printf("Part [%d] does not exist in the database, please add it.\n", part_number);
  return root;
}

item* delete_item(item *root) {
  item* existing_part = NULL;
  int part_number;

  printf("Which part do you want to delete? [part no.]: ");
  scanf("%d", &part_number);
  existing_part = search_item_node(root, part_number);

  if (existing_part != NULL) {

    root = delete_item_node(root, part_number);

    return root;
  }

  printf("Part [%d] does not exist in the database, can't delete it\n", part_number);
  return root;
}

void print_item(item *root) {
  int part_number;
  printf("part number: ");
  scanf("%d", &part_number);
  item *result = search_item_node(root, part_number);
  if (result == NULL) {
    printf("Can't find item: %d\n", part_number);
  } else {
    printf("┌───────────┬─────────────────────────┬────────┐\n");
    printf("│ %-9s │ %-23s │ %-6s │\n", "Part No.", "Part Name", "Qty");
    printf("├───────────┼─────────────────────────┼────────┤\n");
    printf("│ %-9d │ %-23s │ %-6d │\n", result->part_number, result->part_name, result->qty);
    printf("└───────────┴─────────────────────────┴────────┘\n");
  }
}

void print_items(item *root) {
  int array_length = 0;
  item **inventory = build_item_array(root, &array_length);

  if (array_length == 0) {
    printf("No items in the database! Please add some\n");
	return;
  }

  printf("┌───────────┬─────────────────────────┬────────┐\n");
  printf("│ %-9s │ %-23s │ %-6s │\n", "Part No.", "Part Name", "Qty");

  for (int i = 0; i < array_length; i++) {
	printf("├───────────┼─────────────────────────┼────────┤\n");
	printf("│ %-9d │ %-23s │ %-6d │\n", inventory[i]->part_number, inventory[i]->part_name, inventory[i]->qty);
  }

  printf("└───────────┴─────────────────────────┴────────┘\n");
  free(inventory);
}
