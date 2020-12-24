#include "visitor.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main() {
    Parser parser;
    parser.define("x", "20");
	parser.define("y", "10");
	parser.define("z", "50");

    IVisitorPtr calculation = makeVisitor<Calculation>();
    IVisitorPtr print = makeVisitor<Print>();
    std::string input;
    
    try {
        getline(std::cin, input);
        std::string_view input_view(input);

        INodePtr root_node = parser.build(input_view);

        int result = root_node->accept(calculation);
        std::cout << "Result: " << result << std::endl;

        std::cout << "Lexems: " << std::endl;
        root_node->accept(print);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
