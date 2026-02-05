#include "item_fns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

item_t *
create_item_node (item_t *part)
{
  item_t *new_part = (item_t *)malloc (sizeof (item_t));
  if (new_part != NULL)
    {
      new_part = (item_t *)malloc (sizeof (item_t));
      new_part->left_part = NULL;
      new_part->right_part = NULL;
      new_part->part_number = part->part_number;
      strcpy (new_part->part_name, part->part_name);
      new_part->qty = part->qty;
    }
  return new_part;
}

item_t *
insert_item_node (item_t *root, item_t *part)
{
  if (root == NULL)
    {
      return create_item_node (part);
    }

  if (part->part_number < root->part_number)
    {
      root->left_part = insert_item_node (root->left_part, part);
    }
  else
    {
      root->right_part = insert_item_node (root->right_part, part);
    }
  return root;
}

item_t *
search_item_node (item_t *root, int part_number)
{
  if (root == NULL)
    {
      return root;
    }

  if (part_number == root->part_number)
    {
      return root;
    }
  else if (part_number < root->part_number)
    {
      return search_item_node (root->left_part, part_number);
    }
  else
    {
      return search_item_node (root->right_part, part_number);
    }
}

item_t *
find_min (item_t *root)
{
  if (root == NULL || root->left_part == NULL)
    {
      return root;
    }
  return find_min (root->left_part);
}

item_t *
delete_item_node (item_t *root, int part_number)
{
  if (root == NULL)
    {
      return root;
    }

  if (part_number < root->part_number)
    {
      root->left_part = delete_item_node (root->left_part, part_number);
    }
  else if (part_number > root->part_number)
    {
      root->right_part = delete_item_node (root->right_part, part_number);
    }
  else
    {
      if (root->left_part == NULL)
        {
          item_t *temp = root->right_part;
          free (root);
          return temp;
        }
      else if (root->right_part == NULL)
        {
          item_t *temp = root->left_part;
          free (root);
          return temp;
        }
      else
        {
          item_t *successor = find_min (root->right_part);
          root->part_number = successor->part_number;
          root->qty = successor->qty;
          strcpy (root->part_name, successor->part_name);
          root->right_part
              = delete_item_node (root->right_part, successor->part_number);
        }
    }

  return root;
}

void
in_order_collect (item_t *root, item_t ***address_array, int *index, int *capacity)
{
  if (root == NULL)
    {
      return;
    }

  if (*index >= *capacity)
    {
      *capacity *= 2;
      item_t **temp
          = (item_t **)realloc (*address_array, *capacity * sizeof (item_t *));
      *address_array = temp;
    }

  in_order_collect (root->left_part, address_array, index, capacity);
  (*address_array)[(*index)++] = root;
  in_order_collect (root->right_part, address_array, index, capacity);
}

item_t **
build_item_array (item_t *root, int *array_length)
{
  int count = 0, capacity = 10;
  item_t **item_array = (item_t **)malloc (capacity * sizeof (item_t *));

  in_order_collect (root, &item_array, &count, &capacity);
  *array_length = count;
  return item_array;
}
