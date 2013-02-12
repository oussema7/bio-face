#include "stdafx.h"
#include "Parser.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>
#include <iterator>

using namespace std;
using namespace xercesc;


Parser::Parser(void)
{
}

int Parser::Parse(char* xmlFile){
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n"
			<< message << "\n";
		XMLString::release(&message);
		return 1;
	}

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);


	try {
		parser->parse(xmlFile);
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return -1;
	}
	catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return -1;
	}
	catch (...) {
		cout << "Unexpected Exception \n" ;
		return -1;
	}

	DOMNode* docRootNode;
	//  DOMNode* aNode;
	DOMDocument* doc;
	doc = parser->getDocument();
	docRootNode = doc->getDocumentElement();
	const XMLCh* fNodeValue = docRootNode->getNodeName();

	cout << "Ici "<<XMLString::transcode(fNodeValue); //returns Hex
	

	delete parser;
	delete errHandler;
}


Parser::~Parser(void)
{
}
