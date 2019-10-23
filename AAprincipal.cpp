#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "AAModuloHtml.h"
using namespace std;
int main(){
	int operacao = 0;

	ModuloHtml modulo;
	int i = 0;
	while (i != 100){
		cout<<"Digite o numero correspondente a operacao:"<<endl;
		cout<<"1 - Analise sobre modernidade do codigo;"<<endl;
		cout<<"2 - Remover linha;"<<endl;
		cout<<"3 - Exibir titulos;"<<endl;
		cout<<"4 - Exibir quantas tags diferentes existem no arquivo;"<<endl;
		cout<<"5 - Adicionar linha no arquivo;"<<endl;
		cout<<"6 - Exibir arquivo;"<<endl;
		cout<<"7 - Sair;"<<endl;
		cin>>operacao;
		cin.ignore();
			if(operacao == 1){
				modulo.webAtual();
							 }
			if(operacao == 2){
				int linha = 0;
				cout<<"Qual o numero da linha que deseja remover do arquivo?";
				cin>>linha;
				modulo.removeTag(linha);
			}
			if(operacao == 3){
				modulo.exibeTitulos();
			}
			if(operacao == 4){
				cout << "Numero de tags diferentes: " << modulo.totalDeTags()<<endl;
			}
			if(operacao == 5){
				int linha = 0;
				string linhaASerAdicionada = "";
				cout<<"Digite o texto a ser adicionado"<<endl;
				getline(cin,linhaASerAdicionada);
				
				cout<<"Apos que linha deseja adicionar o texto passado?";
				cin>>linha;
				modulo.adicionaTag(linha,linhaASerAdicionada);
			}
			if(operacao == 6){
				modulo.exibeArquivo();
			}
			if(operacao == 7){
				exit(0);
			}
		i++;
	}
	return 0;
}




