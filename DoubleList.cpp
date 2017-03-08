//Daniel Clark
//Last Updated: 09/28/15
//Purpose: Experimentation with doubly linked lists
//Version: 1.0
#include <assert.h>
#include <stdlib.h>
#include "DoubleList.h"

struct DoubleListNode {
    element_type data;
    struct DoubleListNode *next;
    struct DoubleListNode *previous;
};


void DoubleList_construct( DoubleList *object )
{
    assert( object != NULL );

    object->first = NULL;
    object->last  = NULL;
    object->count = 0;
}


void DoubleList_destroy( DoubleList *object )
{
    assert( object != NULL );

    //The ability to declare variables after executable statements is a C99 (or C++) feature.
    struct DoubleListNode *current = object->first;
    while( current != NULL ) {
        struct DoubleListNode *temp = current->next;

        //This assumes element_type has no special destruction needs.
        free( current );
        current = temp;
    }

    // Put the DoubleList object into a well defined state.
    DoubleList_construct( object );
}


size_t DoubleList_size( const DoubleList *object )
{
    assert( object != NULL );

    return object->count;
}


element_type DoubleList_front( const DoubleList *object )
{
    assert( object != NULL && object->first != NULL );

    return object->first->data;
}


element_type DoubleList_back( const DoubleList *object )
{
    assert( object != NULL && object->last != NULL );

    return object->last->data;
}


int DoubleList_equal( const DoubleList *object_1, const DoubleList *object_2 )
{
    assert( object_1 != NULL && object_2 != NULL );

    if( object_1->count != object_2->count ) return 0;

    //The counts are equal...
    DoubleListNode *current_1 = object_1->first;
    DoubleListNode *current_2 = object_2->first;

    while( current_1 != NULL ) {
        //This assumes element_type can be compared with !=.
        if( current_1->data != current_2->data ) return 0;
        current_1 = current_1->next;
        current_2 = current_2->next;
    }
    return 1;
}

void DoubleList_push_front( DoubleList *object, const element_type *item )
{
    assert( object != NULL && item != NULL );

    struct DoubleListNode *new_node =
        ( struct DoubleListNode * )malloc( sizeof( struct DoubleListNode ) );

    //TODO: Maybe return an error indication if the allocation fails?
    if( new_node == NULL ) return;

    //FINISH ME!

    object->count++;
}


element_type DoubleList_pop_front( DoubleList *object )
{
    assert( object != NULL && object->first != NULL );

    //This assumes element_type can be initialized with assignment.
    element_type temp_item = object->first->data;
    struct DoubleListNode *temp = object->first;
    object->first = object->first->next;
    if( object->first != NULL )
        object->first->previous = NULL;
    else
        object->last = NULL;

    //This assumes element_type has no special destruction needs.
    free( temp );
    object->count--;
    return temp_item;
}

void DoubleList_push_back( DoubleList *object, const element_type *item )
{
    assert( object != NULL && item != NULL );

    struct DoubleListNode *new_node =
        ( struct DoubleListNode * )malloc( sizeof( struct DoubleListNode ) );

    //Maybe return an error indication if the allocation fails?
    if( new_node == NULL ) return;

    new_node->data = *item;
    new_node->next = NULL;

    if( object->count == 0 ) {
        object->first = new_node;
    }
    else {
        object->last->next = new_node;
    }
    object->last = new_node;
    object->count++;
}

element_type DoubleList_pop_back( DoubleList *object )
{
    assert( object != NULL && object->last != NULL );

    element_type temp_item = object->last->data;
    struct DoubleListNode *temp = object->last;
    object->last = object->last->next;
    if( object->last != NULL )
        object->last->previous = NULL;
    else
        object->first = NULL;
    free( temp );
    object->count--;
    return temp_item;
}


DoubleListIterator DoubleList_begin( DoubleList *object )
{
    assert( object != NULL );

    DoubleListIterator result;
    result.object = object;
    result.current = object->first;
    return result;
}


DoubleListIterator DoubleList_end( DoubleList *object )
{
    assert( object != NULL );

    DoubleListIterator result;
    result.object = object;
    result.current = NULL;
    return result;
}


int DoubleList_equal_iterator( DoubleListIterator it_1, DoubleListIterator it_2 )
{
    //Say the iterators are valid. This doesn't completely do that.
    assert( it_1.object != NULL && it_2.object != NULL );

    return (it_1.object == it_2.object) && (it_1.current == it_2.current);
}


DoubleListIterator DoubleList_next( DoubleListIterator it )
{
    //Say that it.current points into the list controlled by object.
    assert( it.object != NULL  && it.current != NULL );

	DoubleListIterator result;
	result.object = it.object;
	result.current = it.current->next;
	return result;
}


DoubleListIterator DoubleList_previous( DoubleListIterator it )
{
    //Say that it.current points into the list controlled by object.
    assert( it.object != NULL );
    DoubleListIterator result;

    if( it.current == NULL ) {
        result.object = it.object;
        result.current = it.object->last;
    }
    else {
        result.object = it.object;
        result.current = it.current->previous;
    }
    return result;
}


element_type *DoubleList_get( DoubleListIterator it )
{
    assert( it.object != NULL && it.current != NULL );
	return &it.current->data;
}

void DoubleList_insert_before( DoubleListIterator it, const element_type *item )
{
    assert( it.object != NULL && item != NULL );
	struct DoubleListNode *new_node =
		( struct DoubleListNode * )malloc( sizeof( struct DoubleListNode ) );

	// TODO: Maybe return an error indication if the allocation fails?
	if( new_node == NULL ) return;

    // FINISH ME!
}


int DoubleList_invariant( const DoubleList *object )
{
    DoubleListNode *current;
    DoubleListNode *previous;
    int actual_count;

    previous = NULL;
    current = object->first;
    actual_count = 0;
    while( current != NULL ) {
        actual_count++;
        //Make sure the previous pointers in the nodes are correct.
        if( current->previous != previous ) return 0;
        previous = current;
        current = current->next;
    }

    //Make sure the count in the object is correct.
    if( object->count != actual_count ) return 0;

    //The first and last pointers are either both NULL or both non-NULL.
    if( object->first == NULL && object->last != NULL ) return 0;
    if( object->first != NULL && object->last == NULL ) return 0;

    //Check list terminations.
    if( object->count > 0 ) {
        if( object->first->previous != NULL ) return 0;
        if( object->last->next != NULL ) return 0;
    }

    //Check special handling of a single node.
    if( object->count == 1 ) {
        if( object->first != object->last ) return 0;
    }
    return 1;
}
