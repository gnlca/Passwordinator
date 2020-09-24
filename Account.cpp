#include "librerie.h"

Account::Account() {} //Overload del costruttore
Account::Account(string e, string p):email(e) { set_password(p);}

Account::~Account() {}


void Account::set_email(string s) {email=s;}
string Account::get_email() {return(email);}

void Account::set_password(string s) {

    try {(s.length()<=16 && s.length()>=8)? password = s : throw(113);}
    catch(...){
        cout << endl << "errore - la password deve essere di almeno 8 caratteri e non superiore a 16" << endl;
        cout << "reinserisci la password: ";
        cin >> s;
        set_password(s);
    }
    return;

    }
string Account::get_password() {return(password);}


//Metodo per generare password importato dalla classe Account
//Scambia l'elemento di indice i con un'elemento di indice scelta random
template<class arr>
void Account::arrfuncs<arr>::disordinarr(arr &vettore) {
    char temp;
    int v_size = vettore.size();
    int scelta;
    for(int i=0;i<v_size;i++) {
        scelta=rand()%v_size;
        temp=vettore[scelta];
        vettore[scelta]=vettore[i];
        vettore[i]=temp;
    }
}

        
//Genera una stringa di caratteri randomicamente dal vettore di caratteri
template<class arr>
void Account::arrfuncs<arr>::selezionarr(arr &vettore,arr &selezionati, int n) {
    while((selezionati.size())!=n) {
        selezionati += vettore[rand()%(vettore.size())];
        selezionarr(vettore,selezionati,n); //Ricorsione termina quando soddisfatta la condizione dell'if
    }
}

/*Metodo per genarare una password con opzioni
-int n per il numero di caratteri
-char answ per y/n se includere/escludere i caratteri speciali)*/
string Account::pass_generator() {
    srand(time(NULL));
    int n;
    char answ;

    cout << "Inserisci lunghezza password : ";
    cin >> n ;
    cout << endl;
    while (n<=16 && n<=8) {
        cout << "La lunghezza della password deve essere compresa tra 8-16 caratteri." << endl;
        cout << "Reinserisci la lunghezza della passsword da generare: " ;
        cin >> n ;
        cout << endl;
    }
    cout << "Aggiungere caratteri speciali? y/n : ";
    cin >> answ; cout << endl;
    

    //int cnt=0;
    //int cnt_alfabeto=0, cnt_ALFABETO=0, cnt_specialChars=0, cnt_numeri=0;
    int wsc=4; // wsc come acronimo di with special characters or without special characters, acronimo figo
    int max_numeri=2;
    int max_specialChars=1;
    if(answ=='n'){wsc=3;max_specialChars=0;}
    int max_alfabeto=(n-(max_specialChars+max_numeri))/2;
    int max_ALFABETO= n-(max_alfabeto+max_numeri+max_specialChars);

    
    int max_chars[4] = {max_alfabeto,max_ALFABETO,max_numeri,max_specialChars}; //massimo numero di caratteri per tipo

   
    string caratteri[4] = {
        "abcdefghijklmnopqrstuvwxyz",       //min=1
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",       //min=1
        "0123456789",                       //min=max=1 
        "!@#$%&-",                           //min=1 max=2
    };

    string pass[4] ;
    string pass_completa;
    
    
    for(int i=0; i<wsc; i++) {   
        func.selezionarr(caratteri[i], pass[i], max_chars[i]);
        cout << i <<". batch di caratteri scelti:  " << pass[i] <<endl;
        pass_completa+=pass[i];
    }

    cout << "Effettuo scramble della password: " << pass_completa << endl;
    func.disordinarr(pass_completa);
    cout << "[*] Password completa: " << pass_completa << endl << endl;
    return(pass_completa);
}