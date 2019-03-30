#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nums[2][2]={{1,2},{3,4}};
    int* p=nums[0];
    printf("%d  %d",*p,*(p+1));
    return 0;
}
