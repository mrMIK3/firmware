
#ifndef  ERR_H_
#define  ERR_H_


static const char* const  appName = "hello_world"; 

#define  FOREACH_ES(esPrial) \
	esPrial( 0, ERR_OK             , "OK (no error)") \
\
	esPrial( 1, ERR_MALLOC_QUEUE   , "malloc() fail - queue") \
	esPrial( 2, ERR_MALLOC_STATE   , "malloc() fail - state") \
	esPrial( 3, ERR_MALLOC_TEXT    , "malloc() fail - text") \
	esPrial( 4, ERR_MALLOC_VIEW    , "malloc() fail - viewport") \
	esPrial( 5, ERR_NO_MUTEX       , "Cannot create mutex") \
	esPrial( 6, ERR_NO_GUI         , "Cannot open GUI") \
	esPrial( 7, ERR_NO_TIMER       , "Cannot create timer") \
\
	esPrial(10, ERR_MUTEX_BLOCK    , "Mutex block failed") \
	esPrial(11, ERR_MUTEX_RELEASE  , "Mutex release failed") \
\
	esPrial(20, ERR_QUEUE_RTOS     , "queue - Undefined RTOS error") \
	esPrial(21, DEBUG_QUEUE_TIMEOUT, "queue - Timeout") \
	esPrial(22, ERR_QUEUE_RESOURCE , "queue - Resource not available") \
	esPrial(23, ERR_QUEUE_BADPRM   , "queue - Bad parameter") \
	esPrial(24, ERR_QUEUE_NOMEM    , "queue - Out of memory") \
	esPrial(25, ERR_QUEUE_ISR      , "queue - Banned in ISR") \
	esPrial(26, ERR_QUEUE_UNK      , "queue - Unknown") \
	\
	esPrial(30, WARN_ANIM_START    , "Animate - Already started") \
	esPrial(31, WARN_ANIM_STOP     , "Animate - Already stopped") \
	esPrial(32, ERR_TIMER_START    , "Animate - Cannot start timer") \
	esPrial(33, ERR_TIMER_STOP     , "Animate - Cannot stop timer") \

#define  ES_ENUM(num, ename, string)    ename = num,
#define  ES_STRING(num, ename, string)  string"\r\n",

typedef
	enum err  { FOREACH_ES(ES_ENUM) }
err_t ;


#ifdef ERR_C_
	const char* const  errs[] = { FOREACH_ES(ES_STRING) };
#else
	extern  const char* const  errs[];
#endif


#undef  ES_ENUM
#undef  ES_STRING
#undef  FOREACH_ES

#endif
