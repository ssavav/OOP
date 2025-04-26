        #pragma once
        #include <cstring>
        #include <io.h>
        #include <stdlib.h>
        #include <direct.h>

        // MSVC функции и их эквиваленты в MinGW
        #define _stricmp strcasecmp
        #define _strdup strdup
        #define _fileno fileno
        #define _wcsicmp wcscasecmp
        #define _exit exit
        #define _OUT_TO_STDERR 1
        #define _MAX_PATH 260

        // Заглушки для отсутствующих функций
        inline void _set_error_mode(int) {}
    