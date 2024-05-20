#ifndef _ALIAS_H_
#define _ALIAS_H_

#define alias(old, new)                                                        \
	extern __typeof(old) new __attribute__((__alias__(#old)))
#define weak_alias(old, new)                                                   \
	extern __typeof(old) new __attribute__((__weak__, __alias__(#old)))

#endif /* _ALIAS_H_ */
