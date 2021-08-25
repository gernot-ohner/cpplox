//
// Created by gernotohner on 17.08.21.
//

#include "Scanner.h"
#include "Runner.h"

#include <utility>

std::vector<Token> Scanner::scanTokens() {

    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = line});
    return this->tokens;
}

Scanner::Scanner(std::string source) : source{std::move(source)} {}

bool Scanner::isAtEnd() {
    return current >= source.size();
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '[':
            addToken(TokenType::LEFT_BRACE);
            break;
        case ']':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;

        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        case '/':
            if (match('/')) {
                // a comment goes on until the end of the line
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        case '\"':
            string();
            break;

        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c)) {
                identifier();
            } else if (c == ' ') { // do nothing
            } else {
//                hadError = true;
                Runner::error(line, "Unexpected character.");
                break;
            }
    }
}

char Scanner::advance() {
    return source.at(current++);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;
    current++;
    return true;
}

void Scanner::addToken(TokenType type, literal_t literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token{.type = type,
            .lexeme = text,
            .literal = std::move(literal),
            .line = line
    });
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        Runner::error(line, "Unterminated string.");
        return;
    }

    advance();

    auto literal = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, literal);

}

void Scanner::number() {

    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peekNext())) {
        advance(); // consume the '.'

        while (std::isdigit(peek())) advance();
    }

    auto number = std::stod(source.substr(start, current - start));
    addToken(TokenType::NUMBER, number);
}

char Scanner::peekNext() {
    if (current + 1 >= source.size()) return '\0';
    else return source.at(current + 1);
}

void Scanner::identifier() {

    advance();
    while (std::isalnum(peek())) advance();

    auto identifier = source.substr(start, current - start);
    if (keywords.contains(identifier)) {
        addToken(keywords.at(identifier));
    } else {
        addToken(TokenType::IDENTIFIER, identifier);
    }
}



