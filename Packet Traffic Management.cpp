int selectTrafficMode(){
    int choice;
    cout<<"\n1. Low Traffic";
    cout<<"\n2. High Traffic";
    cout<<"\n3. Random Traffic";
    cout<<"\nEnter choice: ";
    cin>>choice;
    return choice;
}

int generateTraffic(int mode, int arrivals){
    if(mode==1){
        return 1;
    }
    if(mode==2){
        return arrivals;
    }
    return rand() % (arrivals + 1);
}