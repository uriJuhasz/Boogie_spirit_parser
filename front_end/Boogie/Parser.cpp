//
// Created by uri on 10/11/2016.
//

#include "Parser.h"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

#include <iostream>
using namespace std;

namespace front_end{
    namespace Boogie {
		  namespace spirit = boost::spirit;
		  namespace x3 = boost::spirit::x3;


		  using x3::uint_;
		  using x3::char_;
		  using x3::eol;
		  using x3::lexeme;

		  namespace grammar{
				using namespace x3;
				x3::rule<class skip_to_semicolon> const skip_to_semicolon("WIP");
				x3::rule<class semicolon> const semicolon(";");

				x3::rule<class program> const program("program");
				x3::rule<class declaration> const declaration("declaration");
				x3::rule<class type_declaration> const type_declaration("type declaration");


				x3::rule<class skip_parser> const skip_parser("skip");
				x3::rule<class line_comment> const line_comment("line comment");
				x3::rule<class const_declaration> const const_declaration("constant declaration");
				x3::rule<class var_declaration> const var_declaration("variable declaration");
				x3::rule<class axiom_declaration> const axiom_declaration("axiom declaration");

/*				x3::rule<class function_declaration> const function_declaration("function declaration");
				x3::rule<class procedure_declaration> const procedure_declaration("type declaration");
				x3::rule<class implementation_declaration> const implementation_declaration("type declaration");

				x3::rule<class attribute> const attribute("attribute");
				x3::rule<class identifier> const identifier("identifier");
				x3::rule<class semicolon> const semicolon("semicolon");

				x3::rule<class proc_signature> const proc_signature("procedure signature");
				x3::rule<class imp_signature> const imp_signature("implementation signature");
				x3::rule<class proc_body> const proc_body("procedure body");
				x3::rule<class proc_spec> const proc_spec("procedure specification");

*/
				auto const program_def =
					*declaration;

				auto const declaration_def =
					type_declaration
				|	const_declaration
				|	var_declaration
			   |  axiom_declaration
/*				|  function_declaration
				|  procedure_declaration
				|  implementation_declaration*/
				;

				auto const type_declaration_def =
					"type" >> skip_to_semicolon;

				auto const skip_to_semicolon_def =
				*(char_ - (semicolon)) >> semicolon
				;
				auto const semicolon_def =
					';'
				;
				auto const skip_parser_def =
					space | line_comment;

				auto const line_comment_def =
					lexeme["//" >> *(char_ - eol) >> eol];

				auto const const_declaration_def =
					"constant" >> skip_to_semicolon;
				auto const var_declaration_def =
					"var" >> skip_to_semicolon;
/*				auto const function_declaration_def =
					"function" >> skip_to_semicolon;
				auto const axiom_declaration_def =
					"axiom" >> skip_to_semicolon;
				auto const procedure_declaration_def =
					"procedure" >> *attribute >> identifier >> proc_signature >>
					((semicolon >> *proc_spec) | (*proc_spec >> proc_body));

				auto const implementation_declaration_def =
					"implementation" >> *attribute >> identifier >> imp_signature >> proc_body;
*/
				BOOST_SPIRIT_DEFINE(
				  program
				, declaration
				, type_declaration
				, skip_to_semicolon
				, semicolon
				, skip_parser
				, line_comment
	/*			, var_declaration
				, const_declaration
				, function_declaration
				, axiom_declaration
				, procedure_declaration
				, implementation_declaration*/
				)

		  }


       Parser::Parser(std::istream &_input) : input(_input){
			 input.unsetf(std::ios::skipws);
		 }

        void Parser::parse() {
			  spirit::istream_iterator iter(input);
			  spirit::istream_iterator end;

			  ;
			  auto r = x3::phrase_parse(iter,end,grammar::program,grammar::skip_parser);
			  cout << "-------------------------\n";
			  if (r && iter == end)
			  {
				  cout << "Parsing succeeded\n";
				  cout << "-------------------------\n";
			  }
			  else
			  {
				  string rest(iter, end);
				  cout << "Parsing failed\n";
				  cout << "stopped at: \n";
				  cout << rest << "\n";
				  cout << "-------------------------\n";
			  }
		  }

    }
}