
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <stddef.h>

typedef int element_type;

struct DoubleListNode;

typedef struct {
    struct DoubleListNode *first;
    struct DoubleListNode *last;
    size_t count;
} DoubleList;

typedef struct {
    DoubleList *object;
    struct DoubleListNode *current;
} DoubleListIterator;

// Lifecycle operations...
void               DoubleList_construct( DoubleList *object );
void               DoubleList_destroy( DoubleList *object );

// Non-modifying list operations...
size_t             DoubleList_size( const DoubleList *object );
element_type       DoubleList_front( const DoubleList *object );
element_type       DoubleList_back( const DoubleList *object );
int                DoubleList_equal( const DoubleList *object_1, const DoubleList *object_2 );

// Modifying list operations...
void               DoubleList_push_front( DoubleList *object, const element_type *item );
element_type       DoubleList_pop_front( DoubleList *object );
void               DoubleList_push_back( DoubleList *object, const element_type *item );
element_type       DoubleList_pop_back( DoubleList *object );

// Iterator operations...
DoubleListIterator DoubleList_begin( DoubleList *object );
DoubleListIterator DoubleList_end( DoubleList *object );
int                DoubleList_equal_iterator( DoubleListIterator it_1, DoubleListIterator it_2 );
DoubleListIterator DoubleList_next( DoubleListIterator it );
DoubleListIterator DoubleList_previous( DoubleListIterator it );
element_type      *DoubleList_get( DoubleListIterator it );
void               DoubleList_insert_before( DoubleListIterator it, const element_type *item );

// Debugging operations...
int                DoubleList_invariant( const DoubleList *object );

#endif
