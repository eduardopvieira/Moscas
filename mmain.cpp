#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Mosca.h"
#include <iomanip>
using namespace std;

int main() {
    system("chcp 1252>nul");
    srand((unsigned)time(NULL));
    const int tamanho = 10;
    Mosca moscas[tamanho]; // Cria��o do vetor est�tico de 10 moscas conforme o pedido
    //----------------------------DECLARA��O DAS MOSCAS ABAIXO----------------------------------------------------------------------
    
    for (int i = 0; i < 10; i++) { //Cin pedindo os dados das 10 moscas pre-definidas:
        cin >> moscas[i].nome;
        cin >> moscas[i].cor.red >> moscas[i].cor.green >> moscas[i].cor.blue;
    }

    //----------------------------------SORTEIO DAS MOSCAS ABAIXO------------------------------------------------------------------
    
    cout << "\nSimulação" << endl << "--------- " << endl;
    int cont = 1; //Contador inicializado em 1, pois o passo "0" n�o � executado
    do {
        int numMoscas = gerarNum(1, 10); //L�gica: gerar um n�mero aleat�rio de 1 a 10 para ser o n�mero de moscas a serem movidas no passo espec�fico.
        Mosca** moscasSeraoMovidas = new Mosca * [numMoscas]; //Cria��o de um vetor dinamico de ponteiros do tamanho da quantidade de moscas a serem movidas
        int* numSort = new int[numMoscas]; //Tamb�m � criado outro vetor din�mico de inteiros que armazena os n�meros sorteados.
        for (int x = 0; x < numMoscas; x++)
        {
            numSort[x] = gerarNum(0, 10); //Aqui � realizado o sorteio dos n�meros.
            moscasSeraoMovidas[x] = &moscas[numSort[x]];//O vetor "moscasSeraoMovidas" recebe o endere�o de cada uma das moscas correspondentes ao numero sorteado.
        }
        //--------------------------------EXIBI��O DAS MOSCAS ABAIXO--------------------------------------------------------------        
        cout << "#" << cont << ": " << numMoscas << " ( ";
        for (int i = 0; i < numMoscas; i++) {
            Vetor vetor = deslocamento(); //Cada repeti��o cria um vetor de deslocamento aleatorio diferente, apontando para onde as moscas devem ir
            moscasSeraoMovidas[i]->posat = Deslocar(moscasSeraoMovidas[i]->posat, vetor); //A posi��o atual das moscas se torna a posi��o para o qual se deslocou

            if (moscasSeraoMovidas[i]->atividade) {//Verifica a atividade da mosca. Caso esteja ativa, mostra o n�mero correspondente a ela
                cout << numSort[i] << " ";
            }
            else {
                cout << "\x1b[38;2;255;0;0m" << "x " << "\x1b[0m"; //Caso esteja inativa, mostra o x vermelho.
            }
        }
        cout << ") = ";

        bool todasAtivasE100 = true;
        for (int i = 0; i < numMoscas; i++) {
            if (Magnitude(moscasSeraoMovidas[i]->posat) >= 100 && moscasSeraoMovidas[i]->atividade) { //Verifica se a mosca chegou aos 100 cm nesse passo, pois ela ainda estaria dada como "ativa"
                cout << moscasSeraoMovidas[i]->cor << " " << moscasSeraoMovidas[i]->nome << "\x1b[0m" << " ";//Caso tenha chegado, mostra o nome da mosca com sua cor correspondente.
                moscasSeraoMovidas[i]->atividade = false; //Torna a mosca inativa
                moscasSeraoMovidas[i]->passos = cont; //Trava o n�mero de passos da mosca como o n�mero que estava no contador quando ela chegou a 100
                moscas[numSort[i]].atividade = moscasSeraoMovidas[i]->atividade; //Passa a atividade da mosca para seu vetor original (n�o sei se essa linha � necess�ria, escrevi apenas para prevenir)
                moscas[numSort[i]].passos = moscasSeraoMovidas[i]->passos;//Passa os passos da mosca para seu vetor original (mesmo caso da linha acima)
                todasAtivasE100 = false; //Mostra que nem todas est�o Ativas, ent�o n�o vai mostrar um "0" depois dos n�meros das moscas
            }
        }

        if (todasAtivasE100) { //Caso todas as moscas do passo estejam Ativas E n�o chegaram a 100, da cout num 0 no final.
            cout << "0";
        }
        cout << endl;

                    
        cont++;//contador dos passos
        delete[] numSort; //deleta o vetor din�mico que armazena os numeros sorteados
        delete[] moscasSeraoMovidas; //deleta o vetor dinamico que armazena as moscas movidas
    } while (Inativas(moscas, tamanho) == false);

    //------------------------------------------MOSCA MAIS RAPIDA ABAIXO------------------------------------------------------------
   
    Mosca* pivo = nullptr;//cria uma mosca piv� para armazenar os dados da mosca mais r�pida
    int menor = INT_MAX;//cria um n�mero com o m�ximo inteiro poss�vel, para que o n�mero de passos da primeira mosca semrpe possa ser armazenada
    for (int i = 0; i < 10; i++) {
        if (moscas[i].passos < menor) { //verifica se a mosca foi mais r�pida que a anterior
            menor = moscas[i].passos;//caso tenha sido, o n�mero de compara��o se torna os passos dessa mosca
            pivo = &moscas[i];//seu endere�o � armazenado na mosca piv�
        }
    }

    //--------------------------------------------RESULTADOS ABAIXO-----------------------------------------------------------------
    
    cout << "Resultados\n---------------------" << endl;
    for (int i = 0; i < tamanho; i++) {

        cout << moscas[i].cor << " " << moscas[i].nome << "\x1b[0m" << " = " << moscas[i].passos << endl; //Mostra os passos de cada mosca com suas respectivas cores
        
    }
    
    float media = cont / tamanho; //Calcula a m�dia de passos das moscas
    double cmvoo = 100.f / pivo->passos; //Calcula os cm por v�o da mosca mais rapida
    
    
    cout << "\x1b[0m";
    cout << "---------------------" << endl;
    cout << "Total de passos: " << pivo->cor << cont-1 << "\x1b[0m" << endl;
    cout << "Em média as moscas levaram";
    std::cout << std::fixed << std::setprecision(1) << pivo->cor << " " << media << "\x1b[0m" << " passos" << endl;
    cout << "A mosca mais rápida foi" << pivo->cor << " " << pivo->nome << "\x1b[0m" << " com " << pivo->cor << " "
    << pivo->passos << "\x1b[0m" << " " << "passos." << endl;
    cout << "O que equivale a voar " << std::setprecision(6) << pivo->cor << cmvoo << " cm " << "\x1b[0m" << "por passo." << endl;
    //Exibe os dados finais, com as cores da mosca piv� (a mosca mais r�pida)
}

