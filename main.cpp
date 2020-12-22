#include "node.h"
#include "visitor.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main() {
    Parser parser;
    IVisitorPtr calculation = makeVisitor<Calculation>();
    IVisitorPtr print = makeVisitor<Print>();
    std::string input;
    
    try {
        getline(std::cin, input);
        std::string_view input_view(input);
        parser.parse(input_view);
        INodePtr rootNode = parser.build();

        int result = rootNode->accept(calculation);
        std::cout << "Result: " << result << std::endl;

        std::cout << "Lexems: " << std::endl;
        rootNode->accept(print);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
