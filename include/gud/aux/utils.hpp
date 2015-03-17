#if !defined(GUD_AUX_UTILS_H_INCLUDED_)
#define GUD_AUX_UTILS_H_INCLUDED_

/**
 * Throws a runtime error exception with a text representation of the error.
 *
 * Remember to include <cerrno>.
 */
#define __throw_system_exception()                                           \
	do                                                                       \
	{                                                                        \
		int e = errno;                                                       \
		const char * s = std::strerror(e);                                   \
		throw std::runtime_error(s);                                         \
	} while(0)

#endif /* GUD_AUX_UTILS_H_INCLUDED_ */
