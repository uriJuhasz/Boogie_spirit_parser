//
// Created by uri on 10/11/2016.
//

#include "Parser.h"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct_named.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <iostream>
#include <list>
#include <string>

using namespace std;

namespace front_end{
    namespace Boogie {
		  namespace spirit = boost::spirit;
		  namespace x3 = boost::spirit::x3;


		  using x3::uint_;
		  using x3::char_;
		  using x3::eol;
		  using x3::lexeme;
		  using x3::position_tagged;
		  using boost::fusion::traits::tag_of;

		  namespace AST{
			   class VariableDeclaration;
			   class ConstantDeclaration;
			   class TypeDeclaration;
			   class FunctionDeclaration;
			   class Axiom;
			   class Identifier;
			   class Attribute;

				class ASTNode : public x3::position_tagged{};
				class Program : public ASTNode
				{
					 std::list<VariableDeclaration> vars;
					 std::list<ConstantDeclaration> consts;
					 std::list<TypeDeclaration> types;
					 std::list<FunctionDeclaration> functions;
					 std::list<Axiom> axioms;
				};
			   class Identifier{
				    string name;
			   };
				class NamedDeclaration : public ASTNode{
					 Identifier name;
				};
			   class Attribute : public ASTNode{
				    Identifier name;
			   };
				class TypeDeclaration : public NamedDeclaration{};
				class VariableDeclaration : public NamedDeclaration{};
				class ConstantDeclaration : public NamedDeclaration{};
				class FunctionDeclaration : public NamedDeclaration{};
				class Axiom : public ASTNode{};
				using boost::fusion::operator<<;

/*				struct var_declaration;
				struct type_declaration;
				struct const_declaration;
				struct named_declaration: x3::position_tagged
				{
					 string name;
				};
				struct var_declaration : named_declaration{};
				struct const_declaration : named_declaration{};
				struct type_declaration : named_declaration{};
				*/
		  }

	  namespace grammar{
				using namespace x3;

//				typedef x3::rule<identifier, std::string> identifier_type;
//				identifier_type const identifier = "identifier";


				x3::rule<class skip_to_semicolon> const skip_to_semicolon("WIP");
		      x3::rule<class skip_balanced_curly> const skip_balanced_curly("WIP2");
		      x3::rule<class skip_non_curly> const skip_non_curly("WIP3");
		      x3::rule<class skip_balanced_parenthesis> const skip_balanced_parenthesis("WIP2");
		      x3::rule<class skip_non_parenthesis> const skip_non_parenthesis("WIP3");
				x3::rule<class semicolon> const semicolon(";");
		      x3::rule<class type_args> const type_args("type arguments");

				x3::rule<class program/*,Boogie::AST::Program*/> const program("program");
				x3::rule<class type_declaration,Boogie::AST::TypeDeclaration> const type_declaration("type declaration");
		      x3::rule<class const_declaration,Boogie::AST::ConstantDeclaration> const const_declaration("constant declaration");
		      x3::rule<class var_declaration,Boogie::AST::VariableDeclaration> const var_declaration("variable declaration");
		      x3::rule<class axiom,Boogie::AST::Axiom> const axiom("axiom");
		      x3::rule<class function_declaration,Boogie::AST::FunctionDeclaration> const function_declaration("function declaration");

				x3::rule<class identifier,Boogie::AST::Identifier> const identifier("identifier");

				x3::rule<class skip_parser> const skip_parser("skip");
				x3::rule<class line_comment> const line_comment("line comment");

		      x3::rule<class function_signature> const function_signature("function signature");
		      x3::rule<class function_body> const function_body("function body");
		      x3::rule<class attribute/*,Boogie::AST::Attribute*/> const attribute("attribute");
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
				*(
					   type_declaration
				   |	const_declaration
				   |	var_declaration
					|  axiom
				|  function_declaration
/*				|  procedure_declaration
				|  implementation_declaration*/
				);

				auto const type_declaration_def =
					"type" >> identifier >> skip_to_semicolon;


				auto const const_declaration_def =
					"const" >> identifier >> skip_to_semicolon;
				auto const var_declaration_def =
					("var" >> identifier >> skip_to_semicolon);
				auto const axiom_def =
					"axiom" >> skip_to_semicolon;
		      auto const function_declaration_def =
		         "function" >> identifier >> semicolon;
/*		         "function" >> *attribute >> identifier >> function_signature >> (
		            semicolon | function_body
		         );*/
		      auto const attribute_def =
			   '{' >> (':' >> identifier >> skip_balanced_curly >> '}');

		      auto const function_signature_def =
		         type_args
		            >> '(' >> skip_balanced_parenthesis >> ')'
		            >> "returns" >> ('(' >> skip_balanced_parenthesis >> ')')
		            >> (semicolon | ('{' >> skip_balanced_curly >> '}'));

				auto const skip_to_semicolon_def =
				*(char_ - (semicolon)) >> semicolon
				;
		      auto const skip_balanced_curly_def =
		      skip_non_curly >> *(('{' >> skip_balanced_curly >> '}') >> skip_non_curly);

		      auto const skip_non_curly_def =
		         *(char_ - (lit('{'),'}'))
		      ;

		      auto const skip_balanced_parenthesis_def =
		      skip_non_parenthesis >> *(('(' >> skip_balanced_parenthesis >> ')') >> skip_non_parenthesis);

		      auto const skip_non_parenthesis_def =
		         *(char_ - (lit('('),')'))
		      ;

				auto const identifier_def =
					raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

		      auto const function_body_def =
		         '{' >> skip_balanced_curly >> '}';

		      auto const type_args_def =
		         '<' >> *(char_ - (lit('<') | '>')) >> '>';

				auto const semicolon_def =
					raw[lexeme[';']];

				auto const skip_parser_def =
					space | line_comment;

				auto const line_comment_def =
					lexeme["//" >> *(char_ - eol) >> eol];


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

				, type_declaration
				, var_declaration
				, const_declaration
				, axiom
				, function_declaration
				/*			, procedure_declaration
							, implementation_declaration*/


				, identifier
				, semicolon

				, function_body
				, function_signature
				, type_args

				, skip_to_semicolon
				, skip_balanced_curly
				, skip_non_curly
				, skip_balanced_parenthesis
				, skip_non_parenthesis
				, skip_parser
				, line_comment

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
				  cout << "Parsing failed" << endl;
				  cout << "stopped at:" << endl;
				  for (;iter!=end && ((*iter)!='\n');iter++)
					  cout << *iter;
				  cout << endl;
//				  string rest(iter, end);
//				  cout << rest << "\n";
				  cout << "-------------------------\n";
			  }
		  }

    }
}

BOOST_FUSION_ADAPT_STRUCT(
	front_end::Boogie::AST::Identifier,
	(string, name)
)

BOOST_FUSION_ADAPT_STRUCT(
	front_end::Boogie::AST::Program,
	(std::list<front_end::Boogie::AST::TypeDeclaration>,types)
	(std::list<front_end::Boogie::AST::VariableDeclaration>,vars)
	(std::list<front_end::Boogie::AST::ConstantDeclaration>,consts)

	(std::list<front_end::Boogie::AST::Axiom>,axioms)
)

BOOST_FUSION_ADAPT_STRUCT(
	front_end::Boogie::AST::VariableDeclaration,
	(front_end::Boogie::AST::Identifier, name)
)

BOOST_FUSION_ADAPT_STRUCT(
front_end::Boogie::AST::TypeDeclaration,
(front_end::Boogie::AST::Identifier, name)
)

BOOST_FUSION_ADAPT_STRUCT(
front_end::Boogie::AST::ConstantDeclaration,
(front_end::Boogie::AST::Identifier, name)
)

BOOST_FUSION_ADAPT_STRUCT(
front_end::Boogie::AST::FunctionDeclaration,
(front_end::Boogie::AST::Identifier, name)
)

