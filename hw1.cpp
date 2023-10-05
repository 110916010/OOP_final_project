#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream.>


using namespace std;

class CommodityList;
class Store;
class InputHandler;

class InputHandler {
public:
    /*
     * The function is used to read a full line into a string variable.
     * It read the redundant '\n' character to prevent the problem of getline function.
     * There is an overload version which can read from the specified data stream.
     * INPUT: None, or fstream
     * RETURN: Full line input by user
     * */
    static string readWholeLine() {
        string input;
        cin.get();
        getline(cin, input);
        return input;
    }

    static string readWholeLine (fstream& file) {
        string input;
        char t;
        t=file.get();
        getline(file,input);
        if(t!='\n'){
            return t+input;
        }
        else{
            return input;
        }
    }

    /*
     * This function is used to configure whether the input string is a number
     * INPUT: A string
     * RETURN: Bool. True if input string is a number, otherwise false.
     */
    static bool isNum(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    /*
     * Check the input string is a valid number.
     * First check the input is a number or not, then identify whether it is bigger than 0
     * INPUT: string
     * RETURN: bool
     */
    static bool isValidNum(string& str) {
        if (!isNum(str) || (isNum(str) && stoi(str) <= 0))
            return false;
        return true;
    }

    /*
     * Get a number from the user. This function will check the input validation.
     * INPUT: none
     * OUTPUT: integer, the input number
     */
    static int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    /*
     * This function is used in function getInput. Check the input range is inside the specified range
     */
    static int inputCheck(string input, int maxChoiceLen, bool noZero) {
        // Change input to the general integer
        int choice = 0;
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                choice = choice * 10 + (input[i] - '0');
            } else {
                return -1;
            }
        }

        if (noZero) {
            return (choice <= maxChoiceLen && choice > 0) ? choice : -1;
        } else {
            return (choice <= maxChoiceLen && choice >= 0) ? choice : -1;
        }
    }

    /*
     * Get the input from the user, and limit the input between the range [0, maxChoiceLen].
     * If noZero is signaled. Then the range will be [1, maxChoiceLen]
     * INPUT: integer, bool(option)
     * OUTPUT: integer, the choice number
     */
    static int getInput(int maxChoiceLen, bool noZero = false) {
        string input;

        cin >> input;
        int choice = inputCheck(input, maxChoiceLen, noZero);
        while (choice == -1) {
            cout << "your input is wrong, please input again:" << endl;
            cin >> input;
            choice = inputCheck(input, maxChoiceLen, noZero);
        }

        return choice;
    }
};

class shopping{
protected:
    int price;
    string description;
    string commodityName;
    string material;
    string size;
    string color;
    int weight;
    int calories;
    int saveday;
    string use;
    string system;
    string classification;
    string price2;
public:
    int number;
    int classtype;
    shopping *ptr;
    ~shopping()=default;
    shopping(string  Nam,int pri,string descri,int wei,int cal,int sav){//snacks
        this->price = pri;
        this->commodityName = Nam;
        this->description = descri;
        this->weight = wei;
        this->calories = cal;
        this->saveday = sav;
        this->number =1;
        this->classtype=1;
        this->material = "";
        this->size = "";
        this->color = "";
        this->use = "";
        this->classification = "";
        this->system = "";
    }
    shopping(int a,string Nam,int pri,string descri,string use,string cla,string sys) {
        if (a == 1) {//clothes
            this->price = pri;
            this->commodityName = Nam;
            this->description = descri;
            this->material = use;
            this->size = cla;
            this->color = sys;
            this->number = 1;
            this->classtype = 2;
            this->use = "";
            this->classification = "";
            this->system = "";
            this->weight = 0;
            this->calories = 0;
            this->saveday = 0;
        }
        if (a == 2) {//apps
            this->price = pri;
            this->commodityName = Nam;
            this->description = descri;
            this->use = use;
            this->classification = cla;
            this->system = sys;
            this->number = 1;
            this->classtype = 3;
            this->material = "";
            this->size = "";
            this->color = "";
            this->weight = 0;
            this->calories = 0;
            this->saveday = 0;
        }
    }
    /*
     * This method will show the full information of the commodity to user interface.
     * There is a overloading version, with an argument amount which will output the information with the amount
     * INPUT: None, or an integer specify the amount of this commodity
     * RETURN: None
     */
    void appdetail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "use:" << use << endl ;
        cout << "classification:" << classification << endl;
        cout << "system:" << system << endl;
        cout << "description: " << description << endl;
        cout << "-------------------------------" << endl;
    }
    void clodetail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "material:" << material << endl ;
        cout << "size:" << size << endl;
        cout << "color's type:" << color << endl;
        cout << "description: " << description << endl;
        cout << "-------------------------------"<<endl;
    }

    void snadetail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "weight:" << weight << endl ;
        cout << "calories:" << calories << endl;
        cout << "saveday:" << saveday << endl;
        cout << "description: " << description << endl;
        cout << "-------------------------------"<<endl;
    }

    /*
     * Use this function to get the information data from the user, this will init the object.
     * INPUT: none
     * OUTPUT: none
     */
    virtual void userSpecifiedCommodity() {
        cout << "Please input the commodity name:" << endl;
        commodityName = InputHandler::readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = InputHandler::numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        description = InputHandler::readWholeLine();
    }

    /*
     * Save and load function is used to write the data to the file or read the data from the file.
     * According to the input parameter fstr
     * eam, they complete the I/O on the specified file.
     * There have no definition of those method, because it is used to be override in the derived class.
     * INPUT: fstream
     * OUTPUT: none
     */
    virtual void save(fstream& file) {}

    virtual void load(fstream& file) {}

    /*
     * The getter function of commodityName
     */
    string getName() {
        return commodityName;
    }

    /*
     * The getter function of price
     */
    int getPrice() {
        return price;
    }
    string getdescription(){
        return description;
    }
    //Get Snacks
    int getsnawei(){
        return weight;
    }
    int getsnacal(){
        return calories;
    }
    int getsav(){
        return saveday;
    }
    //Get Clothes
    string getmat(){
        return material;
    }
    string getsiz(){
        return size;
    }
    string getcolor(){
        return color;
    }
    string getuse(){
        return use;
    }
    string getsystem(){
        return system;
    }
    string getclassification(){
        return classification;
    }

};

/*
 * [YOU SHOULD FINISH THREE TYPES OF DERIVED COMMODITY CLASS HERE]
 * Please try your best to complete the definition of three classes.
 * Use the knowledge you learned from this course.
 * You should follow the OOP concept.
 */

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * This is a list storing the existing commodity in the store.
 * There are some method which can modify the content.
 * You may use any data structure to complete this class.
 */

class CommodityList {
private:
    shopping *sna_head;
    shopping *clo_head;
    shopping *app_head;
    shopping *snax;
    shopping *clox;
    shopping *appx;
    shopping *snay;
    shopping *cloy;
    shopping *appy;
    shopping *addsna;
    shopping *addclo;
    shopping *addapp;
    shopping *ptr;
    int snanum=0;
    int clonum=0;
    int appnum=0;
    int total=0;
    int notice;
    int weight;
    int calories;
    int saveday;
    string material;
    string size;
    string color;
    string use;
    string classification;
    string system;
    int detectionno1=0;
public:
    CommodityList(){
    }
    /*
     * Print the full information of the commodities inside the list
     * You must call Commodity.detail() to show the commodity information.
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesDetail() {
        snay=sna_head;
        cloy=clo_head;
        appy=app_head;
        total=0;
        if(snanum){
            cout<<"Snacks type:"<<endl;
            while(snay!=NULL){
                total++;
                cout<<total<<" ."<<endl;
                snay->snadetail();
                snay=snay->ptr;
            }
        }
        if(clonum){
            cout<<"Clothes type:"<<endl;
            while(cloy!=NULL){
                total++;
                cout<<total<<" ."<<endl;
                cloy->clodetail();
                cloy=cloy->ptr;
            }
        }
        if(appnum){
            cout<<"Apps type:"<<endl;
            while(appy!=NULL){
                total++;
                cout<<total<<" ."<<endl;
                appy->appdetail();
                appy=appy->ptr;
            }
        }
    }
    /*
     * Print only the commodity name of the commodities inside the list
     * You don't need to use Commodity.detail() here, just call the Commodity.getName() function is ok
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesName() {
        snay=sna_head;
        cloy=clo_head;
        appy=app_head;
        total=0;
        if(snanum){
            cout<<"Snacks type:"<<endl;
            while(snay!=NULL){
                total++;
                cout<<total<<" .";
                cout<<snay->getName()<<endl;
                snay=snay->ptr;
            }
        }
        if(clonum){
            cout<<"Clothes type:"<<endl;
            while(cloy!=NULL){
                total++;
                cout<<total<<" .";
                cout<<cloy->getName()<<endl;
                cloy=cloy->ptr;
            }
        }
        if(appnum){
            cout<<"Apps type:"<<endl;
            while(appy!=NULL){
                total++;
                cout<<total<<" .";
                cout<<appy->getName()<<endl;
                appy=appy->ptr;
            }
        }
    }

    /*
     * Check whether the list is empty or not
     * INPUT: None
     * RETURN: Bool. True if the list is empty, otherwise false
     */
    bool empty() {
        if(snanum==0&&clonum==0&&appnum==0){
            return true;
        }
        else{
            return false;
        }
    }

    /*
     * Return the size(or length) of the list
     * INPUT: None
     * RETURN: Integer. List size
     */
    int getsize() {
        int sum;
        sum=snanum+clonum+appnum;
        return sum;
    }

    /*
     * Return a commodity object at specified position
     * INPUT: Integer. The index of that commodity
     * RETURN: Commodity. The wanted commodity object
     */
    shopping* get(int index) {
        snay=sna_head;
        cloy=clo_head;
        appy=app_head;
        total=0;
        while(snay&&index!=total){
            snay=snay->ptr;
            total++;
        }
        while(cloy&&index!=total){
            cloy=cloy->ptr;
            total++;
        }
        while(appy&&index!=total){
            appy=appy->ptr;
            total++;
        }

        if(snay!=NULL){
            return snay;
        }
        if(cloy!=NULL){
            return cloy;
        }
        if(appy!=NULL){
            return appy;
        }
    }

    /*
     * Push a new commodity object into the list
     * INPUT: Commodity. The object need to be pushed
     * RETURN: None
     */
    void add(int judge,shopping *newshop) {
        if(judge==1){//=0 would happen
            if(snanum==0){
                sna_head=newshop;
                addsna=sna_head;
                snanum++;
            }
            else if (snanum!=0){
                addsna->ptr=newshop;
                addsna=newshop;
                snanum++;
            }
        }
        if(judge==2){
            if(clonum==0){
                clo_head=newshop;
                addclo=clo_head;
                clonum++;
            }
            else if (clonum!=0){
                addclo->ptr=newshop;
                addclo=newshop;
                clonum++;
            }
        }
        if(judge==3){//=0 would happen
            if(appnum==0){
                app_head=newshop;
                addapp=app_head;
                appnum++;
            }
            else if (appnum!=0){
                addapp->ptr=newshop;
                addapp=newshop;
                appnum++;
            }
        }
    }

    /*
     * Check the input commodity object is existing inside the list
     * If the commodity name is the same, we take those objects the same object
     * INPUT: Commodity. The object need to be checked
     * OUTPUT: Bool. True if the object existing, otherwise false
     */
    bool isExist(int a,shopping *newshop) {
        int detect = 0;
        bool realdetect;
        int no = 0;
        snay = sna_head;
        cloy = clo_head;
        appy = app_head;
        if (no != 0) {
            if (a == 1) {
                while (snay != NULL) {
                    if (newshop->getName() == snay->getName()) {
                        detect++;
                    }
                    snay = snay->ptr;
                }
                if (detect != 0) {
                    realdetect = true;
                }
            }
            if (a == 2) {
                while (cloy != NULL) {
                    if (newshop->getName() == cloy->getName()) {
                        detect++;
                    }
                    cloy = cloy->ptr;
                }
                if (detect != 0) {
                    realdetect = true;
                }
            }
            if (a == 3) {
                while (appy != NULL) {
                    if (newshop->getName() == appy->getName()) {
                        detect++;
                    }
                    appy = appy->ptr;
                }
                if (detect != 0) {
                    realdetect = true;
                }
            }
        }
        if (no == 0 || detect == 0) {
            no++;
            realdetect = false;
        }
        return realdetect;
    }

    /*
     * Remove an object specified by the position
     * INPUT: Integer. The position of the object which need to be removed
     * OUTPUT: None
     */
    void remove(int index) {
        notice=0;
        snay=sna_head;
        cloy=clo_head;
        appy=app_head;
        total=0;
        while(snay&&index!=total) {
            snay = snay->ptr;
            total++;
        }
        if(snay==sna_head){
            sna_head=sna_head->ptr;
            snay->ptr=NULL;
            snanum--;
            return;
        }
        while(cloy&&index!=total){
            cloy=cloy->ptr;
            total++;
            clonum--;
        }
        if(cloy==clo_head){
            clo_head=clo_head->ptr;
            cloy->ptr=NULL;
            return;
        }
        while(appy&&index!=total){
            appy=appy->ptr;
            total++;
        }
        if(appy==app_head){
            app_head=app_head->ptr;
            appy->ptr=NULL;
            appnum--;
            return;
        }

        if(index==total){
            total=0;
            while(snax&&index!=total+1){
                snax=snax->ptr;
                total++;
            }
            while(clox&&index!=total+1){
                clox=clox->ptr;
                total++;
            }
            while(appx&&index!=total+1){
                appx=appx->ptr;
                total++;
            }
            if(snay!=NULL){
                notice=1;
                snanum--;
                    snax->ptr=snay->ptr;
                    return;
            }
            if(cloy!=NULL){
                notice=2;
                clonum--;
                if(cloy==clo_head){
                    clo_head=clo_head->ptr;
                    cloy->ptr=NULL;
                    clox->ptr=cloy->ptr;
                    return;
                }
            }
            if(appy!=NULL){
                notice=3;
                appnum--;
                if(appy==app_head){
                    app_head=app_head->ptr;
                    appy->ptr=NULL;
                    appx->ptr=appy->ptr;
                    return;
                }
            }
        }
    }
    void save() {
        snay=sna_head;
        cloy=clo_head;
        appy=app_head;
        ofstream file;
        int total;
        file.open("StoreStore.txt",ios::out|ios::trunc);
        for(int i=0;i<snanum;i++){
                file<<snay->classtype<<endl;
                file << snay->getName() <<endl;
                file << snay->getPrice()<<endl;
                file <<  snay->getdescription() << endl;
                file << snay->getsnawei() << endl;
                file << snay->getsnacal() << endl;
                file << snay->getsav() << endl;
                snay = snay->ptr;
            }
        for(int k=0;k<clonum;k++){
            file<<cloy->classtype<<endl;
            file << cloy->getName() <<endl;
            file << cloy->getPrice()<<endl;
            file << cloy->getdescription() << endl;
            file << cloy->getmat() << endl ;
            file << cloy->getsiz() << endl;
            file << cloy->getcolor() << endl;
            cloy=cloy->ptr;
        }
        for(int j=0;j<appnum;j++){
            file<<appy->classtype<<endl;
            file << appy->getName() <<endl;
            file << appy->getPrice()<<endl;
            file << appy->getdescription() << endl;
            file <<  appy->getuse() << endl ;
            file <<  appy->getclassification() << endl;
            file <<  appy->getsystem() << endl;
            appy=appy->ptr;
        }
        file<<4<<endl;
        file.close();
    }
    void loaddata() {
        fstream file2("StoreStore.txt",ios::in);
        shopping *data;
        if(!file2.is_open()){
            return;
        }
        else {
            int a=1;
            int t=stoi(InputHandler::readWholeLine(file2));
            while (a) {
                if (t==1) {
                    data = new shopping( InputHandler::readWholeLine(file2),stoi(InputHandler::readWholeLine(file2)),
                                        InputHandler::readWholeLine(file2), stoi(InputHandler::readWholeLine(file2)),
                                        stoi(InputHandler::readWholeLine(file2)),
                                        stoi(InputHandler::readWholeLine(file2)));
                    add(1, data);
                }
                if (t==2) {
                    data = new shopping(1,  InputHandler::readWholeLine(file2),stoi(InputHandler::readWholeLine(file2)),
                                        InputHandler::readWholeLine(file2), InputHandler::readWholeLine(file2),
                                        InputHandler::readWholeLine(file2), InputHandler::readWholeLine(file2));
                    add(2, data);
                }
                if (t==3) {
                    data = new shopping(2, InputHandler::readWholeLine(file2),stoi(InputHandler::readWholeLine(file2)),
                                        InputHandler::readWholeLine(file2), InputHandler::readWholeLine(file2),
                                        InputHandler::readWholeLine(file2), InputHandler::readWholeLine(file2));
                    add(3, data);
                }
                t=stoi(InputHandler::readWholeLine(file2));
                cout<<"t:"<<t<<endl;
                if(t==4){
                    return;
                }
            }
        }

    }



};

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * The shopping cart is used to store the commodities user wanted.
 * Because the same name represents the same object, if there is a commodity which have more than one object inside
 * the cart, then it will be store as the same object and the cart must keep the amount of the object.
 * You may use any data structure to complete this class.
 */
class ShoppingCart {
private:
    vector<shopping> shopping_cart;
    int detect=0;
    shopping *newcom;
public:

    /*
     * Push an commodity object into the cart.
     * Be careful that if the input object is existing in the list, then keep the amount of that object rather than
     * actually push the object into the cart.
     * INPUT: Commodity. The object need to be pushed.
     * OUTPUT: None.
     */
    void push(shopping *x) {
        if(x->classtype==1){//snack
            detect=0;
            newcom = new shopping(x->getName(),x->getPrice(),x->getdescription(),x->getsnawei(),x->getsnacal(),x->getsav());
            for(int j=0;j<shopping_cart.size();j++){
                if(shopping_cart[j].getName()==x->getName()){
                    shopping_cart[j].number++;
                    detect++;
                    break;
                }
            }
            if(detect==0){
                shopping_cart.push_back(*newcom);
            }
        }
        if(x->classtype==2){
            detect=0;
            newcom = new shopping(1,x->getName(),x->getPrice(),x->getdescription(),x->getmat(),x->getsiz(),x->getcolor());
            for(int j=0;j<shopping_cart.size();j++){
                if(shopping_cart[j].getName()==x->getName()){
                    shopping_cart[j].number++;
                    detect++;
                    break;
                }
            }
            if(detect==0){
                shopping_cart.push_back(*newcom);
            }
        }
        if(x->classtype==3){//Apps
            detect=0;
            newcom = new shopping(2,x->getName(),x->getPrice(),x->getdescription(),x->getuse(),x->getclassification(),x->getsystem());
            for(int j=0;j<shopping_cart.size();j++){
                if(shopping_cart[j].getName()==x->getName()){
                    shopping_cart[j].number++;
                    detect++;
                    break;
                }
            }
            if(detect==0){
                shopping_cart.push_back(*newcom);
            }
        }
    }

    /*
     * Show the content of the cart to user interface.
     * INPUT: None.
     * OUTPUT: None.
     */
    void showCart() {
        for(int i=0;i<shopping_cart.size();i++){
            cout<<i+1<<" ."<<endl;
            if(shopping_cart[i].classtype==1){
                cout<<shopping_cart[i].getName()<<endl;
                cout<<"price:"<<shopping_cart[i].getPrice()<<endl;
                cout<<"weight:"<<shopping_cart[i].getsnawei()<<endl;
                cout<<"calories:"<<shopping_cart[i].getsnacal()<<endl;
                cout<<"saveday:"<<shopping_cart[i].getsav()<<endl;
                cout<<"description:"<<shopping_cart[i].getdescription()<<endl;
                cout<<"x "<<shopping_cart[i].number<<endl;
            }
            if(shopping_cart[i].classtype==2){
                cout<<shopping_cart[i].getName()<<endl;
                cout<<"price:"<<shopping_cart[i].getPrice()<<endl;
                cout<<"material:"<<shopping_cart[i].getmat()<<endl;
                cout<<"size:"<<shopping_cart[i].getsiz()<<endl;
                cout<<"color's type:"<<shopping_cart[i].getcolor()<<endl;
                cout<<"description:"<<shopping_cart[i].getdescription()<<endl;
                cout<<"x "<<shopping_cart[i].number<<endl;
            }
            if(shopping_cart[i].classtype==3){
                cout<<shopping_cart[i].getName()<<endl;
                cout<<"price:"<<shopping_cart[i].getPrice()<<endl;
                cout<<"use:"<<shopping_cart[i].getuse()<<endl;
                cout<<"classification:"<<shopping_cart[i].getclassification()<<endl;
                cout<<"system:"<<shopping_cart[i].getsystem()<<endl;
                cout<<"description:"<<shopping_cart[i].getdescription()<<endl;
                cout<<"x "<<shopping_cart[i].number<<endl;
            }
        }
    }

    /*
     * Return the cart size. (The same object must be seen as one entry)
     * INPUT: None.
     * OUTPUT: Integer. The cart size.
     */
    int size() {
        return shopping_cart.size();
    }

    /*
     * Remove an entry from the cart. Don't care about the amount of the commodity, just remove it.
     * INPUT: The order of the entry.
     * OUTPUT: None.
     */
    void remove(int index) {
        auto deletenum=shopping_cart.begin()+index;
        shopping_cart.erase(deletenum);
    }

    /*
     * Check the total amount of price for the user.
     * Remember to clear the list after checkout.
     * INPUT: None.
     * OUTPUT: Integer. The total price.
     */
    int checkOut() {
        int sum=0;
        for(int k=0;k<shopping_cart.size();k++){
            sum=sum+shopping_cart[k].getPrice()*shopping_cart[k].number;
        }
        shopping_cart.clear();
        return sum;
    }

    /*
     * Check if the cart have nothing inside.
     * INPUT: None.
     * OUTPUT: Bool. True if the cart is empty, otherwise false.
     */
    bool empty() {
        return shopping_cart.empty();
    }
};

/*
 * [DO NOT MODIFY ANY CODE HERE]
 * The Store class manage the flow of control, and the interface showing to the user.
 * Store use status to choose the interface to show. As the result, status control is very important here.
 * If you can understand the code here, you will have great work on the above two class.
 * The detail of Store is in the README
 */
class Store {
private:
    enum UMode {USER, MANAGER} userStatus;
    enum SMode {OPENING, DECIDING, SHOPPING, CART_CHECKING, CHECK_OUT, MANAGING, CLOSE} storeStatus;
    CommodityList commodityList;
    ShoppingCart cart;
    int judge;



    void commodityInput() {
        cout << "Which type of commodity you want to add?" << endl;
        cout << "1.Snacks 2.Clothes 3.Apps"<<endl;
        cin>>judge;
        int price;
        shopping *newshop;
        string commodityName;
        string description;
        int weight;
        int calories;
        int saveday;
        string material;
        string size;
        string color;
        string use;
        string classification;
        string system;
        if(judge==1){
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
            cout << "Please input the snack Weight:" << endl;
            weight=InputHandler::numberInput();
            cout << "Please input the snack Calories:" << endl;
            calories=InputHandler::numberInput();
            cout << "Please input the snack saveday:" << endl;
            saveday=InputHandler::numberInput();
            newshop =new shopping(commodityName,price,description,weight,calories,saveday);
            if (commodityList.isExist(1,newshop)) {//!=0 would happen
                cout << "[WARNING] " << newshop->getName()<< " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else {
                commodityList.add(1,newshop);
            }
        }
        if(judge==2){
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
            cout << "Please input the clothes material:" << endl;
            material=InputHandler::readWholeLine();
            cout << "Please input the clothes size:" << endl;
            size=InputHandler::readWholeLine();
            cout << "Please input the clothes color's type:" << endl;
            color=InputHandler::readWholeLine();
            newshop=new shopping(1,commodityName,price,description,material,size,color);
            if (commodityList.isExist(2,newshop)) {//!=0 would happen
                cout << "[WARNING] " << newshop->getName()<< " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else{
                commodityList.add(2,newshop);
            }
        }
        if(judge==3){
            cout << "Please input the commodity name:" << endl;
            commodityName = InputHandler::readWholeLine();
            cout << "Please input the commodity price:" << endl;
            price = InputHandler::numberInput();
            cout << "Please input the detail of the commodity:" << endl;
            description = InputHandler::readWholeLine();
            cout << "Please input the App use:" << endl;
            use=InputHandler::readWholeLine();
            cout << "Please input the App classification:" << endl;
            classification=InputHandler::readWholeLine();
            cout << "Please input the App system:" << endl;
            system=InputHandler::readWholeLine();
            newshop=new shopping(2,commodityName,price,description,use,classification,system);
            if (commodityList.isExist(3,newshop)) {//!=0 would happen
                cout << "[WARNING] " << newshop->getName()<< " is exist in the store. If you want to edit it, please delete it first" << endl;
            }
            else {
                commodityList.add(3,newshop);
            }
        }
    }

    /*
     * You should finish this method, because you need to identify the type of commodity, and instantiate a
     * corresponding derived commodity class here.
     */

    void deleteCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        int choice;
        cout << "There are existing commodity in our store:" << endl;
        commodityList.showCommoditiesName();
        cout << "Or type 0 to regret" << endl
             << "Which one do you want to delete?" << endl;

        choice = InputHandler::getInput(commodityList.getsize());
        if (choice != 0) {
            commodityList.remove(choice - 1);
        }
    }

    void showCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        cout << "Here are all commodity in our store:" << endl;
        commodityList.showCommoditiesDetail();
        cout << endl;
    }

    void askMode() {
        int ask=0;
        string input;
        if(ask==0) {
            commodityList.loaddata();
            ask++;
        }
        cout << "Are you a general user or a manager?" << endl
             << "1. general user, 2. manager" << endl
             << "Or type 0 to close the store" << endl;

        int choice = InputHandler::getInput(2);

        userStatus = (choice == 2) ? UMode::MANAGER : UMode::USER;

        if (choice == 0) {
            storeStatus = SMode::CLOSE;
        } else if (userStatus == UMode::USER) {
            storeStatus = SMode::DECIDING;
        } else if (userStatus == UMode::MANAGER) {
            storeStatus = SMode::MANAGING;
        }
    }

    void decideService() {
        string input;

        cout << "Below are our service:" << endl
             << "1. Buy the commodity you want" << endl
             << "2. Check your shopping cart" << endl
             << "3. Check out" << endl
             << "Or type 0 to exit user mode" << endl
             << "You may choose what you need:" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            storeStatus = SMode::SHOPPING;
        } else if (choice == 2) {
            storeStatus = SMode::CART_CHECKING;
        } else if (choice == 3) {
            storeStatus = SMode::CHECK_OUT;
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void chooseCommodity() {
        string input;
        showCommodity();
        cout << "Or input 0 to exit shopping" << endl;

        int choice = InputHandler::getInput(commodityList.getsize());

        // Push the commodity into shopping cart here
        if (choice == 0) {
            storeStatus = SMode::DECIDING;
        } else {
            // May be some bug here, test later
            cart.push(commodityList.get(choice - 1));
        }
    }

    void showCart() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty" << endl;
            storeStatus = SMode::DECIDING;
            return;
        }

        int choice;
        do {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();

            cout << "Do you want to delete the entry from the cart?" << endl
                 << "1. yes, 2. no" << endl;

            choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                     << "Or type 0 to regret" << endl;
                int index = InputHandler::getInput(cart.size());
                // **
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
             << "1. yes, 2. No, I want to buy more" << endl;
        choice = InputHandler::getInput(2, true);
        if (choice == 1) {
            storeStatus = SMode::CHECK_OUT;
        } else {
            storeStatus = SMode::DECIDING;
        }
    }

    void checkOut() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty, nothing can checkout" << endl;
        } else {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout << "Are you sure you want to buy all of them?" << endl
                 << "1. Yes, sure, 2. No, I want to buy more" << endl;

            int choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                int amount = cart.checkOut();
                cout << "Total Amount: " << amount << endl;
                cout << "Thank you for your coming!" << endl;
                cout << "------------------------------" << endl << endl;
            }
        }

        storeStatus = SMode::DECIDING;
    }

    void managerInterface() {
        cout << "Here are some manager services you can use:" << endl
             << "1. Add new commodity" << endl
             << "2. Delete commodity from the commodity list" << endl
             << "3. Show all existing commodity" << endl
             << "Or type 0 to exit manager mode" << endl
             << "Which action do you need?" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            commodityInput();
        } else if (choice == 2) {
            deleteCommodity();
        } else if (choice == 3) {
            showCommodity();
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void userInterface() {
        if (storeStatus == SMode::OPENING) {
            askMode();
        } else if (storeStatus == SMode::DECIDING) {
            decideService();
        } else if (storeStatus == SMode::SHOPPING) {
            chooseCommodity();
        } else if (storeStatus == SMode::CART_CHECKING) {
            showCart();
        } else if (storeStatus == SMode::CHECK_OUT) {
            checkOut();
        } else if (storeStatus == SMode::MANAGING) {
            managerInterface();
        } else if (storeStatus == SMode::CLOSE) {
            return;
        }
    }

public:
    Store() {
        userStatus = UMode::USER;
        storeStatus = SMode::CLOSE;
    }

    void open() {
        storeStatus = SMode::OPENING;
        while (storeStatus != SMode::CLOSE) {
            userInterface();
        }
        commodityList.save();
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}