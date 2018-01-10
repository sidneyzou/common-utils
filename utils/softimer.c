#include "softimer.h"
#include "common.h"


/** \brief ���������ʱ����Ӳ����ʱ������Ƶ�ʣ���������ʱ��Ƶ�ʲ���Ϊ0 */
static unsigned int __g_hwtimer_freq = 0;

/** \brief �����ʱ�������ͷ */
static struct list_head g_softimer_head;

#if   defined (__GNUC__)

static uint32_t __int_cpu_lock(void)
{
    uint32_t key;

    __asm volatile ("MRS %0, primask" : "=r" (key) );

    __asm volatile ("cpsid i" : : : "memory");
    
    return key;
}

static void __int_cpu_unlock(uint32_t key)
{
    __asm volatile ("MSR primask, %0" : : "r" (key) : "memory");
}
#elif defined   (__CC_ARM)
#endif
/******************************************************************************/
static unsigned int __ms_to_ticks (unsigned int ms)
{
    if (__g_hwtimer_freq != 0) {
        return  DIV_ROUND_UP(__g_hwtimer_freq * ms, 1000u);
    }
    return 0;
}

/******************************************************************************/
static void __softimer_add (softimer_t *p_timer, unsigned int ticks)
{
    struct list_head  *p;
    softimer_t        *p_timer_iterator = NULL;
    
    list_for_each(p, &g_softimer_head) {
        p_timer_iterator = list_entry(p, softimer_t, node);
        if (ticks >= p_timer_iterator->ticks ) {  /* ��ͬʱ��Ӧ�����ڽڵ���� */
            ticks -= p_timer_iterator->ticks;
        } else {
            break;
        }
    }
    p_timer->ticks = ticks;

    list_add_tail( &p_timer->node, p);         /* ����ȷ��λ�ò��붨ʱ��   */
    
    if (p != &g_softimer_head ) {                 /* p��ָ��ʱ����ʱҪ����    */
        p_timer_iterator->ticks -= ticks;
    }
}

/******************************************************************************/
static void __softimer_remove (softimer_t *p_timer)
{
    softimer_t *p_next = NULL;

    if (list_empty(&p_timer->node) ) {         /* �ڵ�δ����������         */
        return ;
    }
    
    /* ��ǰ�ڵ㲻�����һ���ڵ�, ɾ���ýڵ�ǰ������һ���ڵ����ʱtick���� */
    if ( (&p_timer->node)->next != &g_softimer_head ) {
        p_next = list_entry((&p_timer->node)->next, softimer_t, node);
        p_next->ticks += p_timer->ticks;
    }
    
    list_del_init(&p_timer->node);
}

/******************************************************************************/
void softimer_hwtimer_callback (void *p_arg)
{
    int old = __int_cpu_lock();
 
    if ( !list_empty( &g_softimer_head ) ) {

        struct list_head *p;
        softimer_t       *p_timer;
        
        /* ָ���һ����ЧԪ�ؽڵ� */
        p       = (&g_softimer_head)->next;
        p_timer = list_entry(p, softimer_t, node);
        
        /* 
         * �����׽ڵ�ֵ��1
         */
        if (p_timer->ticks) {
            p_timer->ticks--;
        }

        while (!list_empty(&g_softimer_head)) {
            
            /* 
             * �����һ����ЧԪ��,�����ý���Ȼ�����ڵ�һ�����
             * (�����ڵ�һ����㣬��ֵҲ����Ϊ 0�����´�ɨ��ͻ��˳�)
             */
            if (p_timer->ticks == 0) {

                /* �ýڵ㱾�ζ�ʱʱ�䵽��ɾ���ýڵ�                  */
                list_del_init(&p_timer->node);
                
                /* �����ڻص�������ֹͣ������Ƚ���������ӽ�������  */
                __softimer_add(p_timer, p_timer->repeat_ticks); 
                
                if (p_timer->timeout_callback ) {
                    p_timer->timeout_callback(p_timer->p_arg);
                }
                
                /* ������һ���ڵ㣬�����ж���һ���׽ڵ�ʱ���Ƿ�Ϊ0 */
                p       = (&g_softimer_head)->next;
                p_timer = list_entry(p, softimer_t, node);
                
                
            /* ֻҪ������Ϊ0�Ľ�㣬���˳�ѭ�� */
            } else {
                break;
            }
        }
    }
    __int_cpu_unlock(old);
}

/******************************************************************************/
int softimer_module_init (int freq)
{
    
    INIT_LIST_HEAD(&g_softimer_head);
    
    __g_hwtimer_freq = freq;
    
    return TRUE;
}
    
/******************************************************************************/
int softimer_init (softimer_t *p_timer, 
                   pfnvoid_t   p_func,
                   void       *p_arg)
{
    int old;
    
    if (__g_hwtimer_freq == 0) {                      /* Ӳ����ʱ��δ�������� */
        return -EPERM;
    }
    
    INIT_LIST_HEAD(&p_timer->node);

    old = __int_cpu_lock();
    
    p_timer->timeout_callback = p_func;
    p_timer->p_arg            = p_arg;
    
    __int_cpu_unlock(old);
    
    return TRUE;
}

/******************************************************************************/
void softimer_start (softimer_t *p_timer, unsigned int ms)
{
    int old;
    unsigned int ticks =  __ms_to_ticks(ms);
    old = __int_cpu_lock();
    
    /* ticks��СֵΪ1 */
    ticks = ticks > 0 ? ticks : 1;
    
    p_timer->repeat_ticks = ticks;
    
    __softimer_remove(p_timer);
    __softimer_add(p_timer, ticks);
    __int_cpu_unlock(old);
}

/******************************************************************************/
void softimer_stop (softimer_t *p_timer)
{
    int old;
    old = __int_cpu_lock();
    __softimer_remove(p_timer);
    __int_cpu_unlock(old);
}

/* end of file */
