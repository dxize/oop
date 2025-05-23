#include "CHttpUrl.h"
#include <regex>
#include <algorithm>
#include <string>

static const unsigned int DEFAULT_HTTP_PORT = 80;
static const unsigned int DEFAULT_HTTPS_PORT = 443;


static const std::regex DOMAIN_REGEX(
    // кажда€ метка:
    //  - начинаетс€ с буквы или цифры
    //  - за ней идут 0Ц61 буква/цифра/дефис
    //  - заканчиваетс€ буквой или цифрой
    //  меток >=1, разделЄнных точками, и затем TLD 2Ц6 букв
    R"(^(?:[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?\.)+[A-Za-z]{2,6}$)"
);


bool CHttpUrl::IsValidDomain(const std::string& domain)
{
    return std::regex_match(domain, DOMAIN_REGEX);
}

bool CHttpUrl::IsValidDocument(const std::string& document)
{
    return !document.empty() && document.front() == '/';
}


void CHttpUrl::ParseProtocol(std::string const& url, size_t& outPos)
{
    outPos = url.find("://");
    if (outPos == std::string::npos)
        throw CUrlParsingError("Invalid URL: missing protocol");

    std::string proto = url.substr(0, outPos);
    std::transform(proto.begin(), proto.end(), proto.begin(), ::tolower);

    if (proto == "http")
        m_protocol = Protocol::HTTP;
    else if (proto == "https")
        m_protocol = Protocol::HTTPS;
    else
        throw CUrlParsingError("Unsupported protocol: " + proto);
}

void CHttpUrl::SplitHostAndDocument(std::string const& rest, std::string& outHostPort)
{
    auto slashPos = rest.find('/');
    if (slashPos == std::string::npos)
    {
        outHostPort = rest;
        m_document = "/";
    }
    else
    {
        outHostPort = rest.substr(0, slashPos);
        m_document = rest.substr(slashPos);
    }
}

unsigned int CHttpUrl::ParsePort(std::string& domain, std::string const& hostPort)
{
    auto colonPos = hostPort.find(':');
    if (colonPos == std::string::npos)
    {
        return (m_protocol == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT);
    }

    domain = hostPort.substr(0, colonPos);
    std::string portStr = hostPort.substr(colonPos + 1);
    try
    {
        int p = std::stoi(portStr); // может выбросить ошибку не того типа который мне нужен
        if (p < 1 || p > 65535)
            throw CUrlParsingError("Port out of range: " + portStr);
        return static_cast<unsigned int>(p);
    }
    catch (...)
    {
        throw CUrlParsingError("Invalid port: " + portStr);
    }
}

void CHttpUrl::ValidateAndStore(std::string const& domain, unsigned int port)
{
    if (!IsValidDomain(domain))
        throw CUrlParsingError("Invalid domain: " + domain);
    if (!IsValidDocument(m_document))
        throw CUrlParsingError("Invalid document: " + m_document);

    m_domain = domain;
    m_port = static_cast<unsigned short>(port);
}

CHttpUrl::CHttpUrl(std::string const& url)
{
    size_t pos = 0;
    ParseProtocol(url, pos);
    std::string rest = url.substr(pos + 3);

    std::string hostPort;
    SplitHostAndDocument(rest, hostPort);

    std::string domain = hostPort; // будет перезаписан внутри ParsePort при наличии Ђ:ї
    unsigned int port = ParsePort(domain, hostPort);

    ValidateAndStore(domain, port);
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
    unsigned int port)
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
    if (port < 1 || port > 65535) //вынести значени€ 1 и 65535 в константы
    {
        throw CUrlParsingError("Port out of range");
    }

    m_domain = domain;
    m_document = doc;
    m_port = port;
}


std::string CHttpUrl::GetURL() const
{
    std::string url = (m_protocol == Protocol::HTTP ? "http://" : "https://")
        + m_domain;

    unsigned int defaultPort = (m_protocol == Protocol::HTTP
        ? DEFAULT_HTTP_PORT
        : DEFAULT_HTTPS_PORT);
 
    if (m_port != defaultPort)
    {
        url += ":" + std::to_string(m_port);
    }

    url += m_document;

    return url;
}



std::string CHttpUrl::GetDomain()   const { return m_domain; }
std::string CHttpUrl::GetDocument() const { return m_document; }
Protocol CHttpUrl::GetProtocol() const { return m_protocol; }
unsigned int CHttpUrl::GetPort()  const { return m_port; }

