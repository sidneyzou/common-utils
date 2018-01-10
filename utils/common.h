/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file common.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief provide header files to be included by all project files. 
*
*******************************************************************************/


#ifndef _COMMON_H_
#define _COMMON_H_

#define swap_bytes(ptrWord)   *ptrWord = (*ptrWord >>8) | (*ptrWord<<8)

#define OK               0         /**< \brief OK               */
#define ERROR          (-1)        /**< \brief 一般错误         */

/**
 * \brief 求结构体成员的偏移
 * \attention 不同平台上，由于成员大小和内存对齐等原因，
 *            同一结构体成员的偏移可能是不一样的
 *
 * \par 示例
 * \code
 *  struct my_struct = {
 *      int  m1;
 *      char m2;
 *  };
 *  int offset_m2;
 *
 *  offset_m2 = AM_OFFSET(struct my_struct, m2);
 * \endcode
 */
#define OFFSET(structure, member)    ((int)(&(((structure *)0)->member)))

/** \brief 求结构体成员的偏移，同 \ref OFFSET 一样 */
#ifndef offsetof
#define offsetof(type, member)           OFFSET(type, member)
#endif

/**
 * \brief 通过结构体成员指针获取包含该结构体成员的结构体
 *
 * \param ptr    指向结构体成员的指针
 * \param type   结构体类型
 * \param member 结构体中该成员的名称
 *
 * \par 示例
 * \code
 *  struct my_struct = {
 *      int  m1;
 *      char m2;
 *  };
 *  struct my_struct  my_st;
 *  char             *p_m2 = &my_st.m2;
 *  struct my_struct *p_st = AM_CONTAINER_OF(p_m2, struct my_struct, m2);
 * \endcode
 */
#define CONTAINER_OF(ptr, type, member) \
            ((type *)((char *)(ptr) - offsetof(type,member)))
                
/**
 * \brief 通过结构体成员指针获取包含该结构体成员的结构体，
 *        同 \ref AM_CONTAINER_OF 一样
 */
#ifndef container_of
#define container_of(ptr, type, member)     CONTAINER_OF(ptr, type, member)
#endif

/** \brief 预取 */
#ifndef prefetch
#define prefetch(x) (void)0
#endif

/** \brief 倍数向上舍入 */
#define DIV_ROUND_UP(n, d)   (((n) + (d) - 1) / (d))

typedef unsigned long   dword;
typedef unsigned short  word;
typedef void (*pfnvoid_t) (void *);

/********************************************************************/

#include "stdlib.h"
#include "stdint.h"
#include "errno.h"
#include "types.h"
/********************************************************************/

#endif /* _COMMON_H_ */
