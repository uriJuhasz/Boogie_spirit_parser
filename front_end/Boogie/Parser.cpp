//
// Created by uri on 10/11/2016.
//

#include "Parser.h"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

namespace front_end{
    namespace Boogie {
		  namespace spirit = boost::spirit;
		  namespace x3 = boost::spirit::x3;


		  using x3::uint_;
		  using x3::char_;

		  namespace grammar{
				x3::rule<class program> const program("program");
				x3::rule<class declaration> const declaration("declaration");
				x3::rule<class type_declaration> const type_declaration("type declaration");
				x3::rule<class const_declaration> const const_declaration("constant declaration");
				x3::rule<class var_declaration> const var_declaration("variable declaration");
				x3::rule<class axiom_declaration> const axiom_declaration("axiom declaration");
				x3::rule<class function_declaration> const function_declaration("function declaration");
				x3::rule<class procedure_declaration> const procedure_declaration("type declaration");
				x3::rule<class implementation_declaration> const implementation_declaration("type declaration");

				x3::rule<class attribute> const attribute("attribute");
				x3::rule<class identifier> const identifier("identifier");
				x3::rule<class semicolon> const semicolon("semicolon");

				x3::rule<class proc_signature> const proc_signature("procedure signature");
				x3::rule<class imp_signature> const imp_signature("implementation signature");
				x3::rule<class proc_body> const proc_body("procedure body");
				x3::rule<class proc_spec> const proc_spec("procedure specification");

				x3::rule<class skip_to_semicolon> const skip_to_semicolon("WIP");

				auto const program_def =
					*declaration;

				auto const declaration_def =
					type_declaration
				|	const_declaration
				|	var_declaration
				|  function_declaration
				|  axiom_declaration
				|  procedure_declaration
				|  implementation_declaration
				;

				auto const type_declaration_def =
					"type" >> skip_to_semicolon;
				auto const const_declaration_def =
					"constant" >> skip_to_semicolon;
				auto const var_declaration_def =
					"var" >> skip_to_semicolon;
				auto const function_declaration_def =
					"function" >> skip_to_semicolon;
				auto const axiom_declaration_def =
					"axiom" >> skip_to_semicolon;
				auto const procedure_declaration_def =
					"procedure" >> *attribute >> identifier >> proc_signature >>
					((semicolon >> *proc_spec) | (*proc_spec >> proc_body));

				auto const implementation_declaration_def =
					"implementation" >> *attribute >> identifier >> imp_signature >> proc_body;

				BOOST_SPIRIT_DEFINE(
				  program = program_def
				, declaration = declaration_def
				, type_declaration = type_declaration_def
				, var_declaration = var_declaration_def
				, const_declaration = const_declaration_def
				, function_declaration = function_declaration_def
				, axiom_declaration = axiom_declaration_def
				, procedure_declaration = procedure_declaration_def
				, implementation_declaration = implementation_declaration_def
				);


		  }


       Parser::Parser(std::istream &_input) : input(_input){
			 input.unsetf(std::ios::skipws);
		 }

        void Parser::parse() {
			  spirit::istream_iterator begin(input);
			  spirit::istream_iterator end;

				x3::parse(begin,end,program);
        }

    }
}