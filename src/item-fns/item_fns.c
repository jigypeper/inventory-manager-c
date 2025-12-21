#include "item_fns.h"
#include <stdio.h>
#include "read_line.h"
#include <stdlib.h>
#include <string.h>


item* create_item_node(item *part) {
  item* new_part = (item*) malloc(sizeof(item));
  if (new_part != NULL) {
    new_part = (item *) malloc(sizeof(item));
    new_part->left_part = NULL;
    new_part->right_part = NULL;
    new_part->part_number = part->part_number;
    strcpy(new_part->part_name, part->part_name);
    new_part->qty = part->qty;
  }
  return new_part;

}

item* insert_item_node(item *root, item *part) {
  if (root == NULL) {
    return create_item_node(part);
  }

  if (part->part_number < root->part_number) {
    root->left_part = insert_item_node(root->left_part, part);
  } else {
    root->right_part = insert_item_node(root->right_part, part);
  }
  return root;
}

item* search_item_node(item *root, int part_number) {
  if (root == NULL) {
    return root;
  }

  if (part_number == root->part_number) {
    return root;
  } else if (part_number < root->part_number) {
    return search_item_node(root->left_part, part_number);
  } else {
    return search_item_node(root->right_part, part_number);
  }
}

item* find_min(item *root) {
  if (root == NULL || root->left_part == NULL) {
    return root;
  }
  return find_min(root->left_part);
}

item* delete_item_node(item *root, int part_number) {
  if (root == NULL) {
    return root;
  }

  if (part_number < root->part_number) {
    root->left_part = delete_item_node(root->left_part, part_number);
  } else if (part_number > root->part_number) {
    root->right_part = delete_item_node(root->right_part, part_number);
  } else {
    if (root->left_part == NULL) {
      item* temp = root->right_part;
      free(root);
      return temp;
    } else if (root->right_part == NULL) {
      item* temp = root->left_part;
      free(root);
      return temp;
    } else {
      item* successor = find_min(root->right_part);
      root->part_number = successor->part_number;
      root->qty = successor->qty;
      strcpy(root->part_name, successor->part_name);
      root->right_part = delete_item_node(root->right_part, successor->part_number);
    }
  }

  return root;

}

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

void in_order_collect(item *root, item ***address_array, int *index, int *capacity) {
  if (root == NULL) {
	return;
  }

  if (*index >= *capacity) {
	*capacity *= 2;
    item **temp = (item **)realloc(*address_array, *capacity * sizeof(item *));
	*address_array = temp;
  }

  in_order_collect(root->left_part, address_array, index, capacity);
  (*address_array)[(*index)++] = root;
  in_order_collect(root->right_part, address_array, index, capacity);
}

item** build_item_array(item *root, int *array_length) {
  int count = 0, capacity = 10;
  item **item_array = (item**) malloc(capacity*sizeof(item*));

  in_order_collect(root, &item_array, &count, &capacity);
  *array_length = count;
  return item_array;
}

void print_item(item *root, int part_number) {
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
  //TODO: need to free the memory of the array after print completes?
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
}
