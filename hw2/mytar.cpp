#include "mytar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <time.h>

using namespace std;

void load(string filename)
{
    fstream fs(filename);
    stringstream s;

    while (fs.peek() != EOF)
    {
        token file;

        fs.read(file.filename, 100);
        fs.read(file.filemode, 8);
        fs.read(file.userid, 8);
        fs.read(file.groupid, 8);
        fs.read(file.filesize, 12); //filesize
        fs.read(file.mtime, 12);
        fs.read(file.checksum, 8);
        fs.get(file.type);
        fs.read(file.lname, 100);
        fs.read(file.USTAR_id, 6);
        /*        if(file.USTAR_id[0] != 'u')
        {
            cerr<<"It's not the USTAR format\n";
            return;
        }*/
        fs.read(file.USTAR_ver, 2);
        fs.read(file.username, 32);
        fs.read(file.groupname, 32);
        fs.read(file.devmajor, 8);
        fs.read(file.devminor, 8);
        fs.read(file.prefix, 155);
        fs.read(file.pad, 12);

        s << oct << file.filesize; //convert octal to decimal
        s >> file.size;
        int x = ceil(file.size / 512.0) * 512; //align 512-size file block
        fs.seekg(x, ios::cur);

        s.str("");
        s.clear(); //clear stringstream

        output(file);
    }

    fs.close();
}

void output(token file)
{
    __type(file.type);

    for (int i = 4; i < 7; i++)
        __mode(file.filemode[i]);

    cout << " " << file.username << "/" << file.groupname
         << setw(10) << file.size
         << " ";

    __time(file.mtime);

    cout << " " << file.filename
         << endl;
}

void __type(char type)
{
    if (type == '1')
        cout << "h";
    else if (type == '2')
        cout << "l";
    else if (type == '5')
        cout << "d";
    else
        cout << "-";
}

void __mode(char filemode)
{
    int decimal = filemode - '0';
    (decimal / 4) ? cout << "r" : cout << "-";
    decimal %= 4;
    (decimal / 2) ? cout << "w" : cout << "-";
    decimal %= 2;
    (decimal) ? cout << "x" : cout << "-";
}

void __time(char t[])
{
    stringstream ss;
    time_t modi;
    ss << oct << t; //octal to decimal
    ss >> modi;

    struct tm *info = localtime(&modi);
    int m, d, h, n;
    //    cout << asctime(info) << " ";
    m = info->tm_mon + 1;
    d = info->tm_mday;
    h = info->tm_hour;
    n = info->tm_min;

    cout << info->tm_year + 1900 << "-";

    m >= 10 ? cout << m : cout << '0' << m; //less than 10, fill 0
    cout << "-";

    d >= 10 ? cout << d : cout << '0' << d;
    cout << " ";

    h >= 10 ? cout << h : cout << '0' << h;
    cout << ":";

    n >= 10 ? cout << n : cout << '0' << n;
}
