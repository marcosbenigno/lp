#ifndef AAMODULOHTML_H
#define AAMODULOHTML_H
#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class ModuloHtml{
	public:
		ModuloHtml();
		
		~ModuloHtml();
		int totalDeTags(string,string);
		
		void webAtual();
		void removeTag(int);
		void exibeTitulos();
		int totalDeTags();
		void adicionaTag(int, string);
		void exibeArquivo();
		
	void runInterpreterWithPerlFile(char *file);
		
		int chamaFuncaoPerl(string a, string perlFunc);
	private:
		vector < string > m_arquivo;
		
		void arquivoVetor();
		void atualizaArquivo(vector<string>);
		string arquivoString();
		PerlInterpreter *my_perl;
		char *my_argv[2];
		
};
#endif
