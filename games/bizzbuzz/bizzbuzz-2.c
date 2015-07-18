/* Rules: Sequential counting up to X.
*  Is X divisible by 3? Replace with "bizz"
*  Is X divisible by 5? Replace with "buzz"
*  Is X divisible by 3 and 5? Replace with "bizz buzz"
*
* Additional rule to make things a little harder
* ---------------------------------------------
* The modulus operator is not allowed
*/

#include <stdio.h>
#include <stdlib.h> // EXIT macros

int main(void)
{
    for (int i = 1; i <= 50; ++i) {
        if ((i - (i/3 * 3)) == 0 && (i - (i / 5 * 5)) == 0) {
            printf("Bizz Buzz\n");
        }

        else if ((i - (i / 3 * 3)) == 0) {
            printf("Bizz\n");
        }

        else if ((i - (i / 5 * 5)) == 0) {
            printf("Buzz\n");
        }

        else
            printf("%d\n", i);
    }
    return EXIT_SUCCESS;
}
