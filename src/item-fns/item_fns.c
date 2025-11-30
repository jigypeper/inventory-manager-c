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
