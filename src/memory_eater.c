#include <stdio.h>
#include <stdlib.h>

// Created by benapetr@gmail.com
// This simple program allocates as many RAM as defined in memory_to_eat


// memory_to_eat is in kilobytes
// Try to allocate max 6GB
unsigned long long memory_to_eat = 1024 * 1024 * 6;
size_t eaten_memory = 0;
char *memory = NULL;

void write_kilobyte(char *pointer, size_t offset)
{
    int size = 0;
    while (size < 1024)
    {
        pointer[offset + (size_t) size++] = 1;
    }
}

int eat_kilobyte()
{
    if (memory == NULL)
    {
        memory = malloc(1024);
    } else
    {
        memory = realloc(memory, (eaten_memory * 1024) + 1024);
    }
    if (memory == NULL)
    {
        return 1;
    }
    else
    {
        write_kilobyte(memory, eaten_memory * 1024);
        eaten_memory++;
        return 0;
    }
}

int main(int argc, char **argv)
{
    printf("I will try to eat %i kb of ram\n", memory_to_eat);
    int megabyte = 0;
    int megabytes = 0;
    while (memory_to_eat-- > 0)
    {
        if (eat_kilobyte())
        {
            printf("Failed to allocate more memory! Stucked at %i kb :(\n", eaten_memory);
            return 200;
        }
        if (megabyte++ >= 1024)
        {
            megabytes++;
            printf("Eaten %i  MB of ram\n", megabytes);
            megabyte = 0;
        }
    }
    printf("Successfully eaten requested memory!\n");
    free(memory);
    return 0;
}

