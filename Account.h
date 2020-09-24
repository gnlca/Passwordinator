class Account {
protected:
    string email;
    string password;
public:
    Account();
    Account(string e, string p);
    ~Account();

    //metodi virtuali setters and getters per i membri della classe Account
    void set_email(string s);
    string get_email();

    void set_password(string s);
    string get_password();


    template<class arr>
     struct arrfuncs{
        void disordinarr(arr &vettore); //array disordinato
        void selezionarr(arr &vettore, arr &selezionati, int n); //metodo per selezionare randomicamente un'elemento dall'array
    } ;
    
    arrfuncs<string> func;

    //metodo per generare password importato dalla classe Account
    string pass_generator();






    







};  
