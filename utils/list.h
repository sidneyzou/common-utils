#ifndef __LIST_H
#define __LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup if_list
 * \copydoc list.h
 * @{
 */


#include "common.h"

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#ifndef LIST_POISON1
#define LIST_POISON1  NULL
#endif

#ifndef LIST_POISON2
#define LIST_POISON2  NULL
#endif

struct list_head {
    struct list_head *next, *prev;
};

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};


/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

#if 0

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

#endif

static __inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}
#define list_head_init(list) INIT_LIST_HEAD(list)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline void __list_add(struct list_head *elm,
                                      struct list_head *prev,
                                      struct list_head *next)
{
    next->prev = elm;
    elm->next = next;
    elm->prev = prev;
    prev->next = elm;
}

/**
 * \brief add a new entry
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 *
 * \param elm   new entry to be added
 * \param head  list head to add it after
 */
static __inline void list_add(struct list_head *elm,
                                    struct list_head *head)
{
    __list_add(elm, head, head->next);
}


/**
 * \brief add a new entry
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 *
 * \param elm   new entry to be added
 * \param head  list head to add it before
 */
static __inline void list_add_tail(struct list_head *elm,
                                         struct list_head *head)
{
    __list_add(elm, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline void __list_del(struct list_head *prev,
                                   struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * \brief deletes entry from list.
 *
 * \param entry     the element to delete from the list.
 *
 * \attention list_empty() on entry does not return true after this, the entry
 * is in an undefined state.
 */
static __inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static __inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);

    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

/**
 * \brief replace old entry by new one
 *
 * If \a old was empty, it will be overwritten.
 *
 * \param old   the element to be replaced
 * \param elm   the new element to insert
 */
static __inline void list_replace(struct list_head *old,
                                        struct list_head *elm)
{
    elm->next = old->next;
    elm->next->prev = elm;
    elm->prev = old->prev;
    elm->prev->next = elm;
}

static __inline void list_replace_init(struct list_head *old,
                                             struct list_head *elm)
{
    list_replace(old, elm);
    INIT_LIST_HEAD(old);
}

/**
 * \brief deletes entry from list and reinitialize it.
 *
 * \param entry     the element to delete from the list.
 */
static __inline void list_del_init(struct list_head *entry)
{
    __list_del_entry(entry);
    INIT_LIST_HEAD(entry);
}

/**
 * \brief delete from one list and add as another's head
 *
 * \param list  the entry to move
 * \param head  the head that will precede our entry
 */
static __inline void list_move(struct list_head *list,
                                     struct list_head *head)
{
    __list_del_entry(list);
    list_add(list, head);
}

/**
 * \brief delete from one list and add as another's tail
 *
 * \param list  the entry to move
 * \param head  the head that will follow our entry
 */
static __inline void list_move_tail(struct list_head *list,
                                          struct list_head *head)
{
    __list_del_entry(list);
    list_add_tail(list, head);
}

/**
 * \brief tests whether \a list is the last entry in list \a head
 *
 * \param list  the entry to test
 * \param head  the head of the list
 */
static __inline int list_is_last(const struct list_head *list,
                                       const struct list_head *head)
{
    return list->next == head;
}

/**
 * \brief tests whether a list is empty
 *
 * \param head  the list to test.
 */
static __inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

/**
 * \brief tests whether a list is empty and not being modified
 *
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * \param head  the list to test
 *
 * \attention using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 */
static __inline int list_empty_careful(const struct list_head *head)
{
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
}

/**
 * \brief rotate the list to the left
 *
 * \param head  the head of the list
 */
static __inline void list_rotate_left(struct list_head *head)
{
    struct list_head *first;

    if (!list_empty(head)) {
        first = head->next;
        list_move_tail(first, head);
    }
}

/**
 * \brief tests whether a list has just one entry.
 *
 * \param head  the list to test.
 */
static __inline int list_is_singular(const struct list_head *head)
{
    return !list_empty(head) && (head->next == head->prev);
}

static __inline void __list_cut_position(struct list_head *list,
                                            struct list_head *head,
                                            struct list_head *entry)
{
    struct list_head *elm_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = elm_first;
    elm_first->prev = head;
}

/**
 * \brief cut a list into two
 *
 * This helper moves the initial part of \a head, up to and
 * including \a entry, from \a head to \a list. You should
 * pass on \a entry an element you know is on \a head. \a list
 * should be an empty list or a list you do not care about
 * losing its data.
 *
 * \param list   a new list to add all removed entries
 * \param head   a list with entries
 * \param entry  an entry within head, could be the head itself
 *               and if so we won't cut the list
 */
static __inline void list_cut_position(struct list_head *list,
                                             struct list_head *head,
                                             struct list_head *entry)
{
    if (list_empty(head))
        return;
    if (list_is_singular(head) &&
        (head->next != entry && head != entry))
        return;
    if (entry == head)
        INIT_LIST_HEAD(list);
    else
        __list_cut_position(list, head, entry);
}

static __inline void __list_splice(const struct list_head *list,
                                      struct list_head       *prev,
                                      struct list_head       *next)
{
    struct list_head *first = list->next;
    struct list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

/**
 * \brief join two lists, this is designed for stacks
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
static __inline void list_splice(const struct list_head *list,
                                       struct list_head       *head)
{
    if (!list_empty(list)) {
        __list_splice(list, head, head->next);
    }
}

/**
 * \brief join two lists, each list being a queue
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
static __inline void list_splice_tail(struct list_head *list,
                                            struct list_head *head)
{
    if (!list_empty(list))
        __list_splice(list, head->prev, head);
}

/**
 * \brief join two lists and reinitialise the emptied list.
 *
 * The list at \a list is reinitialised
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
static __inline void list_splice_init(struct list_head *list,
                                            struct list_head *head)
{
    if (!list_empty(list)) {
        __list_splice(list, head, head->next);
        INIT_LIST_HEAD(list);
    }
}

/**
 * \brief join two lists and reinitialise the emptied list
 *
 * Each of the lists is a queue.
 * The list at \a list is reinitialised
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
static __inline void list_splice_tail_init(struct list_head *list,
                                                 struct list_head *head)
{
    if (!list_empty(list)) {
        __list_splice(list, head->prev, head);
        INIT_LIST_HEAD(list);
    }
}

/**
 * \brief get the struct for this entry
 *
 * \param ptr       the &struct list_head pointer.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * \brief get the first element from a list
 *
 * \param ptr       the list head to take the element from.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 *
 * \attention  that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * \brief iterate over a list
 *
 * \param pos   the &struct list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define list_for_each(pos, head) \
    for (pos = (head)->next; \
         prefetch(pos->next), pos != (head); \
         pos = pos->next)

/**
 * \brief iterate over a list
 *
 * This variant differs from list_for_each() in that it's the
 * simplest possible list iteration code, no prefetching is done.
 * Use this for code that knows the list to be very short (empty
 * or 1 entry) most of the time.
 *
 * \param pos   the &struct list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define __list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * \brief iterate over a list backwards
 *
 * \param pos   the &struct list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define list_for_each_prev(pos, head) \
    for (pos = (head)->prev; prefetch(pos->prev), pos != (head); \
            pos = pos->prev)

/**
 * \brief iterate over a list safe against removal of list entry
 *
 * \param pos   the &struct list_head to use as a loop cursor.
 * \param n     another &struct list_head to use as temporary storage
 * \param head  the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

/**
 * \brief iterate over a list backwards safe against removal of list entry
 *
 * \param pos   the &struct list_head to use as a loop cursor.
 * \param n     another &struct list_head to use as temporary storage
 * \param head  the head for your list.
 */
#define list_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; \
         prefetch(pos->prev), pos != (head); \
         pos = n, n = pos->prev)

/**
 * \brief iterate over list of given type
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, type, member) \
    for (pos = list_entry((head)->next, type, member); \
         prefetch(pos->member.next), &pos->member != (head); \
         pos = list_entry(pos->member.next, type, member))

/**
 * \brief iterate backwards over list of given type.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_reverse(pos, head, type, member) \
    for (pos = list_entry((head)->prev, type, member); \
         prefetch(pos->member.prev), &pos->member != (head); \
         pos = list_entry(pos->member.prev, type, member))

/**
 * \brief prepare a pos entry for use in list_for_each_entry_continue()
 *
 * Prepares a pos entry for use as a start point in list_for_each_entry_continue().
 *
 * \param pos       the type * to use as a start point
 * \param head      the head of the list
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_prepare_entry(pos, head, type, member) \
    ((pos) ? : list_entry(head, type, member))

/**
 * \brief continue iteration over list of given type
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_continue(pos, head, type, member) \
    for (pos = list_entry(pos->member.next, type, member); \
         prefetch(pos->member.next), &pos->member != (head); \
         pos = list_entry(pos->member.next, type, member))

/**
 * \brief iterate backwards from the given point
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_continue_reverse(pos, head, type, member) \
    for (pos = list_entry(pos->member.prev, type, member); \
         prefetch(pos->member.prev), &pos->member != (head); \
         pos = list_entry(pos->member.prev, type, member))

/**
 * \brief iterate over list of given type from the current point
 *
 * Iterate over list of given type, continuing from current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_from(pos, head, type, member) \
    for (; prefetch(pos->member.next), &pos->member != (head); \
         pos = list_entry(pos->member.next, type, member))

/**
 * \brief iterate over list of given type safe against removal of list entry
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, type, member) \
    for (pos = list_entry((head)->next, type, member), \
        n = list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, type, member))

/**
 * \brief continue list iteration safe against removal
 *
 * Iterate over list of given type, continuing after current point,
 * safe against removal of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe_continue(pos, n, head, type, member) \
    for (pos = list_entry(pos->member.next, type, member), \
        n = list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, type, member))

/**
 * \brief iterate over list from current point safe against removal
 *
 * Iterate over list of given type from current point, safe against
 * removal of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe_from(pos, n, head, type, member) \
    for (n = list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, type, member))

/**
 * \brief iterate backwards over list safe against removal
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe_reverse(pos, n, head, type, member) \
    for (pos = list_entry((head)->prev, type, member), \
        n = list_entry(pos->member.prev, type, member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.prev, type, member))

/**
 * \brief reset a stale list_for_each_entry_safe loop
 *
 * list_safe_reset_next is not safe to use in general if the list may be
 * modified concurrently (eg. the lock is dropped in the loop body). An
 * exception to this is if the cursor element (pos) is pinned in the list,
 * and list_safe_reset_next is called after re-taking the lock and before
 * completing the current iteration of the loop body.
 *
 * \param pos       the loop cursor used in the list_for_each_entry_safe loop
 * \param n         temporary storage used in list_for_each_entry_safe
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_safe_reset_next(pos, n, type, member) \
    n = list_entry(pos->member.next, type, member)

/*
 * Double linked lists with a single pointer list head.
 * Mostly useful for hash tables where the two pointer list head is
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */

#if 0
#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
#endif

#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static __inline void INIT_HLIST_NODE(struct hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

static __inline int hlist_unhashed(const struct hlist_node *h)
{
    return !h->pprev;
}

static __inline int hlist_empty(const struct hlist_head *h)
{
    return !h->first;
}

static __inline void __hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next)
        next->pprev = pprev;
}

static __inline void hlist_del(struct hlist_node *n)
{
    __hlist_del(n);
    n->next = LIST_POISON1;
    n->pprev = LIST_POISON2;
}

static __inline void hlist_del_init(struct hlist_node *n)
{
    if (!hlist_unhashed(n)) {
        __hlist_del(n);
        INIT_HLIST_NODE(n);
    }
}

static __inline void hlist_add_head(struct hlist_node *n,
                                          struct hlist_head *h)
{
    struct hlist_node *first = h->first;
    n->next = first;
    if (first)
        first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
}

/* next must be != NULL */
static __inline void hlist_add_before(struct hlist_node *n,
                                            struct hlist_node *next)
{
    n->pprev = next->pprev;
    n->next = next;
    next->pprev = &n->next;
    *(n->pprev) = n;
}

static __inline void hlist_add_after(struct hlist_node *n,
                                           struct hlist_node *next)
{
    next->next = n->next;
    n->next = next;
    next->pprev = &n->next;

    if(next->next)
        next->next->pprev  = &next->next;
}

/* after that we'll appear to be on some hlist and hlist_del will work */
static __inline void hlist_add_fake(struct hlist_node *n)
{
    n->pprev = &n->next;
}

/*
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry if it exists.
 */
static __inline void hlist_move_list(struct hlist_head *old,
                                           struct hlist_head *elm)
{
    elm->first = old->first;
    if (elm->first)
        elm->first->pprev = &elm->first;
    old->first = NULL;
}

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos && ({ prefetch(pos->next); 1; }); \
         pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; 1; }); \
         pos = n)

/**
 * \brief iterate over list of given type
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct hlist_node to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry(tpos, pos, head, type, member) \
    for (pos = (head)->first; \
         pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = hlist_entry(pos, type), member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over a hlist continuing after current point
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct hlist_node to use as a loop cursor.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_continue(tpos, pos, type, member) \
    for (pos = (pos)->next; \
         pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = hlist_entry(pos, type, member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over a hlist continuing from current point
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct hlist_node to use as a loop cursor.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_from(tpos, pos, type, member) \
    for (; pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = hlist_entry(pos, type, member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over list of given type safe against removal of list entry
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct hlist_node to use as a loop cursor.
 * \param n         another &struct hlist_node to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_safe(tpos, pos, n, head, type, member) \
    for (pos = (head)->first; \
         pos && ({ n = pos->next; 1; }) && \
        ({ tpos = hlist_entry(pos, type, member); 1;}); \
         pos = n)

/** @}  if_list */

#ifdef __cplusplus
}
#endif

#endif /* __LIST_H */

/* end of file */
