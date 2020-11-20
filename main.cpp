#include "Hotel.h"

using namespace std;

int main() {
    Hotel H("da Marateca");


    //Quarto Q205(suite, 2, 205, 3, 55.67);
    //Quarto Q100(sem_vista, 1, 100, 2, 34.21);
    //Quarto Q317(com_vista, 3, 317, 4, 44);


    //Reserva R1({.dia = 20, .mes = 5, .ano= 2019}, {.dia = 25, .mes = 6, .ano= 2019}, 4, {Q100}, false, true);
    //Reserva R2({.dia = 20, .mes = 5, .ano= 2019}, {.dia = 1, .mes = 7, .ano= 2021}, 8, {Q205, Q100});
    //Reserva R3({.dia = 20, .mes = 5, .ano= 2019}, {.dia = 1, .mes = 7, .ano= 2019}, 8, {Q100, Q205, Q317});

    /*
    F_Rececao Alfredo("Alfredo", 123456798, 5, 832.78);
    F_Rececao Maria("Maria", 123256798, 3, 750.78);
    F_Rececao Antonio("António", 182886798, 8, 900);
    F_Responsavel Manuel("Manuel", 123555598, 2, 1005.12);
    F_Responsavel Tito("Tito", 123555598, 2, 1005.12, vector <int> {1, 3});
    F_Responsavel Carlota("Carlota Madeira", 696969696, 1, 500.01, vector <int> {2});
    F_Limpeza Fred("Fred", 420420420, 2, 100000.99, noite);
    F_Limpeza Duarte("Duarte", 420420420, 2, 100000.99, dia);
    F_Limpeza Tina("Tina", 420441990, 10, 100, noite);
    F_Gestor Ze("Zé", 999999999, 20, 999999.99, excelente);
    F_Gestor Marta("Marta", 999999779, 2, 999.99);
    F_Gestor Erica("Érica", 991234999, 12, 5000.50, razoavel);

    data d1 = {.dia = 20, .mes = 5, .ano= 2019};
    data d2 = {.dia = 21, .mes = 5, .ano= 2019};
    data d3 = {.dia = 2, .mes = 1, .ano= 2020};
    data d4 = {.dia = 21, .mes = 6, .ano= 2019};
    data d5 = {.dia = 21, .mes = 6, .ano= 2019};
    data d6 = {.dia = 21, .mes = 6, .ano= 2020};
    */

    /*
    cout << endl << "d2-d1 = 1  " << d2-d1 << endl;
    if(d2>d1) cout << endl << "d2>d1 = true" << endl;
    else cout << endl << "Wrong" << endl;
    cout << endl << "d6-d5 = 365  " << d6-d5 << endl;
    if(d4<d3) cout << endl << "d4<d3 = true" << endl;
    else cout << endl << "Wrong" << endl;
    if(d4==d5) cout << endl << "d4==d5 = true" << endl;
    else cout << endl << "Wrong" << endl;
    cout << endl << "d6-d1 = 396  " << d6-d1 << endl;
    cout << endl << "d1-d6 = -396  " << d1-d6 << endl;
    */

    /*
    H.AddReserva(R1);
    H.AddReserva(R2);
    H.AddReserva(R3);
     */


    /*
    Quarto Q207(suite, 2, 207, 3, 12);
    Quarto Q208(suite, 2, 208, 3, 120);
    Quarto Q209(suite, 2, 209, 3, 1);
    Quarto Q210(suite, 2, 210, 3, 12);
    Quarto Q211(suite, 2, 211, 3, 5);
    Quarto Q212(suite, 2, 212, 3, 112);
    Quarto Q213(suite, 2, 213, 3, 15);
    Quarto Q214(suite, 2, 214, 3, 12);
    */
    //Quarto Q206(suite, 2, 206, 3, 12);
    //H.AddQuarto(Q206);
    /*
    H.AddQuarto(Q207);
    H.AddQuarto(Q208);
    H.AddQuarto(Q209);
    H.AddQuarto(Q210);
    H.AddQuarto(Q211);
    H.AddQuarto(Q212);
    H.AddQuarto(Q213);
    H.AddQuarto(Q214);
    H.AddQuarto(Q317);
    H.AddQuarto(Q205);
    H.AddQuarto(Q100);
    */


    //Reserva RR1(1, {.dia = 20, .mes = 11, .ano= 2020}, {.dia = 2, .mes = 12, .ano= 2020}, 1, {Q206});
    //H.AddReserva(RR1);


    /*
    Reserva RR2(2, {.dia = 25, .mes = 10, .ano= 2020}, {.dia = 9, .mes = 11, .ano= 2020}, 2, {Q205});
    Reserva RR3(3, {.dia = 2, .mes = 11, .ano= 2020}, {.dia = 30, .mes = 11, .ano= 2020}, 1, {Q317});
    Reserva RR4(4, {.dia = 22, .mes = 10, .ano= 2020}, {.dia = 7, .mes = 12, .ano= 2020}, 1, {Q206});
    Reserva RR5(5, {.dia = 12, .mes = 10, .ano= 2020}, {.dia = 1, .mes = 11, .ano= 2020}, 1, {Q209});
    Reserva RR6(6, {.dia = 5, .mes = 11, .ano= 2020}, {.dia = 30, .mes = 11, .ano= 2020}, 1, {Q210});
    Reserva RR7(7, {.dia = 1, .mes = 10, .ano= 2020}, {.dia = 20, .mes = 10, .ano= 2020}, 1, {Q211});
    Reserva RR8(8, {.dia = 5, .mes = 11, .ano= 2019}, {.dia = 30, .mes = 11, .ano= 2019}, 1, {Q212});
    Reserva RR9(9, {.dia = 5, .mes = 12, .ano= 2020}, {.dia = 30, .mes = 12, .ano= 2020}, 1, {Q213});

    H.AddReserva(RR1);
    H.AddReserva(RR2);
    H.AddReserva(RR3);
    H.AddReserva(RR4);
    H.AddReserva(RR5);
    H.AddReserva(RR6);
    H.AddReserva(RR7);
    H.AddReserva(RR8);
    H.AddReserva(RR9);
    */

    /*
    Cliente Lucas("Lucas Calvet", 910);

    int rend = H.RendimentosTotais(11, 2020);
    cout << endl << "Rendimentos: " << rend << endl;

    Reserva LR1(222, {.dia = 20, .mes = 11, .ano= 2021}, {.dia = 2, .mes = 12, .ano= 2021}, 1, {Q214});
    Reserva LR2(223, {.dia = 20, .mes = 11, .ano= 2022}, {.dia = 2, .mes = 12, .ano= 2022}, 1, {Q100});

    Lucas.Reservar(LR1);
    Lucas.Reservar(LR2);

    H.ValidarReserva(Lucas, LR1);
    H.ValidarReserva(Lucas, LR2);
    */



    /*
    Reserva RR10(9, {.dia = 6, .mes = 12, .ano= 2020}, {.dia = 30, .mes = 12, .ano= 2020}, 1, {Q214});
    Reserva RR11(10, {.dia = 5, .mes = 12, .ano= 2020}, {.dia = 30, .mes = 12, .ano= 2020}, 1, {Q213});
    Reserva RR12(11, {.dia = 5, .mes = 12, .ano= 2020}, {.dia = 30, .mes = 12, .ano= 2020}, 1, {Q214});
    Reserva RR13(13, {.dia = 5, .mes = 10, .ano= 2019}, {.dia = 30, .mes = 12, .ano= 2019}, 1, {Q212});
    Reserva RR14(14, {.dia = 5, .mes = 10, .ano= 2019}, {.dia = 20, .mes = 11, .ano= 2019}, 1, {Q212});
    Reserva RR15(15, {.dia = 6, .mes = 11, .ano= 2019}, {.dia = 20, .mes = 12, .ano= 2019}, 1, {Q212});
    Reserva RR16(16, {.dia = 7, .mes = 11, .ano= 2019}, {.dia = 10, .mes = 11, .ano= 2019}, 1, {Q212});

    H.AddReserva(RR10);
    H.AddReserva(RR11);
    H.AddReserva(RR12);
    H.AddReserva(RR13);
    H.AddReserva(RR14);
    H.AddReserva(RR15);
    H.AddReserva(RR16);
    */

    //vector<Reserva> r = H.GetReservas();
    //H.PrintV(r);

    /*
    H.AddFuncionario(Ze);
    H.AddFuncionario(Duarte);
    H.AddFuncionario(Antonio);
    H.AddFuncionario(Manuel);
    H.AddFuncionario(Tito);
    H.AddFuncionario(Carlota);
    H.AddFuncionario(Fred);
    H.AddFuncionario(Alfredo);
    H.AddFuncionario(Marta);
    H.AddFuncionario(Maria);
    H.AddFuncionario(Erica);
    H.AddFuncionario(Tina);
    */


    //H.Quartos_Disponiveis({.dia = 1, .mes = 1, .ano= 2020}, {. dia = 30, .mes =12, .ano= 2020});

    //vector<Funcionario> vf = H.GetFuncionarios();
    //H.PrintV(vf);


    //H.Pesquisa_F_Cargo();
    //H.Pesquisa_F_Salario(0);
    //H.Pesquisa_F_Salario(1);

    //H.ImportarQuartos("C:\\Users\\MSI\\Desktop\\h1.txt");
    //vector <Quarto> q = H.GetQuartos();
    //H.PrintV(q);


    //H.ImportarClientes("C:\\Users\\MSI\\Desktop\\h1.txt");
    //vector <Cliente> c = H.GetClientes();
    //H.PrintV(c);

    //H.ImportarFuncionarios("C:\\Users\\MSI\\Desktop\\h1.txt");
    //vector <Funcionario> f = H.GetFuncionarios();
    //H.PrintV(f);

    //H.Contratar("Canas", 9999, fresponsavel);
    //vector<F_Responsavel> frr = H.GetFuncionariosResponsaveis();
    //H.PrintV(frr);

    //H.ImportarProdutos("C:\\Users\\MSI\\Desktop\\h1.txt");
    //vector<Produto> p = H.GetProdutos();
    //H.PrintV(p);

    //H.ImportarReservas("C:\\Users\\MSI\\Desktop\\h1.txt");
    //vector<Reserva> r = H.GetReservas();
    //H.PrintV(r);

    /*
    H.AddProduto(Produto("massa", 1222, restauracao, ma, 4.36));
    H.AddCliente(Cliente("André Soares Meira", 1234587424, true));
    H.AddQuarto(Quarto(suite, 1, 199, 5, 78.5));
    H.AddFuncionarioGestor(F_Gestor("Diogo Pires", 1979801, 5, 1800, boa));
    H.AddFuncionarioResponsavel(F_Responsavel("César Torres", 99995559, 12, 3000, {1, 2}));
    H.PrintV(r);
    H.EscreverHotel("Marateca01");
     */


}