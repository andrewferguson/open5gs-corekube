#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/list.h"
static OpenAPI_lnode_t *listEntry_create(void *data)
{
    OpenAPI_lnode_t *created = ogs_malloc(sizeof(OpenAPI_lnode_t));
    ogs_assert(created);

    if (created == NULL) {
        // TODO Malloc Failure
        return NULL;
    }
    created->data = data;

    return created;
}

void OpenAPI_lnode_free(OpenAPI_lnode_t *listEntry, void *additionalData)
{
    ogs_free(listEntry);
}

void OpenAPI_lnode_print(OpenAPI_lnode_t *listEntry, void *additionalData)
{
    printf("%i\n", *((int *) (listEntry->data)));
}

OpenAPI_list_t *OpenAPI_list_create(void)
{
    OpenAPI_list_t *createdList = ogs_malloc(sizeof(OpenAPI_list_t));
    ogs_assert(createdList);

    if (createdList == NULL) {
        // TODO Malloc Failure
        return NULL;
    }
    createdList->first = NULL;
    createdList->last = NULL;
    createdList->count = 0;

    return createdList;
}

void OpenAPI_list_iterate_forward(OpenAPI_list_t *list,
                                  void (*operationToPerform)(
                                      OpenAPI_lnode_t *, void *callbackFunctionUsedData),
                                  void *additionalDataNeededForCallbackFunction)
{
    OpenAPI_lnode_t *current = list->first;
    OpenAPI_lnode_t *next;

    if (current == NULL) {
        return;
    }

    next = current->next;

    operationToPerform(current, additionalDataNeededForCallbackFunction);
    current = next;

    while (current != NULL) {
        next = current->next;
        operationToPerform(current, additionalDataNeededForCallbackFunction);
        current = next;
    }
}

void OpenAPI_list_iterate_backward(OpenAPI_list_t *list,
                                   void (*operationToPerform)(
                                       OpenAPI_lnode_t *, void *callbackFunctionUsedData),
                                   void *additionalDataNeededForCallbackFunction)
{
    OpenAPI_lnode_t *current = list->last;
    OpenAPI_lnode_t *next = current->prev;

    if (current == NULL) {
        return;
    }

    operationToPerform(current, additionalDataNeededForCallbackFunction);
    current = next;

    while (current != NULL) {
        next = current->prev;
        operationToPerform(current, additionalDataNeededForCallbackFunction);
        current = next;
    }
}

void OpenAPI_list_free(OpenAPI_list_t *list)
{
    if (list) {
        OpenAPI_list_iterate_forward(list, OpenAPI_lnode_free, NULL);
        ogs_free(list);
    }
}

void OpenAPI_list_add(OpenAPI_list_t *list, void *dataToAddInList)
{
    OpenAPI_lnode_t *newListEntry = listEntry_create(dataToAddInList);
    if (newListEntry == NULL) {
        // TODO Malloc Failure
        return;
    }
    if (list->first == NULL) {
        list->first = newListEntry;
        list->last = newListEntry;

        newListEntry->prev = NULL;
        newListEntry->next = NULL;

        list->count++;

        return;
    }

    list->last->next = newListEntry;
    newListEntry->prev = list->last;
    newListEntry->next = NULL;
    list->last = newListEntry;

    list->count++;
}

void OpenAPI_list_remove(OpenAPI_list_t *list, OpenAPI_lnode_t *elementToRemove)
{
    OpenAPI_lnode_t *elementBeforeElementToRemove = elementToRemove->prev;
    OpenAPI_lnode_t *elementAfterElementToRemove = elementToRemove->next;

    if (elementBeforeElementToRemove != NULL) {
        elementBeforeElementToRemove->next = elementAfterElementToRemove;
    } else {
        list->first = elementAfterElementToRemove;
    }

    if (elementAfterElementToRemove != NULL) {
        elementAfterElementToRemove->prev = elementBeforeElementToRemove;
    } else {
        list->last = elementBeforeElementToRemove;
    }

    OpenAPI_lnode_free(elementToRemove, NULL);

    list->count--;
}

OpenAPI_lnode_t *OpenAPI_list_find(OpenAPI_list_t *list, long indexOfElement)
{
    OpenAPI_lnode_t *current;
    int i;

    if ((list->count / 2) > indexOfElement) {
        current = list->first;

        for(i = 0; i < indexOfElement; i++) {
            current = current->next;
        }

        return current;
    } else {
        current = list->last;

        for(i = 1; i < (list->count - indexOfElement); i++) {
            current = current->prev;
        }

        return current;
    }
}
