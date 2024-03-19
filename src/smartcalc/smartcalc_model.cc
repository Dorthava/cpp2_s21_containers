#include "smartcalc_model.h"

namespace s21 {

// Конструкторы
s21::Model::Model()
    : received_string_(""), post_expression_(), valueX_(0.), calculation_() {}

void Model::SetReceived(
    const std::string&
        received) {  // Если в поле lineEdit что-то поменяется - поменяется всё.
  received_string_ = received;
  post_expression_.clear();
}

void Model::SetValueX(const double& valueX) { valueX_ = valueX; }

Token Model::CheckAvailabilityOF(const std::string& str) {
  std::vector<std::string> literals{
      "+",    "-",    "*",    "/",    "^",  "mod", "cos", "sin", "tan",
      "acos", "asin", "atan", "sqrt", "ln", "log", "(",   ")",   "x"};
  short size{};
  for (auto it = literals.begin();
       it != literals.end() && str.compare(0, (*it).length(), *it); ++it) {
    ++size;
  }
  if (size == 18) throw std::string("Unknown character");
  Token result;
  result.SetToken(size);
  return result;
}

std::vector<Token> Model::GetWords(const std::string& text) {
  std::vector<std::string> words;
  std::vector<Token> result;
  size_t begin{text.find_first_not_of(" \n\t")};
  while (begin != std::string::npos) {
    size_t end = text.find_first_of(" ", begin + 1);
    if (end == std::string::npos) end = text.length();
    words.push_back(text.substr(begin, end - begin));
    begin = text.find_first_not_of(" ", end + 1);
  }

  for (std::string word :
       words) {  // все элементы мы тупо попилим на части: числа с запятыми,
                 // операторы, функции. В конец запушим результат(если функции
                 // будут неполными + лишние символы)
    auto it_begin = word.begin();
    for (auto it = word.begin(); it != word.end(); ++it) {
      auto it_end = it;
      if (std::isdigit(*it) || *it == '.') {
        while (std::isdigit(*it_end) || *it_end == '.') ++it_end;
        if (*it_end == 'e') {
          ++it_end;
          if (*it_end == '-' || *it_end == '+') ++it_end;
          if (!std::isdigit(*it_end))
            throw std::string(
                "Violation of the integrity of exponential notation");
          while (std::isdigit(*it_end)) ++it_end;
        }
        result.push_back(
            Token('d', word.substr(it - it_begin, it_end - it), 0));
        it = --it_end;
      } else {
        Token token = CheckAvailabilityOF(word.substr(it - it_begin));
        result.push_back(token);
        it += token.tokens_.size() - 1;
      }
    }
  }
  return result;
}

void s21::Model::SetBinaryOp(s21::Token& token, const char& transcript) {
  if (transcript == '-')
    token = Token('~', "~", 5);
  else
    token = Token('p', "p", 5);
}

std::vector<Token> Model::CheckCondition() {
  auto res = GetWords(received_string_);
  std::vector<Token> words(std::move(res));
  if (words.empty()) throw std::string("Line is empty");
  short brackets_open{};
  for (auto it_word = words.begin(); it_word != words.end();) {
    auto it_copy = it_word++;
    if ((*it_copy).isDigit() || (*it_copy).transcript_ == 'x') {
      short check_ptr{};
      for (auto it = (*it_copy).tokens_.begin();
           check_ptr <= 1 && it != (*it_copy).tokens_.end(); ++it) {
        if (*it == '.') ++check_ptr;
      }
      if (check_ptr > 1 ||
          (*(*it_copy).tokens_.begin() == '.' &&
           (*it_copy).tokens_.end() == ++(*it_copy).tokens_.begin()))
        throw std::string("Incorrect number entered");
      if (it_word != words.end() &&
          ((*it_word).isDigit() || (*it_word).transcript_ == 'x'))
        throw std::string("Two or more numbers in a row");
    } else if ((*it_copy).isOperator()) {
      if ((*it_word).isOperator() || (*it_word).isPMOperator() ||
          (*it_word).isCloseBracket() || it_word == words.end() ||
          it_copy == words.begin())
        throw std::string("Error after statement");
    } else if ((*it_copy).isPMOperator() || (*it_copy).isBinary()) {
      if (((*it_copy).isPMOperator() && it_copy == words.begin()))
        SetBinaryOp(*it_copy, (*it_copy).transcript_);
      if ((*it_word).isOperator() || (*it_word).isPMOperator() ||
          (*it_word).isCloseBracket() || it_word == words.end())
        throw std::string("Erroneous expression");
    } else if ((*it_copy).isOpenBracket()) {
      if ((it_word != words.end() && (*it_copy).isOpenBracket() &&
           (*it_word).isPMOperator()))
        SetBinaryOp(*it_word, (*it_word).transcript_);

      brackets_open += 1;
      if ((it_word != words.end() &&
           ((*it_word).isOperator() || (*it_word).isCloseBracket())) ||
          it_word == words.end())
        throw std::string("Erroneous expression");
    } else if ((*it_copy).isCloseBracket()) {
      brackets_open -= 1;
      // if(it_word != words.end() && ((*it_word).isOpenBracket() ||
      // (*it_word).isFunction() || (*it_word).isDigit())) words.insert(it_copy,
      // Token('*')); Есть и есть че бубнить
    } else {
      if (!(*it_word).isOpenBracket())
        throw std::string("Erroneous expression");
    }
    if (brackets_open <= -1) throw std::string("Erroneous expression");
  }

  return words;
}

void Model::ConvertionPostfix(const std::vector<Token>& checked) {
  std::stack<Token> storage;
  for (auto it = checked.begin(); it != checked.end(); ++it) {
    if ((*it).isDigit())
      post_expression_.push_back(*it);
    else if ((*it).isOpenBracket()) {
      storage.push(*it);
    } else if ((*it).isCloseBracket()) {
      while (!storage.top().isOpenBracket()) {
        post_expression_.push_back(storage.top());
        storage.pop();
      }
      storage.pop();
    } else {
      if (storage.empty()) {
        storage.push(*it);
      } else {
        if ((*it).priority_ <= storage.top().priority_) {
          while (!storage.empty() &&
                 (((*it).priority_ != 4 &&
                   (*it).priority_ <= storage.top().priority_) ||
                  ((*it).priority_ == 4 &&
                   (*it).priority_ < storage.top().priority_))) {
            post_expression_.push_back(storage.top());
            storage.pop();
          }
        }
        storage.push(*it);
      }
    }
  }
  while (!storage.empty()) {
    post_expression_.push_back(storage.top());
    storage.pop();
  }
}

void s21::Model::EvaluationOperation(const char& token) {
  double spare(calculation_.top());
  calculation_.pop();
  if (token == '+')
    calculation_.top() += spare;
  else if (token == '-')
    calculation_.top() -= spare;
  else if (token == '*')
    calculation_.top() *= spare;
  else if (token == '/')
    calculation_.top() /= spare;
  else if (token == '^')
    calculation_.top() = pow(calculation_.top(), spare);
  else
    calculation_.top() = static_cast<int>(calculation_.top()) %
                         static_cast<int>(spare);  // проверить на инт.
}

void s21::Model::EvaluationFunction(const char& token) {
  if (token == 'c')
    calculation_.top() = cos(calculation_.top());
  else if (token == 's')
    calculation_.top() = sin(calculation_.top());
  else if (token == 't')
    calculation_.top() = tan(calculation_.top());
  else if (token == 'C')
    calculation_.top() = acos(calculation_.top());
  else if (token == 'S')
    calculation_.top() = asin(calculation_.top());
  else if (token == 'T')
    calculation_.top() = atan(calculation_.top());
  else if (token == 'l')
    calculation_.top() = log10(calculation_.top());
  else if (token == 'L')
    calculation_.top() = log(calculation_.top());
  else
    calculation_.top() = sqrt(calculation_.top());
}

double s21::Model::CalculatingResult() {
  std::vector<Token> checked_str;
  post_expression_.clear();
  checked_str = CheckCondition();
  ConvertionPostfix(checked_str);
  if (!calculation_.empty()) calculation_.pop();
  for (auto post_word : post_expression_) {
    if (post_word.transcript_ == 'x') {
      calculation_.push(valueX_);
    } else if (post_word.isDigit()) {
      calculation_.push(std::stod(post_word.tokens_));
    } else if (post_word.isBinary()) {
      calculation_.top() = post_word.transcript_ == '~' ? -calculation_.top()
                                                        : calculation_.top();
    } else if (post_word.isOperator() || post_word.isPMOperator()) {
      EvaluationOperation(post_word.transcript_);
    } else
      EvaluationFunction(post_word.transcript_);
  }
  while (calculation_.size() > 1) {
    double copy(calculation_.top());
    calculation_.pop();
    calculation_.top() *= copy;
  }
  return calculation_.top();
}
}  // namespace s21
