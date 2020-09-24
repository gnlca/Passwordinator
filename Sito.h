
class Sito: public Account{
private:
    string dominio;
    char note[200];
    
public:
    Sito();
    Sito(string &d, string &e, string &p);
    ~Sito();

    void riepilogo(char choice='n');


    
    //setters and getters per i membri della classe Sito e della sua classe base Account
    void set_dominio(string s);
    string get_dominio();
    


};

