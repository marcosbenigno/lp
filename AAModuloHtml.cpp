
#include "AAModuloHtml.h"
ModuloHtml::ModuloHtml(){
	PERL_SYS_INIT3(NULL,NULL,NULL);
	
	my_perl = perl_alloc();
	perl_construct(my_perl);
	PL_exit_flags = PERL_EXIT_DESTRUCT_END;
	arquivoVetor();
	}
void ModuloHtml::exibeArquivo (){
	for (int i = 0; i <= m_arquivo.size(); i++){
		cout<<i+1<<"  "<<m_arquivo[i]<<endl;
	}
}
void ModuloHtml::adicionaTag (int linhaAnterior, string linha){
	vector <string> novoArquivo;
	for (int i = 0; i <= m_arquivo.size(); i++)
	{
		if(i < linhaAnterior)
		{
			novoArquivo.push_back(m_arquivo[i]);	
		}
		if (i == linhaAnterior)
		{		
			novoArquivo.push_back(linha);	
		}
		if(i > linhaAnterior)
		{
			novoArquivo.push_back(m_arquivo[i-1]);	
		}	
	}
	m_arquivo = novoArquivo;
	atualizaArquivo(novoArquivo);
	cout<<"Linha adcionada!"<<endl;
}
void ModuloHtml::removeTag (int linha){
	vector <string> novoArquivo;
	if (linha > m_arquivo.size() || linha < 1){
		cout<<"NUmero invalido!"<<endl;
	}else{
		
	for (int i = 0; i < m_arquivo.size(); i++)
	{
		if (i != linha-1)
		{		
			novoArquivo.push_back(m_arquivo[i]);	
		}		
	}
	m_arquivo = novoArquivo;
	atualizaArquivo(novoArquivo);
	cout<<"Linha removida!"<<endl;
}
}

void ModuloHtml::atualizaArquivo(vector<string> arquivoNovo){
	string linha;
	ofstream arquivo("index.html", ios::trunc | ios::out | ios::in);
	if (arquivo.is_open()){
		for (int i = 0; i < arquivoNovo.size(); i++){
			arquivo<<arquivoNovo[i]+"\n";
		}
	}
	arquivo.close();
}

void ModuloHtml::arquivoVetor(){
	string linha;
	ifstream arquivo("index.html", ios::in | ios::out);
	if (arquivo.is_open()){
		while(getline(arquivo,linha)){
			m_arquivo.push_back(linha);
		}
	arquivo.close();
	}
}
string ModuloHtml::arquivoString(){
	string docString = "";
	for(int i = 0; i < m_arquivo.size(); i++){
		docString += m_arquivo[i];
	}
	return docString;
}

void ModuloHtml::exibeTitulos(){
	string arq = arquivoString();
	
	for (int k = 1; k <= 6; k++){
		char hs = '0'+k;
		for (int i = 0; i < arq.length(); i++){
			if(arq[i] == '<' && arq[i+1] == 'h' && arq[i+2] == hs){
				cout<<arq[i]<<arq[i+1]<<arq[i+2];
				for (int j = i+3; j < arq.length(); j++){
					cout<<arq[j];
					if(arq[j] == 'h' && arq[j+1] == hs && arq[j+2] == '>'){
						cout<<arq[j+1]<<arq[j+2]<<endl;
						i = j+3;
						break;
					}
				}
			}
		}
	}
}

ModuloHtml::~ModuloHtml(){
	perl_destruct(my_perl);
	perl_free(my_perl);
	PERL_SYS_TERM();
}
void ModuloHtml::runInterpreterWithPerlFile(char *file){
	string a = "";
	char * S = new char[a.length()+1];
	strcpy(S,a.c_str());
	char *my_argv[] = {S, file};
	perl_parse(my_perl, 0, 2, my_argv, (char **)NULL);
	perl_run(my_perl);
}
int ModuloHtml::chamaFuncaoPerl(string valor, string perlFunc){
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpv(valor.c_str(),perlFunc.length())));
	PUTBACK;
	call_pv (perlFunc.c_str(), G_SCALAR);
	SPAGAIN;
	
	int resultado = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;
	return resultado;
}
int ModuloHtml::totalDeTags(){
				string a = "AAmoduloTrabalhoLP.pl";
				char * S = new char[a.length()+1];
				strcpy(S,a.c_str());
				runInterpreterWithPerlFile(S);

				return chamaFuncaoPerl("index.html", "numeroTags");

}

void ModuloHtml::webAtual(){
			
				string a = "AAmoduloTrabalhoLP.pl";
				char * S = new char[a.length()+1];
				strcpy(S,a.c_str());
				runInterpreterWithPerlFile(S);

				int tags = chamaFuncaoPerl("index.html", "tagsHtml5");
				if (tags == 1){
					cout<<"Este arquivo possui tag(s) HTML5."<<endl;
				} else {
					cout<<"Este arquivo não possui tag(s) HTML5."<<endl;
				}
				int key = chamaFuncaoPerl("index.html", "numeroKeywords");
				if (key != -1){
					cout<<"Este arquivo possui "<<key<<" keywords."<<endl;
				} else {
					cout<<"Este arquivo nao possui keywords."<<endl;
				}
				int scriptcss = chamaFuncaoPerl("index.html", "scriptCss");
				if (scriptcss == 1){
					cout<<"Este arquivo usa scripts ou folhas de estilo."<<endl;
				} else if (scriptcss == 2) {
					cout<<"Este arquivo usa scripts e folhas de estilo."<<endl;
				} else {
					cout<<"Este arquivo não usa scripts e folhas de estilo."<<endl;
				}
}