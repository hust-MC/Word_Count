#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int testdev;
    int count = 0;
    unsigned char buf[4];
    testdev = open("/dev/wordcount", O_RDWR);
    if(testdev == -1)
    {
        printf("Can't open this file\n");
        return 0;
    }

    if(argc > 1)
    {
        write(testdev, argv[1], strlen(argv[1]));
        printf("write:%s\n", argv[1]);
    }
    read(testdev, buf, 4);

    count = ((int)buf[0]) << 24 | ((int)buf[1]) << 16 | ((int)buf[2]) << 8 | ((int)buf[3]);
    printf("the count is:%d\n", count);
    close(testdev);
    return 0;
}
