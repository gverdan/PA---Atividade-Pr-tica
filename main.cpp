#include <iostream>
#include <fstream>

using namespace std;

struct tInvestimento {
  double montanteInvestido; // Montante Investido.
  double taxaDejuros; // Taxa de Juros ao Ano.
  int periodo; // Periodo do Investimento em anos.
};

struct tNo{
  tInvestimento invest;
  tNo* proximo;
};

tNo* criaNo(double m, double j, int p){
  tNo* no = new tNo;
  no -> invest .montanteInvestido = m;
  no -> invest .taxaDejuros = j;
  no -> invest .periodo = p;
  no -> proximo = NULL;
  return no;
}

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho;
};

void inicializarLista(tLista* pLista){
  pLista -> primeiro = NULL;
  pLista -> ultimo = NULL;
  pLista -> marcador = NULL;
  pLista -> tamanho = 0;
}

int obterTamanho(tLista* pLista){
  return pLista->tamanho;
}

bool listaVazia(tLista* pLista){
  return (pLista -> tamanho == 0);
}

bool finalLista(tLista* pLista){
  return (pLista->marcador == NULL);
}

void incluirNoFim(tLista* pLista, double m, double j, int p){
  tNo* no;
  no = criaNo(m,j,p);

  if(listaVazia(pLista)){
    pLista -> primeiro = no;
  }else{
    pLista -> ultimo -> proximo = no;
  }

  pLista -> ultimo = no;
  pLista -> marcador = no;
  pLista -> tamanho++;
}

void imprimirLista(tLista* pLista){

  pLista->marcador = pLista->primeiro;

  while(!finalLista(pLista)){
    double capital = pLista->marcador->invest.montanteInvestido;
    double taxaDejuros = pLista->marcador->invest.taxaDejuros;
    int periodo = pLista->marcador->invest.periodo;
    cout << "\nMontante = R$ " << capital;
    cout << "\nTaxa de juros = " << taxaDejuros;
    cout << "\nPeriodo = " << periodo << "\n";
    pLista->marcador = pLista->marcador->proximo;
  }

}

void gravar(tLista* pLista, double m, double j, int p){

  if (listaVazia(pLista)){
    cout << "Lista vazia\n";
  }else{
    ofstream banco_de_dados("arquivo.txt");
    pLista->marcador = pLista->primeiro;
    while(!finalLista(pLista)){
      double capital = pLista->marcador->invest.montanteInvestido;
      double taxaDejuros = pLista->marcador->invest.taxaDejuros;
      int periodo = pLista->marcador->invest.periodo;
      banco_de_dados << capital << " ";
      banco_de_dados << taxaDejuros << " ";
      banco_de_dados << periodo << "\n";
      pLista->marcador = pLista->marcador->proximo;
    }
    cout << "\nLista descarregada no banco de dados\n";
    banco_de_dados.close();
  }

}

int main() {
  
  tLista* lista = new tLista;

  double capital, taxaDejuros;
  int periodo;
  
  char condicao = 'S';
  int opcao, N;
  
  while (condicao == 'S' || condicao == 's'){

    cout << "1 -> Ler um banco de dados." << endl;
    cout << "2 -> Escrever um banco de dados." << endl;
    cout << "___> ";
    cin >> opcao;

    if (opcao == 1){
      
      ifstream banco_de_dados("arquivo.txt");
      
      while(!banco_de_dados.eof()){
        banco_de_dados >> capital >> taxaDejuros >> periodo;
        incluirNoFim(lista,capital,taxaDejuros,taxaDejuros);
      }

      cout << "\nLista carregada!\n";
      banco_de_dados.close();

      imprimirLista(lista);

    }else{

      cout << "\nQue quantidade de elementos quer inserir: ";
      cin >> N;

      while(N > 0){
        cout << "\nInforme o capital a ser investido = R$ ";
        cin >> capital;
        cout << "Informe a taxa de juros % Ao ano = ";
        cin >> taxaDejuros;
        cout << "Informe o periodo do investimento (em anos) = ";
        cin >> periodo;
        incluirNoFim(lista,capital,taxaDejuros,periodo);
        N--;
      }

      gravar(lista,capital,taxaDejuros,periodo);

    }

    cout << "\n\nDeseja continuar (S/N)? ";
    cin >> condicao;

  }

}