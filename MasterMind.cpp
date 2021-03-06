#include <iostream>
#include <cctype>
#include <time.h>

using namespace std;

static string alfabeto = "ABCDEF";
#define NUM_PINS 6
#define NUM_CHAVE 4

void desenhaSegmento(char const c, int const n)
{
    for (int i = 0; i < n; i++)
    {
        cout << c << ' ';
    }
    cout << endl;
}

void apresentaResultados(int const numCertosLugarCerto, int const numCertos)
{    
    cout << '[';
    for (int i = 0; i < numCertosLugarCerto; i++)
    {
        cout << " + ";
    }
    for (int j = 0; j < (numCertos - numCertosLugarCerto); j++)
    {
        cout << " - ";
    }
    cout << ']';
}

int contarCertosLugarCerto(string const chave, string const inserida)
{
    int acertosLugarCerto = 0;
    for (int i = 0; i < NUM_CHAVE; i++)
    {
        if (inserida[i] == chave[i])
        {
            acertosLugarCerto++;
        }
    }
    return acertosLugarCerto;
}

int contarCertos(string const chave, string const inserida)
{
    string tempChave = chave, tempInserida = inserida;
    int acertos = 0;

    for (int i = 0; i < NUM_CHAVE; i++)
    {
        if (inserida[i] == chave[i])
        {
            tempChave[i] = ' ';
            tempInserida[i] = ' ';
            acertos++;
        }
    }

    for (int i = 0; i < NUM_CHAVE; i++)
    {
        if (tempInserida[i] != ' ')
        {
            for (int j = 0; j < NUM_CHAVE; j++)
            {
                if (tempInserida[i] == tempChave[j])
                {
                    acertos++;
                    tempChave[j] = ' ';
                    break;
                }
            }
        }
    }
    return acertos;
}

bool caractereValido(char const c)
{
    for (int i = 0; i < 6; i++)
    {
        if (c == alfabeto[i])
        {
            return 1;
        }
    }
    return 0;
}

void leCaractere(string const s, char &c)
{
    while (true)
    {
        if (cin.peek() != '\n')
        {
            cout << ' ';
        }
        else
        {
            for (int i = 0; i < s.length(); i++)
            {
                cout << s[i] << ' ';
            }            
        }

        cin >> c;
        c = toupper(c);

        if (caractereValido(c))
        {
            cout << "        ";
            return;
        }
        else
        {
            if(cin.peek() != '\n')
            {
                cout << endl << "        " << "Caractere inv??lido. Introduza novamente a chave apenas com caracteres permitidos." << endl; 
                cout << "        ";
                cin.clear();              
                for (int i = 0; i < s.length(); i++)
                {
                    cout << s[i] << ' ';
                }
                cin.ignore(5,'\n');
            }
            else
            {
                cout << "        "
                    << "Caractere Inv??lido!" << endl;
                cout << "        ";
                cin.clear();
                            
            }
        }
    }
}

string geraChave(int n)
{
    string chave = "";
    for (int i = 0; i < n; i++)
    {
        chave = chave + alfabeto[rand() % NUM_PINS];
    }
    return chave;
}

void jogar()
{
    int numTentativas = 0, numTentativasMax = 0;
    string chave, s = "        ", chaveInserida;
    char c;
    int acertosLugarCerto = 0, acertos = 0;

    cout << endl
         << "Introduza o n??mero m??ximo de tentativas admitido (max 10): ";
    cin >> numTentativasMax;

    if (numTentativasMax > 0 and numTentativasMax <= 10)
    {
        desenhaSegmento('-', NUM_CHAVE);
        srand(time(NULL));
        chave = geraChave(NUM_CHAVE);
        cout << chave << endl; // TENHO PRESENTE PARA TESTES APENAS
        while ((numTentativas < numTentativasMax) && (acertosLugarCerto < NUM_CHAVE))
        {
            chaveInserida = "";
            cout << "Jogada: ";
            for (int i = 0; i < NUM_CHAVE; ++i)
            {
                leCaractere(chaveInserida, c);
                chaveInserida += c;                
            }        
            acertosLugarCerto = contarCertosLugarCerto(chave, chaveInserida);
            acertos = contarCertos(chave, chaveInserida);
            cout << endl;
            apresentaResultados(acertosLugarCerto, acertos);
            numTentativas += 1;
            cout << endl
                 << endl
                 << "Tentativas restantes: " << numTentativasMax - numTentativas << endl;
            cout << endl;
        }

        if (acertosLugarCerto == NUM_CHAVE)
        {
            cout << endl
                 << "Parab??ns! :-)";
            cout << endl
                 << "Encontrou a sequ??ncia correta em " << numTentativas << " tentativa(s)!" << endl;
        }
        else
        {
            if (numTentativas == numTentativasMax)
            {
                cout << "Perdeu! :-( " << endl;
                cout << "A sequ??ncia correta era [" << chave << "]." << endl;
            }
        }
    }
    else
    {
        cout << endl
             << "Deve colocar um n??mero de tentativas entre 1 e 10!" << endl;
        jogar();
    }
}

void instrucoes()
{
    cout << "Instru????es" << endl
         << endl;
    cout << "S??mbolos poss??veis: A C B D E F." << endl;
    cout << "Introduza um s??mbolo de cada vez." << endl;
    cout << "Por cada s??mbolo na posi????o correta ?? exibido um '+'." << endl;
    cout << "Por cada s??mbolo correto na posi????o errada ?? exibido um '-'." << endl;
}

int main()
{
    int opcao;

    while (1)
    {
        cout << endl
             << "*** MasterMind ***" << endl;
        cout << endl;
        cout << "Menu Principal" << endl
             << endl;
        cout << "1. Jogar" << endl;
        cout << "2. Instru????es" << endl;
        cout << "3. Sair" << endl
             << endl;
        cout << "Op????o: ";

        cin >> opcao;

        switch (opcao)
        {
        case 1:
            jogar();
            break;

        case 2:
            cout << endl;
            instrucoes();
            cout << endl;
            break;

        case 3:
            cout << endl
                 << "Terminou o jogo MasterMind! Volte sempre!" << endl;
            return (0);            

        default:
            cout << endl
                 << "Op????o errada. Escolha 1 para jogar, 2 para instru????es ou 3 para terminar jogo." << endl
                 << endl;
        }
    }
}