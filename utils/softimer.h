#ifndef __SOFTIMER_H
#define __SOFTIMER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "common.h"
#include "list.h"
//#include "timer.h"


/**
 * \addtogroup if_softimer
 * \copydoc softimer.h
 * @{
 */

/**
 * \brief 软件定时器结构体，包含了必要的信息
 */
struct softimer {
    struct list_head node;          /**< \brief 用于形成链表结构           */
    unsigned int        ticks;         /**< \brief 剩余时间tick值             */
    unsigned int        repeat_ticks;  /**< \brief 保存下重复定时的tick数     */
    void (*timeout_callback)( void *); /**< \brief 定时时间到回调函数         */
    void               *p_arg;         /**< \brief 回调函数的参数             */
};

typedef struct softimer softimer_t;

/**
 * \brief 软件定时器模块初始化
 *
 * \param[in] freq   : 决定了软件定时器的时间频率
 * \retval OK     : 模块初始化成功，可以正常使用
 * \retval -EINVAL: 参数无效，请检查handle和freq的值
 */
int softimer_module_init (int freq);
    
/**
 * \brief 初始化一个软件定时器
 *
 * \param[in] p_timer  : 指向一个软件定时器的指针
 * \param[in] p_func   : 定时时间到的回调函数
 * \param[in] p_arg    : 回调函数参数
 *
 * \retval OK      : 软件定时器初始化成功
 * \retval -EINVAL : 无效参数
 * \retval -EPERM  : 软件定时器模块还未初始化，操作不运行，请先确保模块正确初始化
 */
int softimer_init(softimer_t *p_timer, pfnvoid_t p_func, void *p_arg);


/**
 * \brief 启动一个软件定时器
 * \param[in] p_timer : 指向一个软件定时器的指针
 * \param[in] ms      : 定时时间(ms)
 * \return 无
 */
void softimer_start(softimer_t *p_timer, unsigned int ms);

/**
 * \brief 停止一个软件定时器
 * \param[in] p_timer : 指向一个软件定时器的指针
 * \return 无
 */
void softimer_stop(softimer_t *p_timer);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SOFTIMER_H */

/* end of file */
