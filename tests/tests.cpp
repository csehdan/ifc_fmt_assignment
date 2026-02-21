#pragma once

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do

#include "../externals/Catch2/src/catch2/catch_all.hpp"
#include "../src/helpers.h"

// Helpers

TEST_CASE("Parenthese checker", "[parentheses]")
{
	REQUIRE(Helpers::AreParenthesesValid("[()()]") == true);
	REQUIRE(Helpers::AreParenthesesValid("[()][()]") == true);
	REQUIRE(Helpers::AreParenthesesValid("[([)()]") == false);
	REQUIRE(Helpers::AreParenthesesValid("[()()]]") == false);
	REQUIRE(Helpers::AreParenthesesValid("[)") == false);
	REQUIRE(Helpers::AreParenthesesValid("[([][])()]") == true);
}

TEST_CASE("Whitespace remover", "[whitespaces]")
{
	REQUIRE(Helpers::RemoveUnquotedWhitespaceExplicit("sdjfh jsjfh'j,snb s',knm bbb") == "sdjfhjsjfh'j,snb s',knmbbb");
	REQUIRE(Helpers::RemoveUnquotedWhitespaceExplicit("sdjfh\tjsjfh'j,snb\ts',knm bbb") == "sdjfhjsjfh'j,snb\ts',knmbbb");
}

TEST_CASE("Collect unquoted parentheses", "[collectparentheses]")
{
	REQUIRE(Helpers::CollectUnquotedParentheses("sdhhb(hd[b'ksdj]'(") == "([(");
}


TEST_CASE("Occurrence counter", "[countoccurrences]")
{
	REQUIRE(Helpers::CountOccurrences("sdhhb(hd[b'ksdj]'(", '(', false) == 2);
}
