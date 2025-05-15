#include "CHttpUrl.h"
#include <regex>
#include <algorithm>
#include <string>

static const unsigned short DEFAULT_HTTP_PORT = 80;
static const unsigned short DEFAULT_HTTPS_PORT = 443;

static const std::regex DOMAIN_REGEX(
    R"(^((?!-)[A-Za-z0-9-]{1,63}(?<!-)\.)+[A-Za-z]{2,6}$)"
);

bool CHttpUrl::IsValidDomain(const std::string& domain)
{
    return std::regex_match(domain, DOMAIN_REGEX);
}

bool CHttpUrl::IsValidDocument(const std::string& document)
{
    return !document.empty() && document.front() == '/';
}

CHttpUrl::CHttpUrl(const std::string& url)
{
    //получить протокол
    auto pos = url.find("://");
    if (pos == std::string::npos)
    {
        throw CUrlParsingError("Invalid URL: missing protocol");
    }
    std::string protocol = url.substr(0, pos);
    std::transform(protocol.begin(), protocol.end(), protocol.begin(), ::tolower);
    if (protocol == "http")
    {
        m_protocol = Protocol::HTTP;
    }
    else if (protocol == "https")
    {
        m_protocol = Protocol::HTTPS;
    }
    else
    {
        throw CUrlParsingError("Unsupported protocol: " + protocol);
    }

    //остаток разграничить на домен с портом и документ
    std::string rest = url.substr(pos + 3);
    std::string hostPort;
    auto slashPos = rest.find("/");
    if (slashPos == std::string::npos)
    {
        hostPort = rest;
    }
    else
    {
        hostPort = rest.substr(0, slashPos);
        m_document = rest.substr(slashPos);
    }

    // разбираю порт, если есть
    auto colonPos = hostPort.find(':');
    std::string domain = hostPort;
    unsigned short port;
    if (colonPos != std::string::npos) 
    {
        domain = hostPort.substr(0, colonPos);
        std::string portStr = hostPort.substr(colonPos + 1);
        try 
        {
            int p = std::stoi(portStr);
            if (p < 1 || p > 65535)
            {
                throw std::out_of_range("Port out of range");
            }
            port = static_cast<unsigned short>(p);
        }
        catch (...) 
        {
            throw CUrlParsingError("Invalid port: " + portStr);
        }
    }
    else
    {
        port = (m_protocol == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT);
    }

    if (!IsValidDomain(domain))
        throw CUrlParsingError("Invalid domain: " + domain);
    if (!IsValidDocument(m_document))
        throw CUrlParsingError("Invalid document: " + m_document);

    m_domain = domain;
    m_port = port;
}

CHttpUrl::CHttpUrl(const std::string& domain,
    const std::string& document,
    Protocol protocol)
    : CHttpUrl(domain, document, protocol,
        protocol == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT)
{}

CHttpUrl::CHttpUrl(const std::string& domain,
    const std::string& document,
    Protocol protocol,
    unsigned short port)
    : m_protocol(protocol)
{
    if (!IsValidDomain(domain))
    {
        throw CUrlParsingError("Invalid domain: " + domain);
    }
    std::string doc = document;
    if (doc.empty() || doc.front() != '/')
    {
        doc.insert(doc.begin(), '/');
    }
    if (!IsValidDocument(doc))
    {
        throw CUrlParsingError("Invalid document: " + doc);
    }
    if (port < 1 || port > 65535)
    {
        throw CUrlParsingError("Port out of range");
    }

    m_domain = domain;
    m_document = doc;
    m_port = port;
}


std::string CHttpUrl::GetURL() const
{
    std::string url;
    if (m_protocol == Protocol::HTTP)
    {
        url = "http://";
    }
    else if (m_protocol == Protocol::HTTPS)
    {
        url = "https://";
    }
    else
    {
        throw CUrlParsingError("Invalid port");
    }
    url += m_domain;
    if (m_port != NAN)
    {
        url += ":" + std::to_string(m_port);
    }
    url += m_document;
    return url;
}

std::string CHttpUrl::GetDomain()   const { return m_domain; }
std::string CHttpUrl::GetDocument() const { return m_document; }
Protocol CHttpUrl::GetProtocol() const { return m_protocol; }
unsigned short CHttpUrl::GetPort()  const { return m_port; }

