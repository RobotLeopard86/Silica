// library/lexers/../src/serialization/json/lexer_json.yy.h generated by reflex 3.0.11 from library/lexers/json.l

#ifndef REFLEX_LIBRARY_LEXERS____SRC_SERIALIZATION_JSON_LEXER_JSON_YY_H
#define REFLEX_LIBRARY_LEXERS____SRC_SERIALIZATION_JSON_LEXER_JSON_YY_H
#define IN_HEADER 1
#define REFLEX_VERSION "3.0.11"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#undef REFLEX_OPTION_dotall
#undef REFLEX_OPTION_fast
#undef REFLEX_OPTION_freespace
#undef REFLEX_OPTION_header_file
#undef REFLEX_OPTION_lex
#undef REFLEX_OPTION_lexer
#undef REFLEX_OPTION_namespace
#undef REFLEX_OPTION_noline
#undef REFLEX_OPTION_outfile
#undef REFLEX_OPTION_unicode

#define REFLEX_OPTION_dotall true
#define REFLEX_OPTION_fast true
#define REFLEX_OPTION_freespace true
#define REFLEX_OPTION_header_file "library/lexers/../src/serialization/json/lexer_json.yy.h"
#define REFLEX_OPTION_lex lex
#define REFLEX_OPTION_lexer LexerJson
#define REFLEX_OPTION_namespace rf_json
#define REFLEX_OPTION_noline true
#define REFLEX_OPTION_outfile "library/lexers/../src/serialization/json/lexer_json.yy.cpp"
#define REFLEX_OPTION_unicode true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %top user code                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>   // strtoul(), strtod()
#include <iomanip>   // std::setw
#include <iostream>  // std::cout etc.

#include "../position.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  ABSTRACT LEXER CLASS                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/abslexer.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

namespace rf_json {

class LexerJson : public reflex::AbstractLexer<reflex::Matcher> {

 public:
  LexerJson(const char* input, size_t input_size) : LexerJson(reflex::Input(input, input_size)) {
  }

  er::Position get_position() {
    return er::Position{.column = columno(), .line_number = lineno()};
  }

  inline std::string& get_word() {
    return _word;
  }

 private:
  std::string _word;  // token value for token '$' (string)

 public:
  typedef reflex::AbstractLexer<reflex::Matcher> AbstractBaseLexer;
  LexerJson(const reflex::Input& input = reflex::Input(), std::ostream& os = std::cout) : AbstractBaseLexer(input, os) {
  }
  static const int INITIAL = 0;
  static const int STRING = 1;
  virtual int lex(void);
  int lex(const reflex::Input& input) {
    in(input);
    return lex();
  }
  int lex(const reflex::Input& input, std::ostream* os) {
    in(input);
    if (os)
      out(*os);
    return lex();
  }
};

}  // namespace rf_json

#endif
