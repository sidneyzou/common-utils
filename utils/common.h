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
#define ERROR          (-1)        /**< \brief һ�����         */

/**
 * \brief ��ṹ���Ա��ƫ��
 * \attention ��ͬƽ̨�ϣ����ڳ�Ա��С���ڴ�����ԭ��
 *            ͬһ�ṹ���Ա��ƫ�ƿ����ǲ�һ����
 *
 * \par ʾ��
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

/** \brief ��ṹ���Ա��ƫ�ƣ�ͬ \ref OFFSET һ�� */
#ifndef offsetof
#define offsetof(type, member)           OFFSET(type, member)
#endif

/**
 * \brief ͨ���ṹ���Աָ���ȡ�����ýṹ���Ա�Ľṹ��
 *
 * \param ptr    ָ��ṹ���Ա��ָ��
 * \param type   �ṹ������
 * \param member �ṹ���иó�Ա������
 *
 * \par ʾ��
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
 * \brief ͨ���ṹ���Աָ���ȡ�����ýṹ���Ա�Ľṹ�壬
 *        ͬ \ref AM_CONTAINER_OF һ��
 */
#ifndef container_of
#define container_of(ptr, type, member)     CONTAINER_OF(ptr, type, member)
#endif

/** \brief Ԥȡ */
#ifndef prefetch
#define prefetch(x) (void)0
#endif

/** \brief ������������ */
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
