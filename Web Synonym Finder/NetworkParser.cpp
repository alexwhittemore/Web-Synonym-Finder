#include "stdafx.h"
#include "Socket.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "NetworkParser.h"


using namespace std;

//PAGEINFO page;		// an PAGEINFO structure called page


PAGEINFO getTextUrl(std::string url) {
	PAGEINFO page;
	page.url = url;
	page.text = "";
	page.error = 0;

	try {
	int pos = page.url.find('/', 7);	// locate the end of the hostname
	string initial;
	string extension;
	string host;
	if (page.url.substr(0,3) == "www")
	{
		if (pos == -1){
		initial = page.url;
		extension="/";
		host = page.url;}
	
		else
	{initial= page.url.substr(0,pos);
	extension = page.url.substr(pos);
		 host = page.url.substr(0,pos);}	
	}
	else
	{
		if (pos == -1){
		initial = page.url.substr(7);
		extension="/";
		host = page.url.substr(7,page.url.length()-7);}
	
		else
		{initial= page.url.substr(7,pos-7);
		extension = page.url.substr(pos);
		 host = page.url.substr(7,pos-7);}	

	}
		SocketClient s(initial, 80);

		
		host = page.url.substr(7,pos-7);	// get the hostname string
		extension = page.url.substr(pos);	// get the rest of the website address
		if (extension.empty()){
			extension = "/";
		}
		
		s.SendLine("GET " + extension + " HTTP/1.0");
		s.SendLine("Host: " + host);
		s.SendLine("");
/*
	// Request Message
		s.SendLine("GET / HTTP/1.0");		// Get command for the specific resource
		s.SendLine("Host: www.asciitable.com");	// Command for sending the hostname
		s.SendLine("");
*/

		// Grab html code
		string l = "       ";	// buffer at begin of string
		while (1) {	// Loop to grab all the html code from the website
			string tempL = s.ReceiveLine();
			if (tempL.empty())
				break;
			l.append(tempL);
		}
		l.append("       ");	// buffer at end of string

		while (l.find('\n') != string::npos) {	// clean out all newline characters
			int ii = l.find('\n');
			l.erase(ii,1);
		}

		while (l.find('\t') != string::npos) {	// clean out all tab characters
			int jj = l.find('\t');
			l.erase(jj,1);
		}

		while (l.find('&') != string::npos) {	// clean out html characters.  ex: &copy;
			int ii = l.find('&');
			int ee = l.find(';',ii);
			l.erase(ii,(ee-ii+1));
		}

		while (l.find("<script") != string::npos) {	// remove all of the script code
			int xx = l.find("<script");
			int yy = l.find("</script>");
			l.erase(xx,(yy-xx+8));
		}

		while (l.find("<style") != string::npos) {	// remove all of the style code
			int aa = l.find("<style");
			int bb = l.find("</style>");
			l.erase(aa,(bb-aa+7));
		}

		l.append("       ");	// buffer at end of string

		// Create a vector from the string
		vector<char> line;	// create a vector sequence container
		line.assign(l.begin(),l.end());	// copy the contents from the string l to the vector

		// Grab and record all the text (as seen on the website) in the html
		bool grab = false;
		int counter = 0;
		for (int it = 0; it < (int)line.size(); it++) {
			if (line[it] == '>') {		// '>' 
				counter--;
				grab = true;
			}
			else if (line[it] == '<') {	// '<' 
				counter++;
				grab = false;
			}
			else if (grab == true && counter <= 0) {	// save the char to text string 
				if (line[it] != 32) {
						page.text.append(string(1,line[it]));
					if (line[it+1] == '<') {
						page.text.append(" ");		// end of string
						it++;
					}
					else if (line[it+1] == 32) {
						page.text.append(" ");		// end of a word
						it++;
					}
				}
				counter = 0;
			}
			else		// -OR- do nothing with it
				;
		}
		page.text.append("\n");	// end the text string with a NULL character


		// Grab all the URLs from the website
		while (l.find("<a href=\"http://") != string::npos){	// look for: <a href="
			int urlStart = l.find("<a href=\"http://");
			int textStart = l.find("\">",urlStart);		// skip to start of text, save start position
			int textStart2 = l.find("\" ",urlStart);
			int textEnd = l.find("</a>",textStart);		// seek to end of text, save end position
			// page.url.append(l, (urlStart+9,(textStart-urlStart-9)) );
			if (textStart2 < textStart) 
				page.url.append(" " + l.substr(urlStart+9,(textStart2-urlStart-9)));
			else
				page.url.append(" " + l.substr(urlStart+9,(textStart-urlStart-9)));
			l = l.substr(textEnd,(l.length()-textEnd));
		}
		page.url.append("\n");	// end the url string with a NULL character

		//output.flush();
	} 

	catch (const char* s) {
		page.error = -1;
	} 
	catch (string s) {
		page.error = -1;
	} 
	catch (...) {
		page.error = -1;
	}

	return page;
}



/*
	ofstream output;
	output.open("sampleText.txt");

	try {
		SocketClient s("www.asciitable.com", 80);

		// Request Message
		s.SendLine("GET / HTTP/1.0");		// Get command for the specific resource
		s.SendLine("Host: www.asciitable.com");	// Command for sending the hostname
		s.SendLine("");

		//output << "GET /" << s.clientResource << " HTTP/1.0" << endl;	
		//output << "Host: " << s.clientHost << endl;	

		// Grab html code
		string l = "       ";	// buffer at begin of string
		while (1) {	// Loop to grab all the html code from the website
			string tempL = s.ReceiveLine();
			if (tempL.empty())
				break;
			l.append(tempL);
		}
		l.append("       ");	// buffer at end of string

		while (l.find('\n') != string::npos) {	// clean out all newline characters
			int ii = l.find('\n');
			l.erase(ii,1);
		}

		while (l.find('\t') != string::npos) {	// clean out all tab characters
			int ii = l.find('\t');
			l.erase(ii,1);
		}

		while (l.find('&') != string::npos) {	// clean out html characters.  ex: &copy;
			int ii = l.find('&');
			int ee = l.find(';',ii);
			l.erase(ii,(ee-ii+1));
		}

		l.append("       ");	// buffer at end of string
	
		// Create a vector from the string
		vector<char> line;	// create a vector sequence container
		line.assign(l.begin(),l.end());	// copy the contents from the string l to the vector

		// Grab and record all the text (as seen on the website) in the html
		bool grab = false;
		static bool ignoreScript = false;
		int counter = 0;
		for (int it = 0; it < (int)line.size(); it++) {
			if (line[it] == '>') {		// '>' 
				if (line[it-7] == '<' && line[it-6] == 's' && line[it-5] == 'c' && line[it-4] == 'r' && line[it-3] == 'i' && line[it-2] == 'p' && line[it-1] == 't')
					ignoreScript = true;	// start recording
				if (line[it-6] == '/' && line[it-5] == 's' && line[it-4] == 't' && line[it-3] == 'y' && line[it-2] == 'l' && line[it-1] == 'e')
					ignoreScript = false;	// stop recording
				counter--;
				grab = true;
			}
			else if (line[it] == '<') {	// '<' 
				if (line[it+1] == '/' && line[it+2] == 's' && line[it+3] == 'c' && line[it+4] == 'r' && line[it+5] == 'i' && line[it+6] == 'p' && line[it+7] == 't' && line[it+8] == '>')
					ignoreScript = false;	// start recording
				if (line[it+1] == 's' && line[it+2] == 't' && line[it+3] == 'y' && line[it+4] == 'l' && line[it+5] == 'e')
					ignoreScript = true;	// stop recording
				counter++;
				grab = false;
			}
			else if (grab == true && counter <= 0 && ignoreScript == false) {	// save the char to text string 
				if (line[it] != ' ') {
					output << line[it];
					if (line[it+1] == '<') {
						output << endl;		// end of string
					}
					else if (line[it+1] == 32) {
						output << endl;		// end of a word
						it++;
					}
					counter = 0;
				}
			}
			else		// -OR- do nothing with it
				;
		}

		// Grab all the URLs from the website
		while (l.find("<a href=\"") != string::npos){	// look for: <a href="
			int urlStart = l.find("<a href=\"");
			int textStart = l.find("\">",urlStart);		// skip to start of text, save start position
			int textStart2 = l.find("\" ",urlStart);
			int textEnd = l.find("</a>",textStart);		// seek to end of text, save end position
			// page.url.append(l, (urlStart+9,(textStart-urlStart-9)) );
			if (textStart2 < textStart) 
				output << l.substr(urlStart+9,(textStart2-urlStart-9)) << endl;
			else
				output << l.substr(urlStart+9,(textStart-urlStart-9)) << endl;
			l = l.substr(textEnd,(l.length()-textEnd));
		}

		output.flush();
	} 

	catch (const char* s) {
		output << s << endl;
	} 
	
	catch (string s) {
		output << s << endl;
	} 
	
	/*catch (...) {
		output << "unhandled exception\n";
	}

	output.close();
	return 0;
}*/
