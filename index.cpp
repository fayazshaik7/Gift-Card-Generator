#include<iostream>
#include<bits/stdc++.h>
#define TRANSACTIONS_SIZE 1000
#define MAX_CUSTOMERS 10
#define TOTAL_GIFT_CARDS 100
#define MAX_CARDS 300
using namespace std;

long Total_Customers = 3;
long gift_card_number = 11111;
long gift_card_pin = 1001;
long Local_card_count = 0;

struct Gift_card{
	long Gift_card_number;
	long Gift_card_pin;
	double Balance;
	int Reward_points;
	bool Status;
	long Transaction_count_credit = 0;
	long Transaction_count_debit = 0;
	long Transaction_count_reward = 0;
    long Transactions[3][TRANSACTIONS_SIZE];
}*Local_cards[MAX_CARDS];

struct Customer{
	long customer_id;
	long Account_number;
	string Name;
	double Balance;
	string Password;
	long Gift_card_count = 0;
	struct Gift_card *Gift_cards[TOTAL_GIFT_CARDS];
}Customers[MAX_CUSTOMERS];


void Initialize_data(){
	Customers[0].customer_id = 11;
	Customers[1].customer_id = 22;
	Customers[2].customer_id = 33;

	Customers[0].Account_number = 11011;
	Customers[1].Account_number = 22022;
	Customers[2].Account_number = 33033;

	Customers[0].Name = "Kumar";
	Customers[1].Name = "Madhu";
	Customers[2].Name = "Robin";

	Customers[0].Balance = 10000.0;
	Customers[1].Balance = 20000.0;
	Customers[2].Balance = 30000.0;

	Customers[0].Password = "Apipmbjm";
	Customers[1].Password = "Cvoljoh";
	Customers[2].Password = "bbbbbb";
}

int User_options(){
	int option;
	cout<<"1.Account Login "<<endl;
	cout<<"2.Purchase "<<endl;
	cout<<"Select the option : ";
	cin>>option;
	return option;
}

int Password_validator(string Entered_password,string Actual_password){
	if(Entered_password.length()!=Actual_password.length())
		return 0;
	for(int index = 0 ; index < Entered_password.length() ; index++){
		if(Entered_password[index]>='0'&&Entered_password[index]<='9'){
            int encode = ((Entered_password[index] - '0')+1)%10;
            int decode = (Actual_password[index]-'0');
            if(encode!=decode)
                return 0;
		}
		else if(Entered_password[index]>='a'&&Entered_password[index]<='z'&&Actual_password[index]>='a'&&Entered_password[index]<='z'){
            int encode = ((Entered_password[index] - 'a')+1)%26;
            int decode = (Actual_password[index]-'a');
            if(encode!=decode)
                return 0;
		}
		else if(Entered_password[index]>='A'&&Entered_password[index]<='Z'&&Actual_password[index]>='A'&&Entered_password[index]<='Z'){
            int encode = ((Entered_password[index] - 'A')+1)%26;
            int decode = (Actual_password[index]-'A');
            if(encode!=decode)
                return 0;
		}
		else
            return 0;
	}
	return 1;
}

void Create_gift_card(long Customer_id,int Customer_index){
    int add_amount;
    cout<<"Enter amount to add in the gift card : ";
    cin>>add_amount;
    if(add_amount>Customers[Customer_index].Balance)
        cout<<"Insufficient amount in your account !!!"<<endl;
    else{
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count] = (struct Gift_card *)malloc(sizeof(Gift_card));
        Local_cards[Local_card_count++] = Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count];
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Gift_card_number = gift_card_number++;
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Gift_card_pin = gift_card_pin++;
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Balance = add_amount;
        Customers[Customer_id].Balance -= add_amount;
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Reward_points = 0;
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Status = true;
        Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Transactions[0][Customers[Customer_index].Gift_cards[Customers[Customer_index].Gift_card_count]->Transaction_count_credit++]=add_amount;
        Customers[Customer_index].Gift_card_count++;
        cout<<"\t\t*New gift card Created*"<<endl;
        cout<<"New gift card number : "<<gift_card_number-1<<endl;
        cout<<"New gift card pin : "<<gift_card_pin-1<<endl;
    }
}

void Topup_gift_card(long Customer_id,int Customer_index){
    if(Customers[Customer_index].Gift_card_count==0){
        cout<<"No gift cards are available with your account!!!"<<endl;
        return;
    }
    long temp_gift_card_number,temp_gift_card_pin;
    cout<<"Enter gift card number : ";
    cin>>temp_gift_card_number;
    cout<<"Enter gift card pin : ";
    cin>>temp_gift_card_pin;
    for(int index = 0 ; index < Customers[Customer_index].Gift_card_count;index++){
        if(Customers[Customer_index].Gift_cards[index]->Gift_card_number == temp_gift_card_number && Customers[Customer_index].Gift_cards[index]->Gift_card_pin == temp_gift_card_pin && Customers[Customer_index].Gift_cards[index]->Status){
            int add_amount;
            cout<<"Enter amount to add : ";
            cin>>add_amount;
            if(add_amount>Customers[Customer_index].Balance)
                cout<<"Insufficient amount in your account !!!\n\n"<<endl;
            else{
                Customers[Customer_index].Gift_cards[index]->Balance+=add_amount;
                Customers[Customer_index].Gift_cards[index]->Transactions[0][Customers[Customer_index].Gift_cards[index]->Transaction_count_credit++] = add_amount;
                Customers[Customer_index].Balance-=add_amount;
                cout<<"Topup added "<<endl;
            }
            return;
        }
        //cout<<Customers[Customer_index].Gift_cards[index]->Balance<<endl;

    }
    cout<<"\t\t*Card not found*"<<endl;
    return;
}

void Display_Transactions(int Customer_id,int Customer_index){
    if(Customers[Customer_index].Gift_card_count==0){
        cout<<"No gift cards are available with your account!!!"<<endl;
        return;
    }
    long temp_gift_card_number,temp_gift_card_pin;
    cout<<"Enter gift card number : ";
    cin>>temp_gift_card_number;
    cout<<"Enter gift card pin : ";
    cin>>temp_gift_card_pin;
    for(int index = 0 ; index < Customers[Customer_index].Gift_card_count;index++){
        if(Customers[Customer_index].Gift_cards[index]->Gift_card_number == temp_gift_card_number && Customers[Customer_index].Gift_cards[index]->Gift_card_pin == temp_gift_card_pin && Customers[Customer_index].Gift_cards[index]->Status){
            cout<<"\t\t**credited Transactions**"<<endl;
            for(int index1 = 0 ; index1 < Customers[Customer_index].Gift_cards[index]->Transaction_count_credit;index1++){
                cout<<"["<<index1+1<<"] "<<Customers[Customer_index].Gift_cards[index]->Transactions[0][index1]<<endl;
            }
            cout<<"\t\t**debited Transactions**"<<endl;
            for(int index1 = 0 ; index1 < Customers[Customer_index].Gift_cards[index]->Transaction_count_debit;index1++){
                cout<<"["<<index1+1<<"] "<<Customers[Customer_index].Gift_cards[index]->Transactions[1][index1]<<endl;
            }
            cout<<"\t\t**rewarded Transactions**"<<endl;
            for(int index1 = 0 ; index1 < Customers[Customer_index].Gift_cards[index]->Transaction_count_reward;index1++){
                cout<<"["<<index1+1<<"] "<<Customers[Customer_index].Gift_cards[index]->Transactions[2][index1]<<endl;
            }
            return;
        }
    }
    cout<<"\t\t*Card Not found*"<<endl;
}


void Block_gift_card(long Customer_id,int Customer_index){
    if(Customers[Customer_index].Gift_card_count==0){
        cout<<"No gift cards are available with your account!!!"<<endl;
        return;
    }
    long temp_gift_card_number,temp_gift_card_pin;
    cout<<"Enter gift card number : ";
    cin>>temp_gift_card_number;
    cout<<"Enter gift card pin : ";
    cin>>temp_gift_card_pin;
    for(int index = 0 ; index < Customers[Customer_index].Gift_card_count;index++){
        if(Customers[Customer_index].Gift_cards[index]->Gift_card_number == temp_gift_card_number && Customers[Customer_index].Gift_cards[index]->Gift_card_pin == temp_gift_card_pin && Customers[Customer_index].Gift_cards[index]->Status){
            Customers[Customer_index].Gift_cards[index]->Status = false;
            cout<<"*Card blocked*"<<endl;
            return;
        }
    }
    cout<<"\t\t*Card not found*"<<endl;
}

void Gift_card_options(long Customer_id,int Customer_index){
    while(1){
        cout<<"1.Create a new gift card"<<endl;
        cout<<"2.Topup the existing gift card"<<endl;
        cout<<"3.Show gift card transaction history"<<endl;
        cout<<"4.Block the existing card"<<endl;
        cout<<"5.Logout"<<endl;
        cout<<"Enter an option : ";
        int option;
        cin>>option;
        switch(option){
            case 1:{
                Create_gift_card(Customer_id,Customer_index);
                break;
            }
            case 2:{
                Topup_gift_card(Customer_id,Customer_index);
                break;
            }
            case 3:{
                Display_Transactions(Customer_id,Customer_index);
                break;
            }
            case 4:{
                Block_gift_card(Customer_id,Customer_index);
                break;
            }
            case 5:{
                return;
            }
        }
    }

}

void Account_Login(){
	long Customer_id;
	string Password;
	cout<<"Customer Id : ";
	cin>>Customer_id;
	cout<<"Password : ";
	cin>>Password;
	for(int index = 0;index < Total_Customers;index++){
		if(Customers[index].customer_id == Customer_id && Password_validator(Password,Customers[index].Password)){
			cout<<"\t\tLogin Successful!!!"<<endl;
			Gift_card_options(Customers[index].customer_id,index);
			return;
		}
	}
	cout<<"\t\tLogin Failed!!!"<<endl;
	return;
}


void Add_reward_credit(int points,int gift_card_number,int gift_card_index){
    if(points<10)
        return;
    Local_cards[gift_card_index]->Balance = (points/10)*10;
    Local_cards[gift_card_index]->Reward_points%=10;
    Local_cards[gift_card_index]->Transactions[2][Local_cards[gift_card_index]->Transaction_count_reward++] = (points/10)*10;
    return;
}

void Purchase(){
    cout<<"\t\t***Billing***"<<endl;
    int bill_amount;
    cout<<"Enter billing amount : ";
    cin>>bill_amount;
    long temp_gift_card_number,temp_gift_card_pin;
    cout<<"Enter gift card number : ";
    cin>>temp_gift_card_number;
    cout<<"Enter gift card pin : ";
    cin>>temp_gift_card_pin;
    for(int index = 0 ; index < Local_card_count ; index++){
        if(Local_cards[index]->Gift_card_number == temp_gift_card_number){
            if(Local_cards[index]->Gift_card_pin == temp_gift_card_pin){
                if(Local_cards[index]->Status == true){
                    if(Local_cards[index]->Balance>bill_amount){
                        Local_cards[index]->Balance-=bill_amount;
                        Local_cards[index]->Transactions[1][Local_cards[index]->Transaction_count_debit++] = bill_amount;
                        Local_cards[index]->Reward_points = bill_amount/100;
                        Add_reward_credit(Local_cards[index]->Reward_points,temp_gift_card_number,index);
                        cout<<"\t\t**purchase Successful**"<<endl;
                        return;

                    }
                    else{
                        cout<<"\t\t**Insufficient amount**"<<endl;
                    }
                }
                else{
                    cout<<"\t\t**card is not active**"<<endl;
                }
            }
            else{
                cout<<"\t\t**wrong password**"<<endl;
            }
        }
        else{
            cout<<"\t\t**Card not found**"<<endl;
        }
    }
}

int main(){
	Initialize_data();
	while(1){
	int option = User_options();
	switch(option){
		case 1:{
			Account_Login();
			break;
		}
		case 2:{
            Purchase();
            break;
		}
	}
	}

}
