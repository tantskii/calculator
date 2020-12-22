#include "node.h"
#include "visitor.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main() {
    Parser parser;
    IVisitorPtr visitor = makeVisitor<Calculation>();
    std::string input;
    
    try {
        getline(std::cin, input);
        std::string_view input_view(input);
        parser.parse(input_view);
        INodePtr root = parser.build();
        std::cout << root->accept(visitor) << std::endl;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
