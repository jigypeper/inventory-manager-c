#ifndef ITEM_FNS_H
#define ITEM_FNS_H

#define NAME_LEN 25

// binary search tree for ordering?
typedef struct item {
  int part_number;
  // set name to max len for simplicity
  char part_name[NAME_LEN + 1];
  int qty;
  struct item *left_part;
  struct item *right_part;
} item;

item* create_item_node(item *part);
item* insert_item_node(item *root, item *part);
item* delete_item_node(item *root, int part_number);
item* search_item_node(item *root, int part_number);
item* find_min(item *root);
item* insert_item(item *root);
item* update_item(item *root);
item *delete_item(item *root);
void in_order_collect(item *root, item ***address_array, int *index, int *capacity);
item** build_item_array(item *root, int *array_length);
void search_item(item *root, int part_number);
void print_item(item *root, int part_number);
void print_items(item *root);



#endif
