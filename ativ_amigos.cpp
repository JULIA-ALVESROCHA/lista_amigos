#include <iostream> 
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

typedef struct {
    int id;
    string name;
    string email;
    string celular;
    string cidade;
} Amigo;

// varáveis globais
const int MAX_AMIGOS = 1000;
Amigo agenda[MAX_AMIGOS];
int totalAmigos = 0;

// TRATAMENTO: searching for case- insensitive
string toLower(const string& str){
    string result = str;
    // transform() aplica o toLower em cada string
    transform(result.begin(), result.end(), result.begin(), ::toLower);
    return result;
}

//Remove os espaços em branco do início e do fim da string
string trim(const string& str){
    // Encontra o primeiro não-espaço.
    size_t start = str.find_first_not_of("\t\n\r");
    if (start == string::npos) return""; // string só com espaços

    // Encontra o último caractere que não é espaço
    size_t end = str.find_last_not_of("\t\n\r");
   return str.substr(start, end - start +1);
}

//validação básica de email 
bool isValidEmail(const string& email) {
    return email.find('@') != string::npos && email.find('.') != string::npos;
}

// Gera  o próximo ID disponível
int getNextId() {
    //percorre todos os amigos para encontrar o Maior ID
    int getNextId() {
        for (int i = 0; i < totalAmigos; i++) {
        if (agenda[i].id > maxId){
            maxId =  agenda[i].id;
             }
    
        }
    }
    return maxId +1;
}

// PERSISTêNCIA DE DADOS
//carrega os dados do arquivo agenda.txt para a memória
void carregarAgenda() {
    totalAmigos = 0;
    ifstream arquivo("agenda.txt");

    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha) && totalAmigos < MAX_AMIGOS) {
            size_t pos1 = linha.find('_');                    /* Primeira posição do '_' */
            size_t pos2 = linha.find('_', pos1 + 1);         /* Segunda posição */
            size_t pos3 = linha.find('_', pos2 + 1);         /* Terceira posição */
            size_t pos4 = linha.find('_', pos3 + 1);  
            
            // Verifica se todos os separadores foram encontrados
            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) 
                try {  // Extrai cada campo usando substring
                    agenda[totalAmigos].id = stoi(linha.substr(0, pos1));  // Converte string para int
                    agenda[totalAmigos].nome = linha.substr(pos1 + 1, pos2 - pos1 - 1);
                    agenda[totalAmigos].email = linha.substr(pos2 + 1, pos3 - pos2 - 1);
                    agenda[totalAmigos].celular = linha.substr(pos3 + 1, pos4 - pos3 - 1);
                    agenda[totalAmigos].cidade = linha.substr(pos4 + 1);
                    totalAmigos++;
            } catch (const exception& e) {
                // trata od erros de conversão ou parsing
                cout << "Erro ao processar linha: " << linha << endl;
            }
        }
    }
    arquivo.close();
    cout << "Agenda carregada com sucesso! (" << totalAmigos << " amigos)" << endl;
} else {
    cout << "Aruivo agenda.txt não encontrado. Criando nova agenda." << endl;
}

//Salva todos os dados da memória no arquivo agenda.txt
void salvarAgenda() {
    ofstream arquivo("agenda.txt");

    if (arquivo.is_open()) {
        //Escreve cada amigo em uma linha no formato desejado
        for(int i = 0; i < totalAmigos; i++){
            arquivo << agenda[i].id << "_" << agenda[i].nome << "_" << agenda[i].email << "_" 
                   << agenda[i].celular << "_" << agenda[i].cidade << endl;
        }
        arquivo.close();
        cout << "Agenda salva com sucesso!" << endl;
    } else {
        cout << "Erro ao salvar a agenda!" << endl;
    }
}

/*OPERAÇÕES CRUD*/
//CREATE : INSERE um novo amigo na agenda
void inserirAmigo() {
    //verificar se exiteespaço na agenda
    if(totalAmigos >= MAX_AMIGOS) {
        cout << "Agenda está cheia! Máximo de " << MAX_AMIGOS << "amigos." << endl;
        return;
    }
    // estrutura temporária para o novo amigo.
    Amigo novo;
    string input;

    cout << "\n--- Inserir Novo Amigo ---" << endl;
    
    do {
        cout << "Nome Completo: ";
        getline(cin, input);
        novo.nome = trim(input); //remove os espaços extras
        if (novo.nome.empty()) {
            cout << "Nome não pode estar vazio!" << endl; //Quando existe a possibilidade de que o input interfira no código precisa de uma estrutura "ErroHandling".
        } while (novo.nome.empty());
            do { // mesmo para o email     
        cout << "Email: ";
        getline(cin, input);
        novo.email = trim(input);
        if (novo.email.empty()) {
            cout << "Email não pode estar vazio!" << endl;
        } else if (!isValidEmail(novo.email)) {
            cout << "Email inválido! Deve conter @ e ." << endl;
            novo.email = "";  // Força nova entrada
        } while (novo.email.empty());
            do {
        cout << "Celular: ";
        getline(cin, input);
        novo.celular = trim(input);
        if (novo.celular.empty()) {
            cout << "Celular não pode estar vazio!" << endl;
        }
    } while (novo.celular.empty());
    
    // Coleta cidade (obrigatória)
    do {
        cout << "Cidade: ";
        getline(cin, input);
        novo.cidade = trim(input);
        if (novo.cidade.empty()) {
            cout << "Cidade não pode estar vazia!" << endl;
        }
        } while (novo.cidade.empty())

        // gera Novo Id
        novo.id = getNextId();
        agenda[totalAmigos] = novo;
        totalAmigos++;
        salvarAgenda();
        cout << "Amigo acionado com sucesso ! ID: " << novo.id << endl;
    }
void buscarPorNome() {
    string termo;
    cout << "\nDigite o nome para buscar: ";
    getline(cin, termo);
    termo = trim(termo);

    if(trmo.empty()) {
        cout << "Termo de busca não pde estar vazio!" << endl;
        return;
    }
    string termoLower = toLower(termo);
    bool encontrado = false;
    cout << "\n--- Resultados da Busca ---" << endl;
    // Percorre toda a agenda procurando correspondências
    for (int i = 0; i < totalAmigos; i++) {
        // Busca case-insensitive usando find()
        if (toLower(agenda[i].nome).find(termoLower) != string::npos) {
            // Exibe todos os dados do amigo encontrado
            cout << "\nID: " << agenda[i].id << endl;
            cout << "Nome: " << agenda[i].nome << endl;
            cout << "Email: " << agenda[i].email << endl;
            cout << "Celular: " << agenda[i].celular << endl;
            cout << "Cidade: " << agenda[i].cidade << endl;
            cout << "-------------------------" << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "Nenhum amigo encontrado com esse nome." << endl;
    }
}

//READ: Buscar amigos por cidade
void buscarPorCidade() {
    string cidade;
    cout << "\nDigite a cidade para buscar: ";
    getline(cin, cidade);
    cidade = trim(cidade);

    if (cidade.empty()) {
        cout << "Nome da cidade não pode estar vazio!" << endl;
        return;
    }
    string cidadeLower = toLower(cidade);
    bool encntrado = false;

    cout << "\n--- Amigos em " << cidade << " ---" << endl;
    for (int i = 0; i < totalAmigos; i++) {
        // Busca case-insensitive na cidade
        if (toLower(agenda[i].cidade).find(cidadeLower) != string::npos) {
           cout << "\nID: " << agenda[i].id << endl;
            cout << "Nome: " << agenda[i].nome << endl;
            cout << "Email: " << agenda[i].email << endl;
            cout << "Celular: " << agenda[i].celular << endl;
            cout << "Cidade: " << agenda[i].cidade << endl;
            cout << "-------------------------" << endl;
            encontrado = true;
        }
    }
} 
if (!encontrado) {
    cout << "Nenhum amigo encontrado nesta cidade." << endl;
    }
}
// READ: Lista todos os amigos cadastrados
void listarTodos() {
    if (totalAmigos == 0) {
        cout << "\nAgenda vazia!" << endl;
        return;
    }
    
    cout << "\n--- Lista de Amigos (" << totalAmigos << " total) ---" << endl;
    // Exibe todos os amigos em formato compacto
    for (int i = 0; i < totalAmigos; i++) {
        cout << "ID: " << agenda[i].id << " | " << agenda[i].nome << " | " << agenda[i].email << " | " 
             << agenda[i].celular << " | " << agenda[i].cidade << endl;
    }
}
// UPDATE: Edita os dados de um amigo existente
