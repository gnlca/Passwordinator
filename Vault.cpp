#include "librerie.h"


Vault::Vault(){
    cout << "[*] Inserisci il nome del Vault: " << endl; cin >> vaultName;
    cout << "[*] Inserisci il nome utente: " << endl; cin >> email;
    cout << "[*] Inserisci la password: " << endl; string pass; cin >> pass; set_password(pass);
    cout << "[*] Vault " << vaultName << " creato!" << endl; 
}

Vault::Vault(string &v, string &e, string &p): vaultName(v) {email=e;password=p;}
Vault::~Vault() {}

void Vault::menuVault() {
    //prima pulisco il vettore di siti
    for (int i=0; i<siti.size();i++) { delete siti[i];} 
    siti.clear();
    //Menu::pulisciSchermo();
    try{
        importa_siti();
        cout << "La KEY usata per XOR -> " << Menu::pass_key << endl << endl;
    } catch(...) {
        cout << "*errore nell'importazione dei dati*" << endl;
    }

    bool continua = true;
    char choice;
    int i;
    int id;
    string pass;
    
    do {
        cout << "Menu vault " << vaultName  << endl << "Seleziona un'opzione:" << endl << endl;
        cout << "1.Elenco account siti" << endl;
        cout << "2.Aggiungi account sito." << endl;
        cout << "3.Modifica password." << endl;
        cout << "4.Password Generator" << endl;
        cout << "5.Elimina account" << endl;
        cout << "6.Salva/esporta siti" << endl << endl;
        cout << "[e] Ritorna al Menu Principale" << endl << endl;
        cout << "Seleziona un'opzione: ";
        cin >> choice;
        cout << endl;
        
        switch (choice){
            
            case '1':
                Menu::pulisciSchermo();
                cout << "Visualizza account siti" << endl;
                get_siti();
                try{
                    id = seleziona_sito();    
                }
                catch(...){
                    Menu::pulisciSchermo();
                    cout << "*errore* - questo sito non esiste" << endl <<endl;
                    break;
                }
                Menu::pulisciSchermo();
                break;

            case '2' :
                Menu::pulisciSchermo();
                cout << "Aggiungi account sito" << endl;
                aggiungi_sito();
                esporta_siti();
                continua = Menu::riprova();
                break;

            case '3' :
                Menu::pulisciSchermo();
                cout << "Modifica account" << endl;
                get_siti();
                try{i = seleziona_sito();}
                catch(...){
                    Menu::pulisciSchermo();
                    cout << "*errore* - questo sito non esiste" << endl <<endl;
                    break;
                }
                cout << "Inserisci la password: ";
                cin >> pass;
                siti.at(i)->set_password(pass);
                cout << endl <<"*password modificata*" << endl << endl;
                esporta_siti();
                //continua = Menu::riprova();
                break;

            case '4' :
                Menu::pulisciSchermo();
                cout << "Genera password " << endl;
                pass = pass_generator();
                cout << "Seleziona il sito a cui vuoi modificare la password con quella appena generata" << endl;
                get_siti();
                try{
                    i = seleziona_sito();    
                }
                catch(...){
                    Menu::pulisciSchermo();
                    cout << "*errore* - questo sito non esiste" << endl <<endl;
                    break;
                }
                siti.at(i)->set_password(pass);
                esporta_siti();
                //continua = Menu::riprova();
                Menu::pulisciSchermo();
                cout << "hai con successo aggiornato la password dell'account di " << siti.at(i)->get_dominio() << " !" << endl;
                break;

            case '5':
                Menu::pulisciSchermo();
                cout << "Elimina vault." << endl;
                get_siti();
                i=seleziona_sito();
                elimina_sito(i);
                continua = Menu::riprova();
                break;

            case '6':
                Menu::pulisciSchermo();
                esporta_siti();
                cout << "*siti esportati con successo*" << endl;
                break;
            
            case 'e':
                esporta_siti();
                continua=false;
                break;
                
            default: 
                cout << "La scelta non esiste, vuoi riprovare?: " ;
                cin >> choice;
                continua =(choice=='y')? true : false;    
                break;
        }
        

    } while (continua);
    
    //pulisco il vettore di siti prima di uscire
    for (int i=0; i<siti.size();i++) { delete siti[i];} 
    siti.clear();
    
    Menu::pulisciSchermo();
}

void Vault::set_vaultName(string s) {vaultName=s;}
string Vault::get_vaultName() {return(vaultName);}

//visualizzazione singolo sito 
void Vault::riepilogo() {
    cout << left << "| " << setw(24) << vaultName.substr(0,23) ;
    cout << left << "| " << setw(26) << email.substr(0,25) ;
    cout << left << "| " << setw(18) << password.substr(0,16) << "|"<< endl; 
    cout << string(77,'_') << endl;
}

//override della funzione set_password della classe base Account
void Vault::set_password(string s) {
    Account::set_password(s);
    password = sha256(password);
    return;
}

int Vault::get_numeroSiti() {return(siti.size());}


//Elenco dei siti registrati nel vault
void Vault::get_siti() {
    cout << "*Ci sono " << get_numeroSiti() << " siti salvati*" << endl;
    cout << string(77,'_') << endl;
    cout << left << "  | " << setw(24) << "DOMINIO"; 
    cout << left << "| " << setw(26) << "EMAIL";
    cout << left << "| " << setw(18) << "PASSWORD" << "|" << endl; 
    cout << string(77,'_') << endl;
    
    for(int i=0;i<(get_numeroSiti());i++) {
        cout << i+1 << ".";
        siti.at(i)->riepilogo('y');
    }

}



int Vault::seleziona_sito() {
    int choice;
    char c;
    cout << endl << "Seleziona il sito  [1- " << get_numeroSiti() << "] : " ;
    cin >> choice; cout << endl;
    cout << "Hai selezionato questo sito:" << endl;
    cout << string(77,'_') << endl;
    siti.at(choice-1)->riepilogo();
    cout << endl << "Scegliere altro? y/n: " ;
    cin >> c;
    if(c=='y') {
        seleziona_sito();
    }
    return(choice-1);
}

void Vault::aggiungi_sito() {siti.push_back(new Sito());}
void Vault::modifica_sito() {}

void Vault::elimina_sito(int id) {
    delete siti[id];
    siti.erase(siti.begin()+id);
}



void Vault::importa_siti() {
    vector<string> content;
    string credenziali[3];
    int cnt=0;
    int j=0;
    int i=0;
    
    content = Menu::read_file("vaults" + Menu::sbarrett() + vaultName + Menu::sbarrett() + vaultName + "_siti.txt");
    if(content.empty()) {cout << "*nessun sito da importare*" << endl; return;}
    
    for (int i=0; i<content.size();i++) {
      Menu::XOR(content.at(i));
    } 

    while(cnt<content.size()) {
        //(content.at(cnt)[i++] != ';') ? (credenziali[j]+=content.at(cnt)[i]) : j=j+1 ;
        for(int i=0; i<content.at(cnt).length() ; i++ ) {
            if( content.at(cnt)[i] != ';' ) {
                credenziali[j] += content.at(cnt)[i];
            } else {j++; }
        }
        siti.push_back(new Sito(credenziali[0], credenziali[1], credenziali[2]));
        credenziali[0].clear();
        credenziali[1].clear();
        credenziali[2].clear();
        j=0;
        cnt++;
        }
    cout << "*siti del vault " << vaultName << " importati con successo*" << endl << endl;
    return;
}



void Vault::esporta_siti() {
    string contenuto;
    string line;
    for(int i=0; i<siti.size(); i++) {
        line+=siti.at(i)->get_dominio() +";";
        line+=siti.at(i)->get_email() +";";
        line+=siti.at(i)->get_password() ;
        Menu::XOR(line);
        line+="\n";
        contenuto+=line;
        line.clear();
    }
    Menu::write_file("vaults" + Menu::sbarrett() + vaultName + Menu::sbarrett() + vaultName + "_siti.txt",contenuto);
}