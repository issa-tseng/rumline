#include <stdio.h>
#include <stdlib.h>

#include "./util.h"
#include "../src/mark.h"
#include "../src/linked-list.h"

void test_mark()
{
  struct mark from;
  from.lat = 47;
  from.lon = -122;
  from.name = "from mark";

  struct mark to;
  to.lat = 49;
  to.lon = -121;
  to.name = "to mark";

  size_t bytes = size_mark(&from);
  printf("bytes: %d (expects 28)\n", (int) bytes);

  void* buffer = malloc(bytes);
  serialize_mark(&from, buffer);

  printf("serialized:\n");
  print_bytes(buffer, bytes);

  printf("\n\n");

  struct mark after;
  deserialize_mark(&after, buffer);
  printf("reinflated:\n");
  print_mark(&after);
  printf("\n");
}

void test_marks()
{
  struct mark x;
  x.lat = 47;
  x.lon = -122;
  x.name = "x mark";

  struct mark y;
  y.lat = 49;
  y.lon = -121;
  y.name = "y mark";

  struct list* l = malloc(sizeof (struct list));
  list_init(l);
  list_add(l, &x);
  list_add(l, &y);

  size_t bytes = size_marks(l);
  printf("mark list in bytes: %d (expects 52)\n", (int) bytes);

  void* buffer = malloc(bytes);
  serialize_marks(l, buffer);

  printf("serialized:\n");
  print_bytes(buffer, bytes);

  struct list* l2 = malloc(sizeof (struct list));
  list_init(l2);
  deserialize_marks(l2, buffer);

  printf("\n\ndeserialized marks: %d (expects 2)\n", list_length(l2));
  printf("first inflated mark:\n");
  print_mark((struct mark*) list_nth(l2, 0));
  printf("\nsecond inflated mark:\n");
  print_mark((struct mark*) list_nth(l2, 1));
  printf("\n");
}

