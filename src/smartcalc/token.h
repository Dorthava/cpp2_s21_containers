#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_TOKEN_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_TOKEN_H

#include <string>

namespace s21 {
class Token {
 public:
  // Конструкторы и деструкторы
  Token() = default;
  Token(const char& transcript, const std::string& tokens,
        const short& priority);
  Token(const Token& other);
  Token(Token&& token);
  Token& operator=(const Token& other) = delete;
  Token& operator=(const Token&& other);
  ~Token() = default;

  // Что это за символ
  bool isDigit() const;
  bool isPMOperator() const;
  bool isOperator() const;
  bool isOpenBracket() const;
  bool isCloseBracket() const;
  bool isBinary() const;
  void SetToken(const size_t& index);

  char transcript_;
  std::string tokens_;
  short priority_;
};
}  // namespace s21

// #include "token.cc"
#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_TOKEN_H
