
    void processPackets(){
        int used=0;
        while(count>0){
            if(used+queue[front].size>bandwidth)
                break;
            cout<<"Processed Packet "<<queue[front].id << endl;
            used +=queue[front].size;
            processed++;
            front=(front + 1) % capacity;
            count--;
        }

        if(count==0){
            front=0;
            rear=-1;
        }

        cout << "Bandwidth Used: "
             << used << "/" << bandwidth << " bytes\n";
    }
    void processAllRouters(){
        for (int i=0;i<3;i++){
            cout<<"\nProcessing Router "<<i+1<<endl;
            routers[i]->processPackets();
        }
    }