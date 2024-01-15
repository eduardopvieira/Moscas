#include <iostream>
#include "mosca.h"
#include <cstdlib>
#include <cmath>
using namespace std;

std::istream& operator>>(std::istream& input, Cor& cor) { //Receber a cor da mosca
	input >> cor.red >> cor.green >> cor.blue;
	return input;
};

std::ostream& operator<<(std::ostream& output, const Cor& cor) { //Mostrar as frases na cor desejada
	output << "\x1b[38;2;" << cor.red << ";" << cor.green << ";" << cor.blue << "m";
	return output;
};

std::ostream& operator<<(std::ostream& os, const Mosca& mosca) { //Mostrar as informações da mosca
    os << "Nome: " << mosca.nome << "\n";
    os << "Posicao atual: (" << mosca.posat.x << ", " << mosca.posat.y << ")\n";
    os << "Cor: (" << mosca.cor.red << ", " << mosca.cor.green << ", " << mosca.cor.blue << ")\n";
    return os;
}


int gerarNum(int x, int y) //Gera um número aleatório entre o num minimo (x) e o num maximo (y)
{
	int num;
	num = x + (rand() % y);
	return num;
}

float Magnitude(Ponto pos) //Calcula a magnitude da mosca em relação ao centro
{
    float mag;
    mag = sqrt(pow(pos.x, 2) + pow(pos.y, 2));
    return mag;
}

Vetor deslocamento() { //Cria um vetor com magnitude aleatoria entre 0 a 10 e um ângulo aleatorio entre 0 e 360
    Vetor deslocamento;
    deslocamento.angulo = gerarNum(0, 360);
    deslocamento.magnitude = gerarNum(0, 10);
    return deslocamento;
}


Ponto Deslocar(Ponto pos, Vetor desloc){ //Função que atualiza a posição da mosca. Decidi usar coordenadas polares.
    Ponto novapos;
    float pi = 3.14159;
    desloc.angulo = desloc.angulo * (pi / 180);
    novapos.x = pos.x + (desloc.magnitude * cos(desloc.angulo));
    novapos.y = pos.y + (desloc.magnitude * sin(desloc.angulo));
    return novapos;
}


bool Inativas(Mosca moscas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (moscas[i].atividade) { //Verifica a atividade de cada mosca. Caso uma esteja ativa, retorna false e o while continua rodando
            return false;
        }
    }
    return true; //Caso todas estejam inativas, retorna "true" e encerra o while
}

