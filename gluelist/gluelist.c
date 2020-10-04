/*
 * =====================================================================================
 *
 *        Filename:  glthread.c
 *
 *        Description:  Implementation of glue based double linked list
 *
 *        Version:  1.0
 *        Created:  10/04/2020
 *        Revision:  1.0
 *        Compiler:  gcc
 *
 *        Author: Er. Chirag Jethava 
 *        email : ercjethava@gmail.com
 * 
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by  
 *        the Free Software Foundation, version 3.
 *
 *        This program is distributed in the hope that it will be useful, but 
 *        WITHOUT ANY WARRANTY; without even the implied warranty of 
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 *        General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License 
 *        along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * =====================================================================================
 */

#include "gluelist.h"
#include <stdlib.h>

/* initialize glue linked list */
void init_gl_dbl_lkdlist(gldblelist_t *glthread)
{

    glthread->left = NULL;
    glthread->right = NULL;
}

/* add node next to current node in glue linked list */
void gl_dbl_lkdlist_add_next(gldblelist_t *curr_glthread, gldblelist_t *new_glthread)
{

    if (!curr_glthread->right)
    {
        curr_glthread->right = new_glthread;
        new_glthread->left = curr_glthread;
        return;
    }

    gldblelist_t *temp = curr_glthread->right;
    curr_glthread->right = new_glthread;
    new_glthread->left = curr_glthread;
    new_glthread->right = temp;
    temp->left = new_glthread;
}

/* add node before current node in glue linked list */
void gl_dbl_lkdlist_add_before(gldblelist_t *curr_glthread, gldblelist_t *new_glthread)
{

    if (!curr_glthread->left)
    {
        new_glthread->left = NULL;
        new_glthread->right = curr_glthread;
        curr_glthread->left = new_glthread;
        return;
    }

    gldblelist_t *temp = curr_glthread->left;
    temp->right = new_glthread;
    new_glthread->left = temp;
    new_glthread->right = curr_glthread;
    curr_glthread->left = new_glthread;
}

/* remove ndoe in glue linked list */
void remove_gl_dbl_lkdlist(gldblelist_t *curr_glthread)
{

    if (!curr_glthread->left)
    {
        if (curr_glthread->right)
        {
            curr_glthread->right->left = NULL;
            curr_glthread->right = 0;
            return;
        }
        return;
    }
    if (!curr_glthread->right)
    {
        curr_glthread->left->right = NULL;
        curr_glthread->left = NULL;
        return;
    }

    curr_glthread->left->right = curr_glthread->right;
    curr_glthread->right->left = curr_glthread->left;
    curr_glthread->left = 0;
    curr_glthread->right = 0;
}

/*  delete glue linked list */
void delete_gl_dbl_lkdlist(gldblelist_t *base_glthread)
{

    gldblelist_t *glthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    {
        remove_gl_dbl_lkdlist(glthreadptr);
    }
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr);
}

/* add node at the end in glue linked list */
void glthread_add_last(gldblelist_t *base_glthread, gldblelist_t *new_glthread)
{

    gldblelist_t *glthreadptr = NULL,
               *prevglthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    {
        prevglthreadptr = glthreadptr;
    }
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr);

    if (prevglthreadptr)
        gl_dbl_lkdlist_add_next(prevglthreadptr, new_glthread);
    else
        gl_dbl_lkdlist_add_next(base_glthread, new_glthread);
}

/* count number of node in glue linked list */
unsigned int get_gl_dbl_lkdlist_count(gldblelist_t *base_glthread)
{

    unsigned int count = 0;
    gldblelist_t *glthreadptr = NULL;

    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    {
        count++;
    }
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr);
    return count;
}

/* insert baded on priority in glue linked list */
void gl_dbl_lkdlist_priority_insert(gldblelist_t *base_glthread,
                              gldblelist_t *glthread,
                              int (*comp_fn)(void *, void *),
                              int offset)
{

    gldblelist_t *curr = NULL,
               *prev = NULL;

    init_gl_dbl_lkdlist(glthread);

    if (IS_GLTHREAD_LIST_EMPTY(base_glthread))
    {
        gl_dbl_lkdlist_add_next(base_glthread, glthread);
        return;
    }

    /* Only one node*/
    if (base_glthread->right && !base_glthread->right->right)
    {
        if (comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(base_glthread->right, offset),
                    GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread, offset)) == -1)
        {
            gl_dbl_lkdlist_add_next(base_glthread->right, glthread);
        }
        else
        {
            gl_dbl_lkdlist_add_next(base_glthread, glthread);
        }
        return;
    }

    if (comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread, offset),
                GLTHREAD_GET_USER_DATA_FROM_OFFSET(base_glthread->right, offset)) == -1)
    {
        gl_dbl_lkdlist_add_next(base_glthread, glthread);
        return;
    }

    ITERATE_GLTHREAD_BEGIN(base_glthread, curr)
    {

        if (comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthread, offset),
                    GLTHREAD_GET_USER_DATA_FROM_OFFSET(curr, offset)) != -1)
        {
            prev = curr;
            continue;
        }

        gl_dbl_lkdlist_add_next(curr, glthread);
        return;
    }
    ITERATE_GLTHREAD_END(base_glthread, curr);

    /*Add in the end*/
    gl_dbl_lkdlist_add_next(prev, glthread);
}
