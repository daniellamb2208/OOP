#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

enum Tag : int
{
    AND = 256,
    BASIC,
    BREAK,
    DO,
    ELSE,
    EQ,
    FALSE,
    GE,
    ID,
    IF,
    INDEX,
    LE,
    MINUS,
    NE,
    NUM,
    OR,
    REAL,
    TEMP,
    TRUE,
    WHILE
};

class Token
{
public:
    int tag;
    Token() = default;
    Token(int t) : tag(t) {}
    virtual string toString() { return "" + to_string(tag); }
    ~Token() = default;
};

class Word : public Token
{
public:
    string lexeme;
    Word() = default;
    Word(std::string s, int tag) : Token(tag), lexeme(s) {}
    string toString() override { return lexeme; }
    ~Word();
};

static Word *And = new Word(string("&&"), Tag::AND);
static Word *Or = new Word(string("||"), Tag::OR);
static Word *eq = new Word(string("=="), Tag::EQ);
static Word *ne = new Word(string("!="), Tag::NE);
static Word *le = new Word(string("<="), Tag::LE);
static Word *ge = new Word(string(">="), Tag::GE);
static Word *minus = new Word(string("minus"), Tag::MINUS);
static Word *True = new Word(string("true"), Tag::TRUE);
static Word *False = new Word(string("false"), Tag::FALSE);
static Word *tmep = new Word(string("t"), Tag::TEMP);

class Type : public Word
{
public:
    int width;
    Type(string s, int tag, int w = 0) : Word(s, tag), width(w) {}
    /*    static bool numeric(Type p)
    {
        if (p == Type::Char || p == Type::Int || p == Type::Float)
            return true;
        return false;
    }
    static Type *max(Type p1, Type p2)
    {
        if (!numeric(p1) || !numeric(p2))
            return nullptr;
        else if (p1 == Type::Float || p2 == Type::Float)
            return Type::Float;
        else if (p1 == Type::Int || p2 == Type::Int)
            return Type::Int;
        else
            return Type::Char;
    }*/
    ~Type();
};

static Type *Int = new Type(string("int"), Tag::BASIC, 4);
static Type *Float = new Type(string("float"), Tag::BASIC, 8);
static Type *Char = new Type(string("char"), Tag::BASIC, 1);
static Type *Bool = new Type(string("bool"), Tag::BASIC, 1);

class Num : public Token
{
public:
    const int value;
    Num(int v) : Token(Tag::NUM), value(v) {}
    string toString() override { return to_string(value); }
    ~Num();
};

class Real : public Token
{
public:
    const float value;
    Real(float v) : Token(Tag::REAL), value(v) {}
    string toString() override { return to_string(value); }
    ~Real();
};

class Lexer
{
public:
    static int line;
    char peek;

    map<string, Word *> words;
    void reserve(Word *w) { words[w->lexeme] = w; }
    Lexer() : peek(' ')
    {
        reserve(new Word(string("if"), Tag::IF));
        reserve(new Word(string("else"), Tag::ELSE));
        reserve(new Word(string("while"), Tag::WHILE));
        reserve(new Word(string("do"), Tag::DO));
        reserve(new Word(string("break"), Tag::BREAK));
        reserve(True);
        reserve(False);
        reserve(Int);
        reserve(Char);
        reserve(Bool);
        reserve(Float);
    }

    void readch()
    {
        char i;
        cin.get(i);
        if (!cin.eof())
            peek = static_cast<char>(i);
        else
        {
            cerr << "End of file reached\n";
            exit(EXIT_SUCCESS);
        }
    }

    bool readch(char c) //get next char
    {
        readch();
        if (peek != c)
            return false;
        peek = ' ';
        return true;
    }

    Token *scan()
    {
        for (;; readch())
        {
            if (peek == ' ' || peek == '\t')
                continue;
            else if (peek == '\n')
                line++;
            else
                break;
        }
        switch (peek)
        {
        case '&':
            if (readch('&'))
                return And;
            else
                return new Token('&');
        case '|':
            if (readch('|'))
                return Or;
            else
                return new Token('|');
        case '=':
            if (readch('='))
                return eq;
            else
                return new Token('=');
        case '!':
            if (readch('='))
                return ne;
            else
                return new Token('!');
        case '<':
            if (readch('='))
                return le;
            else
                return new Token('<');
        case '>':
            if (readch('='))
                return ge;
            else
                return new Token('>');
        }

        if (isdigit(peek))
        {
            int v = 0;
            do
            {
                v = 10 * v + (peek - '0');
                readch();
            } while (isdigit(peek));
            if (peek != '.')
                return new Num(v);

            float x = v;
            float d = 10;
            for (;;)
            {
                readch();
                if (!isdigit(peek))
                    break;
                x += ((peek - '0') / d);
                d *= 10;
            }
            return new Real(x);
        }

        if (isalpha(peek))
        {
            stringstream b;
            do
            {
                b << peek;
                readch();
            } while (isalpha(peek) || isdigit(peek));
            string s = b.str();

            auto iter = words.find(s);
            if (iter != words.end())
                return iter->second;
            Word *w = new Word(s, Tag::ID);
            words[s] = w;
            return w;
        }
        Token *tok = new Token(peek);
        peek = ' ';
        return tok;
    }
};