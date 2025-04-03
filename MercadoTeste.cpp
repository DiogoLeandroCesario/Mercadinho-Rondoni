#include <iostream>
#include <vector>
using namespace std;

int escolha=-1;

struct Produto{
    string nome;
    float preco;
    float quantidade;
};

vector <Produto> estoque;

vector <Produto> carrinho;

void criaProduto(string nome,float preco, float quantidade){
    int tem = 0;
    for (int i = 0; i < estoque.size(); i++){
        if (estoque[i].nome == nome){
            cout << "O produto ja existe." << endl;
            estoque[i].preco = preco;
            estoque[i].quantidade += quantidade;   
            tem = 1;         
            cout << "Produto atualizado com sucesso" << endl;    
        }
    }
    if(tem == 0){
        estoque.push_back({nome, preco, quantidade});
        cout << "Produto criado com sucesso" << endl;    
    }

}

void listarProdutos(){
    for (int i = 0; i < estoque.size(); i++){
        cout << "-------------------------------" << endl << endl;
        cout << "Nome: " << estoque[i].nome << endl;
        cout << "Preco: " << estoque[i].preco << endl;
        cout << "Quantidade: " << estoque[i].quantidade << endl << endl;
        cout << "-------------------------------" << endl << endl;
    }
}

void deletarProdutos(string nome){
    for (int i = 0; i < estoque.size(); i++){
        if (estoque[i].nome == nome){
            estoque.erase(estoque.begin()+i);
        }
    }
}

void addCarrinho(string nome, float preco, float quantidade){
    carrinho.push_back({nome, preco, quantidade});
}

void venderProdutos(string nome, float quantidade){
    for (int i = 0; i < estoque.size(); i++){
        if (estoque[i].nome == nome){
            if (quantidade > estoque[i].quantidade){
                cout << "Quantidade escolhida maior que o estoque" << endl;
            }else {
                estoque[i].quantidade -= quantidade;
                addCarrinho(estoque[i].nome, estoque[i].preco, quantidade);
            }
        }
    }
}

void pagarCarrinho(){
    int escolhaCarrinho;
    float precoTotal=0;

    for (int i = 0; i < carrinho.size(); i++){
        cout << "-------------------------------" << endl << endl;
        cout << "Nome: " << carrinho[i].nome << endl;
        cout << "Preco: " << carrinho[i].preco << endl;
        cout << "Quantidade: " << carrinho[i].quantidade << endl << endl;
        cout << "-------------------------------" << endl << endl;
        precoTotal += (carrinho[i].preco * carrinho[i].quantidade);
    }

    cout << "O preco total eh: " << precoTotal << endl << endl;

    cout << "Voce quer pagar?" << endl;
    cout << "1 - Sim || 0 - Nao" << endl;
    cin >> escolhaCarrinho;

    if (escolhaCarrinho == 1){
        carrinho.clear();
    }

}

void menu(){
    string nome;
    float preco, quantidade;
    while (escolha !=0){

        cout << "-------------------------------" << endl << endl;
        cout << "0 - Encerrar o Programa" << endl;
        cout << "1 - Criar Produtos" << endl;
        cout << "2 - Deletar Produtos" << endl;
        cout << "3 - Vender Produtos" << endl;
        cout << "4 - Listar Produtos" << endl;
        cout << "5 - Pagar o carrinho" << endl;
        cout << endl << "-------------------------------" << endl << endl;
        cin >> escolha;
        
        if (escolha == 1){
            cout << "Escolha um nome para o seu produto: "; cin >> nome;
            cout << "Escolha um preco para o seu produto: "; cin >> preco;
            cout << "Escolha um quantidade para o seu produto: "; cin >> quantidade;

            criaProduto(nome, preco, quantidade);

        }else if (escolha == 2){
            cout << "Qual produto voce quer deletar? "; cin >> nome;
            deletarProdutos(nome);
        }else if (escolha == 3){
            cout << "Qual produto voce ira vender? "; cin >> nome;
            cout << "Qual a quantidade voce ira vender? "; cin >> quantidade;
            venderProdutos(nome, quantidade);
        }else if (escolha == 4){
            listarProdutos();
        }else if (escolha == 5){
            pagarCarrinho();
        }
    
    }
}

int main(){
    
    menu();
    
    

















    return 0;
}