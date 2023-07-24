#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

void clear_screen(void) {
#if defined(__is_libk)
    cls();
#else

#endif
}
