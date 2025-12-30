#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#define SIZE 1000
using namespace std;
char a;
int hashing(string s){
    int idx=0;
    int p=31,c=0;
    for(auto i:s){
        idx=idx*p+c;
        idx%=SIZE;
    }
    return idx;
}
class block{
  protected:
    string name;
    string id;
    vector<string> ip,op,param;
    //block* p;
  public:
    block(string name="",string id="",vector<string> ip=vector<string>(),vector<string> op=vector<string>(),vector<string> param=vector<string>()){
        this->name=name;
        this->id=id;
        this->ip=ip;
        this->op=op;
        this->param=param;
    }
    string getName(){
        return name;
    }
    string getId(){
        return id;
    }
    vector<string> getIp(){
        return ip;
    }
    vector<string> getOp(){
        return op;
    }
    vector<string> getParam(){
        return param;
    }
    void setIp(string s){
        ip.push_back(s);
    }
    void setOp(string s){
        op.push_back(s);
    }
    void setParam(string s){
        param.push_back(s);
    }
    void setName(string s){
        name=s;
    }
    void setId(string s){
        id=s;
    }
    void clearIp(){
        ip.clear();
    }
    void clearOp(){
        op.clear();
    }
    void clearParam(){
        param.clear();
    }
    ~block(){   
        name.clear();
        id.clear();
        ip.clear();
        op.clear();
        param.clear();
    }
};
class mapId{
  private:
    
  public:
    vector<pair<string,block*>> table[SIZE];
    mapId(){
        for(int i=0;i<SIZE;i++) table[i].clear();
    }
    void insert(block* b){
        int idx=hashing(b->getId());
        table[idx].push_back({b->getId(),b});
    }
    block* searchId(string id){
        int idx=hashing(id);
        for(auto p:table[idx]){
            if(p.first==id) return p.second;
        }
        return nullptr;
    }
    void remove(string id){
        int idx=hashing(id);
        for(int i=0;i<=table[idx].size();i++){
            if(table[idx][i].first==id){
                table[idx].erase(table[idx].begin()+i);
                return;
            }
        }
    }
    ~mapId(){
        for(int i=0;i<SIZE;i++){
            table[i].clear();
        }
    }
};
class mapName{
  private:
    vector<pair<string,block*>> table[SIZE];
  public:
    mapName(){
        for(int i=0;i<SIZE;i++) table[i].clear();
    }
    void insert(block* b){
        int idx=hashing(b->getName());
        table[idx].push_back({b->getName(),b});
    }
    block* searchName(string name){
        int idx=hashing(name);
        for(auto p:table[idx]){
            if(p.first==name) return p.second;
        }
        return nullptr;
    }
    void remove(string name){
        int idx=hashing(name);
        for(int i=0;i<=table[idx].size();i++){
            if(table[idx][i].first==name){
                table[idx].erase(table[idx].begin()+i);
                return;
            }
        }
    }
    ~mapName(){
        for(int i=0;i<SIZE;i++){
            table[i].clear();
        }
    }
};
mapId idMap;
mapName nameMap;
void menu0();
void menu2();
void menu3();
void menu4();
void menu5();
void menu();
void menu1();
void menu1(){
    block* newBlock=new block();
    string id,name;
    vector<string> ip,op,param;
    int n,dem=1;
    system("cls");
    cout << "nhập id" << endl ;
    cin >> id ;
    newBlock->setId(id);
    cout << "nhập tên" << endl ;
    cin.ignore(10, '\n');
    getline(cin,name);
    newBlock->setName(name);
    cout << "nhập số input: " ;
    cin >> n ;
    cout << endl ;
    while(dem<=n){
        string ipd;
        cout << "nhập input " << dem++ << ": " ;
        cin.ignore(10, '\n');
        getline(cin,ipd);
        //cout << endl ;
        newBlock->setIp(ipd);
    }
    cout << "nhập số output: " ;
    cin >> n ;
    cout << endl ;
    dem=1;
    while(dem<=n){
        string opd;
        cout << "nhập output " << dem++ << ": " ;
        cin.ignore(10, '\n');
        getline(cin,opd);
        //cout << endl ;
        newBlock->setOp(opd);
    }
    cout << "nhập số param: " ;
    cin >> n ; 
    cout << endl ;
    dem=1;
    while(dem<=n){
        string pard;
        cout << "nhập param " << dem++ << ": " ;
        cin.ignore(10, '\n');
        getline(cin,pard);
        //cout << endl ;
        newBlock->setParam(pard);
    }
    idMap.insert(newBlock);
    nameMap.insert(newBlock);
    menu(); 
}
bool menu(){
    system("cls");
    cout << "=========MENU=========" << endl ;
    cout << "0.nhập file block" << endl ;
    cout << "1.thêm block" << endl ;
    cout << "2.sửa block" << endl ;
    cout << "3.xóa block" << endl ;
    cout << "4.xem danh sách block" << endl ;
    cout << "5.tìm kiếm block" << endl ;
    cout << "6.thoát chương trình" << endl ;
    //thêm chức năng khác ở đây
    cout << "======================" << endl ;
    cout << "nhập lựa chọn của bạn: " ;
    a=getch();
    switch(a){
        case '0':{
            menu0();
        }
        case '1':{
            menu1();
        }
        case '2':{
            menu2();
        }
        case '3':{
            menu3();
        }
        case '4':{
            menu4();
        }
        case '5':{
            menu5();
        }
        case '6':{
            //exit(0);
            return False;
        }
        default: 
            menu();
    }
}
void menu0(){
    system("cls");
    cout << "=========NHẬP FILE=========" << endl ;
    cout << "nhập tên file cần đọc: " ;
    string filename;
    cin >> filename ;
    ifstream filein;
    filein.open(filename);
    if(!filein.is_open()){
        system("cls");
        cout << "không thể mở file: " << filename ;
        Sleep(2000);
        menu();
    }
    string s;
    int dem=1,sli=-1,slo=-1,slp=-1;
    block* newBlock=new block();
    while (getline(filein, s)) {  
        switch(dem){
            case 1:{ // id
                newBlock=new block();
                newBlock->setId(s);
                dem++;
                break;
            }
            case 2:{ // name
                newBlock->setName(s);
                dem++;
                break;
            }
            case 3:{ // input
                if(s[0]>='0' && s[0]<='9'){
                    sli=stoi(s);
                    if(sli==0){
                        dem++;
                    }
                    break;
                }
                if(sli>0){
                    newBlock->setIp(s);
                    sli--;
                    //break;
                }
                if(sli==0){
                    dem++;
                    break;
                }
            }
            case 4:{ // output
                if(s[0]>='0' && s[0]<='9'){
                    slo=stoi(s);
                    if(slo==0){
                        dem++;
                    }
                    break;
                }
                if(slo>0){
                    newBlock->setOp(s);
                    slo--;
                    //break;
                }
                if(slo==0){
                    dem++;
                    break;
                }
            }
            case 5:{ // param
                if(s[0]>='0' && s[0]<='9'){
                    slp=stoi(s);
                    if(slp==0){
                        dem=1;
                        idMap.insert(newBlock);
                        nameMap.insert(newBlock);
                    }
                    break;
                }
                if(slp>0){
                    newBlock->setParam(s);
                    slp--;
                    //break;
                }
                if(slp==0){
                    dem=1;
                    idMap.insert(newBlock);
                    nameMap.insert(newBlock);
                    break;
                }
            }
        }
    }
    filein.close();
    menu();
}
void menu2(){
    system("cls");
    cout << "=========SỬA BLOCK=========" << endl ;
    cout << "0.quay về menu chính" << endl ;
    cout << "1.sửa theo id" << endl ;
    cout << "2.sửa theo name" << endl ;
    cout << "===========================" << endl ;
    cout << "nhập lựa chọn của bạn: " ;
    a=getch();
    system("cls");
    switch(a){
        case '0':{
            menu();
        }
        case '1':{
            string id;
            cout << "nhập id cần sửa: " ;
            cin >> id ;
            block* b=idMap.searchId(id);
            if(b!=nullptr){
                cout << "id: " << b->getId() << endl ;
                cout << "tên: " << b->getName() << endl ;
                for( auto s:b->getIp() ){
                    cout << "input: " << s << endl ;
                }
                for( auto s:b->getOp() ){
                    cout << "output: " << s << endl ;
                }
                for( auto s:b->getParam() ){
                    cout << "param: " << s << endl ;
                }
                string newId;
                cout << "nhập id mới: " ;
                cin >> newId ;
                cout << endl ;
                b->setId(newId);
                string newName;
                cout << "nhập tên mới: " ;
                cin.ignore(10, '\n');
                getline(cin,newName) ;
                //cout << endl ;
                b->setName(newName);
                int n,dem=1;
                cout << "nhập số input mới: " ;
                cin >> n ;
                cout << endl ;
                b->clearIp();
                while(dem<=n){
                    string ipd;
                    cout << "nhập input mới " << dem++ << ": " ;
                    cin.ignore(10, '\n');
                    getline(cin,ipd);
                    //cout << endl ;
                    b->setIp(ipd);
                }
                cout << "nhập số output mới: " ;
                cin >> n ;
                cout << endl ;
                dem=1;
                b->clearOp();
                while(dem<=n){
                    string opd;
                    cout << "nhập output mới " << dem++ << ": " ;
                    cin.ignore(10, '\n');
                    getline(cin,opd);
                    //cout << endl ;
                    b->setOp(opd);
                }
                cout << "nhập số param mới: " ;
                cin >> n ;
                cout << endl ;
                dem=1;
                b->clearParam();
                while(dem<=n){
                    string pard;
                    cout << "nhập param mới " << dem++ << ": " ;
                    cin.ignore(10, '\n');
                    getline(cin,pard);
                    //cout << endl ;
                    b->setParam(pard);
                }
            }
            else {
            system("cls");
            cout << "không tìm thấy block cần sửa" ;
            Sleep(2000);
            }
            break;
        }
        case '2':{
            string name;
            cout << "nhập tên cần sửa: " ;
            cin.ignore(10, '\n');
            getline(cin,name);
            block* b=nameMap.searchName(name);
            if(b!=nullptr){
                if(b->getName()==name){
                    cout << "id: " << b->getId() << endl ;
                    cout << "tên: " << b->getName() << endl ;
                    for( auto s:b->getIp() ){
                        cout << "input: " << s << endl ;
                    }
                    for( auto s:b->getOp() ){
                        cout << "output: " << s << endl ;
                    }
                    for( auto s:b->getParam() ){
                        cout << "param: " << s << endl ;
                    }
                    string newId;
                    cout << "nhập id mới: " ;
                    cin >> newId ;
                    cout << endl ;
                    b->setId(newId);
                    string newName;
                    cout << "nhập tên mới: " ;
                    cin.ignore(10, '\n');
                    getline(cin,newName) ;
                    //cout << endl ;
                    b->setName(newName);
                    int n,dem=1;
                    cout << "nhập số input mới: " ;
                    cin >> n ;
                    cout << endl ;
                    b->clearIp();
                    while(dem<=n){
                        string ipd;
                        cout << "nhập input mới " << dem++ << ": " ;
                        cin.ignore(10, '\n');
                        getline(cin,ipd);
                        //cout << endl ;
                        b->setIp(ipd);
                    }
                    cout << "nhập số output mới: " ;
                    cin >> n ;
                    cout << endl ;
                    dem=1;
                    b->clearOp();
                    while(dem<=n){
                        string opd;
                        cout << "nhập output mới " << dem++ << ": " ;
                        cin.ignore(10, '\n');
                        getline(cin,opd);
                        //cout << endl ;
                        b->setOp(opd);
                    }
                    cout << "nhập số param mới: " ;
                    cin >> n ;
                    cout << endl ;
                    dem=1;
                    b->clearParam();
                    while(dem<=n){
                        string pard;
                        cout << "nhập param mới " << dem++ << ": " ;
                        cin.ignore(10, '\n');
                        getline(cin,pard);
                        //cout << endl ;
                        b->setParam(pard);
                    }
                }
            }
            else {
                system("cls");
                cout << "không tìm thấy block cần sửa" ;
                Sleep(2000);
            }
            break;
        }
        default:
            break;
    }
    menu2();
}
void menu5(){
    system("cls");
    cout << "=========TÌM KIẾM BLOCK=========" << endl ;
    cout << "0.quay về menu chính" << endl ;
    cout << "1.tìm kiếm theo id" << endl ;
    cout << "2.tìm kiếm theo name" << endl ;
    cout << "==============================" << endl ;
    cout << "nhập lựa chọn của bạn: ";
    a=getch();
    system("cls");
    switch(a){
        case '0':{
            menu();
        }
        case '1':{
            string id;
            cout << "nhập id cần tìm: ";
            cin >> id ;
            block* b=idMap.searchId(id);
            if(b!=nullptr){
                cout << "id: " << b->getId() << endl ;
                cout << "tên: " << b->getName() << endl ;
                for( auto s:b->getIp() ){
                    cout << "input: " << s << endl ;
                }
                for( auto s:b->getOp() ){
                    cout << "output: " << s << endl ;
                }
                for( auto s:b->getParam() ){
                    cout << "param: " << s << endl ;
                }
                cout << "---------------------------------" << endl ;
                cout << "nhấn phím bất kỳ để trở về menu tìm kiếm" << endl ;
                a=getch();
            }
            else {
                system("cls");
                cout << "không tìm thấy block " ;
                Sleep(2000);
            }
            menu5();
            //break;
        }
        case '2':{
            string name;
            cout << "nhập tên cần tìm: ";
            cin.ignore(10, '\n');
            getline(cin,name);
            block* b=nameMap.searchName(name);
            if(b!=nullptr){
                cout << "id: " << b->getId() << endl ;
                cout << "tên: " << b->getName() << endl ;
                for( auto s:b->getIp() ){
                    cout << "input: " << s << endl ;
                }
                for( auto s:b->getOp() ){
                    cout << "output: " << s << endl ;
                }
                for( auto s:b->getParam() ){
                    cout << "param: " << s << endl ;
                }
            }
            else {
                system("cls");
                cout << "không tìm thấy block" ;
                Sleep(2000);
            }
            menu5();
        }
        default:
            menu5();
    }
}
void menu4(){
    system("cls");
    cout << "=========DANH SÁCH BLOCK=========" << endl ;
    for(auto i: idMap.table){
        for(auto p:i){
            block* b=p.second;
            cout << "id: " << b->getId() << endl ;
            cout << "tên: " << b->getName() << endl ;
            for( auto s:b->getIp() ){
                cout << "input: " << s << endl ;
            }
            for( auto s:b->getOp() ){
                cout << "output: " << s << endl ;
            }
            for( auto s:b->getParam() ){
                cout << "param: " << s << endl ;
            }
            cout << "---------------------------------" << endl ;
        }
    }
    cout << "=================================" << endl ;
    cout << "nhấn phím bất kỳ để trở về menu chính" << endl ;
    a=getch();
    menu();
}
void menu3(){
    system("cls");
    cout << "=========XÓA BLOCK=========" << endl ;
    cout << "0.quay về menu chính" << endl ;    
    cout << "1.xóa theo id" << endl ;
    cout << "2.xóa theo name" << endl ;
    cout << "==========================" << endl ;
    cout << "nhập lựa chọn của bạn: ";
    a=getch();
    system("cls");
    switch(a){
        case '0':{
            menu();
        }
        case '1':{
            string id;
            cout << "nhập id cần xóa: ";
            cin >> id ;
            block* b=idMap.searchId(id);
            if(b!=nullptr){
                idMap.remove(id);
                nameMap.remove(b->getName());
            }
            else {
                system("cls");
                cout << "không tìm thấy block cần xóa" ;
                Sleep(2000);
            }
            menu3();
            //break;
        }
        case '2':{
            string name;
            cout << "nhập tên cần xóa: ";
            cin.ignore(10, '\n');
            getline(cin,name);
            block* b=nameMap.searchName(name);
            if(b!=nullptr){
                idMap.remove(b->getId());
                nameMap.remove(name);
            }
            else {
                system("cls");
                cout << "không tìm thấy block cần xóa" ;
                Sleep(2000);
            }
            menu3();
            break;
        }
        default:
            menu3();
        //menu3();
    }
}