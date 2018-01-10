/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co.,  Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-21  zsp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup
 * \copydoc
 */


#include "jobq.h"
#include "list.h"
#include <string.h>
#include <assert.h>


#define __JOBQ_INFO_GET_FROM_ELM(p_elm, p_info) {\
                                                p_info = (jobq_info_t *)((int)p_elm - (int)&((jobq_info_t *)0)->elm);\
                                                }

typedef struct __jobq_info {
    pfnvoid_t         p_func;
    void             *p_arg;
    struct list_head  elm;
}jobq_info_t;

static jobq_info_t        __g_jobq_info[JOBQ_TASK_NUM];
static struct list_head   __g_jobq_list_head;


static jobq_info_t *__jobq_info_alloc(void)
{
    uint8_t i = 0;
    for (i = 0; i < JOBQ_TASK_NUM; i++) {
        if (__g_jobq_info[i].elm.next == NULL && __g_jobq_info[i].elm.prev == NULL) {
            return &__g_jobq_info[i];
        }
    }
    return NULL;
}

static void __jobq_info_free(jobq_info_t *p_jobq_info)
{
    assert(p_jobq_info != NULL);

    memset(p_jobq_info, 0, sizeof(jobq_info_t));
}



static void __jobq_entry(jobq_info_t *p_job_info)
{
    if (p_job_info->p_func) {
        p_job_info->p_func(p_job_info->p_arg);
    }
}


int jobq_init(void)
{
    memset(__g_jobq_info, 0, sizeof(__g_jobq_info));

    list_head_init(&__g_jobq_list_head);
    return OK;
}


int jobq_push_job(pfnvoid_t p_func, void *p_arg)
{
    jobq_info_t *p_job_info = __jobq_info_alloc();

    if (p_job_info) {
        p_job_info->p_func = p_func;
        p_job_info->p_arg  = p_arg;

        list_add_tail(&p_job_info->elm, &__g_jobq_list_head);
        return OK;
    }

//    printf("jobq push fail,func:0x%x\n", p_func);
    return ERROR;
}

void jobq_process(void)
{
    struct list_head *pos;
    struct list_head *n;
    jobq_info_t *p_job_info = NULL;
    list_for_each_safe(pos, n, &__g_jobq_list_head) {
        __JOBQ_INFO_GET_FROM_ELM(pos, p_job_info);
        __jobq_entry(p_job_info);
        list_del(&p_job_info->elm);
        __jobq_info_free(p_job_info);
    }
}
/* end of file */