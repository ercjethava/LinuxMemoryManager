#ifndef __GLUELIST__
#define __GLUELIST__

typedef struct _gldblelist
{

    struct _gldblelist *left;
    struct _gldblelist *right;
} gldblelist_t;

void gl_dbl_lkdlist_add_next(gldblelist_t *base_glthread, gldblelist_t *new_glthread);

void ggl_dbl_lkdlist_add_before(gldblelist_t *base_glthread, gldblelist_t *new_glthread);

void remove_gl_dbl_lkdlist(gldblelist_t *glthread);

void init_gl_dbl_lkdlist(gldblelist_t *glthread);

void gl_dbl_lkdlist_add_last(gldblelist_t *base_glthread, gldblelist_t *new_glthread);

#define IS_GLTHREAD_LIST_EMPTY(glthreadptr) \
    ((glthreadptr)->right == 0 && (glthreadptr)->left == 0)

#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name, glthreadptr)                             \
    static inline structure_name *fn_name(gldblelist_t *glthreadptr)                                       \
    {                                                                                                    \
        return (structure_name *)((char *)(glthreadptr) - (char *)&(((structure_name *)0)->field_name)); \
    }


#define BASE(glthreadptr) ((glthreadptr)->right)

#define ITERATE_GLTHREAD_BEGIN(glthreadptrstart, glthreadptr)    \
    {                                                            \
        gldblelist_t *_glthread_ptr = NULL;                        \
        glthreadptr = BASE(glthreadptrstart);                    \
        for (; glthreadptr != NULL; glthreadptr = _glthread_ptr) \
        {                                                        \
            _glthread_ptr = (glthreadptr)->right;

#define ITERATE_GLTHREAD_END(glthreadptrstart, glthreadptr) \
    }                                                       \
    }

#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthreadptr, offset) \
    (void *)((char *)(glthreadptr)-offset)

void delete_gl_dbl_lkdlist(gldblelist_t *base_glthread);

unsigned int
get_gl_dbl_lkdlist_count(gldblelist_t *base_glthread);

void gl_dbl_lkdlist_priority_insert(gldblelist_t *base_glthread,
                              gldblelist_t *glthread,
                              int (*comp_fn)(void *, void *),
                              int offset);
                              
#endif 
