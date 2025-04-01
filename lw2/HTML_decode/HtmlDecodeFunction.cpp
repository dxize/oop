#include <string>
#include <map>
#include "HtmlDecodeFunction.h"

const std::map<std::string, char> cipher = { //посмотреть на кодинг конвекшн 
    {"&quot;", '"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'}
};

std::string HtmlDecode(const std::string& html)
{
    std::string result;
    size_t pos = 0;

    while (pos < html.length())
    {
        bool found = false;

        if (html[pos] == '&')
        {
            for (const auto& pair : cipher) // вынести это цикл в отдельную функицю
            {
                const std::string& entity = pair.first;
                const char symbol = pair.second;

                if (pos + entity.length() <= html.length() && html.substr(pos, entity.length()) == entity)
                {
                    result += symbol;
                    pos += entity.length();
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            continue;
        }

        result += html[pos];
        pos++;
    }

    return result;
}