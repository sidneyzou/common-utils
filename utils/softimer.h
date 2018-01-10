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
 * \brief �����ʱ���ṹ�壬�����˱�Ҫ����Ϣ
 */
struct softimer {
    struct list_head node;          /**< \brief �����γ�����ṹ           */
    unsigned int        ticks;         /**< \brief ʣ��ʱ��tickֵ             */
    unsigned int        repeat_ticks;  /**< \brief �������ظ���ʱ��tick��     */
    void (*timeout_callback)( void *); /**< \brief ��ʱʱ�䵽�ص�����         */
    void               *p_arg;         /**< \brief �ص������Ĳ���             */
};

typedef struct softimer softimer_t;

/**
 * \brief �����ʱ��ģ���ʼ��
 *
 * \param[in] freq   : �����������ʱ����ʱ��Ƶ��
 * \retval OK     : ģ���ʼ���ɹ�����������ʹ��
 * \retval -EINVAL: ������Ч������handle��freq��ֵ
 */
int softimer_module_init (int freq);
    
/**
 * \brief ��ʼ��һ�������ʱ��
 *
 * \param[in] p_timer  : ָ��һ�������ʱ����ָ��
 * \param[in] p_func   : ��ʱʱ�䵽�Ļص�����
 * \param[in] p_arg    : �ص���������
 *
 * \retval OK      : �����ʱ����ʼ���ɹ�
 * \retval -EINVAL : ��Ч����
 * \retval -EPERM  : �����ʱ��ģ�黹δ��ʼ�������������У�����ȷ��ģ����ȷ��ʼ��
 */
int softimer_init(softimer_t *p_timer, pfnvoid_t p_func, void *p_arg);


/**
 * \brief ����һ�������ʱ��
 * \param[in] p_timer : ָ��һ�������ʱ����ָ��
 * \param[in] ms      : ��ʱʱ��(ms)
 * \return ��
 */
void softimer_start(softimer_t *p_timer, unsigned int ms);

/**
 * \brief ֹͣһ�������ʱ��
 * \param[in] p_timer : ָ��һ�������ʱ����ָ��
 * \return ��
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
