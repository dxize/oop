#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "HtmlDecodeFunction.h" 

TEST_CASE("HtmlDecode: Проверка декодирования HTML-сущностей", "[HtmlDecode]") {

    SECTION("Пустая строка") {
        std::string input = "";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "");
    }

    SECTION("Строка без сущностей") {
        std::string input = "Hello, world!";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello, world!");
    }

    SECTION("Декодирование одной сущности (&quot;)") {
        std::string input = "Hello &quot;world&quot;!";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello \"world\"!");
    }

    SECTION("Декодирование нескольких разных сущностей") {
        std::string input = "&lt;p&gt;It&apos;s &amp;cool&amp; &gt; all&lt;/p&gt;";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "<p>It's &cool& > all</p>");
    }

    SECTION("Соседние сущности") {
        std::string input = "&lt;&gt;&amp;&quot;&apos;";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "<>&\"'");
    }

    SECTION("Сущности внутри текста") {
        std::string input = "a&lt;b&amp;&gt;c&quot;d&apos;e";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "a<b&>c\"d'e");
    }

    SECTION("Неизвестная сущность остается без изменений") {
        std::string input = "Hello &unknown; world";
        std::string output = HtmlDecode(input);
        REQUIRE(output == "Hello &unknown; world");
    }
}