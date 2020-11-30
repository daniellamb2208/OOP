#include "lexer.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

int Lexer::line = 1;

int main()
{
    Lexer *lexer = new Lexer();
    try
    {
        while (true)
        {
            Token *t = lexer->scan();
            cout << "Token: " << setw(10) << left << t->toString() << t->getTag() << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}