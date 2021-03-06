#include "Menu.h"


void Menu::PrintPointerListReserva(list<Reserva *> pl) {
    cout << endl;
    cout << "|||-> " << endl << endl;
    for (auto it = pl.begin(); it != pl.end(); it++){
        (*(*it)).Info();
        cout << endl;
    }
    cout << "<-||| " << endl;
}

void Menu::PrintPointerListFunc(list<Funcionario *> pl) {
    cout << endl;
    cout << "|||-> " << endl << endl;
    for (auto it = pl.begin(); it != pl.end(); it++){
        (*(*it)).Info();
        cout << endl;
    }
    cout << "<-||| " << endl;
}

void Menu::PrintPointerListCliente(list<Cliente *> pl) {
    cout << endl;
    cout << "|||-> " << endl << endl;
    for (auto it = pl.begin(); it != pl.end(); it++){
        (*(*it)).Info();
        cout << endl;
    }
    cout << "<-||| " << endl;
}

void Menu::ImportarHotel(Hotel &H, string localizacao) {
    ifstream inficheiro;
    inficheiro.open(localizacao);
    if(inficheiro.fail()){
        cout << endl << "O Ficheiro nao abre!" << endl;
        return;
    }

    string line;
    getline(inficheiro, line);
    if(line != "Hotel") return;
    getline(inficheiro, line);
    if(line != "") H.nome = line;
    inficheiro.close();
    try{
        H.ImportarQuartos(localizacao);
        H.ImportarProdutos(localizacao);
        H.ImportarClientes(localizacao);
        H.ImportarFuncionarios(localizacao);
        H.ImportarReservas(localizacao);
        H.ImportarServicos(localizacao);
        H.ImportarVeiculos(localizacao);
        H.ImportarCompras(localizacao);
    }
    catch (FicheiroIncompativel fi){
        inficheiro.close();
        cout << endl << "O Ficheiro em " << fi.nomeficheiro << " nao e compativel!" << endl;
    }
    catch (MembroIncompativel mi){
        inficheiro.close();
        cout << endl << "Um Membro do tipo " << mi.tipo_membro << " nao e compativel!" << endl;
    }
}

void Menu::PrintHotel() {
    cout << endl << endl << "||| " << "BEM-VINDO AO " << H.nome << " |||" << endl << endl;
    PrintList(H.GetQuartos());
    PrintList(H.GetProdutos());
    PrintList(H.GetFuncionariosGestores());
    PrintList(H.GetFuncionariosResponsaveis());
    PrintList(H.GetFuncionariosLimpeza());
    PrintList(H.GetFuncionariosGestores());
    PrintList(H.GetFuncionarios());
    PrintList(H.GetClientes());
    PrintList(H.GetServicos());
    PrintList(H.GetEstadias());
    PrintList(H.GetReservasAtuais());
    PrintList(H.GetReservas());
    PrintPQ(H.GetCompras());
    PrintBST(H.GetFrota());
}

string Menu::NomeFicheiro(){
    string localizacao;
    ifstream inficheiro;
    cout<<"Introduza o nome do ficheiro: ";
    cin>>localizacao;
    if(!cin.fail()){
        if(localizacao.size() < 4 || localizacao.substr(localizacao.length() - 4) != ".txt") localizacao += ".txt";
    }
    inficheiro.open(localizacao);
    while(cin.fail() || inficheiro.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        inficheiro.clear();
        cout << "Nome do ficheiro incorreto." << endl;
        cout<<"Introduza o nome do ficheiro: ";
        cin>>localizacao;
        if(!cin.fail()){
            if(localizacao.substr(localizacao.size() < 4 || localizacao.length() - 4) != ".txt") localizacao += ".txt";
        }
        inficheiro.open(localizacao);
    }
    cin.clear();
    cin.ignore(1000, '\n');
    inficheiro.close();
    return localizacao;
}

void Menu::ImprimeTit(string titulo) {
    string uptitulo = titulo;
    for (int i = 0; titulo.size() > i; i++){
        uptitulo[i] = toupper(titulo[i]);
    }
    cout << endl << endl << "|| " << uptitulo << " ||" << endl << endl;
}

void Menu::ImprimeOp(vector <string> opcoes, bool aviso, bool enm) {
    for(int i = 0; opcoes.size() > i; i++) {
        if (opcoes.size() <= 10) cout << "[" << i << "] " << opcoes[i] << endl;
        else {
            if (i <= 9) cout << "[0" << i << "] " << opcoes[i] << endl;
            else cout << "[" << i << "] " << opcoes[i] << endl;
        }
    }
    if(aviso) cout << "Input invalido. Insira um numero entre 0 e " << opcoes.size() - 1 << "." << endl;
    if(!enm) cout << "Escolha: ";
}

unsigned Menu::ProcessarInputInt(vector<string> opcoes, string titulo, unsigned liminf, unsigned limsup) {
    unsigned resposta;
    ImprimeTit(titulo);
    ImprimeOp(opcoes, false, false);
    cin >> resposta;
    while (cin.fail() || resposta < liminf || resposta > limsup){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeTit(titulo);
        ImprimeOp(opcoes, true, false);
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

unsigned Menu::ProcessarInputInt(vector<string> opcoes, string titulo) {
    unsigned liminf = 0, limsup = opcoes.size() - 1, resposta;
    ImprimeTit(titulo);
    ImprimeOp(opcoes, false, false);
    cin >> resposta;
    while (cin.fail() || resposta < liminf || resposta > limsup){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeTit(titulo);
        ImprimeOp(opcoes, true, false);
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

vector <int> Menu::ProcessarIntIndef(string colecao_sing, string colecao_plural, int lim) {
    vector <int> respostas;
    int resp;
    bool repetido = false;
    cout << "[-X] para parar de introduzir mais inputs a colecao de " << colecao_plural << endl;
    cout << "[+X] para adicionar input a colecao de " << colecao_plural << endl;
    cout << "Introduza [-X] ou " << colecao_sing << ": ";
    cin >> resp;
    if(resp >= 0){
        repetido = false;
        for(int i = 0; respostas.size() > i; i++){
            if(respostas[i] == resp){
                repetido = true;
                break;
            }
        }
        if(!repetido) respostas.push_back(resp);
    }
    while (cin.fail() || resp >= 0 || respostas.size() < lim){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[-X] para parar de introduzir mais inputs a colecao de " << colecao_plural << endl;
        cout << "[+X] para adicionar input a colecao de " << colecao_plural << endl;
        cout << "Introduza [-X] ou " << colecao_sing << ": ";
        cin >> resp;
        if(resp >= 0){
            repetido = false;
            for(int i = 0; respostas.size() > i; i++){
                if(respostas[i] == resp){
                    repetido = true;
                    break;
                }
            }
            if(!repetido) respostas.push_back(resp);
        }
    }
    return respostas;
}

template<class T>
vector <int> Menu::ProcessarIntIndef(string colecao_sing, string colecao_plural, int lim, list <T> l){
    vector <int> respostas;
    int resp;
    bool repetido = false, pertence = false;
    cout << endl << "[-X] para parar de introduzir mais inputs a colecao de " << colecao_plural << endl;
    cout << "[+X] para adicionar input a colecao de " << colecao_plural << endl;
    cout << "Introduza [-X] ou " << colecao_sing << ": ";
    cin >> resp;
    if(resp >= 0){
        repetido = false;
        pertence = false;
        for(int i = 0; respostas.size() > i; i++){
            if(respostas[i] == resp){
                repetido = true;
                break;
            }
        }
        for(auto it = l.begin(); it != l.end(); it++){
            if((*it).ID() == resp){
                pertence = true;
                break;
            }
        }
        if(!repetido && pertence) respostas.push_back(resp);
    }
    while (cin.fail() || resp >= 0 || respostas.size() < lim){
        cin.clear();
        cin.ignore(1000, '\n');
        if(resp >= 0 && !pertence) cout << endl << "Membro Inexistente! Insira um ID Valido para um membro que exista." << endl;
        if(resp < 0 && respostas.size() < lim) cout << endl << "Colecao Insuficiente! Insira mais inputs ate atingir o minimo de " << lim << endl;
        cout << endl <<  "[-X] para parar de introduzir mais inputs a colecao de " << colecao_plural << endl;
        cout << "[+X] para adicionar input a colecao de " << colecao_plural << endl;
        cout << "Introduza [-X] ou " << colecao_sing << ": ";
        cin >> resp;
        if(resp >= 0){
            repetido = false;
            pertence = false;
            for(int i = 0; respostas.size() > i; i++){
                if(respostas[i] == resp){
                    repetido = true;
                    break;
                }
            }
            for(auto it = l.begin(); it != l.end(); it++){
                if((*it).ID() == resp){
                    pertence = true;
                    break;
                }
            }
            if(!repetido && pertence) respostas.push_back(resp);
        }
    }
    return respostas;
}


template<class T>
T Menu::InputRestrito(string texto) {
    T resposta;
    cout << endl << texto;
    cin >> resposta;
    while (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto;
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

string Menu::InputNome(string texto) {
    string resposta;
    cout << endl << texto;
    getline(cin, resposta);
    while (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto;
        getline(cin, resposta);
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

data Menu::InputData(string texto) {
    data resposta;
    int dia, mes, ano;
    bool mespr = false;
    vector <int> mesproibido;
    cout << endl << texto << endl << "Introduza o dia: ";
    cin >> dia;
    while (cin.fail() || dia < 1 || dia > 31){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto << endl << "Introduza o dia: ";
        cin >> dia;
    }
    if(dia > 28) mesproibido.push_back(2);
    if(dia > 30){
        mesproibido.push_back(4);
        mesproibido.push_back(6);
        mesproibido.push_back(9);
        mesproibido.push_back(11);
    }
    cout << endl << texto << endl << "Introduza o mes: ";
    cin >> mes;
    if(!cin.fail() && mes >= 1 && mes <= 12){
        for(int i = 0; mesproibido.size() > i; i++){
            if(mesproibido[i] == mes) {
                mespr = true;
                break;
            }
        }
    }
    while (cin.fail() || mes < 1 || mes > 12 || mespr){
        mespr = false;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto << endl << "Introduza o mes: ";
        cin >> mes;
        if(!cin.fail() && mes >= 1 && mes <= 12){
            for(int i = 0; mesproibido.size() > i; i++){
                if(mesproibido[i] == mes) {
                    mespr = true;
                    break;
                }
            }
        }
    }
    cout << endl << texto << endl << "Introduza o ano: ";
    cin >> ano;
    while (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto << endl << "Introduza o ano: ";
        cin >> ano;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    resposta = {.dia = dia, .mes = mes, .ano = ano};
    return resposta;
}

matricula Menu::InputMatricula(string texto) {
    string resposta;
    matricula res;
    cout << endl << texto << endl << "A matricula e aceite no seguinte formato : AA-AA-AA." << endl << "onde A (um caracter) pode ser uma letra ou um numero" << endl <<"Introduza a Matricula: ";
    cin >> resposta;
    while (cin.fail() || resposta.size() != 8 || resposta[2] != '-' || resposta[5] != '-'){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << texto << endl << "Matricula Invalida" << endl <<"A matricula e aceite no seguinte formato : AA-AA-AA." << endl << "onde A (um caracter) pode ser uma letra ou um numero" << endl <<"Introduza a Matricula: ";
        cin >> resposta;
    }

    cin.clear();
    cin.ignore(1000, '\n');
    res = transf_matricula(resposta);
    return res;
}

char Menu::InputLetra(string texto) {
    char resp;
    cout << texto;
    cin >> resp;
    while(cin.fail() || resp < 65 || resp > 122 || (resp >= 91 && resp <= 96)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Tem de inserir uma Letra!" << endl;
        cout << texto;
        cin >> resp;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resp;
}

nota_avaliacao Menu::InputNota(string texto){
    int respint;
    nota_avaliacao resposta;
    vector<string> opcoes = {"Ma" , "Insuficiente", "Razoavel", "Boa", "Excelente"};
    ImprimeOp(opcoes, false, true);
    cout << texto;
    cin >> respint;
    while(cin.fail() || respint < 0 || respint > 4){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeOp(opcoes, true, true);
        cout << texto;
        cin >> respint;
    }
    switch (respint){
        case 0:
            resposta = ma;
            break;
        case 1:
            resposta = insuficiente;
            break;
        case 2:
            resposta = razoavel;
            break;
        case 3:
            resposta = boa;
            break;
        case 4:
            resposta = excelente;
            break;
        default:
            resposta = razoavel;
            break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

tipo_cargo Menu::InputCargo(string texto) {
    int respint;
    tipo_cargo resposta;
    vector<string> opcoes = {"Normal" , "Rececao", "Responsavel", "Limpeza", "Gestor"};
    ImprimeOp(opcoes, false, true);
    cout << texto;
    cin >> respint;
    while(cin.fail() || respint < 0 || respint > 4){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeOp(opcoes, true, true);
        cout << texto;
        cin >> respint;
    }
    switch (respint){
        case 0:
            resposta = naodef;
            break;
        case 1:
            resposta = frececao;
            break;
        case 2:
            resposta = fresponsavel;
            break;
        case 3:
            resposta = flimpeza;
            break;
        case 4:
            resposta = fgestor;
            break;
        default:
            resposta = naodef;
            break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

tipo_turno Menu::InputTurno(string texto) {
    int respint;
    tipo_turno resposta;
    vector<string> opcoes = {"Dia" , "Noite"};
    ImprimeOp(opcoes, false, true);
    cout << texto;
    cin >> respint;
    while(cin.fail() || respint < 0 || respint > 1){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeOp(opcoes, true, true);
        cout << texto;
        cin >> respint;
    }
    switch (respint){
        case 0:
            resposta = dia;
            break;
        case 1:
            resposta = noite;
            break;
        default:
            resposta = dia;
            break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

tipo_produto Menu::InputTProd(string texto) {
    int respint;
    tipo_produto resposta;
    vector<string> opcoes = {"Restauracao" , "Limpeza", "Souvenir"};
    ImprimeOp(opcoes, false, true);
    cout << texto;
    cin >> respint;
    while(cin.fail() || respint < 0 || respint > 2){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeOp(opcoes, true, true);
        cout << texto;
        cin >> respint;
    }
    switch (respint){
        case 0:
            resposta = restauracao;
            break;
        case 1:
            resposta = limpeza;
            break;
        case 2:
            resposta = souvenir;
            break;
        default:
            resposta = souvenir;
            break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

tipo_quarto Menu::InputTQuarto(string texto) {
    int respint;
    tipo_quarto resposta;
    vector<string> opcoes = {"Sem Vista" , "Com Vista", "Suite"};
    ImprimeOp(opcoes, false, true);
    cout << texto;
    cin >> respint;
    while(cin.fail() || respint < 0 || respint > 2){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeOp(opcoes, true, true);
        cout << texto;
        cin >> respint;
    }
    switch (respint){
        case 0:
            resposta = sem_vista;
            break;
        case 1:
            resposta = com_vista;
            break;
        case 2:
            resposta = suite;
            break;
        default:
            resposta = sem_vista;
            break;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return resposta;
}

template<class T>
bool Menu::ProcuraValida(int id, list<T> l) {
    for(auto it = l.begin(); it != l.end(); it++){
        if((*it).ID() == id) return true;
    }
    return false;
}

template<class T>
bool Menu::ProcuraValida(int id, priority_queue<T> pq) {
    vector <T> temp;
    while(!pq.empty()){
        T element = pq.top();
        if(element.ID() == id){
            for(int i = 0; temp.size() > i; i++) pq.push(temp[i]);
            return true;
        }
        temp.push_back(element);
        pq.pop();
    }
    for(int i = 0; temp.size() > i; i++) pq.push(temp[i]);
    return false;
}

template<class T>
bool Menu::ProcuraValida(int id, BST<T> bst) {
    BSTItrIn<Veiculo> it(bst);
    for (; !it.isAtEnd();it.advance()) {
        if((it.retrieve()).ID() == id) return true;
    }
    return false;
}


template<class T>
T Menu::EfetuarProcura(int id, list<T> l) {
    for(auto it = l.begin(); it != l.end(); it++){
        if((*it).ID() == id) return (*it);
    }
    throw MembroFalta();
}

template<class T>
T Menu::EfetuarProcura(int id, priority_queue<T> pq) {
    vector <T> temp;
    while(!pq.empty()){
        T element = pq.top();
        if(element.ID() == id){
            for(int i = 0; temp.size() > i; i++) pq.push(temp[i]);
            return (element);
        }
        temp.push_back(element);
        pq.pop();
    }
    for(int i = 0; temp.size() > i; i++) pq.push(temp[i]);
    throw MembroFalta();
}

template<class T>
T Menu::EfetuarProcura(int id, BST<T> bst) {
    BSTItrIn<Veiculo> it(bst);
    for (; !it.isAtEnd();it.advance()) {
        if((it.retrieve()).ID() == id) return it.retrieve();
    }
    throw MembroFalta();
}


template<class T>
int Menu::ProcessarInputProcura(string titulo, list<T> l) {
    int resposta;
    ImprimeTit(titulo);
    PrintList(l);
    cout << "[-X] Voltar" << endl;
    cout << "[-1] Ver Info" << endl;
    cout << "[+X] O ID do Elemento que Procura" << endl;
    cout << "Escolha: ";
    cin >> resposta;
    while(cin.fail() || resposta == -1 || (resposta >= 0 && !ProcuraValida(resposta, l))){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeTit(titulo);
        if(resposta == -1) PrintList(l);
        cout << "[-X] Voltar" << endl;
        cout << "[-1] Ver Info" << endl;
        cout << "[+X] O ID do Elemento que Procura" << endl;
        if(cin.fail()) cout << "Input Invalido! Tem de ser um numero inteiro." << endl;
        else{
            cout << "Nao foi encontrado nenhum elemento correspondente a sua Pesquisa." << endl;
            cout << "Escolha [-1] para a Informacao dos elementos da Classe que escolheu ou tente pesquisar novamente." << endl;
        }
        cout << "Escolha: ";
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    if(resposta < -1) return -1;
    else return resposta;
}

template<class T>
int Menu::ProcessarInputProcura(string titulo, priority_queue<T> pq) {
    int resposta;
    ImprimeTit(titulo);
    PrintPQ(pq);
    cout << "[-X] Voltar" << endl;
    cout << "[-1] Ver Info" << endl;
    cout << "[+X] O ID do Elemento que Procura" << endl;
    cout << "Escolha: ";
    cin >> resposta;
    while(cin.fail() || resposta == -1 || (resposta >= 0 && !ProcuraValida(resposta, pq))){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeTit(titulo);
        if(resposta == -1) PrintPQ(pq);
        cout << "[-X] Voltar" << endl;
        cout << "[-1] Ver Info" << endl;
        cout << "[+X] O ID do Elemento que Procura" << endl;
        if(cin.fail()) cout << "Input Invalido! Tem de ser um numero inteiro." << endl;
        else{
            cout << "Nao foi encontrado nenhum elemento correspondente a sua Pesquisa." << endl;
            cout << "Escolha [-1] para a Informacao dos elementos da Classe que escolheu ou tente pesquisar novamente." << endl;
        }
        cout << "Escolha: ";
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    if(resposta < -1) return -1;
    else return resposta;
}

template<class T>
int Menu::ProcessarInputProcura(string titulo, BST<T> bst) {
    int resposta;
    ImprimeTit(titulo);
    PrintBST(bst);
    cout << "[-X] Voltar" << endl;
    cout << "[-1] Ver Info" << endl;
    cout << "[+X] O ID do Elemento que Procura" << endl;
    cout << "Escolha: ";
    cin >> resposta;
    while(cin.fail() || resposta == -1 || (resposta >= 0 && !ProcuraValida(resposta, bst))){
        cin.clear();
        cin.ignore(1000, '\n');
        ImprimeTit(titulo);
        if(resposta == -1) PrintBST(bst);
        cout << "[-X] Voltar" << endl;
        cout << "[-1] Ver Info" << endl;
        cout << "[+X] O ID do Elemento que Procura" << endl;
        if(cin.fail()) cout << "Input Invalido! Tem de ser um numero inteiro." << endl;
        else{
            cout << "Nao foi encontrado nenhum elemento correspondente a sua Pesquisa." << endl;
            cout << "Escolha [-1] para a Informacao dos elementos da Classe que escolheu ou tente pesquisar novamente." << endl;
        }
        cout << "Escolha: ";
        cin >> resposta;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    if(resposta < -1) return -1;
    else return resposta;
}



void Menu::Inicial() {
    string titulo = "Inicio";
    vector<string> opcoes = {"Importar Hotel a partir de Ficheiro", "Criar Hotel do Inicio"};
    unsigned resposta;
    resposta = ProcessarInputInt(opcoes, titulo, 0, 1);
    if(resposta == 0){
        string localizacao = NomeFicheiro();
        ImportarHotel(H, localizacao);
        PrintHotel();
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return Principal();
}

void Menu::Importar() {
    string titulo = "Importar";
    unsigned resposta;
    vector<string> opcoes = membros;
    for (int i = 0; opcoes.size() > i; i++){
        opcoes[i] = opcoes[i] + "s";
    }
    opcoes.push_back("Hotel");
    for (int i = 0; opcoes.size() > i; i++){
        opcoes[i] = "Importar " + opcoes[i];
    }
    opcoes.push_back("Voltar");
    resposta = ProcessarInputInt(opcoes, titulo);
    string localizacao;
    if(resposta != 9) localizacao = NomeFicheiro();
        switch (resposta) {
            case 0:
                H.ImportarClientes(localizacao);
                PrintList(H.GetClientes());
                break;
            case 1:
                H.ImportarFuncionarios(localizacao);
                PrintList(H.GetFuncionariosRececao());
                PrintList(H.GetFuncionariosResponsaveis());
                PrintList(H.GetFuncionariosLimpeza());
                PrintList(H.GetFuncionariosGestores());
                PrintList(H.GetFuncionarios());
                break;
            case 2:
                H.ImportarProdutos(localizacao);
                PrintList(H.GetProdutos());
                break;
            case 3:
                H.ImportarQuartos(localizacao);
                PrintList(H.GetQuartos());
                break;
            case 4:
                H.ImportarReservas(localizacao);
                PrintList(H.GetReservas());
                break;
            case 5:
                H.ImportarServicos(localizacao);
                PrintList(H.GetServicos());
                break;
            case 6:
                H.ImportarVeiculos(localizacao);
                PrintBST(H.GetFrota());
                break;
            case 7:
                H.ImportarCompras(localizacao);
                PrintPQ(H.GetCompras());
                break;
            case 8:
                ImportarHotel(H, localizacao);
                PrintHotel();
                break;
            case 9:
                return Principal();
            default:
                return Importar();
        }
        return Importar();
}

void Menu::VerInfo() {
    string titulo = "Ver Informacao";
    unsigned resposta, segresp;
    vector<string> opcoes = membros;
    opcoes.push_back("Hotel");
    for (int i = 0; opcoes.size() > i; i++) {
        opcoes[i] = "Ver Info " + opcoes[i];
    }
    opcoes.push_back("Voltar");
    resposta = ProcessarInputInt(opcoes, titulo);
    if (resposta == 9) return Principal();
    if (resposta == 8) {
        PrintHotel();
        return VerInfo();
    }
    vector<string> segopcoes = {"Ver Informacao de Todos", "Ver Informacao de 1 em Especifico", "Voltar",
                                "Voltar ao Menu Principal"};
    segresp = ProcessarInputInt(segopcoes, opcoes[resposta]);
    unsigned tresposta;
    string sectit = segopcoes[segresp] + " " + opcoes[resposta];
    vector<string> topcoes;
    vector<string> resopcoes = {"Estadia", "Reserva Atual", "Reserva"};
    for (int i = 0; resopcoes.size() > i; i++) {
        resopcoes[i] = "Ver Info de " + resopcoes[i];
    }
    resopcoes.push_back("Voltar");
    resopcoes.push_back("Voltar ao Menu Principal");
    for (int i = 0; tfuncionarios.size() > i; i++) {
        topcoes.push_back("Ver Info Funcionarios " + tfuncionarios[i]);
    }
    topcoes.push_back("Voltar");
    topcoes.push_back("Voltar ao Menu Principal");
    if (segresp == 3) return Principal();
    if (segresp == 2) return VerInfo();
    if (segresp == 0) {
        switch (resposta) {
            case 0:
                PrintList(H.GetClientes());
                return VerInfo();
            case 1:
                tresposta = ProcessarInputInt(topcoes, sectit);
                switch (tresposta) {
                    case 0:
                        PrintList(H.GetFuncionarios());
                        break;
                    case 1:
                        PrintList(H.GetFuncionariosRececao());
                        break;
                    case 2:
                        PrintList(H.GetFuncionariosResponsaveis());
                        break;
                    case 3:
                        PrintList(H.GetFuncionariosLimpeza());
                        break;
                    case 4:
                        PrintList(H.GetFuncionariosGestores());
                        break;
                    case 5:
                        return VerInfo();
                    case 6:
                        return Principal();
                    default:
                        break;
                }
                return VerInfo();
            case 2:
                PrintList(H.GetProdutos());
                return VerInfo();
            case 3:
                PrintList(H.GetQuartos());
                return VerInfo();
            case 4:
                PrintList(H.GetEstadias());
                PrintList(H.GetReservasAtuais());
                PrintList(H.GetReservas());
                return VerInfo();
            case 5:
                PrintList(H.GetServicos());
                return VerInfo();
            case 6:
                PrintBST(H.GetFrota());
                return VerInfo();
            case 7:
                PrintPQ(H.GetCompras());
                return VerInfo();
            default:
                return VerInfo();
        }
    }
    int procurainput;
    if (segresp == 1) {
        switch (resposta) {
            case 0:
                procurainput = ProcessarInputProcura(sectit, H.GetClientes());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetClientes()).Info();
                break;
            case 1:
                tresposta = ProcessarInputInt(topcoes, sectit);
                switch (tresposta) {
                    case 0:
                        procurainput = ProcessarInputProcura(sectit, H.GetFuncionarios());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetFuncionarios()).Info();
                        break;
                    case 1:
                        procurainput = ProcessarInputProcura(sectit, H.GetFuncionariosRececao());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetFuncionariosRececao()).Info();
                        break;
                    case 2:
                        procurainput = ProcessarInputProcura(sectit, H.GetFuncionariosResponsaveis());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetFuncionariosResponsaveis()).Info();
                        break;
                    case 3:
                        procurainput = ProcessarInputProcura(sectit, H.GetFuncionariosLimpeza());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetFuncionariosLimpeza()).Info();
                        break;
                    case 4:
                        procurainput = ProcessarInputProcura(sectit, H.GetFuncionariosGestores());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetFuncionariosGestores()).Info();
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                procurainput = ProcessarInputProcura(sectit, H.GetProdutos());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetProdutos()).Info();
                break;
            case 3:
                procurainput = ProcessarInputProcura(sectit, H.GetQuartos());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetQuartos()).Info();
                break;
            case 4:
                tresposta = ProcessarInputInt(resopcoes, sectit);
                switch (tresposta) {
                    case 0:
                        procurainput = ProcessarInputProcura(sectit, H.GetEstadias());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetEstadias()).Info();
                        break;
                    case 1:
                        procurainput = ProcessarInputProcura(sectit, H.GetReservasAtuais());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetReservasAtuais()).Info();
                        break;
                    case 2:
                        procurainput = ProcessarInputProcura(sectit, H.GetReservas());
                        if (procurainput == -1) return VerInfo();
                        else EfetuarProcura(procurainput, H.GetReservas()).Info();
                        break;
                    case 3:
                        return VerInfo();
                    case 4:
                        return Principal();
                    default:
                        break;
                }
            case 5:
                procurainput = ProcessarInputProcura(sectit, H.GetServicos());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetServicos()).Info();
                break;
            case 6:
                procurainput = ProcessarInputProcura(sectit, H.GetFrota());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetFrota()).Info();
                break;
            case 7:
                procurainput = ProcessarInputProcura(sectit, H.GetCompras());
                if (procurainput == -1) return VerInfo();
                else EfetuarProcura(procurainput, H.GetCompras()).Info();
                break;
            default:
                break;
        }
    }
    return VerInfo();
}

void Menu::Adicionar() {
    unsigned resposta;
    string titulo = "Adicionar";
    vector <string> opcoes = {"Cliente", "Produto", "Quarto", "Veiculo"};
    for(int i = 0; opcoes.size() > i; i++){
        opcoes[i] = "Adicionar " + opcoes[i];
    }
    opcoes.push_back("Voltar");
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetClientes());
        int nif = InputRestrito<int>("Insira o NIF do Cliente: ");
        string nome = InputNome("Insira o nome do Cliente: ");
        bool usual = InputRestrito<bool>("Insira [1] se o Cliente for usual ou [0] caso nao o seja: ");
        while(!H.AddCliente(Cliente(nome, nif, usual))){
            PrintList(H.GetClientes());
            cout << "O Cliente que inseriu ja existe!" << endl;
            InputRestrito<int>("Insira o NIF do Cliente");
            InputNome("Insira o nome do Cliente");
            InputRestrito<bool>("Insira [1] se o Cliente for usual ou [0] caso nao o seja: ");
        }
        EfetuarProcura(nif, H.GetClientes()).Info();
        return Adicionar();
    }
    if(resposta == 1){
        PrintList(H.GetProdutos());
        int numero = InputRestrito<int>("Insira o Numero do Produto: ");
        string nome = InputNome("Insira o nome do Produto: ");
        tipo_produto tp = InputTProd("Insira o Tipo do Produto: ");
        nota_avaliacao nav = InputNota("Insira a Qualidade do Produto: ");
        float preco = InputRestrito<float>("Insira o Preco do Produto: ");
        int stock = InputRestrito<int>("Insira o Stock do Produto no Hotel: ");
        string fornecedor = InputNome("Insira o nome do Fornecedor do Produto: ");
        while(!H.AddProduto(Produto(nome, numero, tp, nav, preco, stock))){
            PrintList(H.GetProdutos());
            cout << "O Produto que inseriu ja existe!" << endl;
            numero = InputRestrito<int>("Insira o Numero do Produto: ");
            nome = InputNome("Insira o nome do Produto: ");
            tp = InputTProd("Insira o Tipo do Produto: ");
            nav = InputNota("Insira a Qualidade do Produto: ");
            preco = InputRestrito<float>("Insira o Preco do Produto: ");
        }
        EfetuarProcura(numero, H.GetProdutos()).Info();
        return Adicionar();
    }
    if(resposta == 2){
        PrintList(H.GetQuartos());
        int numero = InputRestrito<int>("Insira o Numero do Quarto: ");
        tipo_quarto tq = InputTQuarto("Insira o Tipo de Quarto: ");
        int piso = InputRestrito<int>("Insira o Piso do Quarto: ");
        int capacidade = InputRestrito<int>("Insira a Capacidade do Quarto: ");
        float preco = InputRestrito<float>("Insira o Preco do Quarto: ");
        while(!H.AddQuarto(Quarto(tq, piso, numero, capacidade, preco))){
            PrintList(H.GetQuartos());
            cout << "O Quarto que inseriu ja existe!" << endl;
            numero = InputRestrito<int>("Insira o Numero do Quarto: ");
            tq = InputTQuarto("Insira o Tipo de Quarto: ");
            piso = InputRestrito<int>("Insira o Piso do Quarto: ");
            capacidade = InputRestrito<int>("Insira a Capacidade do Quarto: ");
            preco = InputRestrito<float>("Insira o Preco do Quarto: ");
        }
        EfetuarProcura(numero, H.GetQuartos()).Info();
        return Adicionar();
    }
    if(resposta == 3){
        PrintBST(H.GetFrota());
        matricula matricula = InputMatricula("Matricula do Vaiculo: ");
        double kms = InputRestrito<double>("Insira os Kilometros Percorridos: ");
        string marca = InputNome("Insira a Marca do Veiculo: ");
        int lugares = InputRestrito<int>("Insira o numero de Lugares do Veiculo: ");
        while(!H.addVeiculo(matricula, kms, lugares, marca)){
            PrintBST(H.GetFrota());
            cout << "O Veiculo que inseriu ja existe ou nao e valido!" << endl;
            matricula = InputMatricula("Matricula do Vaiculo: ");
            kms = InputRestrito<double>("Insira os Kilometros Percorridos: ");
            marca = InputNome("Insira a Marca do Veiculo: ");
            lugares = InputRestrito<int>("Insira o numero de Lugares do Veiculo: ");
        }
        EfetuarProcura(matricula.id, H.GetFrota()).Info();
        return Adicionar();

    }
    if(resposta == 4) return Principal();
    return Adicionar();
}


void Menu::Apagar() {
    unsigned resposta;
    int id;
    string titulo = "Apagar", mensagem = "Insira o ID do membro que pretende apagar: ";
    vector <string> opcoes = {"Cliente", "Produto", "Quarto"};
    for(int i = 0; opcoes.size() > i; i++){
        opcoes[i] = "Apagar " + opcoes[i];
    }
    opcoes.push_back("Voltar");
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetClientes());
        id = InputRestrito<int>(mensagem);
        H.ApagarCliente(id);
        PrintList(H.GetClientes());
        return Apagar();
    }
    if(resposta == 1){
        PrintList(H.GetProdutos());
        id = InputRestrito<int>(mensagem);
        H.ApagarProduto(id);
        PrintList(H.GetProdutos());
        return Apagar();
    }
    if(resposta == 2){
        PrintList(H.GetQuartos());
        id = InputRestrito<int>(mensagem);
        H.ApagarQuarto(id);
        PrintList(H.GetQuartos());
        return Apagar();
    }
    if(resposta == 3) return Principal();
    return Apagar();
}

void Menu::MReserva() {
    string titulo = "Reservar / Cancelar Reserva";
    unsigned resposta;
    vector <string> opcoes = {"Reservar", "Cancelar Reserva", "Voltar"};
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetClientes());
        int nifcliente  = ProcessarInputProcura("Reservar", H.GetClientes());
        if(nifcliente < 0) return MReserva();
        else{
            EfetuarProcura(nifcliente, H.GetClientes()).Info();
            int idnumero = InputRestrito<int>("Insira o ID da Reserva: ");
            data datai = InputData("Insira a Data de Inicio da Reserva: ");
            data dataf = InputData("Insira a Data de Fim da Reserva: ");
            int lugares = InputRestrito<int>("Insira o Numero de Lugares Esperados: ");
            PrintList(H.GetQuartos());
            vector <int> nquartos = ProcessarIntIndef("o numero do quarto a reservar", "Numeros de Quartos a Reservar", 1, H.GetQuartos());
            while(!H.Reservar(nifcliente, idnumero, datai, dataf, lugares, nquartos)){
                cout << "Impossivel Realizar a Reserva pretendida" << endl;
                EfetuarProcura(nifcliente, H.GetClientes()).Info();
                idnumero = InputRestrito<int>("Insira o ID da Reserva: ");
                datai = InputData("Insira a Data de Inicio da Reserva: ");
                dataf = InputData("Insira a Data de Fim da Reserva: ");
                lugares = InputRestrito<int>("Insira o Número de Lugares Esperados: ");
                PrintList(H.GetQuartos());
                nquartos = ProcessarIntIndef("o numero do quarto a reservar", "Numeros de Quartos a Reservar", 1, H.GetQuartos());
            }
            PrintList(H.GetReservas());
            return MReserva();
        }
    }
    if (resposta == 1){
        PrintList(H.GetClientes());
        int nifcliente  = ProcessarInputProcura("Cancelar Reserva", H.GetClientes());
        if(nifcliente < 0) return MReserva();
        else{
            EfetuarProcura(nifcliente, H.GetClientes()).Info();
            int idnumero = InputRestrito<int>("Insira o ID da Reserva: ");
            H.CancelarReserva(nifcliente, idnumero);
            PrintList(H.GetReservas());
            return MReserva();
        }
    }
    if (resposta == 2) return Principal();
    return MReserva();
}

void Menu::MGerirFunc() {
    string titulo = "Gerir Funcionarios";
    vector<string> opcoes = {"Contratar", "Selecionar Funcionario", "Voltar"};
    unsigned resposta;
    resposta = ProcessarInputInt(opcoes, titulo);
    if (resposta == 0) {
        int nif = InputRestrito<int>("Insira o NIF do Novo Funcionario: ");
        string nome = InputNome("Insira o nome do Novo Funcionario: ");
        bool escolhercargo = InputRestrito<bool>(
                "Insira [1] se quiser esolher um cargo especifico ou [0] se quiser que este seja escolhido automaticamente de acordo com as necessidades atuais do Hotel: ");
        if (escolhercargo) {
            tipo_cargo cargo = InputCargo("Escolha o cargo que o novo funcionario irá exercer: ");
            H.Contratar(nome, nif, cargo);
        }
        else H.Contratar(nome, nif);
        bool escolhersalario = InputRestrito<bool>(
                "Deseja atribuir um salario diferente ao Novo Funcionario [1 = sim | 0 = não]: ");
        if (escolhersalario) {
            float salario = InputRestrito<float>("Insere o salario a ser atribuido ao Novo Funcionario: ");
            H.SetSalario(nif, salario);
        }
        PrintList(H.GetFuncionarios());
        return MGerirFunc();
    }
    if (resposta == 1){
        int idfunc = ProcessarInputProcura("Selecionar Funcionario", H.GetFuncionarios());
        if(idfunc == -1) return MGerirFunc();
        vector<string> topcoes = {"Despedir", "Definir Salario", "Aumentar um Ano de Servico", "Voltar", "Voltar ao Menu Principal"};
        unsigned tresposta = ProcessarInputInt(topcoes, EfetuarProcura(idfunc, H.GetFuncionarios()).nome);
        if(tresposta == 3) return MGerirFunc();
        if(tresposta > 3) return Principal();
        if(tresposta == 0) H.Despedir(idfunc);
        if(tresposta == 1){
            float salario = InputRestrito<float>("Insere o salario a ser atribuido ao Funcionario Selecionado: ");
            H.SetSalario(idfunc, salario);
        }
        if(tresposta == 2) H.AddAnoServico(idfunc);
        PrintList(H.GetFuncionarios());
        return MGerirFunc();
    }
    if (resposta == 2) return Principal();
    return MGerirFunc();
}

void Menu::Checks() {
    string titulo = "Check-In / Check-Out";
    vector<string> opcoes = {"Check-In", "Check-Out", "Voltar"};
    unsigned resposta = ProcessarInputInt(opcoes, titulo);
    if (resposta == 0) {
        PrintList(H.GetClientes());
        int idc = ProcessarInputProcura("Check-In", H.GetClientes());
        if (idc == -1) return Checks();
        else H.CheckIn(idc);
        PrintList(H.GetClientes());
        PrintList(H.GetReservas());
        return Checks();
    }
    if (resposta == 1) {
        if (H.GetClientesnoHotel().empty()) {
            cout << endl << "Nao ha clientes no hotel, por isso nao e possivel fazer nenhum Check-Out!" << endl;
        }
        else {
            list<Cliente *> lc = H.GetClientesnoHotel();
            PrintPointerListCliente(lc);
            bool valida = false;
            int nifcliente;
            cout << endl << "Insere o NIF do cliente que pretende fazer Check-Out: ";
            cin >> nifcliente;
            if (!cin.fail()) {
                for (auto it = lc.begin(); it != lc.end(); it++) {
                    if ((*it)->nif == nifcliente) {
                        valida = true;
                        break;
                    }
                }
            }
            while (cin.fail() || !valida) {
                valida = false;
                PrintPointerListCliente(lc);
                cout << endl << "Input invalido. Tem de ser um NIF de um cliente que esteja no Hotel.";
                cout << endl << "Insere o NIF do cliente que pretende fazer Check-Out: ";
                cin >> nifcliente;
                if (!cin.fail()) {
                    for (auto it = lc.begin(); it != lc.end(); it++) {
                        if ((*it)->nif == nifcliente) {
                            valida = true;
                            break;
                        }
                    }
                }
            }
            H.CheckOut(nifcliente);
            PrintList(H.GetClientes());
            PrintList(H.GetReservas());
        }
        return Checks();
    }
    if (resposta == 2) return Principal();
    return Checks();
}

void Menu::FinancasSelect() {
    string titulo = "Financas";
    ImprimeTit(titulo);
    int mes, ano;
    cout << endl << "Insira o mes que pretende analisar: ";
    cin >> mes;
    while (cin.fail() || mes < 1 || mes > 12){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Insira o mes que pretende analisar: ";
        cin >> mes;
    }
    cout << endl << "Insira o ano que pretende analisar: ";
    cin >> ano;
    while (cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Insira o ano que pretende analisar: ";
        cin >> ano;
    }
    return Financas(mes, ano);
}

void Menu::Financas(int mes, int ano) {
    string titulo = "Financas " + to_string(mes) + "-" + to_string(ano);
    vector<string> opcoes = {"Custos", "Rendimentos", "Balanco", "Voltar", "Voltar ao Menu Principal"};
    unsigned resposta = ProcessarInputInt(opcoes, titulo);
    if (resposta == 0) {
        float impostos = InputRestrito<float>("Insira o custo mensal dos impostos: ");
        float despesas = InputRestrito<float>("Insira o total gasto em Despesas Fixas (agua, eletricidade...) pelo Hotel mensalmente: ");
        cout << endl << "FOLHA SALARIAL" << endl;
        for (auto it = H.GetFuncionarios().begin(); it != H.GetFuncionarios().end(); it++) {
            cout << endl << (*it).nome << " ---> Salario: " << (*it).salario;
        }
        cout << endl << endl << "STOCK" << endl;
        for (auto it = H.GetProdutos().begin(); it != H.GetProdutos().end(); it++) {
            cout << endl << (*it).nome << " ---> Preco: " << (*it).preco;
        }
        cout << endl << endl << "CUSTOS NO MES " << mes << "-" << ano << " :  " << H.CustosTotais(impostos, despesas);
        return Financas(mes, ano);
    }
    if (resposta == 1) {
        list <Servico *> sf = H.Servicos_Fin(mes, ano);
        list <Reserva *> rf = H.Reservas_Fin(mes, ano);
        if(!sf.empty()){
            cout << endl << "LUCRO SERVICOS PRESTADOS ESTE MES" << endl;
            for (auto it = sf.begin(); it != sf.end(); it++) {
                cout << endl << (*it)->nome << " ---> Lucro para o Hotel: " << (*it)->lucro;
            }
        }
        if(!rf.empty()){
            cout << endl << endl << "RESERVAS FEITAS (parcial ou totalmente) PARA ESTE MES" << endl;
            for (auto it = rf.begin(); it != rf.end(); it++) {
                cout << endl << (*it)->idnumero << "---> Preco/dia: " << (*it)->preco;
            }
        }
        cout << endl << endl << "RENDIMENTOS NO MES " << mes << "-" << ano << " :  " << H.RendimentosTotais(mes, ano);
        return Financas(mes, ano);
    }
    if (resposta == 2){
        float impostos = InputRestrito<float>("Insira o custo mensal dos impostos: ");
        float despesas = InputRestrito<float>("Insira o total gasto em Despesas Fixas (agua, eletricidade...) pelo Hotel mensalmente: ");
        cout << endl << "CUSTOS NO MES " << mes << "-" << ano << " :  " << H.CustosTotais(impostos, despesas);
        cout << endl << "RENDIMENTOS NO MES " << mes << "-" << ano << " :  " << H.RendimentosTotais(mes, ano);
        cout << endl << endl << "BALANCO FINANCEIRO NO MES " << mes << "-" << ano << " :  " << H.BalancoFin(mes, ano, impostos, despesas);
        return Financas(mes, ano);
    }
    if(resposta == 3) return FinancasSelect();
    if(resposta > 3) return Principal();
    return Financas(mes, ano);
}

void Menu::Outros() {
    string titulo = "Outros";
    vector<string> opcoes = {"Prestar Servico", "Promocoes", "Mudar Rating a Compra", "Escolher Produto", "Escolher Compra", "Fazer Pesquisas", "Voltar"};
    unsigned resposta = ProcessarInputInt(opcoes, titulo);
    if (resposta == 0){
        int nifcliente = ProcessarInputProcura("Prestar Servico", H.GetClientes());
        if (nifcliente == -1) return Outros();
        bool done = false;
        float margemlucro;
        string nome = InputNome("Insira o nome do Servico: ");
        int sid = InputRestrito<int>("Insira o numero do Servico: ");
        data dr = InputData("Insira a data de realizacao do Servico: ");
        float taxa = InputRestrito<float>("Insira a taxa aplicada ao Servico: ");
        PrintList(H.GetFuncionarios());
        vector<int> fnum = ProcessarIntIndef("NIF de Funcionario Ocupado", "NIFS de Funcionarios Ocupados", 0, H.GetFuncionarios());
        PrintList(H.GetProdutos());
        vector<int> pnum = ProcessarIntIndef("Numero do Produto Consumido", "Numeros dos Produtos Consumidos", 0, H.GetProdutos());
        if (!pnum.empty()) margemlucro = InputRestrito<float>("Insira a margem de lucro do Hotel sobre os Produtos (em %): ");
        if (!fnum.empty()){
            if(!pnum.empty()) done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, fnum, pnum, margemlucro);
            else done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, fnum);
        }
        else{
            if(!pnum.empty()) done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, pnum, margemlucro);
            else done = H.PrestarServico(nifcliente, nome, sid, dr, taxa);
        }
        while(!done){
            cout << endl << "Servico Impossivel de prestar, porque ja existe!" << endl;
            fnum.clear();
            pnum.clear();
            nome = InputNome("Insira o nome do Servico: ");
            sid = InputRestrito<int>("Insira o numero do Servico: ");
            dr = InputData("Insira a data de realizacao do Servico: ");
            taxa = InputRestrito<float>("Insira a taxa aplicada ao Servico: ");
            PrintList(H.GetFuncionarios());
            fnum = ProcessarIntIndef("NIF de Funcionario Ocupado", "NIFS de Funcionarios Ocupados", 0, H.GetFuncionarios());
            PrintList(H.GetProdutos());
            pnum = ProcessarIntIndef("Numero do Produto Consumido", "Numeros dos Produtos Consumidos", 0, H.GetProdutos());
            if (!pnum.empty()) margemlucro = InputRestrito<float>("Insira a margem de lucro do Hotel sobre os Produtos (em %): ");
            if (!fnum.empty()){
                if(!pnum.empty()) done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, fnum, pnum, margemlucro);
                else done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, fnum);
            }
            else{
                if(!pnum.empty()) done = H.PrestarServico(nifcliente, nome, sid, dr, taxa, pnum, margemlucro);
                else done = H.PrestarServico(nifcliente, nome, sid, dr, taxa);
            }
        }
        PrintList(H.GetClientes());
        PrintList(H.GetServicos());
        return Outros();
    }
    if (resposta == 1){
        if (H.GetFuncionariosGestores().empty()){
            cout << endl << "Nao ha Funcionários Gestores para realizarem a Promocao!" << endl;
            return Outros();
        }
        if (H.GetQuartos().empty()){
            cout << endl << "Nao ha Quartos a incluir na Promocao!" << endl;
            return Outros();
        }
        int fid = ProcessarInputProcura("Promocao", H.GetFuncionariosGestores());
        if (fid == -1) return Outros();
        vector<int> nquartos = ProcessarIntIndef("Numero do Quarto a incluir na Promocao", "Numeros dos Quartos a incluir na Promocao", 1, H.GetQuartos());
        H.Promocoes(EfetuarProcura(fid, H.GetFuncionariosGestores()), nquartos);
        PrintList(H.GetQuartos());
        return Outros();
    }
    if (resposta == 2){
        if (H.GetFuncionariosGestores().empty()){
            cout << endl << "Nao ha Funcionários Gestores para mudarem Ratings!" << endl;
            return Outros();
        }
        if (H.GetCompras().empty()){
            cout << endl << "Nao ha Compras com Rating a ser mudado!" << endl;
            return Outros();
        }
        int fid = ProcessarInputProcura("Mudar Rating", H.GetFuncionariosGestores());
        if (fid == -1) return Outros();
        PrintPQ(H.GetCompras());
        int ncomp = ProcessarInputProcura("Numero da Compra a qual se vai mudar o Rating", H.GetCompras());
        nota_avaliacao new_rating = InputNota("Insira o novo Rating: ");
        H.MudarRating(ncomp, new_rating);
        PrintPQ(H.GetCompras());
        return Outros();
    }
    if (resposta == 3){
        if (H.GetFuncionariosGestores().empty()){
            cout << endl << "Nao ha Funcionarios Gestores para escolherem o Produto!" << endl;
            return Outros();
        }
        if (H.GetProdutos().empty()){
            cout << endl << "Nao ha Produtos para escolher!" << endl;
            return Outros();
        }
        int fid = ProcessarInputProcura("Escolha do Melhor Produto", H.GetFuncionariosGestores());
        if (fid == -1) return Outros();
        PrintList(H.GetProdutos());
        vector<int> nprod = ProcessarIntIndef("Numero do Produto a incluir na lista", "Numeros dos Produtos a incluir na lista", 1, H.GetProdutos());
        cout << endl << "Produto Escolhido: " << endl;
        (H.EscolherProduto(EfetuarProcura(fid, H.GetFuncionariosGestores()), nprod)).Info();
        return Outros();
    }
    if (resposta == 4){
        if (H.GetFuncionariosGestores().empty()){
            cout << endl << "Nao ha Funcionarios Gestores para escolherem as Compras!" << endl;
            return Outros();
        }
        if (H.GetCompras().empty()){
            cout << endl << "Nao ha Compras para escolher!" << endl;
            return Outros();
        }
        int fid = ProcessarInputProcura("Escolha da Melhor Compra", H.GetFuncionariosGestores());
        if (fid == -1) return Outros();
        PrintPQ(H.GetCompras());
        int stock_min = InputRestrito<int>("Escolha o Stock Minimo: ");
        int stock_max = InputRestrito<int>("Escolha o Stock Maximo: ");
        try{
            cout << endl << "Compra Escolhida: " << endl;
            EfetuarProcura(fid, H.GetFuncionariosGestores()).Escolher_Compra(H.GetComprasStocks(stock_min, stock_max)).Info();
        }
        catch (InputInvalido iv){
            cout << endl << "O limite de stocks e Invalido!" << endl;
        }
        catch (MembroFalta mf){
            cout << endl << "Membro em Falta do tipo " << mf.tipo << endl;
        }
        return Outros();
    }
    if (resposta == 5){
        vector<string> topcoes = {"Quartos", "Funcionarios", "Reservas", "Clientes", "Voltar", "Voltar ao Menu Principal"};
        unsigned membro_ordenar = ProcessarInputInt(topcoes, "Pesquisas");
        unsigned criterio;
        if (membro_ordenar == 4) return Outros();
        if (membro_ordenar >= 5) return Principal();
        if (membro_ordenar == 0){
            vector<string> q_opcoes = {"Numero Crescente", "Numero Decrescente", "Preco Crescente", "Preco Decrescente", "Voltar", "Voltar ao Menu Principal"};
            criterio = ProcessarInputInt(q_opcoes, "Pesquisa Quartos");
            if (criterio == 4) return Outros();
            if (criterio > 4) return Principal();
            list <Quarto> lq = H.GetQuartos();
            if (criterio == 0){
                lq.sort(Quarto::Numcomp_Cr);
            }
            if (criterio == 1){
                lq.sort(Quarto::Numcomp_Decr);
            }
            if (criterio == 2){
                lq.sort(Quarto::Preco_Cr);
            }
            if (criterio == 3){
                lq.sort(Quarto::Preco_Decr);
            }
            PrintList(lq);
            return Outros();
        }
        if (membro_ordenar == 1){
            vector<string> f_opcoes = {"Cargo", "Salario Crescente", "Salario Decrescente", "Voltar", "Voltar ao Menu Principal"};
            criterio = ProcessarInputInt(f_opcoes, "Pesquisa Funcionarios");
            if (criterio == 3) return Outros();
            if (criterio > 3) return Principal();
            list <Funcionario> lf = H.GetFuncionarios();
            if (criterio == 0){
                lf.sort(Funcionario::Cargocomp);
            }
            if (criterio == 1){
                lf.sort(Funcionario::Salariocomp_Cr);
            }
            if (criterio == 2){
                lf.sort(Funcionario::Salariocomp_Decr);
            }
            PrintList(lf);
            return Outros();
        }
        if (membro_ordenar == 2){
            vector<string> r_opcoes = {"Primeira Vez", "Preco Crescente", "Preco Decrescente", "Duracao Crescente", "Duracao Decrescente", "Data Inicial Crescente", "Data Inicial Decrescente", "Data Final Crescente", "Data Final Decrescente", "Voltar", "Voltar ao Menu Principal"};
            criterio = ProcessarInputInt(r_opcoes, "Pesquisa Reservas");
            if (criterio == 9) return Outros();
            if (criterio > 9) return Principal();
            list <Reserva> lr = H.GetReservas();
            if (criterio == 0){
                lr.sort(Reserva::PrimeiraReserva);
            }
            if (criterio == 1){
                lr.sort(Reserva::Precocomp_Cr);
            }
            if (criterio == 2){
                lr.sort(Reserva::Precocomp_Decr);
            }
            if (criterio == 3){
                lr.sort(Reserva::Duracaocomp_Cr);
            }
            if (criterio == 4){
                lr.sort(Reserva::Duracaocomp_Decr);
            }
            if (criterio == 5){
                lr.sort(Reserva::DataIcomp_Cr);
            }
            if (criterio == 6){
                lr.sort(Reserva::DataIcomp_Decr);
            }
            if (criterio == 7){
                lr.sort(Reserva::DataFcomp_Cr);
            }
            if (criterio == 8){
                lr.sort(Reserva::DataFcomp_Decr);
            }
            PrintList(lr);
            return Outros();
        }
        if (membro_ordenar == 3){
            char inicial = InputLetra("Insira a Inicial que pretende Pesquisar: ");
            PrintPointerListCliente(H.GetClientesInicial(inicial, false));
        }
    }
    if (resposta > 5) return Principal();
    return Outros();
}

void Menu::Exportar() {
    string localizacao, titulo = "Exportar Hotel";
    ImprimeTit(titulo);
    cout << endl << "Introduza a Localizacao do Ficheiro para onde quer Exportar o Hotel: ";
    cin >> localizacao;
    H.EscreverHotel(localizacao);
    return Principal();
}

void Menu::MViagem() {
    string titulo = "Viajar";
    unsigned resposta;
    vector <string> opcoes = {"Viajar", "Voltar"};
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetViagens());
        PrintList(H.GetClientes());
        int nifcliente  = ProcessarInputProcura("Viajar", H.GetClientesHabituais());
        if(nifcliente < 0) return MReserva();
        else{
            Cliente cliente = EfetuarProcura(nifcliente, H.GetClientesHabituais());
            cliente.Info();
            int idnumero = InputRestrito<int>("Insira o ID da sua Viagem: ");
            string ponto_partida = InputNome("Insira o nome do Ponto de Partida: ");
            string chegada = InputNome("Insira o nome do Local de Chegada: ");
            double distancia = InputRestrito<double>("Insira a distancia da sua Viagem: ");
            if(!H.Viajar(cliente, distancia, ponto_partida, chegada, idnumero)){
                cout << "Impossivel Realizar a Viagem pretendida" << endl;
            }
            PrintList(H.GetViagens());
            return MViagem();
        }
    }
    else return Principal();
    return MViagem();
}

void Menu::MCompra() {
    string titulo = "Efetuar Compra";
    unsigned resposta;
    vector <string> opcoes = {"Comprar Produto em Stock", "Comprar Novo Produto", "Voltar"};
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetProdutos());
        int idnumero = InputRestrito<int>("Insira o ID da sua Compra: ");
        int nprod = InputRestrito<int>("Insira o ID do Produto que pretende comprar: ");
        string fornecedor = InputNome("Insira o nome do Fornecedor: ");
        int quantidade = InputRestrito<int>("Insira a Quantidade que pretende comprar: ");
        while(!H.FazerCompra(idnumero, nprod, fornecedor, quantidade)){
            PrintList(H.GetProdutos());
            cout << "Impossivel Realizar a Compra pretendida" << endl;
            idnumero = InputRestrito<int>("Insira o ID da sua Compra: ");
            nprod = InputRestrito<int>("Insira o ID do Produto que pretende comprar: ");
            fornecedor = InputNome("Insira o nome do Fornecedor: ");
            quantidade = InputRestrito<int>("Insira a Quantidade que pretende comprar: ");
        }
        PrintList(H.GetProdutos());
        PrintPQ(H.GetCompras());
        return MCompra();
    }
    if(resposta == 1){
        PrintList(H.GetProdutos());
        int idnumero = InputRestrito<int>("Insira o ID da sua Compra: ");
        int nprod = InputRestrito<int>("Insira o ID do Novo Produto que pretende comprar: ");
        string nome_produto = InputNome("Insira o nome do Novo Produto: ");
        tipo_produto tprod = InputTProd("Insira o tipo do Novo Produto: ");
        nota_avaliacao nota_prod = InputNota("Insira a avaliacao do Novo Produto: ");
        float preco = InputRestrito<float>("Insira o preco unitario do Novo Produto: ");
        int stock = InputRestrito<int>("Insira o stock do Novo Produto: ");
        string fornecedor = InputNome("Insira o nome do Fornecedor: ");
        int quantidade = InputRestrito<int>("Insira a Quantidade que pretende comprar: ");
        while(!H.FazerCompra_NovoProduto(idnumero, nome_produto, nprod, tprod, nota_prod, preco, stock, fornecedor, quantidade)){
            PrintList(H.GetProdutos());
            cout << "Impossivel Realizar a Compra pretendida" << endl;
            idnumero = InputRestrito<int>("Insira o ID da sua Compra: ");
            nome_produto = InputNome("Insira o nome do Novo Produto: ");
            nprod = InputRestrito<int>("Insira o ID do Novo Produto que pretende comprar: ");
            tprod = InputTProd("Insira o tipo do Novo Produto: ");
            nota_prod = InputNota("Insira a avaliacao do Novo Produto: ");
            preco = InputRestrito<float>("Insira o preco unitario do Novo Produto: ");
            stock = InputRestrito<int>("Insira o stock do Novo Produto: ");
            fornecedor = InputNome("Insira o nome do Fornecedor: ");
            quantidade = InputRestrito<int>("Insira a Quantidade que pretende comprar: ");
        }
        PrintList(H.GetProdutos());
        PrintPQ(H.GetCompras());
        return MCompra();
    }
    else return Principal();
    return MCompra();
}

void Menu::PromocaoIniciais(){
    string titulo = "Promocao Iniciais";
    unsigned resposta;
    vector <string> opcoes = {"Efetuar Promocao", "Voltar"};
    resposta = ProcessarInputInt(opcoes, titulo);
    if(resposta == 0){
        PrintList(H.GetClientesHabituais());
        char p_inicial = InputLetra("Insira a primeira Inicial a receber a promocao: ");
        char s_inicial = InputLetra("Insira a segunda Inicial a receber a promocao: ");
        H.PromoIniciais(p_inicial, s_inicial);
        PrintList(H.GetClientesHabituais());
        return PromocaoIniciais();
    }
    else return Principal();
    return PromocaoIniciais();
}



void Menu::Principal() {
    unsigned resposta;
    string titulo = "Bem-vindo ao " + H.nome;
    vector <string> opcoes = {"Importar...", "Ver Informacao...", "Adicionar Membro...", "Apagar Membro...", "Reservar / Cancelar Reserva", "Gerir Funcionarios", "Check-in / Check-out", "Viajar", "Efetuar Compra", "Promocao Iniciais", "Financas", "Outros", "Exportar", "Sair"};
    resposta = ProcessarInputInt(opcoes, titulo);
    switch (resposta){
        case 0:
            return Importar();
        case 1:
            return VerInfo();
        case 2:
            return Adicionar();
        case 3:
            return Apagar();
        case 4:
            return MReserva();
        case 5:
            return MGerirFunc();
        case 6:
            return Checks();
        case 7:
            return MViagem();
        case 8:
            return MCompra();
        case 9:
            return PromocaoIniciais();
        case 10:
            return FinancasSelect();
        case 11:
            return Outros();
        case 12:
            return Exportar();
        case 13:
            cout << endl << "THE END" << endl;
            return;
        default:
            return Principal();
    }
    return Principal();
}
