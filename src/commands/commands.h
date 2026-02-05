#ifndef COMMANDS_H
#define COMMANDS_H
#define MAXCHAR 1024

#include "../item-fns/item_fns.h"

item *insert_item (item *root);
item *update_item (item *root);
item *update_item_part_number (item *root);
item *update_item_name (item *root);
item *update_item_qty (item *root);
item *delete_item (item *root);
void search_item (item *root, int part_number);
item *print_item (item *root);
item *print_items (item *root);

// impl import from csv's to start
item *import_items (item *root);
item *export_items (item *root);

#endif
