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
 * \name POSIX错误值
 * @{
 */
#define EPERM           1       /**< \brief 操作不允许          */
#define ENOENT          2       /**< \brief 文件或目录不存在    */
#define ESRCH           3       /**< \brief 进程不存在          */
#define EINTR           4       /**< \brief 调用被中断          */
#define EIO             5       /**< \brief I/O 错误            */
#define ENXIO           6       /**< \brief 设备或地址不存在    */
#define E2BIG           7       /**< \brief 参数列表太长        */
#define ENOEXEC         8       /**< \brief 可执行文件格式错误  */
#define EBADF           9       /**< \brief 文件描述符损坏      */
#define ECHILD          10      /**< \brief 没有子进程          */
#define EAGAIN          11      /**< \brief 资源不可用，需重试  */
#define ENOMEM          12      /**< \brief 空间（内存）不足    */
#define EACCES          13      /**< \brief 权限不够            */
#define EFAULT          14      /**< \brief 地址错误            */
#define ENOTEMPTY       15      /**< \brief 目录非空            */
#define EBUSY           16      /**< \brief 设备或资源忙        */
#define EEXIST          17      /**< \brief 文件已经存在        */
#define EXDEV           18      /**< \brief 跨设备连接          */
#define ENODEV          19      /**< \brief 设备不存在          */
#define ENOTDIR         20      /**< \brief 不是目录            */
#define EISDIR          21      /**< \brief 是目录              */
#define EINVAL          22      /**< \brief 无效参数            */
#define ENFILE          23      /**< \brief 系统打开文件太多，描述符不够用 */
#define EMFILE          24      /**< \brief 打开的文件太多      */
#define ENOTTY          25      /**< \brief 不合适的I/O控制操作 */
#define ENAMETOOLONG    26      /**< \brief 文件名太长          */
#define EFBIG           27      /**< \brief 文件太大            */
#define ENOSPC          28      /**< \brief 设备剩余空间不足    */
#define ESPIPE          29      /**< \brief 无效的搜索（Invalid seek） */
#define EROFS           30      /**< \brief 文件系统只读        */
#define EMLINK          31      /**< \brief 链接太多            */
#define EPIPE           32      /**< \brief 损坏的管道          */
#define EDEADLK         33      /**< \brief 资源可能死锁        */
#define ENOLCK          34      /**< \brief 无可用（空闲）的锁  */
#define ENOTSUP         35      /**< \brief 不支持              */
#define EMSGSIZE        36      /**< \brief 消息太大            */

/** @} */

/**
 * \name ANSI错误值
 * @{
 */

#define EDOM            37      /**< \brief 数学函数参数超出范围 */
#define ERANGE          38      /**< \brief 数学函数计算结果太大 */
#define EILSEQ          39      /**< \brief 非法的字节顺序       */
 
/** @} */

/**
 * \name 网络参数错误相关
 * @{
 */

#define EDESTADDRREQ    40      /**< \brief 需要目标地址         */
#define EPROTOTYPE      41      /**< \brief socket协议类型错误   */
#define ENOPROTOOPT     42      /**< \brief 协议不可用           */
#define EPROTONOSUPPORT 43      /**< \brief 协议不支持           */
#define ESOCKTNOSUPPORT 44      /**< \brief Socket类型不支持     */
#define EOPNOTSUPP      45      /**< \brief socket不支持该操作   */
#define EPFNOSUPPORT    46      /**< \brief 协议族不支持         */
#define EAFNOSUPPORT    47      /**< \brief 地址簇不支持         */
#define EADDRINUSE      48      /**< \brief 地址已经被占用       */
#define EADDRNOTAVAIL   49      /**< \brief 地址不可用           */
#define ENOTSOCK        50      /**< \brief 被操作对象不是socket */

/** @} */

/**
 * \name 可选择实现的错误值
 * @{
 */

#define ENETUNREACH     51        /**< \brief 网络不可达         */
#define ENETRESET       52        /**< \brief 网络中断了连接     */
#define ECONNABORTED    53        /**< \brief 连接中断           */
#define ECONNRESET      54        /**< \brief 连接复位           */
#define ENOBUFS         55        /**< \brief 缓冲空间不足       */
#define EISCONN         56        /**< \brief Socket已经连接     */
#define ENOTCONN        57        /**< \brief Socket没有连接     */
#define ESHUTDOWN       58        /**< \brief Socket已经关闭，不能发送数据 */
#define ETOOMANYREFS    59        /**< \brief 引用太多，无法拼接 */
#define ETIMEDOUT       60        /**< \brief 连接超时           */
#define ECONNREFUSED    61        /**< \brief 连接被拒绝         */
#define ENETDOWN        62        /**< \brief 网络已经停止       */
#define ETXTBSY         63        /**< \brief 文本文件忙         */
#define ELOOP           64        /**< \brief 符号链接级数太多   */
#define EHOSTUNREACH    65        /**< \brief 主机不可达         */
#define ENOTBLK         66        /**< \brief 非块设备           */
#define EHOSTDOWN       67        /**< \brief 主机已经关闭       */

/** @} */

/**
 * \name 非阻塞和中断I/O错误值
 * @{
 */

#define EINPROGRESS     68         /**< \brief 操作正在进行中 */
#define EALREADY        69         /**< \brief 连接正被使用中 */

/* 70 */

#define EWOULDBLOCK     EAGAIN  /**< \brief 操作会阻塞（同EAGAIN） */
#define ENOSYS          71         /**< \brief 不支持的功能（功能未实现）*/
 
/** @} */

/**
 * \name 异步I/O错误值
 * @{
 */
#define ECANCELED       72         /**< \brief 操作已经取消 */

/* 73 */
/** @} */

/**
 * \name 流相关错误值
 * @{
 */
#define ENOSR           74        /**< \brief 没有流资源 */
#define ENOSTR          75        /**< \brief 不是流设备 */
#define EPROTO          76        /**< \brief 协议错误 */
#define EBADMSG         77        /**< \brief 损坏的消息 */
#define ENODATA         78        /**< \brief 流中无数据 */
#define ETIME           79        /**< \brief 流ioctl()超时 */
#define ENOMSG          80        /**< \brief 没有所需的消息类型 */
#define EUCLEAN         81        /**< \brief Structure需要清理 */
/** @} */                            

/**
* \name 其它自定义错误值
 * @{
 */
 
#define EFULL           100     /**< \brief 满               */ 
#define EEMPTY          101     /**< \brief 空               */
#define ERXOV           102     /**< \brief 接收溢出         */
#define ETXUR           103     /**< \brief 发送Underrun错误 */
#define ESSA            104     /**< \brief 从机断言         */
#define ESSD            105     /**< \brief 从机解除断言     */
#define EHIGH           106     /**< \brief 值过高           */
#define ELOW            107     /**< \brief 值过低           */

/** @} */

/** \brief 用户自定义错误起始值 */
#define ERRNO_USER_START 2000

/** \brief 用户自定义错误值 */
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
