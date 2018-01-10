/**
 * \file
 * \brief ͨ������������ض���ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * \endinternal
 */

#ifndef __TYPES_H
#define __TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdio.h"
//#include "errno.h"
 
/**
 * \addtogroup if_types
 * \copydoc types.h
 * @{
 */
#ifdef __GNUC__

typedef _Bool bool_t;
#define TRUE   1
#define FALSE  0
#else

#ifndef TRUE

/**
 * \brief �������Ͷ���
 */
typedef int bool_t;

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#endif /* TRUE */

#endif

/**
 * \brief ��ָ�붨��
 */
#ifndef NULL
#define NULL      ((void *)0)
#endif
 
/**
 * \brief inline ����
 * @{
 */
#if   defined (__CC_ARM)     

typedef	 long		off_t;	

#define inline   __inline             /**< inline for ARMCC    */
#define static_inline  static  __inline
    
#elif defined (__ICCARM__)
#define inline   inline               /**< inline for IAR      */
#define static_inline  static inline

#elif defined   (__GNUC__)
#define inline   inline               /**< inline for GNU      */
#define static_inline  static inline

#elif defined   (__TASKING__)
#define inline   inline               /**< inline for TASKING  */
#define static_inline  static inline

#endif /* __CC_ARM */
/** @} */

#ifdef __cplusplus
  #define   __I     volatile             /**< Defines ֻ��     */
#else
  #define   __I     volatile const       /**< Defines ֻ��     */
#endif
#define     __O     volatile             /**< Defines ֻд     */
#define     __IO    volatile             /**< Defines �ɶ���д */


/** \brief void (*pfn) (void *) */
typedef void (*pfnvoid_t) (void *);

/** \brief unsigned int type for short   */
typedef unsigned int    uint_t;

/** \brief unsigned char type for short  */
typedef unsigned char   uchar_t;

/** \brief unsigned long type for short  */
typedef unsigned long   ulong_t;

/** \brief unsigned short type for short */
typedef unsigned short  ushort_t;

/** \brief the tick type for system ticks */
typedef unsigned long   tick_t;

/**
 * @} 
 */
 
#ifdef __cplusplus
}
#endif
 
#endif /* __TYPES_H */

/* end of file */
