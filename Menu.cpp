#include "librerie.h"



Menu::Menu() {mainMenu();}
Menu::~Menu(){}

char Menu::pass_key;

void Menu::mainMenu() {
    bool continua = true;
    char choice;
    int id;
    pulisciSchermo();
    try {
    importa_Vault(read_file("vaults" + sbarrett() +"vaults.txt"));

    } catch(...) { cout << "ERRRORONE" <<endl;

    }
    do {
        
        cout << "Menu principale" << endl << endl;
        cout << "1.Accedi ad un Vault" << endl;
        cout << "2.Crea un Vault" << endl;
        cout << "3.Elimina un Vault" << endl;
        cout << "4.Esporta vaults" << endl << endl;
        cout << "[e] Esci" << endl << endl;
        cout << "Seleziona un'opzione: " ;
        cin >> choice;
        cout << endl;
        switch (choice){
            
            case '1':
                pulisciSchermo();
                cout << "Seleziona il tuo vault" << endl;
                get_vaults();

                if(get_numeroVaults()==0) {
                    pulisciSchermo();
                    cout << endl <<"*Nessun vault registrato*" << endl << endl;
                    //continua = riprova();
                    break;
                }

                try{
                    id = select_Vault();    
                }
                catch(...){
                    pulisciSchermo();
                    cout << "*errore* - questo vault non esiste" << endl <<endl;
                    break;
                }

                if(check_password(id)) {
                    pulisciSchermo();
                    cout << "*Password corretta*" << endl;
                } else {
                    pulisciSchermo();
                    cout << "*Password ERRATA*" << endl << endl;
                    break;
                }
                vaults.at(id)->menuVault(); 
                continua = true;
                break;

            case '2' :
                pulisciSchermo();
                cout << "Creazione vault." << endl;
                vaults.push_back(new Vault());
                esporta_Vault();
                continua = riprova();
                break;

            case '3':
                pulisciSchermo();
                cout << "Elimina vault." << endl;
                if(get_numeroVaults()==0) {
                    cout << "*Nessun vault registrato*" << endl;
                    continua = riprova();
                    break;
                }
                get_vaults();
                id=select_Vault();
                elimina_Vault(id);
                esporta_Vault();
                continua = riprova();
                break;
            

            case '4':   
                esporta_Vault();
                cout << "Esportazione Vault completata" << endl;
                continua = riprova();
                break;
            
            case 'e':   
                esporta_Vault();
                continua = false;
                break;
            
            
            default: 
                pulisciSchermo();
                cout << "[*] La scelta non esiste, vuoi riprovare? y/n: " ;
                cin >> choice;
                continua =(choice=='y')? true : false;    
                break;
        }

    } while (continua);
    pulisciSchermo();
    
}

bool Menu::check_password(int id) {
    string s;
    cout << "Accedi al Vault inserendo la password: ";
    cin >> s;
    cout << "SHA256 della password del vault " <<  vaults.at(id)->get_password() <<endl;
    string pass = sha256(s);
    cout << "Questa è la password inserita" << s << endl;
    cout << "SHA256 della tua password " << pass <<endl;
    if (!strcmp(pass.c_str(),(vaults.at(id)->get_password()).c_str())) {
        cout << "LA KEY PER XOR -> " << s[0] << endl;
        pass_key = s[0];
        return(true);
    }
    return(false);
}


int Menu::select_Vault() {
    int choice;
    char c;
    cout << endl << "Seleziona il Vault [1- " << get_numeroVaults() << "] : " ;
    cin >> choice;
    cout << endl << "Hai selezionato questo vault:" << endl;
    cout << string(77,'_') << endl;
    vaults.at(choice-1)->riepilogo();
    cout << endl << "Corretto? y/n: " ;
    cin >> c;
    if(c!='y') {
        select_Vault();
    } else {
        return(choice-1);
    }
    return(-1);
}

int Menu::get_numeroVaults() {return(vaults.size());}

void Menu::get_vaults() {
    cout << "*Ci sono " << get_numeroVaults() << " siti salvati*" << endl;
    cout << string(77,'_') << endl;
    cout << left << "  | " << setw(24) << "DOMINIO"; 
    cout << left << "| " << setw(26) << "EMAIL";
    cout << left << "| " << setw(18) << "PASSWORD" << "|" << endl; 
    cout << string(77,'_') << endl;

    for(int i=0;i<(vaults.size());i++) {
        cout << string(77,'_') << endl;
        cout << i+1 << ".";
        vaults.at(i)->riepilogo();
    }
    return;
}


void Menu::elimina_Vault(int id) {
    remove_dir(vaults.at(id)->get_vaultName());
    delete vaults[id];
    vaults.erase(vaults.begin()+id);
    cout << endl << "*vault eliminato correttamente*" << endl;
    return;
}




bool Menu::riprova() {
    char c;
    cout << "[*] Digita y se vuoi tornare al menu : " ;
    cin >> c; cout << endl;
    pulisciSchermo();
    return((c=='y')? true : false);
}




vector<string> Menu::read_file(string nomeFileVault) {
    vector<string> content ;
    string line;
    int i=0;
    ifstream miofile(nomeFileVault);
    if (miofile.is_open())
    {
      while ( getline(miofile,line) ) {
        content.push_back(line);
      }
      miofile.close();
    }   
    else cout << "*file non trovato, creazione di uno nuovo.*"  << endl;
    return(content); 
}


void Menu::importa_Vault(vector<string> nomi_vaults) {
    string credenziali[3];
    vector<string> content;
    int cnt=0;
    int j=0;
    int i=0;

    for(int i=0; i<nomi_vaults.size(); i++) {
        content.push_back(read_file("vaults" + sbarrett() + nomi_vaults.at(i) + sbarrett() + nomi_vaults.at(i) + ".txt").at(0));
    }
    while(cnt<content.size()) {
        //(content.at(cnt)[i++] != ';') ? (credenziali[j]+=content.at(cnt)[i]) : j=j+1 ;
        for(int i=0; i<content.at(cnt).length() ; i++ ) {
            if( content.at(cnt)[i] != ';' ) {
                credenziali[j] += content.at(cnt)[i];
            } else {j++; }
        }
        vaults.push_back(new Vault(credenziali[0], credenziali[1], credenziali[2]));
        credenziali[0]= "";
        credenziali[1]= "";
        credenziali[2]= "";
        j=0;
        cnt++;
        }
    cout << "*vaults importati con successo*" << endl << endl;
    return;
}




void Menu::write_file(string nomefile,string &content) {    
    ofstream miofile(nomefile);
    miofile << content;
    miofile.close();
}


void Menu::esporta_Vault() {
    string contentVault;
    string nomi_vaults;
    make_dir("vaults");
    for(int i=0; i<vaults.size(); i++) {
        contentVault=vaults.at(i)->get_vaultName() + ";" + vaults.at(i)->get_email() + ";" + vaults.at(i)->get_password() + "\n";
        make_dir("vaults"+ sbarrett() + vaults.at(i)->get_vaultName());
        write_file( "vaults" + sbarrett() + vaults.at(i)->get_vaultName() + sbarrett() + vaults.at(i)->get_vaultName() + ".txt",contentVault);
        nomi_vaults+=vaults.at(i)->get_vaultName() + "\n";
    }
        write_file("vaults" + sbarrett() +"vaults.txt",nomi_vaults);    
}




void Menu::pulisciSchermo() {
	#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) ) && !defined(__LINUX__)
		system("cls");
	#else
		system("clear");
	#endif
}

void Menu::make_dir(string folderName) {
    #if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) ) && !defined(__LINUX__)
		system(("mkdir " + folderName).c_str());
	#else
		system(("mkdir " + folderName).c_str());
	#endif
}

void Menu::remove_dir(string folderName) {
    #if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) ) && !defined(__LINUX__)
		system(("rmdir -r vaults\\" + folderName).c_str() );
	#else
		system(("rm -r vaults/" + folderName).c_str());
	#endif
}

string Menu::sbarrett(){
    #if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) ) && !defined(__LINUX__)
		return("\\");
	#else
		return("/");
	#endif
}





string Menu::aoCesare_encrypt(string text, int s) 
{ 
    string result = ""; 
  
    // traverse text 
    for (int i=0;i<text.length();i++) 
    { 
        // apply transformation to each character 
        // Encrypt Uppercase letters 
    if (isupper(text[i])) result += char(int(text[i]+s-65)%26 +65); 
  
    // Encrypt Lowercase letters 
    else result += char(int(text[i]+s-97)%26 +97); 
    } 

    return(result);
}

string Menu::aoCesare_decrypt(string text, int s) 
{ 
    string result = ""; 
  
    // traverse text 
    for (int i=0;i<text.length();i++) 
    { 
        // apply transformation to each character 
        // Encrypt Uppercase letters 
    if (isupper(text[i])) result += char(int(text[i]+s-65)%26 +65); 
  
    // Encrypt Lowercase letters 
    else result += char(int(text[i]+s-97)%26 +97); 
    } 

    return(result);
}


//Funzione xor accetta in ingresso una stringa
void Menu::XOR(string &inpString) { 
    char xorKey = pass_key; //chiave usata  
    int len = inpString.length(); 
    for (int i = 0; i < len; i++) { 
        inpString[i] = inpString[i] ^ xorKey; 
    }
}



void Menu::encrypt(string &inpString) {
    XOR(inpString);
}