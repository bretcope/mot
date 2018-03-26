#ifndef GOT_LEXER_H
#define GOT_LEXER_H


#include <cstddef>
#include <cstdint>
#include "Token.h"

class Lexer
{
private:
    const char* _input;         ///< Raw binary representation of the file to lex. Encoding is expected to be UTF-8.
    uint32_t _position = 0;     ///< Current byte position in the input;
    uint32_t _size;             ///< The size (in bytes) of the input.
    int _indentLevel = 0;       ///< Number of indent tokens which have been emitted, minus the number of outdent tokens emitted.
    uint32_t _lineNumber = 0;   ///< The number of times a new line sequence (LF or CRLF) has been encountered.
    uint32_t _lineStart;        ///< Byte position of the first character of the current line.
    uint32_t _lineSpaces;       ///< The number of spaces before first non-space character on the current line. Used to detect indentation levels.

    Token* _nextToken = nullptr;                        ///< Next unconsumed token, stored here for peek operations.
    Span _trivia = {};                                  ///< Span of leading trivia which will be attached to the next lexed token.
    TokenType _lastTokenType = TokenType::StartOfInput; ///< The last token type lexed.

public:
    const int SPACES_PER_INDENT = 4;

    Lexer(const char* input, uint32_t size);
    ~Lexer();

    Token* Peek();
    Token* Advance();

private:
    Token* Lex();
    void ConsumeTrivia();
    Token* LexEndOfInput();
    Token* LexIndentation();
    Token* LexEndOfLine(char currentChar);
    Token* LexWord();
    Token* LexLineText();
    Token* LexQuotedText();
    Token* LexBlockText();
    /**
     * Denotes the start of a new line (does not update _position).
     * @param lineStart The position of the start of the line.
     * @return The number of spaces at the start of the new line.
     */
    uint32_t StartNewLine(uint32_t lineStart);
    Token* NewToken(TokenType type, uint32_t length);
};


#endif //GOT_LEXER_H