class Menu
{
private:
vector<Vault*> vaults;

public:
    Menu(/* args */);
    ~Menu();

    static char pass_key;
    

    void mainMenu();

    void accedi_Vault();
    int select_Vault();
    bool check_password(int id);
    void aggiungi_Vault();
    void elimina_Vault(int id);

    int get_numeroVaults();
    void get_vaults();
    void esci_Vault();

    static vector<string> read_file(string nomeFileVault);
    static void write_file(string nomefile, string &content);

    void importa_Vault(vector<string> nomi_vaults);
    void esporta_Vault();    
    
    static bool riprova();
    static void pulisciSchermo();
    static void make_dir(string folderName);
    static string sbarrett();
    static void remove_dir(string folderName);


    static string aoCesare_encrypt(string text, int s);
    static string aoCesare_decrypt(string text, int s);
    
    static void XOR(string &inpString);

    static void encrypt(string &inpString);
    static void decrypt();

};

