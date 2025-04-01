#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "HtmlDecodeFunction.h" 

TEST_CASE("HtmlDecode: �������� ������������� HTML-���������", "[HtmlDecode]") {

    SECTION("������ ������") {
        std::string input = "";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "");
    }

    SECTION("������ ��� ���������") {
        std::string input = "Hello, world!";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello, world!");
    }

    SECTION("������������� ����� �������� (&quot;)") {
        std::string input = "Hello &quot;world&quot;!";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello \"world\"!");
    }

    SECTION("������������� ���������� ������ ���������") {
        std::string input = "&lt;p&gt;It&apos;s &amp;cool&amp; &gt; all&lt;/p&gt;";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "<p>It's &cool& > all</p>");
    }

    SECTION("�������� ��������") {
        std::string input = "&lt;&gt;&amp;&quot;&apos;";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "<>&\"'");
    }

    SECTION("�������� ������ ������") {
        std::string input = "a&lt;b&amp;&gt;c&quot;d&apos;e";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "a<b&>c\"d'e");
    }

    SECTION("����������� �������� �������� ��� ���������") {
        std::string input = "Hello &unknown; world";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello &unknown; world");
    }
}