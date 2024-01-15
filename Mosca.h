struct Cor
{
	int red;
	int green;
	int blue;
};

struct Ponto
{
	float x = 0;
	float y = 0;
};

struct Vetor
{
	float magnitude;
	float angulo;
};

struct Mosca
{
	char nome[20];
	Ponto posat;
	Cor cor;
	float passos = 1;
	bool atividade = true;
};

Ponto Deslocar (Ponto, Vetor);

Vetor deslocamento();

int gerarNum(int, int);

bool Inativas(Mosca moscas[], int tamanho);

float Magnitude(Ponto);

//Fun��o operator para exibir mosca
std::ostream& operator<<(std::ostream& os, const Mosca& mosca);

//Fun��o operator>> para ler as cores do registro Cor
std::istream& operator>>(std::istream& input, Cor& cor);

//Fun��o operator<< para alterar as cores do terminal
std::ostream& operator<<(std::ostream& output, const Cor& cor);