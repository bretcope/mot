#include <cassert>
#include <cstring>
#include <algorithm>
#include "Token.h"
#include "../io/Utf8.h"
#include "Lexer.h"


Token::Token(TokenType type, FileSpan trivia, FileSpan text, MotString* value):
        _type(type),
        _trivia(trivia),
        _text(text),
        _value(value)
{
    assert(trivia.End() == text.Start());

#ifndef NDEBUG
    switch (type)
    {
        case TokenType::Word:
        case TokenType::LineText:
        case TokenType::QuotedText:
        case TokenType::BlockText:
            assert(value != nullptr);
            break;
        default:
            assert(value == nullptr);
    }
#endif
}

Token::~Token()
{
    delete _value;
}

bool Token::IsToken() const
{
    return true;
}

TokenType Token::Type() const
{
    return _type;
}

const FileSpan& Token::Trivia() const
{
    return _trivia;
}

const FileSpan& Token::Text() const
{
    return _text;
}

void Token::DebugPrint(FILE* stream, bool positions, bool color) const
{
    auto reset = color ? "\033[0m" : "";
    auto boldGreen = color ? "\033[1;32m" : "";
    auto boldBlue = color ? "\033[1;34m" : "";
    auto boldRed = color ? "\033[1;31m" : "";
    auto red = color ? "\033[31m" : "";
    auto yellow = color ? "\033[33m" : "";

    auto tokenColor = _type == TokenType::EndOfLine ? boldBlue : boldGreen;
    if (_type <= TokenType::Error_)
        tokenColor = boldRed;

    auto tokenName = GetTokenTypeName(_type);

    auto start = _text.Start();

    fprintf(stream, "%s%s%s ", tokenColor, tokenName, reset);

    if (positions)
    {
        // todo: use out_column param
        uint32_t lineNumber, lineStart;
        _text.Content()->PositionDetails(start, &lineNumber, &lineStart, nullptr);
        fprintf(stream, "%u:%u ", lineNumber, start - lineStart + 1);
    }

    if (_value != nullptr)
    {
        if (_type == TokenType::BlockText)
            fprintf(stream, "\n");

        fprintf(stream, "%s", yellow);
        _value->Print(stream);
    }

    fprintf(stream, "%s\n", reset);
}

const MotString* Token::Value() const
{
    return _value;
}
