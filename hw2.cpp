#include <iostream>
#include <string>
#include<stdio.h>

using namespace std;

class Commodity;
class Store;


/*
 * The function is used to read a full line into a string variable
 * INPUT: None
 * RETURN: Full line input by user
 * */
string readWholeLine() {
    string input;
    cin.get();
    getline(cin, input);
    return input;
}

/*
 * This function is used to configure whether the input string is a number
 * INPUT: A string
 * RETURN: Bool. True if input string is a number, otherwise false.
 */
bool isNum(string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

/*
 * Commodity is about an item which the user can buy and the manager can add or delete.
 * ATTRIBUTE:
 *  price: The price of the commodity, an integer.
 *  description: The text which describe the commodity detail, a string.
 *  commodityName: The name of the commodity, a string.
 */
class Commodity {
protected:
    int price;
    string description;
    string commodityName;
public:
    Commodity *ptr;
    int number;
    ~Commodity()=default;
    Commodity() {
        price = 0;
        description = "";
        commodityName = "";
    }

    Commodity(int price, string commodityName, string description) {
        this->price = price;
        this->commodityName = commodityName;
        this->description = description;
        this->number=1;
    }

    /*
     * This method will show the full information of the commodity to user interface.
     * There is a overloading version, with an argument amount which will output the information with the amount
     * INPUT: None, or an integer specify the amount of this commodity
     * RETURN: None
     */
    void detail() {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;
    }

    void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

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
};

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * This is a list storing the existing commodity in the store.
 * There are some method which can modify the content.
 * You may use any data structure to complete this class.
 */
class CommodityList {
private:
    int detectcomnum=0;
    int num=0;
    Commodity *ptr;
    Commodity *head=NULL;
    Commodity *x;
    Commodity *y; 
    Commodity *addx;
    Commodity *addy;
public:
    /*
     * Print the full information of the commodities inside the list
     * You must call Commodity.detail() to show the commodity information.
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesDetail() {
        y=head;
        num=0;
        while(y!=NULL){
            num++;
            cout<<num<<" ."<<endl;
            y->detail();
            y=y->ptr;
        }
    }

    /*
     * Print only the commodity name of the commodities inside the list
     * You don't need to use Commodity.detail() here, just call the Commodity.getName() function is ok
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesName() {
        y=head;
        num=0;
        while (y->ptr!=NULL){
            num++;
            cout<<num<<" ."<<y->getName()<<endl;
            y=y->ptr;
        }
        if(y->ptr==NULL){
            num++;
            cout<<num<<" ."<<y->getName()<<endl;
        }
    }

    /*
     * Check whether the list is empty or not
     * INPUT: None
     * RETURN: Bool. True if the list is empty, otherwise false
     */
    bool empty() {
        bool realdetect;
        y=head;
        num=0;
        while(y!=NULL){
            y=y->ptr;
            num++;
        }
        if(num==0){
        realdetect=true;
        }
        else{
            realdetect=false;
        }
        return realdetect;
    }

    /*
     * Return the size(or length) of the list
     * INPUT: None
     * RETURN: Integer. List size
     */
    int size() {
        y=head;
        num=0;
        while(y!=NULL){
            y=y->ptr;
            num++;
        }
        return  num;
    }

    /*
     * Return a commodity object at specified position
     * INPUT: Integer. The index of that commodity
     * RETURN: Commodity. The wanted commodity object
     */
    Commodity get(int index) {
        y=head;
        for(int i=0;i<index;i++){
            y=y->ptr;
        }
        return *y;
    }

    /*
     * Push a new commodity object into the list
     * INPUT: Commodity. The object need to be pushed
     * RETURN: None
     */
    void add(Commodity *newCommodity) {
        if(detectcomnum==0){
            head=newCommodity;
            addx=head;
            detectcomnum++;
        }
        else if (detectcomnum!=0){
            addx->ptr=newCommodity;
            addx=newCommodity;
            detectcomnum++;
        }
    }

    /*
     * Check the input commodity object is existing inside the list
     * If the commodity name is the same, we take those objects the same object
     * INPUT: Commodity. The object need to be checked
     * OUTPUT: Bool. True if the object existing, otherwise false
     */
    bool isExist(Commodity* commodity) {
        int detect=0;
        bool realdetect;
        int no=0;
        no++;
        y=head;
        if(no!=0){
            while(y!=NULL){
                if(commodity->getName()==y->getName()){
                    detect++;
                }
                    y=y->ptr;
            }
            if(detect!=0){
                realdetect=true;
            }
        }
        if(no==0||detect==0){
            realdetect=false;
        }
        return realdetect;
    }

    /*
     * Remove an object specified by the position
     * INPUT: Integer. The position of the object which need to be removed
     * OUTPUT: None
     */
    void remove(int index) {
        y=head;
        x=head;
        for(int i=0;i<index;i++){
            y=y->ptr;
        }
        for(int j=0;j<index-1;j++){
            x=x->ptr;
        }
        if(index==0){
            head=head->ptr;
            y->ptr=NULL;
        }
        x->ptr=y->ptr;
        detectcomnum--;
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
    Commodity *head;
    Commodity *x;
    Commodity *y;
    Commodity *addx;
    Commodity *ptr;
    Commodity *cart;
    int detect=0;
    int num;
    int commoditytype=0;
    int detection=0;
    int detect1=0;
public:

    /*
     * Push an commodity object into the cart.
     * Be careful that if the input object is existing in the list, then keep the amount of that object rather than
     * actually push the object into the cart.
     * INPUT: Commodity. The object need to be pushed.
     * OUTPUT: None.
     */
    void push(Commodity entry) { 
        if(detect>0){//Push but not the first one
            y=head;
            addx=head;
            detect1=0;
            while(y!=NULL){
                cart =new Commodity(entry.getPrice(),entry.getName(),entry.getdescription());
                if(y->getName()==cart->getName()){
                     y->number++;
                     return;
                }
                if(y->getName()!=cart->getName()){
                    y=y->ptr;
                    detect1++;
                }
            }
            if(y==NULL){
                for(int i=0;i<detect1-1;i++){
                    addx=addx->ptr;
                }
                addx->ptr=cart;
                addx=cart;
                detect++;
            }
        }
        if(detect==0){//Push the first one
            detect++;
            cart =new Commodity(entry.getPrice(),entry.getName(),entry.getdescription());
            head=cart;
        }

    }
    /*
     * Show the content of the cart to user interface.
     * INPUT: None.
     * OUTPUT: None.
     */
    void showCart() {
        y=head;
        num=0;
        while(y!=NULL){
            num++;
            cout<<num<<" ."<<endl;
            y->detail(y->number);
            y=y->ptr;
        }
    }

    /*
     * Return the cart size. (The same object must be seen as one entry)
     * INPUT: None.
     * OUTPUT: Integer. The cart size.
     */
    int size() {
        y=head;
        num=0;
        while(y->ptr!=NULL){
            num++;
            y=y->ptr;
        }
        if(y->ptr==NULL){
            num++;
        }
        return num;
    }

    /*
     * Remove an entry from the cart. Don't care about the amount of the commodity, just remove it.
     * INPUT: The order of the entry.
     * OUTPUT: None.
     */
    void remove(int index) {
        y=head;
        x=head;
        for(int i=0;i<index;i++){
            y=y->ptr;
        }
        for(int j=0;j<index-1;j++){
            x=x->ptr;
        }
        if(index==0){
            head=head->ptr;
            y->ptr=NULL;
        }
        else{
            x->ptr=y->ptr;
        }
        detect--;
    }

    /*
     * Check the total amount of price for the user.
     * Remember to clear the list after checkout.
     * INPUT: None.
     * OUTPUT: Integer. The total price.
     */    
    // void LinkListClear(){
    //     y=head;
    //     x=head;
    //     while(y!=NULL){
    //         x=y;
    //         y=y->ptr;
    //         ~Commodity();
    //         x=0;
    //         detect--;
    //     }
    // }
    int checkOut() {
        int sum=0;
        y=head;
        x=head;
        
        while(y!=NULL){
            sum=sum+y->getPrice()*y->number;
            y=y->ptr;
        }
        head=NULL;
        detect=0;
        // y=head;
        // x=head;
        // LinkListClear();
        return sum;
    }

    /*
     * Check if the cart have nothing inside.
     * INPUT: None.
     * OUTPUT: Bool. True if the cart is empty, otherwise false.
     */
    bool empty() {
       bool realdetect;
        if(detect==0){
            realdetect=true;
        }
        else{
            realdetect=false;
        }
        return realdetect;
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

    bool isValidNum(string& str) {
        if (isNum(str) && stoi(str) <= 0)
            return false;
        return true;
    }

    int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    int inputCheck(string input, int maxChoiceLen, bool noZero) {
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

    int getInput(int maxChoiceLen, bool noZero = false) {
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

    void commodityInput() {
        string name, detail;
        int price;
        Commodity* newCom;

        cout << "Please input the commodity name:" << endl;
        name = readWholeLine();
        cout << "Please input the commodity price:" << endl;
        price = numberInput();
        cout << "Please input the detail of the commodity:" << endl;
        detail = readWholeLine();
        newCom = new Commodity(price, name, detail);
        if (commodityList.isExist(newCom)) {//!=0 would happen
            cout << "[WARNING] " << name << " is exist in the store. If you want to edit it, please delete it first" << endl;
        } else {//=0 would happen
            commodityList.add(newCom);
        }
    }

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

        choice = getInput(commodityList.size());

        if (choice != 0) {
            commodityList.remove(choice-1);
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
        string input;

        cout << "Are you a general user or a manager?" << endl
             << "1. general user, 2. manager" << endl
             << "Or type 0 to close the store" << endl;

        int choice = getInput(2);

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

        int choice = getInput(3);

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

        int choice = getInput(commodityList.size());

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

            choice = getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                     << "Or type 0 to regret" << endl;
                int index = getInput(cart.size());
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
             << "1. yes, 2. No, I want to buy more" << endl;
        choice = getInput(2, true);
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

            int choice = getInput(2, true);

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

        int choice = getInput(3);

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
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}
