#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

bool digitos = true;
bool digitosFloat = true;
string stgEscolha;
string stgPreco;
string stgQtdd;
int escolha;

struct Produto
{
    string nome;
    float preco;
    float quantidade;
};

vector<Produto> estoque;

vector<Produto> carrinho;

void VerificarEscolha()
{
    for (char &c : stgEscolha)
    {
        if (!isdigit(c))
        {
            digitos = false;
            break;
        }
    }
}

void VerificarFloat()
{
    int countDot = 0;
    for (char &c : stgEscolha)
    {
        if (!isdigit(c))
        {
            if (c == '.')
            {
                countDot++;
            }
            else if (c == ',') //nao funciona
            {
                c = '.';
                countDot++;
            }
            else if (countDot > 1)
            {
                digitosFloat = false;
                break;
            }
            else
            {
                digitosFloat = false;
                break;
            }
        }
    }

    countDot = 0;
}

void criaProduto(string nome, float preco, float quantidade)
{
    int tem = 0;
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            cout << "O produto ja existe." << endl;
            estoque[i].preco = preco;
            estoque[i].quantidade += quantidade;
            tem = 1;
            cout << "Produto atualizado com sucesso" << endl;
        }
    }
    if (tem == 0)
    {
        estoque.push_back({nome, preco, quantidade});
        cout << "Produto criado com sucesso" << endl;
    }
}

void listarProdutos()
{
    for (int i = 0; i < estoque.size(); i++)
    {
        cout << "-------------------------------" << endl
             << endl;
        cout << "Nome: " << estoque[i].nome << endl;
        cout << "Preco: " << estoque[i].preco << endl;
        cout << "Quantidade: " << estoque[i].quantidade << endl
             << endl;
        cout << "-------------------------------" << endl
             << endl;
    }
}

void deletarProdutos(string nome)
{
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            estoque.erase(estoque.begin() + i);
        }
    }
}

void addCarrinho(string nome, float preco, float quantidade)
{
    carrinho.push_back({nome, preco, quantidade});
}

void venderProdutos(string nome, float quantidade)
{
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            if (quantidade > estoque[i].quantidade)
            {
                cout << "Quantidade escolhida maior que o estoque" << endl;
            }
            else
            {
                estoque[i].quantidade -= quantidade;
                addCarrinho(estoque[i].nome, estoque[i].preco, quantidade);
            }
        }
    }
}

void pagarCarrinho()
{
    int escolhaCarrinho;
    float precoTotal = 0;

    for (int i = 0; i < carrinho.size(); i++)
    {
        cout << "-------------------------------" << endl
             << endl;
        cout << "Nome: " << carrinho[i].nome << endl;
        cout << "Preco: " << carrinho[i].preco << endl;
        cout << "Quantidade: " << carrinho[i].quantidade << endl
             << endl;
        cout << "-------------------------------" << endl
             << endl;
        precoTotal += (carrinho[i].preco * carrinho[i].quantidade);
    }

    cout << "O preco total eh: " << precoTotal << endl
         << endl;

    cout << "Voce quer pagar?" << endl;
    cout << "1 - Sim || 0 - Nao" << endl;
    cin >> escolhaCarrinho;

    if (escolhaCarrinho == 1)
    {
        carrinho.clear();
    }
}

void menu()
{
    string nome;
    float preco, quantidade;

    do
    {

        cout << "-------------------------------" << endl
             << endl;
        cout << "0 - Encerrar o Programa" << endl;
        cout << "1 - Criar Produtos" << endl;
        cout << "2 - Deletar Produtos" << endl;
        cout << "3 - Vender Produtos" << endl;
        cout << "4 - Listar Produtos" << endl;
        cout << "5 - Pagar o carrinho" << endl;
        cout << endl
             << "-------------------------------" << endl
             << endl;
        cin >> stgEscolha;

        VerificarEscolha();

        if (digitos)
        {
            escolha = stoi(stgEscolha);

            if (escolha == 1)
            {
                cout << "Escolha um nome para o seu produto: ";
                cin >> nome;
                cout << "Escolha um preco para o seu produto: ";
                cin >> preco;
                cout << "Escolha um quantidade para o seu produto: ";
                cin >> quantidade;

                stgEscolha = preco;
                VerificarFloat();

                stgEscolha = quantidade;
                VerificarFloat();
                if (digitosFloat)
                {
                criaProduto(nome, preco, quantidade);
                }else{
                    cout << endl << endl << "Escolha um numero valido!" << endl << endl;
                }
            }
            else if (escolha == 2)
            {
                cout << "Qual produto voce quer deletar? ";
                cin >> nome;
                deletarProdutos(nome);
            }
            else if (escolha == 3)
            {
                cout << "Qual produto voce ira vender? ";
                cin >> nome;
                cout << "Qual a quantidade voce ira vender? ";
                cin >> quantidade;
                venderProdutos(nome, quantidade);
            }
            else if (escolha == 4)
            {
                listarProdutos();
            }
            else if (escolha == 5)
            {
                pagarCarrinho();
            }
            else if (escolha == 0)
            {
                break;
            }
            else
            {
                cout << "Escolha Invalida";
            }
        }
        else if (digitos == false)
        {
            cout << "Escolha Invalida";
            escolha = -1;
        }

    } while (escolha != 0);
}

int main()
{

    menu();
}