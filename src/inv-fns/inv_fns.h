#ifndef INV_FNS

// binary search tree for ordering?
typedef struct item {
  int part_number;
  item *left_part;
  item *right_part;
   
} item;

void insert_item(item *root);
void update_item(item *root, int part_number);
void delete_item(item *root, int part_number);
item* search(item *root, int part_number);


#endif
