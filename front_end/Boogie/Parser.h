#ifndef FRONTEND_BOOGIE_PARSER_H
#define FRONTEND_BOOGIE_PARSER_H

#include <istream>

namespace front_end{
namespace Boogie{

class Parser {
public:
    Parser(std::istream& input);
    void parse();
private:
    std::istream& input;
};

}
}


#endif //FRONTEND_BOOGIE_PARSER_H
