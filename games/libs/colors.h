/*  0 -> normal ;  31 -> red
*   1 -> bold ;  36 -> cyan
*   4 -> underline ;  32 -> green
*   9 -> strike ;  34 -> blue
*
*   I.e. "\033[0;31m" (red)
*       "\033[1;31m" (red bold)
*
*   Description: Specifies color codes for the terminal
*   To make certain text more easily distinguishable.
*/


#define color_red   "\033[0;31m"
#define color_cyan  "\033[0;36m"
#define color_green "\033[0;32m"
#define color_blue  "\033[0;34m"
#define color_black  "\033[0;30m"
#define color_brown  "\033[0;33m"
#define color_magenta  "\033[0;35m"
#define color_gray  "\033[0;37m"
#define color_reset "\033[0m"
