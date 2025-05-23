#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

TEST_CASE("������ ���������� HTTP � HTTPS URL", "[CHttpUrl]")
{
    SECTION("HTTP ��� ����� � ���������")
    {
        CHttpUrl url("http://example.com/");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "http://example.com/");
    }

    SECTION("HTTPS � ������ �� ��������� � �������� ����������") {
        CHttpUrl url("https://example.org/");
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.org");
        REQUIRE(url.GetPort() == 443);
        REQUIRE(url.GetDocument() == "/");
        REQUIRE(url.GetURL() == "https://example.org/");
    }

    SECTION("HTTP � ������������� ������ � ���� � ���������") {
        CHttpUrl url("http://sub.domain.com:8080/path/to/page.html");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "sub.domain.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/path/to/page.html");
        REQUIRE(url.GetURL() == "http://sub.domain.com:8080/path/to/page.html");
    }
}

TEST_CASE("������������ URL ����������� CUrlParsingError", "[CHttpUrl]") {
    SECTION("����������� ����������� ���������") {
        REQUIRE_THROWS_AS(CHttpUrl("example.com/path"), CUrlParsingError);
    }

    SECTION("���������������� ��������") {
        REQUIRE_THROWS_AS(CHttpUrl("ftp://example.com"), CUrlParsingError);
    }

    SECTION("�������� �������� �����") {
        REQUIRE_THROWS_AS(CHttpUrl("http://example.com:0/index.html"), CUrlParsingError);
        REQUIRE_THROWS_AS(CHttpUrl("https://example.com:70000/index.html"), CUrlParsingError);
    }

    SECTION("�������� ������ ������") {
        REQUIRE_THROWS_AS(CHttpUrl("http://-invalid-.com/"), CUrlParsingError);
    }

    SECTION("�������� ���� ���������") { //�������������� ����������� �������� ����� �����
        REQUIRE_THROWS_AS(CHttpUrl("http://example.comnoslash"), CUrlParsingError);
    }
}

TEST_CASE("��������������� �� ������", "[CHttpUrl]") {
    SECTION("����� � �������� ��� �������� �����") {
        CHttpUrl url("example.com", "page.html", Protocol::HTTP);
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetDocument() == "/page.html");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetURL() == "http://example.com/page.html");
    }

    SECTION("����� ���� � HTTPS") {
        CHttpUrl url("example.com", "/doc", Protocol::HTTPS, 8443);
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetDocument() == "/doc");
        REQUIRE(url.GetPort() == 8443);
        REQUIRE(url.GetURL() == "https://example.com:8443/doc");
    }

    SECTION("�������� ����� ����������� ����������") {
        REQUIRE_THROWS_AS(CHttpUrl("bad_domain", "/doc", Protocol::HTTP), CUrlParsingError);
    }

    SECTION("���� ��� ��������� ����������� ����������") {
        REQUIRE_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 0), CUrlParsingError);
        REQUIRE_THROWS_AS(CHttpUrl("example.com", "doc", Protocol::HTTP, 70000), CUrlParsingError);
    }
}
