#pragma once

#include "CUrlParsingError.h"
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

using Port = unsigned short;

class CHttpUrl
{
	
public:
	// ==> Constructors <==
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port
	);

	// ==> Getters <==
	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
	std::string GetURL() const;


	std::string GetDomain() const;
	/* 
		¬озвращает им€ документа. ѕримеры: 
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

private:
	std::string ParseProtocolToString(Protocol protocol) const;


	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
