#ifndef COMMANDS_H
#define COMMANDS_H
#define MAXCHAR 1024

#include "../item-fns/item_fns.h"

item_t *insert_item(item_t *root);
item_t *update_item(item_t *root);
item_t *update_item_part_number(item_t *root);
item_t *update_item_name(item_t *root);
item_t *update_item_qty(item_t *root);
item_t *delete_item(item_t *root);
void search_item(item_t *root, int part_number);
item_t *print_item(item_t *root);
item_t *print_items(item_t *root);

// impl import from csv's to start
item_t *import_items(item_t *root);
item_t *export_items(item_t *root);

#endif
