#include <stdio.h>
#include <unistd.h>

/* Rules: Sequential counting up to X.
*  Is X divisible by 3? Replace with "bizz"
*  Is X divisible by 5? Replace with "buzz"
*  Is X divisible by 3 and 5? Replace with "bizz buzz"
*/

int main(void)
{
    int i = 0;

    for (i = 1; i <= 50; ++i) {
        if (i % 3 == 0 && i % 5 == 0)
            printf("Bizz Buzz\n");
        else if (i % 3 == 0)
            printf("Bizz\n");
        else if (i % 5 == 0)
            printf("Buzz\n");
        else
            printf("%d\n", i);

        usleep(150*1000);
    }
    return 0;
}
