#ifndef HEAPS_ASSERTIONS_H
#define HEAPS_ASSERTIONS_H

#include <exception>
#include <string>

class AssertionException : public std::exception {
    std::string message;

    const char *what() const noexcept override {
        return message.c_str();
    }

public:
    AssertionException(const std::string &message) : message(message) {}
};


#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
#define DESCRIPTION(file, line) std::string("  [line ") + \
    std::string(STR(line)) + \
    std::string(", file ") + \
    std::string(STR(file)) + \
    std::string("]")

#define ASSERT_EQUAL(a, b) {if (a != b) \
    throw AssertionException(std::string(STR(a)) + std::string(" is not equal to ") + std::string(STR(b)) + \
     DESCRIPTION(__FILE__, __LINE__));}

#define ASSERT_THROW(expr, ExceptionClass) { \
    bool thrown = false; \
    try {expr;} \
    catch (const ExceptionClass &e) {thrown = true;} \
    catch (const std::exception &e) { \
      throw AssertionException( \
      std::string("While evaluating expression '") + \
      std::string(STR(expr)) + \
      std::string("' expected exception: ") + \
      std::string(STR(ExceptionClass)) + \
      std::string(" but another exception was thrown: ") + \
      std::string(e.what()) + \
      DESCRIPTION(__FILE__, __LINE__)); \
    } \
    if (!thrown) throw AssertionException( \
    std::string("expression '") + \
    std::string(STR(expr)) + \
    std::string("' evaluated but exception not thrown: ") + \
    std::string(STR(ExceptionClass)) + \
    DESCRIPTION(__FILE__, __LINE__)); }

#define ASSERT_NO_THROW(expr) { \
    try {expr;} \
    catch (const std::exception &e) { throw AssertionException( \
      std::string("While evaluating expression '") + \
      std::string(STR(expr)) + \
      std::string("' no exceptions expected but one was thrown: ") + \
      std::string(e.what()) + \
      DESCRIPTION(__FILE__, __LINE__)); \
      } \
}
#endif //HEAPS_ASSERTIONS_H
