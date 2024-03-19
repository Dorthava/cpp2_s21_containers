#include "token.h"

namespace s21 {
Token::Token(const char &transcript, const std::string &tokens,
             const short &priority)
    : transcript_(transcript), tokens_(tokens), priority_(priority) {}

Token::Token(const Token &other) {
  transcript_ = other.transcript_;
  tokens_ = other.tokens_;
  priority_ = other.priority_;
}

Token::Token(Token &&other) {
  transcript_ = std::move(other.transcript_);
  tokens_ = std::move(other.tokens_);
  priority_ = std::move(other.priority_);
}

s21::Token &s21::Token::operator=(const s21::Token &&other) {
  transcript_ = other.transcript_;
  tokens_ = other.tokens_;
  priority_ = other.priority_;
  return *this;
}

bool Token::isDigit() const { return transcript_ == 'd' || transcript_ == 'x'; }

bool Token::isPMOperator() const {
  return transcript_ == '+' || transcript_ == '-';
}

bool Token::isOperator() const {
  return transcript_ == '*' || transcript_ == '/' || transcript_ == '^' ||
         transcript_ == 'M';
}

bool Token::isOpenBracket() const { return transcript_ == '('; }

bool Token::isCloseBracket() const { return transcript_ == ')'; }

bool Token::isBinary() const { return priority_ == 5; }

void Token::SetToken(const size_t &index) {
  Token result;
  switch (index) {
    case 0:
      *this = Token('+', "+", 1);
      break;
    case 1:
      *this = Token('-', "-", 1);
      break;
    case 2:
      *this = Token('*', "*", 2);
      break;
    case 3:
      *this = Token('/', "/", 2);
      break;
    case 4:
      *this = Token('^', "^", 4);
      break;
    case 5:
      *this = Token('M', "mod", 2);
      break;
    case 6:
      *this = Token('c', "cos", 6);
      break;
    case 7:
      *this = Token('s', "sin", 6);
      break;
    case 8:
      *this = Token('t', "tan", 6);
      break;
    case 9:
      *this = Token('C', "acos", 6);
      break;
    case 10:
      *this = Token('S', "asin", 6);
      break;
    case 11:
      *this = Token('T', "atan", 6);
      break;
    case 12:
      *this = Token('q', "sqrt", 6);
      break;
    case 13:
      *this = Token('l', "ln", 6);
      break;
    case 14:
      *this = Token('L', "log", 6);
      break;
    case 15:
      *this = Token('(', "(", 0);
      break;
    case 16:
      *this = Token(')', ")", 0);
      break;
    case 17:
      *this = Token('x', "x", 0);
      break;
    default:
      break;
  }
}

}  // namespace s21
