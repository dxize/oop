#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

TEST_CASE("Разбор корректных HTTP и HTTPS URL", "[CHttpUrl]")
{
    SECTION("HTTP без порта и документа")
    {
        CHttpUrl url("http://example.com/");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "http://example.com/");
    }

    SECTION("HTTPS с портом по умолчанию и корневым документом") {
        CHttpUrl url("https://example.org/");
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.org");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "https://example.org/");
    }

    SECTION("HTTP с нестандартным портом и путём к документу") {
        CHttpUrl url("http://sub.domain.com:8080/path/to/page.html");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "sub.domain.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/path/to/page.html");
        REQUIRE(url.GetURL() == "http://sub.domain.com:8080/path/to/page.html");
    }
}

TEST_CASE("Некорректные URL выбрасывают CUrlParsingError", "[CHttpUrl]") {
    SECTION("Отсутствует разделитель протокола") {
        REQUIRE_THROWS_AS(CHttpUrl("example.com/path"), CUrlParsingError);
    }

    SECTION("Неподдерживаемый протокол") {
        REQUIRE_THROWS_AS(CHttpUrl("ftp://example.com"), CUrlParsingError);
    }

    SECTION("Неверное значение порта") {
        REQUIRE_THROWS_AS(CHttpUrl("http://example.com:0/index.html"), CUrlParsingError);
        REQUIRE_THROWS_AS(CHttpUrl("https://example.com:70000/index.html"), CUrlParsingError);
    }

    SECTION("Неверный формат домена") {
        REQUIRE_THROWS_AS(CHttpUrl("http://-invalid-.com/"), CUrlParsingError);
    }

    SECTION("Неверный путь документа") { //неограничивать количесвтво символов после точки
        REQUIRE_THROWS_AS(CHttpUrl("http://example.comnoslash"), CUrlParsingError);
    }
}

TEST_CASE("Конструирование из частей", "[CHttpUrl]") {
    SECTION("Домен и документ без ведущего слеша") {
        CHttpUrl url("example.com", "page.html", Protocol::HTTP);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetDocument() == "/page.html");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetURL() == "http://example.com/page.html");
    }

    SECTION("Явный порт и HTTPS") {
        CHttpUrl url("example.com", "/doc", Protocol::HTTPS, 8443);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetDocument() == "/doc");
        REQUIRE(url.GetPort() == 8443);
        REQUIRE(url.GetURL() == "https://example.com:8443/doc");
    }

    SECTION("Неверный домен выбрасывает исключение") {
        REQUIRE_THROWS_AS(CHttpUrl("bad_domain", "/doc", Protocol::HTTP), CUrlParsingError);
    }

    SECTION("Порт вне диапазона выбрасывает исключение") {
        REQUIRE_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 0), CUrlParsingError);
        REQUIRE_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 70000), CUrlParsingError);
    }
}
