#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_MODEL_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_MODEL_H

#include <math.h>

#include <list>
#include <stack>
#include <string_view>
#include <vector>

#include "token.h"

namespace s21 {

class Model {  // В этом классе мы должны все обработать и вернуть выше в
               // контроллер.
 public:
  // Конструкторы:
  Model();
  Model(const Model& other) = delete;
  Model(Model&& other) = delete;
  Model& operator=(const Model& other) = delete;
  Model& operator=(Model&& other) = delete;
  ~Model() = default;

  // Проверка на правописание:
  std::vector<Token> CheckCondition();
  std::vector<Token> GetWords(const std::string& text);

  double CalculatingResult();
  void ConvertionPostfix(const std::vector<Token>& checked);

  // Вспомогательные функции
  void EvaluationOperation(const char& token);
  void EvaluationFunction(const char& token);

  //  Сеттеры
  void SetReceived(const std::string& received);  // Check received
  void SetValueX(const double& valueX);
  void SetBinaryOp(Token& token, const char& transcript);

  // Геттеры

  Token CheckAvailabilityOF(const std::string& str);

 private:
  std::string received_string_;  // Принимаемая строка.
  std::list<Token> post_expression_;  // Преобразованное в постфиксный
                                      // вид(очередь) выражение.
  double valueX_;  // Тут хранится значение x в виде строки.
  std::stack<double> calculation_;  // Стек для вычисления значений.
};
};  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_MODEL_H
