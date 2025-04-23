#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool digitos = true;
bool digitosPreco = true;
bool digitosQtdd = true;
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

void LimparTexto()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SalvarEstoque()
{
    ofstream arquivo("estoque.txt");

    for (const auto &produto : estoque)
    {
        arquivo << produto.nome << "," << produto.preco << "," << produto.quantidade << "\n";
    }

    arquivo.close();
}

void SalvarCarrinho()
{
    ofstream arquivo("carrinho.txt");

    for (const auto &item : carrinho)
    {
        arquivo << item.nome << "," << item.preco << "," << item.quantidade << "\n";
    }

    arquivo.close();
}

void CarregarEstoque()
{
    ifstream arquivo("estoque.txt");
    string linha;

    while (getline(arquivo, linha))
    {
        size_t pos1 = linha.find(',');
        size_t pos2 = linha.rfind(',');

        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
        {
            string nome = linha.substr(0, pos1);
            float preco = stof(linha.substr(pos1 + 1, pos2 - pos1 - 1));
            float quantidade = stof(linha.substr(pos2 + 1));

            estoque.push_back({nome, preco, quantidade});
        }
    }

    arquivo.close();
}

void CarregarCarrinho()
{
    ifstream arquivo("carrinho.txt");
    string linha;

    while (getline(arquivo, linha))
    {
        size_t pos1 = linha.find(',');
        size_t pos2 = linha.rfind(',');

        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2)
        {
            string nome = linha.substr(0, pos1);
            float preco = stof(linha.substr(pos1 + 1, pos2 - pos1 - 1));
            float quantidade = stof(linha.substr(pos2 + 1));

            carrinho.push_back({nome, preco, quantidade});
        }
    }

    arquivo.close();
}


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

void VerificarPreco()
{
    int countDot = 0;
    int countChar = 0;
    for (char &c : stgPreco)
    {
        if (!isdigit(c))
        {
            if (c == '.')
            {
                countDot++;
            }

            if (c != '.')
            {
                countDot += 2;
            }

            if (countDot > 1)
            {
                digitosPreco = false;
                break;
            }
        }
        countChar++;
    }

    if (countChar == 1 && countDot >= 1)
    {
        digitosPreco = false;
    }
}

void VerificarQuantidade()
{
    int countDot = 0;
    int countChar = 0;
    for (char &c : stgQtdd)
    {
        if (!isdigit(c))
        {
            if (c == '.')
            {
                countDot++;
            }

            if (c != '.')
            {
                countDot += 2;
            }

            if (countDot > 1)
            {
                digitosQtdd = false;
                break;
            }
        }
        countChar++;
    }

    if (countChar == 1 && countDot >= 1)
    {
        digitosQtdd = false;
    }
}

string Maiusculo(string nome)
{
    for (char &c : nome) {
        c = toupper(c);
    }
    return nome;
}

void CriaProduto(string nome, float preco, float quantidade)
{
    int tem = 0;
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            cout << endl
                 << "-------------------------------" << endl
                 << endl;
            cout << "O produto ja existe." << endl;
            estoque[i].preco = preco;
            estoque[i].quantidade += quantidade;
            tem = 1;
            cout << "Produto atualizado com sucesso" << endl;
            cout << endl
                 << "-------------------------------" << endl
                 << endl;
        }
    }

    if (tem == 0)
    {
        estoque.push_back({nome, preco, quantidade});
        cout << endl
             << "----------------------------" << endl
             << endl;
        cout << "Produto criado com sucesso" << endl;
        cout << endl
             << "----------------------------" << endl
             << endl;
    }
}

void ListarProdutos()
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

void DeletarProdutos(string nome)
{
    bool encontrado = false;
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            estoque.erase(estoque.begin() + i);

            cout << endl
                 << "-----------------------" << endl
                 << endl;
            cout << "!! Produto Deletado !!" << endl;
            cout << endl
                 << "-----------------------" << endl
                 << endl;
            encontrado = true;
        }
    }

    if (encontrado == false)
    {
        cout << endl
             << "-----------------------------" << endl
             << endl;
        cout << "!! Produto Nao Encontrado !!" << endl;
        cout << endl
             << "-----------------------------" << endl
             << endl;
    }
}

void AddCarrinho(string nome, float preco, float quantidade)
{
    carrinho.push_back({nome, preco, quantidade});
}

void VenderProdutos(string nome, float quantidade)
{
    bool encontrado = false;
    for (int i = 0; i < estoque.size(); i++)
    {
        if (estoque[i].nome == nome)
        {
            if (quantidade > estoque[i].quantidade)
            {
                cout << endl
                     << "-----------------------------------------" << endl
                     << endl;
                cout << "Quantidade escolhida maior que o estoque" << endl;
                cout << endl
                     << "-----------------------------------------" << endl
                     << endl;
                encontrado = true;
            }
            else
            {
                estoque[i].quantidade -= quantidade;
                AddCarrinho(estoque[i].nome, estoque[i].preco, quantidade);

                cout << endl
                     << "-------------------------------------" << endl
                     << endl;
                cout << "!! Produto Adicionado ao Carrinho !!" << endl;
                cout << endl
                     << "-------------------------------------" << endl
                     << endl;
                encontrado = true;
            }
        }
    }

    if (encontrado == false)
    {
        cout << endl
             << "-----------------------------" << endl
             << endl;
        cout << "!! Produto Nao Encontrado !!" << endl;
        cout << endl
             << "-----------------------------" << endl
             << endl;
    }
}

void 
PagarCarrinho()
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

    cout << "O preco total dos produtos eh: " << precoTotal << endl
         << endl;

    cout << "Voce quer pagar?" << endl;
    cout << "1 - Sim || 0 - Nao" << endl;
    cin >> stgEscolha;

    VerificarEscolha();
    LimparTexto();

    if (digitos)
    {
        escolhaCarrinho = stoi(stgEscolha);

        if (escolhaCarrinho == 1)
        {
            cout << "Escolha uma forma de pagamento:" << endl;
            cout << "1 - A vista (5% de desconto)" << endl;
            cout << "2 - Parcelado" << endl;
            cin >> stgEscolha;

            VerificarEscolha();
            LimparTexto();

            if (digitos)
            {
                escolhaCarrinho = stoi(stgEscolha);

                if (escolhaCarrinho == 1)
                {
                    cout << endl
                         << "---------------------------------------" << endl
                         << endl;
                    cout << "O preco dos produtos ficou em: " << precoTotal * 0.95 << endl;
                    cout << endl
                         << "---------------------------------------" << endl
                         << endl;

                    carrinho.clear();
                }
                else if (escolhaCarrinho == 2)
                {
                    cout << "Ate 3x sem juros ou ate 12x com 10% de juros" << endl;
                    cout << "Em quantas parcelas voce ira querer fazer? " << endl;
                    cin >> stgEscolha;

                    VerificarEscolha();
                    LimparTexto();

                    if (digitos)
                    {
                        escolhaCarrinho = stoi(stgEscolha);

                        if (escolhaCarrinho >= 1 && escolhaCarrinho <= 12)
                        {
                            if (escolhaCarrinho <= 3)
                            {
                                cout << endl
                                     << "---------------------------------------" << endl
                                     << endl;
                                cout << "O preco dos produtos ficou em: " << precoTotal << endl;
                                cout << "O preco da parcela ficou em: " << precoTotal / escolhaCarrinho << endl;
                                cout << endl
                                     << "---------------------------------------" << endl
                                     << endl;

                                carrinho.clear();
                            }
                            else
                            {
                                cout << endl
                                     << "---------------------------------------" << endl
                                     << endl;
                                cout << "O preco dos produtos ficou em: " << precoTotal * 1.1 << endl;
                                cout << "O preco da parcela ficou em: " << (precoTotal * 1.1) / escolhaCarrinho << endl;
                                cout << endl
                                     << "---------------------------------------" << endl
                                     << endl;

                                carrinho.clear();
                            }
                        }
                        else
                        {
                            cout << endl
                                 << "----------------------------------" << endl
                                 << endl;
                            cout << "Escolha Invalida!" << endl;
                            cout << "!! Escolha um Numero de 1 a 12 !!" << endl;
                            cout << endl
                                 << "----------------------------------" << endl
                                 << endl;
                        }
                    }
                    else
                    {
                        cout << endl
                             << "---------------------------------------" << endl
                             << endl;
                        cout << "Escolha Invalida!" << endl;
                        cout << "Nao utilize virgulas nem coloque ponto" << endl;
                        cout << endl
                             << "---------------------------------------" << endl
                             << endl;

                        escolha = -1;
                        escolhaCarrinho = -1;
                        digitos = true;
                    }

                    carrinho.clear();
                }
                else
                {
                    cout << endl
                         << "------------------" << endl
                         << endl;
                    cout << "Escolha Invalida!" << endl;
                    cout << endl
                         << "------------------" << endl
                         << endl;
                }
            }
            else
            {
                cout << endl
                     << "---------------------------------------" << endl
                     << endl;
                cout << "Escolha Invalida!" << endl;
                cout << "Nao utilize virgulas nem coloque ponto" << endl;
                cout << endl
                     << "---------------------------------------" << endl
                     << endl;

                escolha = -1;
                escolhaCarrinho = -1;
                digitos = true;
            }
        }
        else if (escolhaCarrinho == 0)
        {
            // Saiu do carrinho
        }
        else
        {
            cout << endl
                 << "------------------" << endl
                 << endl;
            cout << "Escolha Invalida!" << endl;
            cout << endl
                 << "------------------" << endl
                 << endl;
        }
    }
    else
    {
        cout << endl
             << "---------------------------------------" << endl
             << endl;
        cout << "Escolha Invalida!" << endl;
        cout << "Nao utilize virgulas nem coloque ponto" << endl;
        cout << endl
             << "---------------------------------------" << endl
             << endl;

        escolha = -1;
        escolhaCarrinho = -1;
        digitos = true;
    }
}

void Menu()
{
    string nome;
    float preco, quantidade;

    do
    {

        cout << endl
             << "--------------------------------" << endl
             << endl;
        cout << "0 - Encerrar/Salvar o Programa" << endl;
        cout << "1 - Criar/Atualizar Produtos" << endl;
        cout << "2 - Deletar Produtos" << endl;
        cout << "3 - Adicionar ao Carrinho" << endl;
        cout << "4 - Listar Estoque" << endl;
        cout << "5 - Pagar o Carrinho" << endl;
        cout << endl
             << "--------------------------------" << endl
             << endl;
        cin >> stgEscolha;

        VerificarEscolha();
        LimparTexto();

        if (digitos)
        {
            escolha = stoi(stgEscolha);

            if (escolha == 1)
            {
                cout << "Qual o nome do produto:" << endl;
                cin >> nome;
                cout << "Escolha o preco para o produto:" << endl;
                cin >> stgPreco;
                cout << "Qual a quantidade do produto:" << endl;
                cin >> stgQtdd;
                
                nome = Maiusculo(nome);

                LimparTexto();
                VerificarPreco();
                VerificarQuantidade();

                if (digitosPreco && digitosQtdd)
                {
                    preco = stof(stgPreco);
                    quantidade = stof(stgQtdd);
                    CriaProduto(nome, preco, quantidade);
                }
                else
                {
                    cout << endl
                         << "--------------------------------------------------" << endl
                         << endl;
                    cout << "Escolha Invalida!" << endl;
                    cout << "Nao utilize virgulas nem coloque mais de um ponto" << endl;
                    cout << endl
                         << "--------------------------------------------------" << endl
                         << endl;

                    escolha = -1;
                    digitosQtdd = true;
                    digitosPreco = true;
                }
            }
            else if (escolha == 2)
            {
                cout << "Qual produto voce quer deletar?" << endl;
                cin >> nome;

                nome = Maiusculo(nome);

                LimparTexto();

                DeletarProdutos(nome);
            }
            else if (escolha == 3)
            {
                cout << "Qual produto voce ira adicionar? ";
                cin >> nome;
                cout << "Qual a quantidade voce ira colocar? ";
                cin >> stgQtdd;

                nome = Maiusculo(nome);

                VerificarQuantidade();
                LimparTexto();

                if (digitosQtdd)
                {
                    quantidade = stof(stgQtdd);
                    VenderProdutos(nome, quantidade);
                }
                else
                {
                    cout << endl
                         << "--------------------------------------------------" << endl
                         << endl;
                    cout << "Escolha Invalida!" << endl;
                    cout << "Nao utilize virgulas nem coloque mais de um ponto" << endl;
                    cout << endl
                         << "--------------------------------------------------" << endl
                         << endl;

                    escolha = -1;
                    digitosQtdd = true;
                    digitosPreco = true;
                }
            }
            else if (escolha == 4)
            {
                LimparTexto();
                ListarProdutos();
            }
            else if (escolha == 5)
            {
                LimparTexto();
                PagarCarrinho();
            }
            else if (escolha == 0)
            {
                cout << endl
                     << "-------------------------" << endl
                     << endl;
                cout << "!! Programa Encerrado !!" << endl;
                cout << "!! Alteracoes Salvas !!" << endl;
                cout << endl
                     << "-------------------------" << endl
                     << endl;

                break;
            }
            else
            {
                cout << endl
                     << "-----------------" << endl
                     << endl;
                cout << "Escolha Invalida" << endl;
                cout << endl
                     << "-----------------" << endl
                     << endl;
            }
        }
        else if (digitos == false)
        {
            cout << endl
                 << "-----------------" << endl
                 << endl;
            cout << "Escolha Invalida" << endl;
            cout << endl
                 << "-----------------" << endl
                 << endl;

            escolha = -1;
            digitos = true;
        }

    } while (escolha != 0);
}

int main()
{
    LimparTexto();

    CarregarEstoque();
    CarregarCarrinho();

    Menu();

    SalvarEstoque();
    SalvarCarrinho();

    return 0;
}
