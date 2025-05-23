#pragma once
#include <string>
#include "CUrlParsingError.h"

enum class Protocol { HTTP, HTTPS };

class CHttpUrl
{
public:
    // ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
    // ����������� ���������� CUrlParsingError, ���������� ��������� �������� ������
    CHttpUrl(std::string const& url);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned int port);

    // ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
    // ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
    // �� ������ ����������
    std::string GetURL()const;

    // ���������� �������� ���
    std::string GetDomain()const;

    /*
        ���������� ��� ���������. �������:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // ���������� ��� ���������
    Protocol GetProtocol()const;

    // ���������� ����� �����
    unsigned int GetPort()const;
private:
    std::string m_domain;
    std::string m_document = "/";
    Protocol m_protocol;
    unsigned int m_port;

    static bool IsValidDomain(const std::string& domain);
    static bool IsValidDocument(const std::string& document);

    void ParseProtocol(std::string const& url, size_t& outPos);
    void SplitHostAndDocument(std::string const& rest, std::string& outHostPort);
    unsigned int ParsePort(std::string& domain, std::string const& hostPort);
    void ValidateAndStore(std::string const& domain, unsigned int port);
};