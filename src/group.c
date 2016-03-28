#include <stdlib.h>
#include <string.h>

#include "./group.h"
#include "./mark.h"

void group_init(struct group* g)
{
  struct list* l = malloc(sizeof (struct list));
  list_init(l);
  g->marks = l;
}

size_t size_group(struct group* g)
{
  return size_marks(g->marks) + (sizeof (short)) + strlen(g->name) + 1;
}

void serialize_group(struct group* g, void* buffer)
{
  size_t list_size = size_marks(g->marks);
  serialize_marks(g->marks, buffer);
  buffer += list_size;

  size_t name_length = strlen(g->name) + 1;
  *(short*) buffer = name_length;
  buffer += sizeof (short);

  strcpy(buffer, g->name);
}

void deserialize_group(struct group* g, void* buffer)
{
  deserialize_marks(g->marks, buffer);
  buffer += size_marks(g->marks);

  size_t name_length = *(short*) buffer;
  buffer += sizeof (short);

  g->name = malloc(name_length);
  strncpy(g->name, buffer, name_length);
}

void group_free_marks(struct group* g)
{
  int mark_count = list_length(g->marks);
  for (int i = 0; i < mark_count; i++) free(list_nth(g->marks, i));
}

void group_destruct(struct group* g)
{
  list_destruct(g->marks);
  free(g); // again probably bad form.
}
