
#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <stddef.h>

typedef int element_type;

struct SingleListNode;

typedef struct {
    struct SingleListNode *first;
    struct SingleListNode *last;
    size_t count;
} SingleList;

typedef struct {
    SingleList *object;
    struct SingleListNode *current;
} SingleListIterator;

// Lifecycle operations...
void               SingleList_construct( SingleList *object );
void               SingleList_destroy( SingleList *object );
void               SingleList_copy( SingleList *destination, const SingleList *source );

// Non-modifying list operations...
size_t             SingleList_size( const SingleList *object );
element_type       SingleList_front( const SingleList *object );
element_type       SingleList_back( const SingleList *object );
int                SingleList_equal( const SingleList *object_1, const SingleList *object_2 );

// Modifying list operations...
void               SingleList_push_front( SingleList *object, const element_type *item );
element_type       SingleList_pop_front( SingleList *object );
void               SingleList_push_back( SingleList *object, const element_type *item );

// Iterator operations...
SingleListIterator SingleList_begin( SingleList *object );
SingleListIterator SingleList_end( SingleList *object );
int                SingleList_equal_iterator( SingleListIterator it_1, SingleListIterator it_2 );
SingleListIterator SingleList_next( SingleListIterator it );
element_type      *SingleList_get( SingleListIterator it );
void               SingleList_insert_after( SingleListIterator it, const element_type *item );

#endif
