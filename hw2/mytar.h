#ifndef __MYTAR_H__
#define __MYTAR_H__

#include <string>

struct TarHeader
{
    char filename[100];
    char filemode[8];
    char userid[8];
    char groupid[8];
    char filesize[12]; //octal
    char mtime[12];    //last modification time in numeric Unix time format
    char checksum[8];
    char type;       //link indicator, 0 normal, 1 hard link, 2 sybolic link
    char lname[100]; //name of linkd file
    /* USTAR Section */
    char USTAR_id[6];
    char USTAR_ver[2];
    char username[32];
    char groupname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char pad[12];

    int size;//file size in decimal
};
typedef struct TarHeader token;

void load(std::string);
void output(token);
void __type(char);
void __mode(char);
void __time(char[]);

#endif