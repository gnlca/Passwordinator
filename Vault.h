

class Vault: public Account{
private:
    string vaultName;
    vector<Sito*> siti;


public:
    Vault();
    Vault(string &v, string &e, string &p);
    ~Vault(); 

    void menuVault();

    

    void set_vaultName(string s);
    string get_vaultName();

    void riepilogo();

    virtual void set_password(string s);


    int get_numeroSiti();

    void get_siti();

    int seleziona_sito();
    void aggiungi_sito();
    void modifica_sito();
    void elimina_sito(int id);

    void importa_siti();
    void esporta_siti();




 
    


};

