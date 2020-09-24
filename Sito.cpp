#include "librerie.h"


//Costruttore Sito
Sito::Sito(){
    cout << "[*] INSERIMENTO ACCOUNT SITO" << endl;
    cout << "Inserisci il dominio del sito: " << endl; cin >> dominio;
    cout << "Inserisci il nome utente: " << endl; cin >> email;
    cout << "Inserisci la password: " << endl; string pass; cin >> pass; set_password(pass);
    cout << "[*] Account Sito " << dominio << " aggiunto!" << endl; 
} //Overload del costruttore
Sito::Sito(string &d, string &e, string &p):dominio(d), Account(e,p) {}
Sito::~Sito() {} //Distruttore Sito



void Sito::riepilogo(char choice) {
    cout << left << "| " << setw(24) << dominio.substr(0,23);
    cout << left << "| " << setw(26) << email.substr(0,25);
    cout << left << "| " << setw(18) << ((choice=='y' ) ? string(password.length(),'*').substr(0,15) : password.substr(0,15) )<< "|"<< endl; 
    cout << string(77,'_') << endl;

}




//setters and getters per i membri della classe Sito e della sua classe base Account
void Sito::set_dominio(string s) {dominio=s;}
string Sito::get_dominio() {return(dominio);}
