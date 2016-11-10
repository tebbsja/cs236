/*
 * main.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: mocklera
 */

#include <iostream>
#include <string>
#include "Parser.h"
#include "Database.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Get filenames from command line
    char* input_file = "/Users/Austin/Desktop/C++/cs236/lab5/lab5/in61.txt";//argv[1];
    char* output_file = "/Users/Austin/Desktop/C++/cs236/Test/test_5/test_5/out61.txt"; //argv[2];
    
    // Run the scanner
    //std::cout << "Running Scanner..." << std::endl;
    Scanner* scanner = new Scanner(input_file);
    scanner->scan();
    std::vector<Token*> tokens = scanner->getTokens();
    //std::cout << "\tFinished Scanning!" << std::endl;
    
    // Run the parser
    //std::cout << "Running Parser..." << std::endl;
    Parser * parser = new Parser(tokens);
    //std::cout << "\tFinished Parsing!" << std::endl;
    
    DatalogProgram program = parser->get_program();
    
    // Make the database and load in the program
    Database db = Database();
    db.load(program);
    
    std::ofstream output(output_file);
    
    // Evaluate Schemes
    //std::cout << "Evaluating Schemes..." << std::endl;
    db.evaluate_schemes();
    //output << "Scheme Evaluation\n\n";
    //std::cout << "\tSchemes Evaluated!" << std::endl;
    
    // Evaluate Facts
    //std::cout << "Evaluating Facts..." << std::endl;
    db.evaluate_facts();
    //output << "Fact Evaluation\n\n";
    //output << db.relations_to_string();
    //std::cout << "\tFacts Evaluated!" << std::endl;
    
    // Evaluate Rules
    
    // TODO: This is where the new code will be called && the new output will go.
    //output << "Rule Evaluation\n";
    //cout << db.initialize_graph();
    db.initialize_graph();
    //cout << db.evaluate_rules_from_graph();
    db.evaluate_rules_from_graph();
    //output << db.evaluate_rules(db.program.rules);
    
    // Evaluate Queries
    //std::cout << "Evaluating Queries..." << std::endl;
    //std::string query_results = db.evaluate_queries();
   // output << query_results;
    //std::cout << "\tQueries Evaluated!" << std::endl;
    
    output.close();
    //std::cout << "\nFinished Output!" << std::endl;
    
    // Clean up
    delete scanner;
    scanner = NULL;
    delete parser;
    parser = NULL;
    
    return 0;
}


