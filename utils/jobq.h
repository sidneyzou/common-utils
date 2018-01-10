/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AMKS16 SPI寄存器模块接口
 *
 * \internal
 * \par Modification history
 * - 1.00 16-07-21  ldm, first implementation.
 * \endinternal
 */

#ifndef  __JOBQ_H
#define  __JOBQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "jobq.h"

#define JOBQ_TASK_NUM    10  /* 任务队列中同时存在的个数  */

int jobq_init(void);

int jobq_push_job(pfnvoid_t p_func, void *p_arg);

void jobq_process(void);
#ifdef __cplusplus
}
#endif

#endif /*__JOBQ_H */

/* end of file */
