#include <stdio.h>
#include <locale>>


// FUNÇÃO MAIN
int main(){
	setlocale(LC_ALL, "Portuguese");
	tContato *contato = NULL;
	tContato c;
	int i, opcao = 1, totalContatos = 0;
	
	do{
		system("cls");
		opcao = menu();
		switch(opcao){
			case 1:
				//CADASTRAR UM NOVO CONTATO
				system("cls");
				contato = cadastrarContato(contato, &totalContatos);		
				atualizarArquivoTotalContatos("Total de Contatos.txt", &totalContatos);
				printf("CONTATO CADASTRADO COM SUCESSO\n\n");
				break;
			case 2:
				//LISTAR TODOS OS CONTATOS
				contato = lerArquivoDeContatos(contato, "Contatos.txt", &totalContatos);
				listarTodosOsContatos(contato, &totalContatos, FULL);
				printf("TOTAL DE CONTATOS: %d\n\n", totalContatos);
				break;
			case 3:
				//PESQUISAR UM CONTATO PELO NOME
				system("cls");
				tituloFormatado("PESQUISAR CONTATO PELO NOME");
				fazerPesquisaPorNome(contato, &totalContatos);
				break;
			case 4:
				//PESQUISAR UM CONTATO PELO NOME
				system("cls");
				tituloFormatado("PESQUISAR CONTATO PELO NOME");
				pesquisarContatoPeloNomeAproximado(contato, &totalContatos);
				break;
			case 5:
				//LISTAR CONTATOS INICIADOS COM DETERMINADA LETRA
				system("cls");
				listarContatosPorLetra(contato, &totalContatos);
				break;
			case 6:
				//EDITAR UM CONTATO
				lerTotalContatos("Total de Contatos.txt", &totalContatos);
				contato = lerArquivoDeContatos(contato, "Contatos.txt", &totalContatos);
				int i;
				i = pesquisarContatoPeloNome(contato, &totalContatos, capturarNomeParaPesquisa(nome));
				editarContato(contato, i, &totalContatos);
				break;
			case 7:
				//jdfsdjfsjfk
				break;
			case 0:
				//FINALIZA A AGENDA
				printf("Ao precionar uma tecla a agenda será encerrada\n\n");
				getch();
				exit(EXIT_FAILURE);
			default:
				printf("Opcao Inválida. Tente novamente..\n\n");
		}
		system("pause");
	}while(opcao);	
	return 0;
}
