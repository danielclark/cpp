
#include <assert.h>
#include <stdlib.h>
#include "SingleList.h"

struct SingleListNode {
    element_type data;
    struct SingleListNode *next;
};


void SingleList_construct( SingleList *object )
{
    assert( object != NULL );

    object->first = NULL;
    object->last  = NULL;
    object->count = 0;
}


void SingleList_destroy( SingleList *object )
{
    assert( object != NULL );

    // NOTE: The ability to declare variables after executable statements is a C99 (or C++) feature.
    struct SingleListNode *current = object->first;
    while( current != NULL ) {
        struct SingleListNode *temp = current->next;

        // NOTE: This assumes element_type has no special destruction needs.
        free( current );
        current = temp;
    }
}


// Daniel Clark
// 09/03/15
void SingleList_copy( SingleList *destination, const SingleList *source ) {
    assert( destination != NULL && source != NULL );
	SingleList_destroy(destination);
	destination->count = 0; //I discussed this with Zach Matthews... why doesn't SingleList_Destroy do this?
	struct SingleListNode *current=source->first;
	while (current!=NULL) {
		SingleList_push_back(destination, &current->data);
		current=current->next;
	}
}


size_t SingleList_size( const SingleList *object )
{
    assert( object != NULL );

    return object->count;
}


element_type SingleList_front( const SingleList *object )
{
    assert( object != NULL && object->first != NULL );

    return object->first->data;
}


element_type SingleList_back( const SingleList *object )
{
    assert( object != NULL && object->last != NULL );

    return object->last->data;
}


int SingleList_equal( const SingleList *object_1, const SingleList *object_2 )
{
    assert( object_1 != NULL && object_2 != NULL );

    if( object_1->count != object_2->count ) return 0;

    // The counts are equal...
    SingleListNode *current_1 = object_1->first;
    SingleListNode *current_2 = object_2->first;

    while( current_1 != NULL ) {
        // NOTE: This assumes element_type can be compared with !=.
        if( current_1->data != current_2->data ) return 0;
        current_1 = current_1->next;
        current_2 = current_2->next;
    }
    return 1;
}


void SingleList_push_front( SingleList *object, const element_type *item )
{
    assert( object != NULL && item != NULL );

    struct SingleListNode *new_node =
        ( struct SingleListNode * )malloc( sizeof( struct SingleListNode ) );

    // TODO: Maybe return an error indication if the allocation fails?
    if( new_node == NULL ) return;

    // NOTE: This assumes element_type can be copied with assignment.
    new_node->data = *item;
    new_node->next = object->first;
    object->first = new_node;

    // If the list was empty, it must be handled in a special way.
    if( object->last == NULL ) {
        object->last = object->first;
    }
    object->count++;
}


element_type SingleList_pop_front( SingleList *object )
{
    assert( object != NULL && object->first != NULL );

    // NOTE: This assumes element_type can be initialized with assignment.
    element_type temp_item = object->first->data;
    struct SingleListNode *temp = object->first;
    object->first = object->first->next;

    // NOTE: This assumes element_type has no special destruction needs.
    free( temp );
    object->count--;
    return temp_item;
}


void SingleList_push_back( SingleList *object, const element_type *item )
{
    assert( object != NULL && item != NULL );

    struct SingleListNode *new_node =
        ( struct SingleListNode * )malloc( sizeof( struct SingleListNode ) );

    // TODO: Maybe return an error indication if the allocation fails?
    if( new_node == NULL ) return;

    // NOTE: This assumes element_type can be copied with assignment.
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


SingleListIterator SingleList_begin( SingleList *object )
{
    assert( object != NULL );

    SingleListIterator result;
    result.object = object;
    result.current = object->first;
    return result;
}


SingleListIterator SingleList_end( SingleList *object )
{
    assert( object != NULL );

    SingleListIterator result;
    result.object = object;
    result.current = NULL;
    return result;
}


int SingleList_equal_iterator( SingleListIterator it_1, SingleListIterator it_2 )
{
    // We really want to say the iterators are valid. This doesn't completely do that.
    assert( it_1.object != NULL && it_2.object != NULL );

    return (it_1.object == it_2.object) && (it_1.current == it_2.current);
}


SingleListIterator SingleList_next( SingleListIterator it )
{
    // We'd also like to say that it.current points into the list controlled by object.
    assert( it.object != NULL  && it.current != NULL );

	SingleListIterator result;
	result.object = it.object;
	result.current = it.current->next;
	return result;
}


element_type *SingleList_get( SingleListIterator it )
{
    assert( it.object != NULL && it.current != NULL );
	return &it.current->data;
}


void SingleList_insert_after( SingleListIterator it, const element_type *item )
{
    assert( it.object != NULL && it.current != NULL && item != NULL );
	struct SingleListNode *new_node =
		( struct SingleListNode * )malloc( sizeof( struct SingleListNode ) );

	// TODO: Maybe return an error indication if the allocation fails?
	if( new_node == NULL ) return;

	// This assumes element_type can be copied with assignment.
	new_node->data = *item;
	new_node->next = it.current->next;

	it.current->next = new_node;
	it.object->count++;

    // If we are inserting after the last node (appending), we need to update the last pointer.
    if( it.current == it.object->last ) {
        it.object->last = new_node;
    }
}
