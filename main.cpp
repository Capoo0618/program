#include <bits/stdc++.h>
using namespace std;
using namespace rel_ops;

class person{
public:
        string name;
        long int id;
};

class player:public person{
private:
        int score=0;
public:
        int order;
        player(string name,long int id,int order){
            this->name = name;
            this->id = id;
            this->order = order;
        }
        int getscore(){
            return score;
        }
        void countscore(int x){
            score+=x;
        }
        bool operator<(const player& pplayer){
            return score < pplayer.score;
        }
        bool operator==(const player& pplayer){
            return score == pplayer.score;
        }
};



template<class T>
class Equal{
public:
    bool check(T data1, T data2){
        if(data1 == data2){
            return true;
        }
        else{
            return false;
        }
    }
};

void print(vector<player> &playerlist){
    int i;
    for(i=1;i<=playerlist.size();i++){
        cout<<"編號"<<playerlist[i-1].order<<" "<<"id:"<<playerlist[i-1].id<<" "<<"玩家名稱"<<playerlist[i-1].name<<endl;
    }
}

void gamestart(vector<player> &playerlist){
    srand(time(NULL));
    int i,j,count=1;
    vector<int> pair;
    for(i=0;i<playerlist.size();i++){
        int x = rand();
        for(j=0;j<pair.size();j++){
            if(pair[j]==(x%playerlist.size())){
                count=0;
                i--;
            }
        }
        if(count==1){
            pair.push_back(x%playerlist.size());
        }
        count=1;
    }
    int table=1;
    for(i=0;i<playerlist.size();i=i+2){
        cout<<"第"<<table<<"桌"<<playerlist[pair[i]].name<<"vs"<<playerlist[pair[i+1]].name<<endl;
        table++;
    }
}


void printresult(vector<player> &playerlist){
    int i;
    for(i=0;i<playerlist.size();i++){
        cout<<"排名"<<i+1<<":"<<" "<<"編號"<<playerlist[i].order<<"名稱:"<<playerlist[i].name<<" "<<" 分數:"<<playerlist[i].getscore()<<endl;
    }
}

void sortplayer(vector<player> &playerlist){
    int i,j;
    for(i=0;i<playerlist.size()-1;i++){
        for(j=i+1;j<playerlist.size();j++){
            if(playerlist[i]<playerlist[j]){
                player tmp=player("tmp",1,1);
                tmp=playerlist[i];
                playerlist[i]=playerlist[j];
                playerlist[j]=tmp;
            }
        }
    }
}



void gamefinish(vector<player> &playerlist){
    int wwin[100]={0},draw[100]={0};
    int i=0,j=0;
    cout<<"win:";
    while(cin>>wwin[i] && getchar()!='\n'){
        i++;
    }
    for(i=0;wwin[i]!=0;i++){
        for(int ii=0;ii<playerlist.size();ii++){
            if(wwin[i]==playerlist[ii].order)
            playerlist[ii].countscore(3);
        }
    }
    cout<<"draw:";
    while(cin>>draw[j] && getchar()!='\n'){
        j++;
    }
    for(j=0;draw[j]!=0;j++){
       for(int jj=0;jj<playerlist.size();jj++){
            if(wwin[j]==playerlist[jj].order)
            playerlist[jj].countscore(1);
        }
    }
    sortplayer(playerlist);
}

void no(){
    cout<<"參加人數不符合";
}

void yes(){
    cout<<"參加人數符合，請繼續執行"<<endl;
}

int main()
{
    string name;
    vector<player> playerlist;
    int id,numofplayer,order=1,gametimes;
    int i,checktool=0;
    void (*pfunc)();
    Equal<int> e1;
    cout<<"請輸入參賽人數:";
    cin>>numofplayer;  
    if(numofplayer%2==1){
        pfunc=no;
        pfunc();
        return 0;
    }
    else{
        pfunc=yes;
        pfunc();
    }
    cout<<"請輸入遊戲次數:";
    cin>>gametimes;
    for(i=0;i<numofplayer;i++){
        cout<<"請輸入id:";
        cin>>id;
        cout<<"請輸入名稱:";
        cin>>name;
        player tmp=player(name,id,order);
        playerlist.push_back(tmp);
        order++;
        if(i>=1){
            for(int j=0;j<playerlist.size()-1;j++){
                for(int k=j+1;k<playerlist.size();k++){
                    if(e1.check(playerlist[j].id, playerlist[k].id)){
                        cout<<"id有重複輸入，請重新輸入"<<endl;
                        playerlist.pop_back();
                        i--;
                        order--;
                        checktool++;
                        break;
                    }
                }
                if(checktool!=0){
                    checktool=0;
                    break;
                }
            }
        }
    }
    print(playerlist);
    for(i=0;i<gametimes;i++){
        gamestart(playerlist);
        gamefinish(playerlist);
        printresult(playerlist);
    }
    return 0;
}