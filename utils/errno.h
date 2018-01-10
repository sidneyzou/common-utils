#ifndef __ERRNO_H
#define __ERRNO_H
 
#ifdef __cplusplus
extern "C" {
#endif


/**
 * \addtogroup if_errno
 * \copydoc errno.h
 * @{
 */

/**
 * \name POSIX����ֵ
 * @{
 */
#define EPERM           1       /**< \brief ����������          */
#define ENOENT          2       /**< \brief �ļ���Ŀ¼������    */
#define ESRCH           3       /**< \brief ���̲�����          */
#define EINTR           4       /**< \brief ���ñ��ж�          */
#define EIO             5       /**< \brief I/O ����            */
#define ENXIO           6       /**< \brief �豸���ַ������    */
#define E2BIG           7       /**< \brief �����б�̫��        */
#define ENOEXEC         8       /**< \brief ��ִ���ļ���ʽ����  */
#define EBADF           9       /**< \brief �ļ���������      */
#define ECHILD          10      /**< \brief û���ӽ���          */
#define EAGAIN          11      /**< \brief ��Դ�����ã�������  */
#define ENOMEM          12      /**< \brief �ռ䣨�ڴ棩����    */
#define EACCES          13      /**< \brief Ȩ�޲���            */
#define EFAULT          14      /**< \brief ��ַ����            */
#define ENOTEMPTY       15      /**< \brief Ŀ¼�ǿ�            */
#define EBUSY           16      /**< \brief �豸����Դæ        */
#define EEXIST          17      /**< \brief �ļ��Ѿ�����        */
#define EXDEV           18      /**< \brief ���豸����          */
#define ENODEV          19      /**< \brief �豸������          */
#define ENOTDIR         20      /**< \brief ����Ŀ¼            */
#define EISDIR          21      /**< \brief ��Ŀ¼              */
#define EINVAL          22      /**< \brief ��Ч����            */
#define ENFILE          23      /**< \brief ϵͳ���ļ�̫�࣬������������ */
#define EMFILE          24      /**< \brief �򿪵��ļ�̫��      */
#define ENOTTY          25      /**< \brief �����ʵ�I/O���Ʋ��� */
#define ENAMETOOLONG    26      /**< \brief �ļ���̫��          */
#define EFBIG           27      /**< \brief �ļ�̫��            */
#define ENOSPC          28      /**< \brief �豸ʣ��ռ䲻��    */
#define ESPIPE          29      /**< \brief ��Ч��������Invalid seek�� */
#define EROFS           30      /**< \brief �ļ�ϵͳֻ��        */
#define EMLINK          31      /**< \brief ����̫��            */
#define EPIPE           32      /**< \brief �𻵵Ĺܵ�          */
#define EDEADLK         33      /**< \brief ��Դ��������        */
#define ENOLCK          34      /**< \brief �޿��ã����У�����  */
#define ENOTSUP         35      /**< \brief ��֧��              */
#define EMSGSIZE        36      /**< \brief ��Ϣ̫��            */

/** @} */

/**
 * \name ANSI����ֵ
 * @{
 */

#define EDOM            37      /**< \brief ��ѧ��������������Χ */
#define ERANGE          38      /**< \brief ��ѧ����������̫�� */
#define EILSEQ          39      /**< \brief �Ƿ����ֽ�˳��       */
 
/** @} */

/**
 * \name ��������������
 * @{
 */

#define EDESTADDRREQ    40      /**< \brief ��ҪĿ���ַ         */
#define EPROTOTYPE      41      /**< \brief socketЭ�����ʹ���   */
#define ENOPROTOOPT     42      /**< \brief Э�鲻����           */
#define EPROTONOSUPPORT 43      /**< \brief Э�鲻֧��           */
#define ESOCKTNOSUPPORT 44      /**< \brief Socket���Ͳ�֧��     */
#define EOPNOTSUPP      45      /**< \brief socket��֧�ָò���   */
#define EPFNOSUPPORT    46      /**< \brief Э���岻֧��         */
#define EAFNOSUPPORT    47      /**< \brief ��ַ�ز�֧��         */
#define EADDRINUSE      48      /**< \brief ��ַ�Ѿ���ռ��       */
#define EADDRNOTAVAIL   49      /**< \brief ��ַ������           */
#define ENOTSOCK        50      /**< \brief ������������socket */

/** @} */

/**
 * \name ��ѡ��ʵ�ֵĴ���ֵ
 * @{
 */

#define ENETUNREACH     51        /**< \brief ���粻�ɴ�         */
#define ENETRESET       52        /**< \brief �����ж�������     */
#define ECONNABORTED    53        /**< \brief �����ж�           */
#define ECONNRESET      54        /**< \brief ���Ӹ�λ           */
#define ENOBUFS         55        /**< \brief ����ռ䲻��       */
#define EISCONN         56        /**< \brief Socket�Ѿ�����     */
#define ENOTCONN        57        /**< \brief Socketû������     */
#define ESHUTDOWN       58        /**< \brief Socket�Ѿ��رգ����ܷ������� */
#define ETOOMANYREFS    59        /**< \brief ����̫�࣬�޷�ƴ�� */
#define ETIMEDOUT       60        /**< \brief ���ӳ�ʱ           */
#define ECONNREFUSED    61        /**< \brief ���ӱ��ܾ�         */
#define ENETDOWN        62        /**< \brief �����Ѿ�ֹͣ       */
#define ETXTBSY         63        /**< \brief �ı��ļ�æ         */
#define ELOOP           64        /**< \brief �������Ӽ���̫��   */
#define EHOSTUNREACH    65        /**< \brief �������ɴ�         */
#define ENOTBLK         66        /**< \brief �ǿ��豸           */
#define EHOSTDOWN       67        /**< \brief �����Ѿ��ر�       */

/** @} */

/**
 * \name ���������ж�I/O����ֵ
 * @{
 */

#define EINPROGRESS     68         /**< \brief �������ڽ����� */
#define EALREADY        69         /**< \brief ��������ʹ���� */

/* 70 */

#define EWOULDBLOCK     EAGAIN  /**< \brief ������������ͬEAGAIN�� */
#define ENOSYS          71         /**< \brief ��֧�ֵĹ��ܣ�����δʵ�֣�*/
 
/** @} */

/**
 * \name �첽I/O����ֵ
 * @{
 */
#define ECANCELED       72         /**< \brief �����Ѿ�ȡ�� */

/* 73 */
/** @} */

/**
 * \name ����ش���ֵ
 * @{
 */
#define ENOSR           74        /**< \brief û������Դ */
#define ENOSTR          75        /**< \brief �������豸 */
#define EPROTO          76        /**< \brief Э����� */
#define EBADMSG         77        /**< \brief �𻵵���Ϣ */
#define ENODATA         78        /**< \brief ���������� */
#define ETIME           79        /**< \brief ��ioctl()��ʱ */
#define ENOMSG          80        /**< \brief û���������Ϣ���� */
#define EUCLEAN         81        /**< \brief Structure��Ҫ���� */
/** @} */                            

/**
* \name �����Զ������ֵ
 * @{
 */
 
#define EFULL           100     /**< \brief ��               */ 
#define EEMPTY          101     /**< \brief ��               */
#define ERXOV           102     /**< \brief �������         */
#define ETXUR           103     /**< \brief ����Underrun���� */
#define ESSA            104     /**< \brief �ӻ�����         */
#define ESSD            105     /**< \brief �ӻ��������     */
#define EHIGH           106     /**< \brief ֵ����           */
#define ELOW            107     /**< \brief ֵ����           */

/** @} */

/** \brief �û��Զ��������ʼֵ */
#define ERRNO_USER_START 2000

/** \brief �û��Զ������ֵ */
#define ERRNO_USER(x)    (ERRNO_USER_START + (x))

/** @} */

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __ERRNO_H */

/* end of file */
