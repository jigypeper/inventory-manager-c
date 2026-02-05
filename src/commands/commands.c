#include "commands.h"
#include "../item-fns/item_fns.h"
#include "read_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

item_t *
insert_item (item_t *root)
{
  item_t *part = malloc (sizeof (item_t));

  printf ("Part no.: ");
  scanf ("%d", &part->part_number);

  printf ("Part name: ");
  read_line (part->part_name, NAME_LEN);

  printf ("Quantity: ");
  scanf ("%d", &part->qty);

  if (search_item_node (root, part->part_number) == NULL)
    {
      // Update root, not part
      root = insert_item_node (root, part);
    }
  else
    {
      printf ("Part [%d] already exists\n", part->part_number);
      // Free the allocated memory since we're not using it
      free (part);
    }
  // Always return the root
  return root;
}

item_t *
update_item (item_t *root)
{
  item_t *existing_part = NULL;
  int part_number, new_part_number, new_qty;
  char choice;
  char new_part_name[NAME_LEN];

  printf ("Which part do you want to update? [part no.]: ");
  scanf ("%d", &part_number);
  existing_part = search_item_node (root, part_number);

  if (existing_part != NULL)
    {

      printf (
          "Choose an option\na: Update all fields\np: Update part number\nn: "
          "Update part name\nq: Update quantity\n");
      scanf (" %c", &choice);

      switch (choice)
        {
        case 'a':
        case 'A':
          printf ("Part no.: ");
          scanf ("%d", &new_part_number);

          printf ("New Part name: ");
          read_line (new_part_name, NAME_LEN);

          printf ("Quantity: ");
          scanf ("%d", &new_qty);

          strcpy (existing_part->part_name, new_part_name);
          existing_part->part_number = new_part_number;
          existing_part->qty = new_qty;
          break;
        case 'p':
        case 'P':
          printf ("Part no.: ");
          scanf ("%d", &new_part_number);
          existing_part->part_number = new_part_number;
          break;
        case 'n':
        case 'N':
          printf ("New Part name: ");
          read_line (new_part_name, NAME_LEN);
          strcpy (existing_part->part_name, new_part_name);
          break;
        case 'q':
        case 'Q':
          printf ("Quantity: ");
          scanf ("%d", &new_qty);
          existing_part->qty = new_qty;
          break;
        }

      return root;
    }

  printf ("Part [%d] does not exist in the database, please add it.\n",
          part_number);
  return root;
}

item_t *
delete_item (item_t *root)
{
  item_t *existing_part = NULL;
  int part_number;

  printf ("Which part do you want to delete? [part no.]: ");
  scanf ("%d", &part_number);
  existing_part = search_item_node (root, part_number);

  if (existing_part != NULL)
    {

      root = delete_item_node (root, part_number);

      return root;
    }

  printf ("Part [%d] does not exist in the database, can't delete it\n",
          part_number);
  return root;
}

item_t *
print_item (item_t *root)
{
  int part_number;
  printf ("part number: ");
  scanf ("%d", &part_number);
  item_t *result = search_item_node (root, part_number);
  if (result == NULL)
    {
      printf ("Can't find item: %d\n", part_number);
    }
  else
    {
      printf ("┌───────────┬─────────────────────────┬────────┐\n");
      printf ("│ %-9s │ %-23s │ %-6s │\n", "Part No.", "Part Name", "Qty");
      printf ("├───────────┼─────────────────────────┼────────┤\n");
      printf ("│ %-9d │ %-23s │ %-6d │\n", result->part_number,
              result->part_name, result->qty);
      printf ("└───────────┴─────────────────────────┴────────┘\n");
    }
  return root;
}

item_t *
print_items (item_t *root)
{
  int array_length = 0;
  item_t **inventory = build_item_array (root, &array_length);

  if (array_length == 0)
    {
      printf ("No items in the database! Please add some\n");
      return root;
    }

  printf ("┌───────────┬─────────────────────────┬────────┐\n");
  printf ("│ %-9s │ %-23s │ %-6s │\n", "Part No.", "Part Name", "Qty");

  for (int i = 0; i < array_length; i++)
    {
      printf ("├───────────┼─────────────────────────┼────────┤\n");
      printf ("│ %-9d │ %-23s │ %-6d │\n", inventory[i]->part_number,
              inventory[i]->part_name, inventory[i]->qty);
    }

  printf ("└───────────┴─────────────────────────┴────────┘\n");
  free (inventory);
  return root;
}

/* TODO: Read into BST */
item_t *
import_items (item_t *root)
{
  FILE *data_file = fopen ("inventory.csv", "r");

  if (data_file == NULL)
    {
      printf ("Error opening data file\n");
      return root;
    }

  char line[MAXCHAR];

  while (fgets (line, sizeof (line), data_file))
    {
      item_t new;

      char *token = strtok (line, ",");
      if (token)
        new.part_number = atoi (token);

      token = strtok (NULL, ",");
      if (token)
        strcpy (new.part_name, token);

      token = strtok (NULL, ",");
      if (token)
        new.qty = atoi (token);

      root = insert_item_node (root, &new);
    }
  fclose (data_file);
  return root;
}

item_t *
export_items (item_t *root)
{
  int array_length = 0;
  item_t **inventory = build_item_array (root, &array_length);

  if (array_length == 0)
    {
      printf ("No items in the database! Please add some\n");
      return root;
    }

  FILE *data_file = fopen ("inventory.csv", "w");

  if (data_file == NULL)
    {
      printf ("Error opening data file\n");
      return root;
    }

  for (int i = 0; i < array_length; i++)
    {
      fprintf (data_file, "%d,%s,%d\n", inventory[i]->part_number,
               inventory[i]->part_name, inventory[i]->qty);
    }

  fclose (data_file);
  return root;
}
