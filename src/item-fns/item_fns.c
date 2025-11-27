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
    return NULL;
  }

  if (part_number == root->part_number) {
    return root;
  } else if (part_number < root->part_number) {
    return search_item_node(root->left_part, part_number);
  } else {
    return search_item_node(root->right_part, part_number);
  }
}

void insert_item(item *root) {
  item *part;
  
  printf("Part no.: ");
  scanf("%d", &part->part_number);

  printf("Part name: ");
  read_line(part->part_name, NAME_LEN);

  if (search_item_node(root, part->part_number) == NULL){
    insert_item_node(root, part);
  } else {
    printf("Part [%d] already exists\n", part->part_number);
  }
}
