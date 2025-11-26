#ifndef ITEM_FNS_H
#define ITEM_FNS_H

#define NAME_LEN 25

// binary search tree for ordering?
typedef struct item {
  int part_number;
  // set name to max len for simplicity
  char part_name[NAME_LEN + 1]; 
  struct item *parent_part;
  struct item *left_part;
  struct item *right_part;
} item;

void insert_item(item *root);
void update_item(item *root, int part_number);
void delete_item(item *root, int part_number);
item* search_item(item *root, int part_number);
void print_item(item *root, int part_number);


#endif
