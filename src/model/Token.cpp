//
// Created by gernotohner on 17.08.21.
//

#include <sstream>
#include "Token.h"

std::string Token::toString() const {
    std::stringstream ss;
    ss << "{ lexeme: " << lexeme << ", token type: " << magic_enum::enum_name(type) << ", line: " << line;
    if (holds_alternative<std::string>(literal)) ss << ", literal: " << get<std::string>(literal);
    else if (holds_alternative<double>(literal)) ss << ", literal: " << get<double>(literal);
    // TODO (25.8.2021) technically I should put the bool into literal_t rather than into expr_t
    //   but something breaks at this point if I do.
    //else if (holds_alternative<bool>(literal)) ss << ", literal: " << get<bool>(literal);
    ss << "}";
    return ss.str();
}

bool Token::operator==(const Token &other) const {
    return this->type == other.type
           && this->lexeme == other.lexeme
           && this->line == other.line
           && this->literal == other.literal;
}

std::ostream &operator<<(std::ostream &os, Token const &token) {
    os << token.toString();
    return os;
}
