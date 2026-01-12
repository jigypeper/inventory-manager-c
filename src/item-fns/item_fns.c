#include "item_fns.h"
#include <stdio.h>
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

