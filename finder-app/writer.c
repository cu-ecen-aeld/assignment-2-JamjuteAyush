#include "fcntl.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "syslog.h"
#include "unistd.h"

int main(int argc, char * argv[])
{
    printf("running writer application\n");
    openlog(NULL, 0, LOG_USER);
    if(argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments %d\n", argc);
        return 1;
    }
    else
    {
        int fd;
        char* write_str = argv[2];
        char* file_str = argv[1];
        size_t size = strlen(write_str);
        fd = open (file_str, O_WRONLY | O_CREAT | O_TRUNC, 0644); // 0644 (u=rw, grp=r, oth=r)
        
        if(fd == -1)
        {
            syslog(LOG_ERR, "%s\n", strerror(errno));
            return 1;
        }
        else
        {
            syslog(LOG_DEBUG, "Writing %s to %s\n", write_str, file_str);
            write(fd, write_str, size);
            close(fd);
            return 0;
        }
    }
}