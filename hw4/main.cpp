#include "lexer.cpp"
#include <iostream>
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
            cout << "Token: " << t->toString() << endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}