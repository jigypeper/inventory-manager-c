#ifndef ITEM_FNS_H
#define ITEM_FNS_H

#define NAME_LEN 25

// binary search tree for ordering?
typedef struct item
{
  int part_number;
  // set name to max len for simplicity
  char part_name[NAME_LEN + 1];
  int qty;
  struct item *left_part;
  struct item *right_part;
} item_t;

item_t *create_item_node (item_t *part);
item_t *insert_item_node (item_t *root, item_t *part);
item_t *delete_item_node (item_t *root, int part_number);
item_t *search_item_node (item_t *root, int part_number);
item_t *find_min (item_t *root);
void in_order_collect (item_t *root, item_t ***address_array, int *index,
                       int *capacity);
item_t **build_item_array (item_t *root, int *array_length);

#endif
