#include "mytar.h"

using namespace std;

bool parsecmd(int argc, char *argv[])
{
    int leng = strlen(argv[1]);

    if (argc < 2)
        cerr << "mytar: tar list requires an argument" << endl
             << "Try give a tar file to check the program" << endl;
    else if (argc > 2)
        cerr << "mytar: Too many arguments" << endl //there is a optional argv 'dir or file' can found in archive
             << "mytar: Exiting with failure status due to previous errors" << endl;
    else if (argv[1][leng - 1] == '/') //tar could recgnize whether is a directory no matter it has '/'
        cerr << "mytar: " << argv[1] << ": Cannot read: Is a directory" << endl
             << "mytar: At begining of tape, quitting now" << endl
             << "mytar: Error is not recoverable: exiting now" << endl;
    else if (!(argv[1][leng - 4] == '.' && argv[1][leng - 3] == 't' && argv[1][leng - 2] == 'a' && argv[1][leng - 1] == 'r'))
        cerr << "mytar: This does not look like a tar archive" << endl
             << "mytar: Skipping to next header" << endl
             << "mytar: Exiting with failure status due to previous errors" << endl;
    else
        return true;
        cout<<"?";
    return false;
}
void load(char *filename)
{
    fstream fs(filename);
    stringstream s;
    token file;

    if (!fs.is_open())
    {
        cerr << "mytar: fail to open the file" << endl;
        return;
    }

    while (fs.peek() != EOF)
    {
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

        char buffer; //check EOF
        fs.get(buffer);
        if (buffer == '\0')
        {
            fs.close();
            return;
        }
        else
            fs.seekg(-1, ios::cur);
    }

    fs.close();
}

void output(token file)//example output:  drwxrwxr-x lamb/lamb         0 2020-10-23 20:49 hw1/c/
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
