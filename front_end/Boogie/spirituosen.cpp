//
// Created by uri on 10/11/2016.
//
#include <string>
#include <iostream>

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <boost/spirit/include/support_istream_iterator.hpp>

using std::string;

namespace AST{
	class ASTNode : public boost::spirit::x3::position_tagged{};
	class Identifier : public ASTNode{
	public:
		std::string name;
   };
	 class Attribute : public ASTNode{
	 public:
		  Identifier name;
	 };
	 class StringAttribute : public Attribute{
	 public:
		  std::string value;
	 };
/*	 class ExpressionAttribute : public Attribute{
	 public:
		  std::string value;
	 };*/
}//namespace AST

BOOST_FUSION_ADAPT_STRUCT(
   AST::Identifier,
   (std::string, name)
)

namespace grammar {
	 using namespace boost::spirit::x3;

    rule<class pChar, char> const pChar("char");
    auto const pChar_def = char_;
    BOOST_SPIRIT_DEFINE(pChar)

/*    x3::rule<class string, std::string> const pString("string");
    auto const pString_def = *pChar;
    BOOST_SPIRIT_DEFINE(string)
*/
	 rule<class string_literal, std::string> const string_literal("string literal");
	 auto const string_literal_def = '"' >> *(pChar-'"') >> '"';
	 BOOST_SPIRIT_DEFINE(string_literal)

	 rule<class identifier_start, std::string> const identifier_start("id start");
	 auto const identifier_start_def = '_' | alpha;
	 BOOST_SPIRIT_DEFINE(identifier_start)

	 rule<class identifier_char, char> const identifier_char("id char");
	 auto const identifier_char_def = '_' | alnum;
	 BOOST_SPIRIT_DEFINE(identifier_char)

    rule<class identifier1, std::string> const identifier1("identifier1");
    auto const identifier1_def = raw[lexeme[(alpha | '_') >> *(alnum | '_')]];
    BOOST_SPIRIT_DEFINE(identifier1)
	 rule<class identifier, AST::Identifier> const identifier("identifier");
	 auto const identifier_def = identifier1;
	 BOOST_SPIRIT_DEFINE(identifier)

    rule<class attribute, AST::Attribute> const attribute("attribute");
    auto const attribute_def =
		lit('{') >> ':' >> identifier >> /*skip_balanced_curly >>*/ '}';
    BOOST_SPIRIT_DEFINE(attribute)

}

using boost::spirit::istream_iterator;

void parseTest(std::istream& ins){
   boost::spirit::istream_iterator end;

   std::string in = "_ABABAB";

   char c;
   boost::spirit::istream_iterator iter1(ins);
	boost::spirit::x3::parse(iter1,end,grammar::pChar,c);

   std::string s2;
   boost::spirit::istream_iterator iter2(ins);
	boost::spirit::x3::parse(iter2,end,grammar::string_literal,s2);

	boost::spirit::x3::parse(in.begin(),in.end(),grammar::identifier1,s2);

	AST::Identifier id;
	boost::spirit::x3::parse(in.begin(),in.end(),grammar::identifier,id);
	std::cout << id.name << std::endl;
/*   AST::Identifier id;
   boost::spirit::x3::parse(in.begin(),in.end(),grammar::identifier,id);

*/
/*	AST::StringAttribute sAttrib;
	std::string attribIn = "{ : weight \"5\" }";
	x3::parse(attribIn .begin(),attribIn .end(),grammar::attribute,sAttrib);
	std::cout << sAttrib.name << ": " << sAttrib.value << std::endl;*/
}